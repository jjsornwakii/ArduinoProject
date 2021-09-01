int button1 = 2, button2 = 3 , button3 = 4 ;
int led1 = 8 , c1 = 0 ;
int led2 = 9 , c2 = 0 ;
int led3 = 10 , c3 = 0 ;

int countT1 = 0;
 
int buttonState ;
int lastbuttonState = LOW ;

long lastTime = 0;
long DBdelay = 50 ; //ms


/////////////////////////////////////////// แดงดับใน 3 วิ
long lastT1 = 0;
void turn_off_left() {

  int readP1 = digitalRead(button1) ;


  if (readP1 == 1) {
    lastT1 = millis();
  }

  if (millis() - lastT1 > 3000 ) {
    // Serial.println("pass222222222");
    digitalWrite(led1, 0);
    c1 = 0;
  }
}


/////////////////////////////////////////// เขียวดับใน 3 วิ
long lastT3 = 0;
void turn_off_right() {

  int readP3 = digitalRead(button3) ;


  if (readP3 == 0) {
    lastT3 = millis();
  }

  if (millis() - lastT3 > (long)3000 ) {
   
    digitalWrite(led3, 0);
    c3 = 0;
    lastT3 = 0;
  }
}
/////////////////////////////////////////////////////
int sw2 = 0;
long lastT2 = 0;
long countT2 = 0;
void bibi() {

  int readP2 = digitalRead(button2);

  if (readP2 == 0) {
    lastT2 = millis();
  }

  if (millis() - lastT2 < (long)250) {
    digitalWrite(led2, 1);
    Serial.println("1");
  }

  else if (millis() - lastT2 < (long)500) {
    digitalWrite(led2, 0);
    Serial.println("2");
  }

  else if (millis() - lastT2 < (long)750) {
    digitalWrite(led2, 1);
    Serial.println("3");
  }

  else if (millis() - lastT2 < (long)1000) {
    digitalWrite(led2, 0);
    Serial.println("4");
  }

  else if (millis() - lastT2 < (long)1250) {
    digitalWrite(led2, 1);
    Serial.println("5");
  }

  else if (millis() - lastT2 < (long)1500) {
    digitalWrite(led2, 0);
    Serial.println("6");
  }

  else if (millis() - lastT2 < (long)1750) {
    digitalWrite(led2, 1);
    Serial.println("7");
  }

  else {
    digitalWrite(led2, 0);
    Serial.println("CCCCCCCCCCCCCCCCCCCCCCC");
    sw2 = 0;
  }
}

//////////////////////////////////////////////////////////



void setup() {

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int readPin = -1 ;
///////////////// เช็คว่ากดปุ่มไหน
  if (digitalRead(button1) == 1)
    readPin = digitalRead(button1);

  if (digitalRead(button2) == 0)
    readPin = 1 ;

  if (digitalRead(button3) == 0)
    readPin = 1 ;

/////////////////////////

  if (readPin != lastbuttonState) {
    lastTime = millis();
  }

  if ((millis() - lastTime) > DBdelay) {

    if (readPin != buttonState) {
      buttonState = readPin;

      ///////////////////////////////////////////// 1 กดติต กดดับ
      if (digitalRead(button1) == 1) {
        if (buttonState == 1) {
          if (c1 == 0) {
            digitalWrite(led1, 1);
            c1 = 1;
          }
          else {
            digitalWrite(led1, 0);
            c1 = 0;
          }
        }
      }

      ////////////////////////////////////////////// 2
      if (c1 == 0 && c3 == 0) {
        if (digitalRead(button2) == 0) {

          sw2 = 1;


        }
      }
      ////////////////////////////////////////////// 3 กดติด กดดับ
      if (c1 == 0) {
        if (digitalRead(button3) == 0) {

          if (buttonState == 1) {
            if (c3 == 0) {
              digitalWrite(led3, 1);
              c3 = 1;
            }
            else {
              digitalWrite(led3, 0);
              c3 = 0;
            }
          }
        }
      }
      //////////////////////////////////////////////







  }
}
  ////// 2 กระพริบ
  if (sw2 == 1) {
    bibi();
  }
  ////// 3 วิ ดับ เอง
  turn_off_left();
  turn_off_right();


  lastbuttonState = readPin ;
}
