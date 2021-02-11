#include <HID-Project.h>
#include <HID-Settings.h>

#include <Adafruit_NeoPixel.h>


#define R1 2
#define G1 3
#define B1 4
#define R2 5
#define G2 6
#define B2 7
#define R3 8
#define G3 9
#define B3 10
#define R4 11
#define G4 12
#define B4 13
#define LED A5
Adafruit_NeoPixel RGBLED = Adafruit_NeoPixel(4, A5, NEO_RGB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(R1, INPUT_PULLUP);
  pinMode(R2, INPUT_PULLUP);
  pinMode(R3, INPUT_PULLUP);
  pinMode(R4, INPUT_PULLUP);
  pinMode(G1, INPUT_PULLUP);
  pinMode(G2, INPUT_PULLUP);
  pinMode(G3, INPUT_PULLUP);
  pinMode(G4, INPUT_PULLUP);
  pinMode(B1, INPUT_PULLUP);
  pinMode(B2, INPUT_PULLUP);
  pinMode(B3, INPUT_PULLUP);
  pinMode(B4, INPUT_PULLUP);

  RGBLED.begin() ;                   // RGBLEDのライブラリを初期化する
}

void loop() {
  // put your main code here, to run repeatedly
  int i = 0;
  int R[4] = {0, 0, 0, 0};
  int G[4] = {0, 0, 0, 0};
  int B[4] = {0, 0, 0, 0};
  int data[2] = {0, 0};
  char a = 0;
  int lane = 0;
  int LN[4] = {0, 0, 0, 0}; //オートプレイのときLN中かどうか
  int Lighttime[4] = {0, 0, 0, 0}; //オートプレイでLEDを光らせる時間

  while (1) {
    RGBLED.setBrightness(20) ;
    for (i = 0; i <= 3; i++) {
      if (Lighttime[i] == 0 && LN[i] == 0) {//もう光らせる必要が無いとき
        R[i] = 0;
        G[i] = 0;
        B[i] = 0;
      } else {
        if (Lighttime[i] >= 1)Lighttime[i] -= 1;
      }
    }

    a = Serial.read();//シリアル通信で来たデータを読み込む
    if (a != -1) {
      if (a == '0')lane = 3;
      if (a == '1')lane = 2;
      if (a == '2')lane = 1;
      if (a == '3')lane = 0;


      data[0] = Serial.read();
      data[1] = Serial.read();

      if (data[1] == '0') {
        Lighttime[lane] = 20;
      }
      if (data[1] == '1') {
        LN[lane] = 1;
      }
      if (data[1] == '2') {
        LN[lane] = 0;
      }

      if (data[0] == 'R') {
        R[lane] = 255;
      }
      if (data[0] == 'G') {
        G[lane] = 255;
      }
      if (data[0] == 'B') {
        B[lane] = 255;
      }
      if (data[0] == 'Y') {
        R[lane] = 255;
        G[lane] = 255;
      }
      if (data[0] == 'C') {
        G[lane] = 255;
        B[lane] = 255;
      }
      if (data[0] == 'M') {
        R[lane] = 255;
        B[lane] = 255;
      }
      if (data[0] == 'W') {
        R[lane] = 255;
        G[lane] = 255;
        B[lane] = 255;
      }
      if (data[0] == 'F') {
        R[lane] = random(100, 255) ;
        G[lane] = random(100, 255) ;
        B[lane] = random(100, 255) ;
      }

    }

    if (digitalRead(R1) == 0) {
      //Serial.println(1);
      R[3] = 255;
      NKROKeyboard.add('v');
    } else {
      NKROKeyboard.remove('v');
    }
    if (digitalRead(R2) == 0) {
      //Serial.println(2);
      R[2] = 255;
      NKROKeyboard.add('b');
    } else {
      NKROKeyboard.remove('b');
    }
    if (digitalRead(R3) == 0) {
      //Serial.println(3);
      R[1] = 255;
      NKROKeyboard.add('n');
    } else {
      NKROKeyboard.remove('n');
    }
    if (digitalRead(R4) == 0) {
      //Serial.println(4);
      R[0] = 255;
      NKROKeyboard.add('m');
    } else {
      NKROKeyboard.remove('m');
    }
    if (digitalRead(G1) == 0) {
      //Serial.println(5);
      G[3] = 255;
      NKROKeyboard.add('f');
    } else {
      NKROKeyboard.remove('f');
    }
    if (digitalRead(G2) == 0) {
      //Serial.println(6);
      G[2] = 255;
      NKROKeyboard.add('g');
    } else {
      NKROKeyboard.remove('g');
    }
    if (digitalRead(G3) == 0) {
      //Serial.println(7);
      G[1] = 255;
      NKROKeyboard.add('h');
    } else {
      NKROKeyboard.remove('h');
    }
    if (digitalRead(G4) == 0) {
      //Serial.println(8);
      G[0] = 255;
      NKROKeyboard.add('j');
    } else {
      NKROKeyboard.remove('j');
    }
    if (digitalRead(B1) == 0) {
      //Serial.println(9);
      B[3] = 255;
      NKROKeyboard.add('r');
    } else {
      NKROKeyboard.remove('r');
    }
    if (digitalRead(B2) == 0) {
      //Serial.println(10);
      B[2] = 255;
      NKROKeyboard.add('t');
    } else {
      NKROKeyboard.remove('t');
    }
    if (digitalRead(B3) == 0) {
      //Serial.println(11);
      B[1] = 255;
      NKROKeyboard.add('y');
    } else {
      NKROKeyboard.remove('y');
    }
    if (digitalRead(B4) == 0) {
      //Serial.println(12);
      B[0] = 255;
      NKROKeyboard.add('u');
    } else {
      NKROKeyboard.remove('u');
    }

    NKROKeyboard.send();

    RGBLED.setPixelColor(0, R[0], G[0], B[0]) ;
    RGBLED.setPixelColor(1, R[1], G[1], B[1]) ;
    RGBLED.setPixelColor(2, R[2], G[2], B[2]) ;
    RGBLED.setPixelColor(3, R[3], G[3], B[3]) ;

    RGBLED.show() ;
    delay(8);
  }
}
