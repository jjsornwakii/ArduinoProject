int b1=2, b2=3, b3=4;   //ปุ่ม
int led1=8 , c1=0 ;         //led แดง
int led2=9 , c2=2, sw2=0 ;  //led เหลือง
int led3=10, c3=0 ;         //led เขียว

int lastButtonState = 0 , ButtonState  , ReadButton = 0;
long lastTime = 0 ;
long DELAY = 50 ; //ms
long t1,t2,t3;


void turn_off_red(){                /// ปิดไฟสีแดง
    if(digitalRead(b1) == 1){
      t1 = millis();  
    }
    if(millis() - t1 > 3000){
      digitalWrite(led1, 0);
      c1=0;
    }
}

void turn_off_green(){              /// ปิดไฟสีเขียว
    if(digitalRead(b3) == 0){
      t3 = millis();  
    }
    if(millis() - t3 > 3000){
      digitalWrite(led3, 0);
      c3=0;
    }
}

void blink_yellow(){                /// กระพริบสีเหลือง c2 วินาที
    if(digitalRead(b2) == 0){
      t2 = millis();  
    }
    if(millis() - t2 < 250)
      digitalWrite(led2, 1);
    
    else if(millis() - t2 < 500)
      digitalWrite(led2, 0);

    else if(millis() - t2 < 750)
      digitalWrite(led2, 1);

    else if(millis() - t2 < 1000){
      digitalWrite(led2, 0);
    }
    else{
      c2--;
      t2 = millis();
    }
}

void setup()
{
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
    
    
  if(digitalRead(b1) == 1 || digitalRead(b2) == 0 || digitalRead(b3) == 0 ){  /// เช็คว่ากดปุ่ม
    ReadButton = 1;
  }
  else
    ReadButton = 0;
  

  if(ReadButton != lastButtonState){
    lastTime = millis();
  }

  if((millis() - lastTime) > DELAY ){    /// ดีเลย์ตอนกดปุ่ม .05 วิ
    
    if(ReadButton != ButtonState){
       ButtonState = ReadButton;

          if(digitalRead(b1) == 1 && ButtonState == 1 ){ 
                  if(c1==0){
                      digitalWrite(led1, 1);  
                      c1=1;
                  }                                                 /// กดติด,ดับ สีแดง
                  else{
                      digitalWrite(led1, 0);
                       c1=0;
                  }
           }
        
           if(digitalRead(b3) == 0 && ButtonState == 1 && c1!=1 ){ 
                  if(c3==0){
                      digitalWrite(led3, 1);  
                      c3=1;
                  }                                                 /// กดติด,ดับ สีเขียว
                  else{
                      digitalWrite(led3, 0);
                       c3=0;
                  }
           }

           if(digitalRead(b2) == 0 && ButtonState == 1 && ( c1!=1 || c3!=1 ) ){ 
              sw2 = 1;                                             
           }                                                        /// เปิดการทำงานของสีเหลือง
           
    }
  }
  
  
  if(sw2==1){
    if(c2>0){
      blink_yellow();   ///กระพริบ
    }
    if(c2==0){
      sw2=0;      /// ปิดการทำงานของสีเหลือง
      c2=2;
    }
  }
  
  turn_off_red();     ///ปิดแดง หลังผ่านไป 3 วิ
  turn_off_green();   ///ปิดเขียว หลังผ่านไป 3 วิ
  
  lastButtonState = ReadButton ;
  
}
