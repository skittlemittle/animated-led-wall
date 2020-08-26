// led "wall" thing
// MIT
// author: skittlemittle

int gndPins[] = {5, 6, 7};
int pwrPins[] = {8, 9, 10};

const int len_sequence = 2;
int* sequence[50];
int frameRate = 10;
bool sequenceExists = false;

void setup()
{
    Serial.begin(9600);
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
        for (int i = 0; i < sizeof gndPins / sizeof gndPins[0]; i++) {
            for (int j = 0; j < sizeof gndPins / sizeof gndPins[0]; j++) {
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
 * Read the animation
 */
void serialEvent()
{
    int frameCount = 0;
    int valCount = 0;
    bool headerRead = false;
    // me and the boys parsing
    while (Serial.available()) {
        char check = (char)Serial.peek();
        size_t didRead = 0;
        char value[3] = "";

        if (headerRead) {
            if (check == '+') {        // new frame
                frameCount++;
                Serial.read();
            } else if (check == ',') { // new val
                valCount++;
                Serial.read();
            } else {
                didRead = Serial.readBytes(value, 3);
            }
            // finally write it
            if (didRead > 0) {
                sequence[frameCount][valCount] = atoi(value);
                Serial.println(atoi(value));
            }
        } else {
            /*
             * Read header and prep sequence array
             * numFrames, frameRate, and each frameSize are all 2 bytes
             */
            char nfArr[4];
            Serial.readBytes(nfArr, 4);
            String head = String(nfArr);
            int numFrames = head.substring(0,2).toInt();
            frameRate = head.substring(2).toInt();
            Serial.print("Header");
            Serial.print(numFrames);
            Serial.print(' ');
            Serial.println(frameRate);

            for (size_t i = 0; i < numFrames; i++) {
                char frameSizeArr[2] = "";
                Serial.readBytes(frameSizeArr, 2);
                const int frameSize = atoi(frameSizeArr);
                sequence[i] = new int[frameSize];
            }
            headerRead = true;
        }
    }

    for (int i = 0; i < len_sequence; i++) {
        for (int j = 0; j < 10; j += 5) {
            Serial.print(sequence[i][j]);
            Serial.print(' ');
            Serial.print(sequence[i][j+1]);
            Serial.print(' ');
            Serial.print(sequence[i][j+2]);
            Serial.print(' ');
            Serial.print(sequence[i][j+3]);
            Serial.print(' ');
            Serial.println(sequence[i][j+4]);
        }
    }
    sequenceExists = true;
}
