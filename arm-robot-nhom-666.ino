#include <Servo.h> 
const int SERVOS = 4;
int PIN[SERVOS], value[SERVOS], idle[SERVOS], currentAngle[SERVOS], MIN[SERVOS], MAX[SERVOS], INITANGLE[SERVOS];
Servo myservo[SERVOS]; // khai báo mảng servo gồm 4 servo mà ta sẽ sử dụng

void setup() {
  Serial.begin(57600);
  pinMode(3, OUTPUT);  
  digitalWrite(3, HIGH);
                         //CHÚ KHI KHI LẮP PHẢI ĐỂ Ý GÓC BAN ĐẦU (TƯƠNG ĐỐI, SERVO BAN ĐẦU MẶC ĐỊNH 90 ĐỘ)
                         //KHI LẮP XONG CHÚNG TA CHỈNH GÓC MIN, GÓC MAX (ĐỂ ĐIỀU CHỈNH KHOẢNG LÀM VIỆC SERVO)
                         //GÓC BAN ĐẦU LÀ GÓC KHI CẮM NGUỒN SERVO NÓ CHẠY VỀ, CHÚ Ý TÙY CHỈNH ĐỂ KHÔNG HỎNG CÁNH TAY
  PIN[0] = 6;                   // Chân nối Servo mỏ kẹp, đây chân số 6
  MIN[0] = 50;                  //góc min
  MAX[0] = 100;                 //góc Max
  INITANGLE[0] = 80;//90;       //ĐÂY LÀ GÓC BAN ĐẦU Servo 4 (mỏ kẹp)
  
  PIN[1] = 12;                   //Chân nối Servo lên xuống
  MIN[1] = 0;                  //góc min
  MAX[1] = 150;                //góc Max
  INITANGLE[1] = 90;           //ĐÂY LÀ GÓC BAN ĐẦU servo 3
  
  PIN[2] = 4;                 //Chân nối Servo vào ra
  MIN[2] = 30;                 //góc min
  MAX[2] = 179;                //góc Max
  INITANGLE[2] = 90;           // ĐÂY LÀ GÓC BAN ĐẦU servo 2
  
  PIN[3] = 8;                 //Chân nối Servo quay
  MIN[3] = 0;                  //góc min
  MAX[3] = 179;                //góc Max
  INITANGLE[3] = 90;//25;      // ĐÂY LÀ GÓC BAN ĐẦU servo 1 (Servo quay đế)

  // gán servo cho mỗi đối tượng trong mảng, góc ban đầu gán với INITANGLE
  for (int i = 0; i < SERVOS; i++){
    myservo[i].attach(PIN[i]); // gán servo
    myservo[i].write(INITANGLE[i]); // góc ban đầu
    
    currentAngle[i]=INITANGLE[i];
  }
  
}

void loop() {
      
      for (int i = 0; i < SERVOS; i++){
        value[i] = analogRead(i); // đọc tín hiệu điện trở truyền từ joystick vào
        Serial.print(value[i]);
        Serial.print(" ; ");
        
        
        currentAngle[i] = myservo[i].read(); // giá trị hiện tại của servo

        // có một mức biến trở cân bằng ở giữa, theo code của mình, nếu biến trở tăng thì góc tăng, biến trở giảm thì góc giảm
        // tại đây giá trị biến trở của joystick dao động trong khoảng từ 500 - 550
        if (value[i] > 550) 
        {
            if (currentAngle[i] < MAX[i]) 
              currentAngle[i]+=1;
            myservo[i].write(currentAngle[i]);  
        } 
        else if (value[i] < 500) 
        {
            if (currentAngle[i] > MIN[i]) 
              currentAngle[i]-=1;
            myservo[i].write(currentAngle[i]);   
        }  
       
      }  
    
      delay(10);
      
      Serial.print(currentAngle[0]);
      Serial.print(" ; ");
      Serial.print(currentAngle[1]);
      Serial.print(" ; ");
      Serial.print(currentAngle[2]);
      Serial.print(" ; ");
      Serial.println(currentAngle[3]);
  
}
