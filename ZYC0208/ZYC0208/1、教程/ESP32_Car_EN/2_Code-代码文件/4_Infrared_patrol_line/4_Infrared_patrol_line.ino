#define LEFT_LINE_TRACJING      34
#define CENTER_LINE_TRACJING    35
#define right_LINE_TRACJING     14
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

int Left_Tra_Value;
int Center_Tra_Value;
int Right_Tra_Value;

int Black_Line = 200;

int motorSpeed = 1;

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

void rotateRight(int motorSpeed) { 
  //右转
  digitalWrite(RightFrontFWD, motorSpeed); // 右前轮，后进方向，利用PWM进行速度调控
  digitalWrite(RightFrontBWD, LOW);
  digitalWrite(RightBackBWD, motorSpeed); // 右后轮，后退方向，利用PWM进行速度调控
  digitalWrite(RightBackFWD, LOW); // 若RightBackFWD不支持PWM，则设为低电平
  
  digitalWrite(LeftFrontFWD, motorSpeed); // 左前轮，前退方向，利用PWM进行速度调控
  digitalWrite(LeftFrontBWD, LOW); // 若LeftFrontFWD不支持PWM，则设为低电平
  digitalWrite(LeftBackFWD, motorSpeed); // 左后轮，前进方向，利用PWM进行速度调控
  digitalWrite(LeftBackBWD, LOW); // 若LeftBackBWD不支持PWM，则设为低电平
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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LEFT_LINE_TRACJING, INPUT);
  pinMode(CENTER_LINE_TRACJING, INPUT);
  pinMode(right_LINE_TRACJING, INPUT);

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
  Left_Tra_Value = analogRead(LEFT_LINE_TRACJING);
  Center_Tra_Value = analogRead(CENTER_LINE_TRACJING);
  Right_Tra_Value = analogRead(right_LINE_TRACJING);
  Serial.print("Left: ");
  Serial.print(Left_Tra_Value);
  Serial.print("\tCenter: ");
  Serial.print(Center_Tra_Value);
  Serial.print("\tRight: ");
  Serial.println(Right_Tra_Value);
  if (Left_Tra_Value < Black_Line && Center_Tra_Value >= Black_Line && Right_Tra_Value < Black_Line)
    {
       moveForward(motorSpeed);
    }

    if (Left_Tra_Value >= Black_Line && Left_Tra_Value > Right_Tra_Value)
    {
      rotateLeft(motorSpeed);//左移
    }

    if (Right_Tra_Value >= Black_Line && Right_Tra_Value > Left_Tra_Value)
    {
      rotateRight(motorSpeed);//右移
    }

    if (Left_Tra_Value >= Black_Line && Center_Tra_Value >= Black_Line && Right_Tra_Value >= Black_Line)
    {
      stopMoving();
    }

    if (Left_Tra_Value < Black_Line && Center_Tra_Value < Black_Line && Right_Tra_Value < Black_Line)
      {
        stopMoving();
      }

    delay(100);
}
