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
void setup() {
  // put your setup code here, to run once:
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
 digitalWrite(RightFrontBWD, motorSpeed); // 右前，前转，使用PWM控制速度
  digitalWrite(RightFrontFWD, 0);       // 如果RightFrontFWD不是PWM引脚，则设为低电平
  digitalWrite(RightBackBWD, 0);  // 右后，前转，使用PWM控制速度
  digitalWrite(RightBackFWD, motorSpeed);  // 如果RightBackBWD不是PWM引脚，则设为低电平
  
  digitalWrite(LeftFrontFWD, motorSpeed);  // 左前，前转，使用PWM控制速度
  digitalWrite(LeftFrontBWD, 0);        // 如果LeftFrontBWD不是PWM引脚，则设为低电平
  digitalWrite(LeftBackBWD, 0);   // 左后，前转，使用PWM控制速度
  digitalWrite(LeftBackFWD, motorSpeed);    // 如果LeftBackBWD不是PWM引脚，则设为低电平       
  delay(3000);

  digitalWrite(RightFrontFWD, motorSpeed); // 右前轮，后退方向，利用PWM进行速度调控
  digitalWrite(RightFrontBWD, 0); // 若RightFrontBWD不支持PWM，则设为低电平
  digitalWrite(RightBackFWD, 0); // 右后轮，后退方向，利用PWM进行速度调控
  digitalWrite(RightBackBWD, motorSpeed); // 若RightBackFWD不支持PWM，则设为低电平
  
  digitalWrite(LeftFrontBWD, motorSpeed); // 左前轮，后退方向，利用PWM进行速度调控
  digitalWrite(LeftFrontFWD, 0); // 若LeftFrontFWD不支持PWM，则设为低电平
  digitalWrite(LeftBackFWD, 0); // 左后轮，后退方向，利用PWM进行速度调控
  digitalWrite(LeftBackBWD, motorSpeed); // 若LeftBackFWD不支持PWM，则设为低电平
  delay(3000);

  digitalWrite(RightFrontBWD, motorSpeed); // 右前轮，前退方向，利用PWM进行速度调控
  digitalWrite(RightFrontFWD, LOW); // 若RightFrontFWD不支持PWM，则设为低电平
  digitalWrite(RightBackFWD, motorSpeed); // 右后轮，前进方向，利用PWM进行速度调控
  digitalWrite(RightBackBWD, LOW); // 若RightBackBWD不支持PWM，则设为低电平
  
  digitalWrite(LeftFrontBWD, motorSpeed); // 左前轮，后进方向，利用PWM进行速度调控
  digitalWrite(LeftFrontFWD, LOW); // 若LeftFrontBWD不支持PWM，则设为低电平
  digitalWrite(LeftBackBWD, motorSpeed); // 左后轮，后退方向，利用PWM进行速度调控
  digitalWrite(LeftBackFWD, LOW); // 若LeftBackFWD不支持PWM，则设为低电平
  delay(3000);

  digitalWrite(RightFrontFWD, motorSpeed); // 右前轮，后进方向，利用PWM进行速度调控
  digitalWrite(RightFrontBWD, LOW);
  digitalWrite(RightBackBWD, motorSpeed); // 右后轮，后退方向，利用PWM进行速度调控
  digitalWrite(RightBackFWD, LOW); // 若RightBackFWD不支持PWM，则设为低电平
  
  digitalWrite(LeftFrontFWD, motorSpeed); // 左前轮，前退方向，利用PWM进行速度调控
  digitalWrite(LeftFrontBWD, LOW); // 若LeftFrontFWD不支持PWM，则设为低电平
  digitalWrite(LeftBackFWD, motorSpeed); // 左后轮，前进方向，利用PWM进行速度调控
  digitalWrite(LeftBackBWD, LOW); // 若LeftBackBWD不支持PWM，则设为低电平
  delay(3000);

  digitalWrite(RightFrontFWD, motorSpeed); // 右前轮，后进方向，利用PWM进行速度调控
  digitalWrite(RightFrontBWD, LOW);
  digitalWrite(RightBackFWD, motorSpeed); // 右后轮，后退方向，利用PWM进行速度调控
  digitalWrite(RightBackBWD, LOW);

  digitalWrite(LeftFrontFWD, motorSpeed); // 左前轮，前退方向，利用PWM进行速度调控
  digitalWrite(LeftFrontBWD, LOW);
  digitalWrite(LeftBackFWD, LOW);
  digitalWrite(LeftBackBWD, motorSpeed); // 左后轮，前进方向，利用PWM进行速度调控
  delay(3000);

  digitalWrite(RightFrontFWD, LOW);
  digitalWrite(RightFrontBWD, motorSpeed); // 右前轮，前退方向，利用PWM进行速度调控
  digitalWrite(RightBackFWD, LOW);
  digitalWrite(RightBackBWD, motorSpeed); // 右后轮，后进方向，利用PWM进行速度调控

  digitalWrite(LeftFrontFWD, LOW);
  digitalWrite(LeftFrontBWD, motorSpeed); // 左前轮，后退方向，利用PWM进行速度调控
  digitalWrite(LeftBackFWD, motorSpeed); // 左后轮，前退方向，利用PWM进行速度调控
  digitalWrite(LeftBackBWD, LOW);
  delay(3000);
}
