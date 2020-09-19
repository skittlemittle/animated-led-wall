// led "panel" thing
// animation frames are stored as a 2d array of hex color vals
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
CRGB leds[NUM_LEDS];

uint8_t lenSequence;
long *sequence[50];
uint8_t frameRate;
bool sequenceExists = false;
// serial stuff
char command[1024];
char commandBuffer[128];
int commandBufferSize;

void loop() {
    if (!sequenceExists)
        return;

    // draw the frames
    for (int frame = 0; frame < lenSequence; frame++) {
        for (int pixel = 0; pixel < NUM_LEDS; pixel++) {
          leds[pixel] = sequence[frame][pixel];
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
            sequence[i] = new long[NUM_LEDS]; // lmao magic nums
        }

        // parse body
        char *body = strtok(NULL, "+");
        int framecnt = 0;
        int fieldcnt = 0;
        String accumulator;
        for (size_t i = 0; i < strlen(body); i++) {
            // stuff go in accumulator
            if (body[i] != '-') {
                accumulator.concat(body[i]);
            } else {
                framecnt++;
                fieldcnt = 0;
            }
            // accumulator get flushed
            if (body[i + 1] == '#') {
                accumulator.replace(String('#'), String("0x")); // wink wink
                Serial.println(accumulator);
                sequence[framecnt][fieldcnt] = strtol(accumulator.c_str(), NULL, 16); // lmao
                accumulator.remove(0);

                fieldcnt++;
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
