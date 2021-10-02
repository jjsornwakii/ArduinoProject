#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 32);

int startButton = 2;  // ปุ่มเริ่ม
int speaker = 3;      // ลำโพง
int sw = 0;           // สถานะจอ
int State ;           // สถานะปุ่ม
int LastState = 0;
long LastTime = 0;
int readState ;
int rNumb;
long LastTimeBall = 0;

void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.display();

  pinMode(speaker, OUTPUT);
  srand(analogRead(A0));
  rNumb = random(0, 122);
  Serial.begin(9600);
}


float X;
int x = 59 ;
int xBall = rNumb, yBall = 0;
int newgame = 0;
int posX, posY;
int score = 0;


void loop() {

  readState = digitalRead(startButton);

  if (readState != LastState) { /// กดปุ่ม
    LastTime = millis();
  }

  if (millis() - LastTime > (long)20 ) {
    if (readState != State) {
      State = readState;

      if (State == HIGH) {

        if (newgame == 0) { //กดปุ่ม ครั้งแรก เพื่อเล่น
          newgame = 1;
          sw = 0;
        }
        else {
          newgame = 0;    //กดปุ่มอีกครั้ง เพื่อจบเกม
          xBall = rNumb;  // แล้วสุ่มจุดเกิดใหม่
          yBall = 0;
          score = 0;      // รีเซตคะแนน
        }
        
        sw = !sw ;
        display.clearDisplay();
        display.display();
        rNumb = random(0, 122);       // สุ่มจุดเกิดบอลใหม่
        xBall = rNumb;

        if (rNumb % 2 == 0) {         // สุ่มทิศทางบอล
          posX = 1;
        }
        else {
          posX = 0;
        }
      }
    }

  }
  // บอลไหลอัตโนมัติ ทุกๆ 5 ms
  if (millis() - LastTimeBall > 5) {
    // #################################### หน้าแรก menu sw==0
    if (sw == 0) {
      display.setCursor(15, 0);
      display.setTextSize(1);
      display.print("PONG GAME ver.itc");
      display.setCursor(1, 15);
      display.print("press button to start");
      display.display();
    }
    // #################################### เกมเริ่ม sw==1
    if (sw == 1) {
      display.clearDisplay();           // ล้างจอ
      display.display();

      int barX = analogRead(A2);        //อ่านค่า จาก R ปรับค่าได้ 0 - 1023

      if (barX <= 936) {
        X = barX * 0.119;               // ปรับสัดส่วน ค่าที่อ่านได้จาก R ให้เหมาะกับ ความกว้าง x ในจอ
      }                                 // 0 - 1023 ไปเป็น  X = ช่วง 0 - 121  (ใกล้เคียงกับขนาดความกว้างจอ)
      display.setCursor((int)X, 28);
      display.setTextSize(1);
      display.print("---");             // แสดงไม้กระดานที่ ตำแหน่ง (X,28)   บรรทัดล่างสุด28


      display.setCursor(xBall, yBall);

      if (xBall > 110) {  // ถ้าบอลชิดขวา
        posX = 1;         // ให้ posX==1 เป็นการ กำหนดว่าให้บอลไปทางซ้าย
      }
      if (xBall <= 1) {   // ถ้าบอลชิดขวา
        posX = 0;         // ให้ posX==0 เป็นการ กำหนดว่าให้บอลไปทางขวา
      }
      if (yBall < 1) {    // ถ้าบอลชิดบน
        posY = 1;         // ให้ posY==1 เป็นการ กำหนดว่าให้บอลเด้งลง
      }
      if (yBall > 24) {                   // ถ้าบอลชิดบน
        if (xBall >= X - 5 && xBall <= X + 16) { // แล้วอยู่ในช่วง ที่ไม้ --- อยู่พอดี
          posY = 0;                     // ให้ posY==0 เป็นการ กำหนดว่าให้บอลเด้งกลับขึ้นไป
          score++;          // นับคะแนน
          tone(speaker, 500);
          delay(50);
          noTone(speaker);

        }
        else {                          // ถ้าไม่ได้อนู่อยู่ในช่วง  ที่ไม้ --- อยู่
          for (int i = 0; i < 2; i++) {
            tone(speaker, 700);
            delay(50);                  // sound effect ดัง 2 รอบ
            tone(speaker, 400);
            delay(50);
          }

          noTone(speaker);
          rNumb = random(0, 122);       // สุ่มจุดเกิดบอลใหม่ (หำหรับเกมต่อไป)
          xBall = rNumb;
          sw = 2;                       // ให้ไปหน้า ที่ sw==3
          display.clearDisplay();
          display.display();
        }

      }

      // บอลไหล !!!!
      if (sw == 1) {
        if (posX == 1) {
          --xBall;      //ซ้าย
        }
        else {
          ++xBall;      //ขวา
        }

        if (posY == 1) { //ล่าง
          ++yBall;
        }
        else {
          --yBall;      //บน
        }
        display.setCursor(xBall, yBall);
        display.print("o");
        display.setCursor(115, 0);
        display.print(score);             // แสดงคะแนน Real Time

      }


    }
    // #################################### จบเกม sw==2
    if (sw == 2) {

      display.setCursor(10, 5);
      display.setTextSize(1);
      display.print("SCORE : ");
      display.print(score);           // แสดงคะแนน
      display.setCursor(1, 19);
      display.print("press button to menu");
    }
    display.display();
    LastTimeBall = millis();
  }
  LastState = readState;
}
