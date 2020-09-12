// led "wall" thing
// MIT
// author: skittlemittle

#include <FastLED.h>

#define LED_PIN 3
#define COLOR_ORDER GRB
#define CHIPSET WS2811
#define BRIGHTNESS 64
// wow global vars what a loser
const uint8_t kMatrixWidth = 8;
const uint8_t kMatrixHeight = 8;
const bool kMatrixSerpentineLayout = true;
#define NUM_LEDS (kMatrixHeight * kMatrixWidth)
CRGB leds_plus_safety_pixel[NUM_LEDS + 1];
CRGB *const leds(leds_plus_safety_pixel + 1);

uint8_t lenSequence;
int *sequence[50];
uint8_t frameSizes[50];
uint8_t frameRate;
bool sequenceExists = false;
// serial stuff
char command[1024];
char commandBuffer[128];
int commandBufferSize;

/*
 *Helper function that returns led index number given an xy
 *yoinked from the fastled examples:https://github.com/FastLED/
 */
uint16_t XY(uint8_t x, uint8_t y) {
    uint16_t i;

    if (kMatrixSerpentineLayout == false) {
        i = (y * kMatrixWidth) + x;
    }

    if (kMatrixSerpentineLayout == true) {
        if (y & 0x01) {
            // Odd rows run backwards
            uint8_t reverseX = (kMatrixWidth - 1) - x;
            i = (y * kMatrixWidth) + reverseX;
        } else {
            // Even rows run forwards
            i = (y * kMatrixWidth) + x;
        }
    }

    return i;
}

/*
 * wraps XY() and gives you array out of bounds protection
 * you have to provide an array 1 bigger than what you need
 * and you never use the [0]th position thats the overflow
 * also yoinked from the fastled examples
 */
uint16_t XYsafe(uint8_t x, uint8_t y) {
    if (x >= kMatrixWidth)
        return -1;
    if (y >= kMatrixHeight)
        return -1;
    return XY(x, y);
}

void loop() {
    if (!sequenceExists)
        return;

    byte curFrame[8][8][3] = {0};
    // generate the frame amirite
    for (int frame = 0; frame < lenSequence; frame++) {
        // TODO: magic numbers!
        for (int j = 0; j < frameSizes[frame]; j += 5) {
            // monkey brain
            int row = sequence[frame][j];
            int col = sequence[frame][j + 1];
            int red = sequence[frame][j + 2];
            int green = sequence[frame][j + 3];
            int blue = sequence[frame][j + 4];
            // monkey brain ctd
            curFrame[row][col][0] = red;
            curFrame[row][col][1] = green;
            curFrame[row][col][2] = blue;
        }
        // draw the frame
        for (byte y = 0; y < kMatrixHeight; y++) {
            for (byte x = 0; x < kMatrixWidth; x++) {
                leds[XYsafe(x, y)].r = curFrame[x][y][0];
                leds[XYsafe(x, y)].g = curFrame[x][y][1];
                leds[XYsafe(x, y)].b = curFrame[x][y][2];
            }
        }
        FastLED.setBrightness(BRIGHTNESS);
        FastLED.show();
        delay(1000 / frameRate);
    }
}

/*
 * read large data from the serial port
 * author: Andrei Ostanin
 * https://ostanin.org/2012/01/08/sending-large-strings-of-data-to-arduino/
 */

void readCommandBuffer(int bytesToRead) {
    int i = 0;
    char c = 0;
    while (i < 128 && (i < bytesToRead || bytesToRead <= 0)) {
        while (!Serial.available())
            ;
        c = Serial.read();
        if (c == '\r' || c == '\n') {
            break;
        }
        commandBuffer[i] = c;
        i++;
    }
    commandBufferSize = i;
}

void readCommand() {
    command[0] = '\0';
    readCommandBuffer(0);
    if (strncmp(commandBuffer, "RCV", 3) == 0) {
        commandBuffer[commandBufferSize] = '\0';
        int expectedSize = atoi(commandBuffer + 4);
        if (expectedSize <= 0 || expectedSize > 1024) {
            return;
        }
        Serial.println("RDY");
        int bytesRead = 0;
        while (bytesRead < expectedSize) {
            readCommandBuffer(expectedSize - bytesRead);
            memcpy(command + bytesRead, commandBuffer, commandBufferSize);
            bytesRead += commandBufferSize;
            Serial.print("ACK ");
            Serial.println(commandBufferSize);
        }
        command[bytesRead] = '\0';
    } else {
        memcpy(command, commandBuffer, commandBufferSize);
        command[commandBufferSize] = '\0';
    }
}

/*
 * Read the animation
 */
void serialEvent() {
    if (Serial.available()) {
        readCommand();

        // parse header
        char *header = strtok(command, "+");
        String headStr = String(header);
        int numFrames = headStr.substring(0, 2).toInt();
        if (numFrames <= 0)
            return; // deal with stupid empty commands wiping data

        lenSequence = numFrames;
        frameRate = headStr.substring(2, 4).toInt();
        headStr.remove(0, 4); // we dont need em anymore

        for (size_t i = 0; i < numFrames; i++) {
            const int frameSize = headStr.substring(0, 2).toInt();
            headStr.remove(0, 2); // monke brain
            sequence[i] = new int[frameSize];
            frameSizes[i] = frameSize;
        }
        // parse body
        char *body = strtok(NULL, "+");
        int framecnt = 0;
        int fieldcnt = 0;
        String accumulator;
        for (size_t i = 0; i < strlen(body); i++) {
            if (body[i] != ',' && body[i] != '-') {
                accumulator.concat(body[i]);
            } else {
                sequence[framecnt][fieldcnt] = accumulator.toInt();
                accumulator.remove(0);
                if (body[i] == ',') {
                    fieldcnt++;
                } else if (body[i] == '-') {
                    framecnt++;
                    fieldcnt = 0;
                }
            }
        }
        sequenceExists = true;
    }
}

void setup() {
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)
        .setCorrection(TypicalSMD5050);
    FastLED.setBrightness(BRIGHTNESS);
    Serial.begin(115200);
}
