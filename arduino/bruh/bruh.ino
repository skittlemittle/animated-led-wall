// led "wall" thing
// MIT
// author: skittlemittle

int gndPins[] = {5, 6, 7};
int pwrPins[] = {8, 9, 10};

uint8_t image[3][3][3] = {
    {{0, 0, 0}, {0, 254, 254}, {0, 0, 0}},
    {{0, 0, 0}, {255, 0, 254}, {0, 0, 0}},
    {{0, 0, 254}, {0, 0, 254}, {0, 0, 0}}};

const int len_sequence = 3;
int* sequence[len_sequence];

void setup()
{
    Serial.begin(9600);
    Serial.println(sizeof sequence);
    for (int i = 0; i < sizeof gndPins / sizeof gndPins[0]; i++) {
        pinMode(gndPins[i], OUTPUT);
        pinMode(pwrPins[i], OUTPUT);
        // have em all off
        digitalWrite(gndPins[i], HIGH);
    }
    
    // generate sequence of deltas
    for (int i = 0; i < len_sequence; i++) {
        sequence[i] = new int[10];  /// new int[frameSize];
        // delta frames
        for (int j = 0; j < 10; j+=5) {
            /*
            sequence[i][j]   = 3; // row
            sequence[i][j+1] = 2; // col
            sequence[i][j+2] = 255; // r
            sequence[i][j+3] = 0; // g
            sequence[i][j+4] = 0; // b
            Serial.print(i);
            Serial.print("__");
            Serial.print(j);
            Serial.println("AAAAAA");
            */
        }
    }

    for (size_t i = 0; i < len_sequence; i++) {
        for (size_t j = 0; j < 10; j++) {
            Serial.print(sequence[i][j]);  // very good
            Serial.println(" | ");
        }
        Serial.println("============");
    }
    // dummy deltas
    //1
    sequence[0][0] = 0;
    sequence[0][1] = 0;
    sequence[0][2] = 255;
    sequence[0][3] = 0;
    sequence[0][4] = 0;
    //2
    sequence[1][0] = 1;
    sequence[1][1] = 0;
    sequence[1][2] = 255;
    sequence[1][3] = 0;
    sequence[1][4] = 0;
    // off the prev one
    sequence[1][5] = 0;
    sequence[1][6] = 0;
    sequence[1][7] = 0;
    sequence[1][8] = 0;
    sequence[1][9] = 0;
    //3
    sequence[2][0] = 2;
    sequence[2][1] = 0;
    sequence[2][2] = 255;
    sequence[2][3] = 0;
    sequence[2][4] = 0;
    // off the prev one
    sequence[2][5] = 1;
    sequence[2][6] = 0;
    sequence[2][7] = 0;
    sequence[2][8] = 0;
    sequence[2][9] = 0;

}

// AAAAAAAA GHOSTING
void loop()
{
    int curFrame[3][3][3] = {0};
    // generate the frame amirite
    for (int frame = 0; frame < len_sequence; frame++) {
        for (int j = 0; j < sizeof sequence[0] / sizeof(sequence[0][0]); j+=5) {
            // monkey brain
            int row = sequence[frame][j];
            int col = sequence[frame][j+1];
            int red = sequence[frame][j+2];
            int green = sequence[frame][j+3];
            int blue = sequence[frame][j+4];
            // holy shit even more monkey brain
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
            delay(500);
            digitalWrite(gndPins[i], HIGH);
        }
    }
}
