// led "wall" thing
// MIT
// author: skittlemittle
#include <string.h>
// wow global vars what a loser
int gndPins[] = {5, 6, 7};
int pwrPins[] = {8, 9, 10};

int len_sequence;
int* sequence[50];
int frameRate = 10;
bool sequenceExists = false;
// serial stuff
char command[1024];
char commandBuffer[128];
int commandBufferSize;

void setup()
{
    Serial.begin(115200);
    for (int i = 0; i < sizeof gndPins / sizeof gndPins[0]; i++) {
        pinMode(gndPins[i], OUTPUT);
        pinMode(pwrPins[i], OUTPUT);
        // have em all off
        digitalWrite(gndPins[i], HIGH);
    }
/*
    // dummy deltas
    //1
    sequence[0][0] = 0;
    sequence[0][1] = 0;
    sequence[0][2] = 255;
    sequence[0][3] = 0;
    sequence[0][4] = 0;
    //
    sequence[0][5] = 1; //2
    sequence[0][6] = 0;
    sequence[0][7] = 0;
    sequence[0][8] = 0;
    sequence[0][9] = 0;
    //2
    sequence[1][0] = 0;
    sequence[1][1] = 0;
    sequence[1][2] = 0;
    sequence[1][3] = 0;
    sequence[1][4] = 0;
    // off the prev one
    sequence[1][5] = 1;
    sequence[1][6] = 0;
    sequence[1][7] = 255;
    sequence[1][8] = 0;
    sequence[1][9] = 0;
    //3
    sequence[2][0] = 1;
    sequence[2][1] = 0;
    sequence[2][2] = 0;
    sequence[2][3] = 0;
    sequence[2][4] = 0;
    // off the prev one
    sequence[2][5] = 2;
    sequence[2][6] = 0;
    sequence[2][7] = 255;
    sequence[2][8] = 0;
    sequence[2][9] = 0;
*/
}

void loop()
{
    if (!sequenceExists) return;

    int curFrame[3][3][3] = {0};
    // generate the frame amirite
    for (int frame = 0; frame < len_sequence; frame++) {
        // TODO: magic numbers!
        for (int j = 0; j < 10; j+=5) {
            // monkey brain
            int row = sequence[frame][j];
            int col = sequence[frame][j+1];
            int red = sequence[frame][j+2];
            int green = sequence[frame][j+3];
            int blue = sequence[frame][j+4];
            // monkey brain ctd
            curFrame[row][col][0] = red;
            curFrame[row][col][1] = green;
            curFrame[row][col][2] = blue;
        }
        // draw the frame
        // TODO: fastLED
        for (int i = 0; i < sizeof gndPins / sizeof gndPins[0]; i++) {
            for (int j = 0; j < sizeof pwrPins / sizeof pwrPins[0]; j++) {
                if (curFrame[i][j][0] > 0) {
                    digitalWrite(gndPins[i], LOW);
                    analogWrite(pwrPins[j], curFrame[i][j][0]);
                    delayMicroseconds(1);
                }
            }
        }
        delay(1000 / frameRate);
        for (size_t i = 0; i < sizeof gndPins / sizeof gndPins[0]; i++) {
            digitalWrite(gndPins[i], HIGH);
        }
    }
}

/*
 * read large data from the serial port
 * author: Andrei Ostanin
 * https://ostanin.org/2012/01/08/sending-large-strings-of-data-to-arduino/ 
 */

void readCommandBuffer(int bytesToRead)
{
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

void readCommand()
{
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
    }
    else {
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
        Serial.println(header);
        String headStr = String(header);
        int numFrames = headStr.substring(0, 2).toInt();
        len_sequence = numFrames;
        frameRate = headStr.substring(2, 4).toInt();
        Serial.println(numFrames);
        Serial.println(frameRate);
        headStr.remove(0, 4); // we dont need em anymore

        for (size_t i = 0; i < numFrames; i++) {
            const int frameSize = headStr.substring(0, 2).toInt();
            headStr.remove(0, 2); // monke brain
            sequence[i] = new int[frameSize];
        }
        // parse body
        char *body = strtok(NULL, "+");
        int framecnt = 0;
        int fieldcnt = 0;
        String accumulator;
        Serial.print("B ");
        Serial.println(body);
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
        Serial.println("SEQUENCE");
        for (int i = 0; i < numFrames; i++) {
            for (int j = 0; j < 10; j++) {
                Serial.println(sequence[i][j]);
            }
        }
        sequenceExists = true;
    }
}

