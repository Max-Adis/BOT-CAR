#include <ESP32Servo.h>

Servo myServo;  // 创建一个Servo对象
Servo myServo1;  // 创建一个Servo对象
Servo myServo2;  // 创建一个Servo对象

int  angle ;
int  angle1 ;
int  angle2 ;
void setup() {
  // put your setup code here, to run once:
  myServo.attach(2);  // 将舵机的信号线连接到ESP32的GPIO 
  myServo1.attach(21);  // 将舵机的信号线连接到ESP32的GPIO 
  myServo2.attach(22);  // 将舵机的信号线连接到ESP32的GPIO
}

void loop() {
  // put your main code here, to run repeatedly:
      for ( angle = 140; angle >= 10; angle -= 1)
    { 
        myServo.write(angle);    
        delay(15);
    } 
    for (angle = 10 ; angle<= 140; angle += 1)
    { 
        myServo.write(angle);            
        delay(15);                     
    }
    
    for (angle1 = 10; angle1 <= 170; angle1 += 1)
    { 
        myServo1.write(angle1);            
        delay(15);                     
    }

    for (angle1 = 170; angle1 >= 10; angle1 -= 1)
    { 
        myServo1.write(angle1);    
        delay(15);
    }
    
    for (angle2 = 60; angle2 >= 0; angle2 -= 1)
    { 
        myServo2.write(angle2);    
        delay(15);
    }
    for (angle2 = 0; angle2 <= 60; angle2 += 1)
    { 
        myServo2.write(angle2);            
        delay(15);                     
    }

}
