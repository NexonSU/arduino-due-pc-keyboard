#include "Keyboard.h"

byte cols[] = {34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53};
const int colCount = sizeof(cols)/sizeof(cols[0]);
byte rows[] = {22,23,24,25,26,27,28,29};
const int rowCount = sizeof(rows)/sizeof(rows[0]);
char keycaps[8][20] = {
    {0,0,KEY_F5,KEY_F6,0,KEY_F9,KEY_F8,KEY_TAB,0,0,KEY_RIGHT_ALT,101+136,0,0,31+136,0,0,KEY_F7,32+136,0},
    {0,0,0,KEY_F4,71+136,48+136,47+136,29+136,0,0,KEY_RIGHT_CTRL,13+136,0,0,55+136,0,70+136,KEY_END,51+136,0},
    {0,0,0,19+136,0,12+136,24+136,KEY_LEFT_ALT,0,0,0,17+136,0,0,KEY_RIGHT_SHIFT,0,0,28+136,0,0},
    {0,0,49+136,KEY_F3,72+136,38+136,37+136,27+136,0,0,KEY_LEFT_GUI,15+136,0,0,33+136,0,KEY_HOME,36+136,56+136,0},
    {0,0,KEY_PAGE_DOWN,0,0,0,52+136,25+136,0,0,0,34+136,0,0,35+136,0,11+136,0,0,0},
    {0,0,39+136,0,KEY_PAGE_UP,KEY_F10,KEY_F12,6+136,0,0,KEY_INSERT,14+136,0,0,18+136,0,KEY_DELETE,KEY_F11,0,0},
    {0,0,KEY_F1,KEY_F2,0,53+136,KEY_ESC,KEY_LEFT_SHIFT,46+136,0,0,54+136,0,45+136,30+136,0,0,KEY_RETURN,0,KEY_BACKSPACE},
    {KEY_RIGHT_ARROW,KEY_DOWN_ARROW,26+136,8+136,20+136,7+136,22+136,0,9+136,KEY_UP_ARROW,23+136,16+136,KEY_CAPS_LOCK,44+136,KEY_LEFT_ARROW,10+136,KEY_LEFT_CTRL,4+136,21+136,5+136}
};

void setup() {
    for (int x=0; x<rowCount; x++) pinMode(rows[x], INPUT);
    for (int x=0; x<colCount; x++) pinMode(cols[x], INPUT);
    Keyboard.begin();
    //SerialUSB.begin(115200);
}

void loop() {
    for (int colIndex=0; colIndex < colCount; colIndex++) {
        byte curCol = cols[colIndex];
        pinMode(curCol, OUTPUT);
        digitalWrite(curCol, LOW);
        for (int rowIndex=0; rowIndex < rowCount; rowIndex++) {
            byte curRow = rows[rowIndex];
            digitalWrite(curRow, HIGH);
            if(digitalRead(curRow) == 0){
              //SerialUSB.print(String(rowIndex));
              //SerialUSB.print(" - ");
              //SerialUSB.print(String(colIndex));
              //SerialUSB.print("\n");
              if(rowIndex == 4 && colIndex == 5){
                rstc_start_software_reset(RSTC);
              } else {
                Keyboard.press(keycaps[rowIndex][colIndex]);
              }
            } else {
              Keyboard.release(keycaps[rowIndex][colIndex]);
            }
            pinMode(curRow, INPUT);
        }
        pinMode(curCol, INPUT);
    }
    delay(50);
}
