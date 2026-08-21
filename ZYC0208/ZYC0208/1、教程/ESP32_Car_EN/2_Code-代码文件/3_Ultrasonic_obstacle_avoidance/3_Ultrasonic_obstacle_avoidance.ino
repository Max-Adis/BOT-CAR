//超声波传感器
#define Trigpin 13
#define Echopin 12

#define RightFrontFWD 23
#define RightFrontBWD 27
#define RightBackFWD  33
#define RightBackBWD  32

//左
#define LeftFrontFWD 18
#define LeftFrontBWD 19
#define LeftBackFWD  26
#define LeftBackBWD  25

int motorSpeed = 5;

void moveForward(int motorSpeed) {  
  //前进
  digitalWrite(RightFrontBWD, motorSpeed); // 右前，前转，使用PWM控制速度
  digitalWrite(RightFrontFWD, 0);       // 如果RightFrontFWD不是PWM引脚，则设为低电平
  digitalWrite(RightBackBWD, 0);  // 右后，前转，使用PWM控制速度
  digitalWrite(RightBackFWD, motorSpeed);  // 如果RightBackBWD不是PWM引脚，则设为低电平
  
  digitalWrite(LeftFrontFWD, motorSpeed);  // 左前，前转，使用PWM控制速度
  digitalWrite(LeftFrontBWD, 0);        // 如果LeftFrontBWD不是PWM引脚，则设为低电平
  digitalWrite(LeftBackBWD, 0);   // 左后，前转，使用PWM控制速度
  digitalWrite(LeftBackFWD, motorSpeed);    // 如果LeftBackBWD不是PWM引脚，则设为低电平
}

void stopMoving() {
  //停止
  digitalWrite(RightFrontFWD, 0);
  digitalWrite(RightFrontBWD, 0);
  digitalWrite(RightBackFWD, 0);
  digitalWrite(RightBackBWD, 0);
  digitalWrite(LeftFrontFWD, 0);
  digitalWrite(LeftFrontBWD, 0);
  digitalWrite(LeftBackFWD, 0);
  digitalWrite(LeftBackBWD, 0);
}


void moveBackward(int motorSpeed) {
  //后退
  digitalWrite(RightFrontFWD, motorSpeed); // 右前轮，后退方向，利用PWM进行速度调控
  digitalWrite(RightFrontBWD, 0); // 若RightFrontBWD不支持PWM，则设为低电平
  digitalWrite(RightBackFWD, 0); // 右后轮，后退方向，利用PWM进行速度调控
  digitalWrite(RightBackBWD, motorSpeed); // 若RightBackFWD不支持PWM，则设为低电平
  
  digitalWrite(LeftFrontBWD, motorSpeed); // 左前轮，后退方向，利用PWM进行速度调控
  digitalWrite(LeftFrontFWD, 0); // 若LeftFrontFWD不支持PWM，则设为低电平
  digitalWrite(LeftBackFWD, 0); // 左后轮，后退方向，利用PWM进行速度调控
  digitalWrite(LeftBackBWD, motorSpeed); // 若LeftBackFWD不支持PWM，则设为低电平
}

void rotateLeft(int motorSpeed) { 
  //左转
  digitalWrite(RightFrontBWD, motorSpeed); // 右前轮，前退方向，利用PWM进行速度调控
  digitalWrite(RightFrontFWD, LOW); // 若RightFrontFWD不支持PWM，则设为低电平
  digitalWrite(RightBackFWD, motorSpeed); // 右后轮，前进方向，利用PWM进行速度调控
  digitalWrite(RightBackBWD, LOW); // 若RightBackBWD不支持PWM，则设为低电平
  
  digitalWrite(LeftFrontBWD, motorSpeed); // 左前轮，后进方向，利用PWM进行速度调控
  digitalWrite(LeftFrontFWD, LOW); // 若LeftFrontBWD不支持PWM，则设为低电平
  digitalWrite(LeftBackBWD, motorSpeed); // 左后轮，后退方向，利用PWM进行速度调控
  digitalWrite(LeftBackFWD, LOW); // 若LeftBackFWD不支持PWM，则设为低电平
}

unsigned long measureDistance() {
    digitalWrite(Trigpin, HIGH);
    delayMicroseconds(20);
    digitalWrite(Trigpin, LOW);
    delayMicroseconds(10);
    unsigned long Time_Echo_us = pulseIn(Echopin, HIGH, 60000); // 设置超时时间为60000微秒
    if(Time_Echo_us > 1) {
        return (Time_Echo_us * 34 / 100) / 2;
    } else {
        return 0; // 如果读取失败，返回0
    }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(Trigpin,OUTPUT);
  pinMode(Echopin,INPUT);

  pinMode(RightFrontFWD, OUTPUT);
  pinMode(RightFrontBWD, OUTPUT);
  pinMode(RightBackFWD, OUTPUT);
  pinMode(RightBackBWD, OUTPUT);
  pinMode(LeftFrontFWD, OUTPUT);
  pinMode(LeftFrontBWD, OUTPUT);
  pinMode(LeftBackFWD, OUTPUT);
  pinMode(LeftBackBWD, OUTPUT);

}

void loop() {
  unsigned long Len_mm = measureDistance();
  Serial.print(Len_mm,DEC);
  Serial.println("mm");
  delay(100);
  if(Len_mm >= 150) moveForward(motorSpeed);
  if(Len_mm < 150)
    {
      stopMoving();
      Serial.print("Len_mm: ");
      Serial.println(Len_mm);

      moveBackward(motorSpeed);//后退
      delay(800);
      rotateLeft(motorSpeed);//左移
      delay(5000);
      stopMoving();
    }
}
