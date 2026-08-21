//超声波传感器
#define Trigpin 13
#define Echopin 12
//右
#define RightFrontFWD 23
#define RightFrontBWD 27
#define RightBackFWD  33
#define RightBackBWD  32

//左
#define LeftFrontFWD 18
#define LeftFrontBWD 19
#define LeftBackFWD  26
#define LeftBackBWD  25

int motorSpeed = 1;
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
  // put your main code here, to run repeatedly:
  unsigned long UT_distance = measureDistance();
  Serial.print(UT_distance,DEC);
  Serial.println("mm");
  delay(100);
   if(UT_distance < 150) moveBackward(motorSpeed);
   if(150 <= UT_distance && UT_distance  <= 250) stopMoving();
   if(UT_distance  >= 250) moveForward(motorSpeed);

}
