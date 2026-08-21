#include <ESP32Servo.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// 定义服务和特性 UUID
#define SERVICE_UUID        "12345678-1234-5678-1234-56789abcdef1"
#define CHARACTERISTIC_UUID "abcdef01-2345-6789-1234-56789abcdef0"

Servo myServo;  // 创建一个Servo对象
Servo myServo1;  // 创建一个Servo对象
Servo myServo2;  // 创建一个Servo对象
int model_var = 1;
int Left_Tra_Value;
int Center_Tra_Value;
int Right_Tra_Value;
int Black_Line = 2000;

int angle = 70; //机械臂向左向右
int angle1 = 0; //机械臂向上向下
int angle2 = 100;

bool AngleI = false;
bool AngleK = false;
bool AngleJ = false;
bool AngleL = false;
bool Angle5 = false;
bool Angle6 = false;


//舵机
#define MOTOR 2
#define MOTOR1 21
#define MOTOR2 22

// 循迹控制引脚
#define LEFT_LINE_TRACJING      34
#define CENTER_LINE_TRACJING    35
#define right_LINE_TRACJING     14

//超声波
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

unsigned long Time_Echo_us;
// unsigned long Len_mm;
unsigned long mid_distance;
// 全局变量
BLEServer *pServer = nullptr;
BLECharacteristic *pCharacteristic = nullptr;
bool deviceConnected = false; // 记录 BLE 连接状态

void moveForward() {  
  //前进
  digitalWrite(RightFrontBWD, 1); // 右前，前转，使用PWM控制速度
  digitalWrite(RightFrontFWD, 0);       // 如果RightFrontFWD不是PWM引脚，则设为低电平
  digitalWrite(RightBackBWD, 0);  // 右后，前转，使用PWM控制速度
  digitalWrite(RightBackFWD, 1);  // 如果RightBackBWD不是PWM引脚，则设为低电平
  
  digitalWrite(LeftFrontFWD, 1);  // 左前，前转，使用PWM控制速度
  digitalWrite(LeftFrontBWD, 0);        // 如果LeftFrontBWD不是PWM引脚，则设为低电平
  digitalWrite(LeftBackBWD, 0);   // 左后，前转，使用PWM控制速度
  digitalWrite(LeftBackFWD, 1);    // 如果LeftBackBWD不是PWM引脚，则设为低电平
}

void moveBackward() {
  //后退
  digitalWrite(RightFrontFWD, 1); // 右前轮，后退方向，利用PWM进行速度调控
  digitalWrite(RightFrontBWD, 0); // 若RightFrontBWD不支持PWM，则设为低电平
  digitalWrite(RightBackFWD, 0); // 右后轮，后退方向，利用PWM进行速度调控
  digitalWrite(RightBackBWD, 1); // 若RightBackFWD不支持PWM，则设为低电平
  
  digitalWrite(LeftFrontBWD, 1); // 左前轮，后退方向，利用PWM进行速度调控
  digitalWrite(LeftFrontFWD, 0); // 若LeftFrontFWD不支持PWM，则设为低电平
  digitalWrite(LeftBackFWD, 0); // 左后轮，后退方向，利用PWM进行速度调控
  digitalWrite(LeftBackBWD, 1); // 若LeftBackFWD不支持PWM，则设为低电平
}

void rotateLeft() { 
  //左转
  digitalWrite(RightFrontBWD, 1); // 右前轮，前退方向，利用PWM进行速度调控
  digitalWrite(RightFrontFWD, LOW); // 若RightFrontFWD不支持PWM，则设为低电平
  digitalWrite(RightBackFWD, 1); // 右后轮，前进方向，利用PWM进行速度调控
  digitalWrite(RightBackBWD, LOW); // 若RightBackBWD不支持PWM，则设为低电平
  
  digitalWrite(LeftFrontBWD, 1); // 左前轮，后进方向，利用PWM进行速度调控
  digitalWrite(LeftFrontFWD, LOW); // 若LeftFrontBWD不支持PWM，则设为低电平
  digitalWrite(LeftBackBWD, 1); // 左后轮，后退方向，利用PWM进行速度调控
  digitalWrite(LeftBackFWD, LOW); // 若LeftBackFWD不支持PWM，则设为低电平
}

void rotateRight() { 
  //右转
  digitalWrite(RightFrontFWD, 1); // 右前轮，后进方向，利用PWM进行速度调控
  digitalWrite(RightFrontBWD, LOW);
  digitalWrite(RightBackBWD, 1); // 右后轮，后退方向，利用PWM进行速度调控
  digitalWrite(RightBackFWD, LOW); // 若RightBackFWD不支持PWM，则设为低电平
  
  digitalWrite(LeftFrontFWD, 1); // 左前轮，前退方向，利用PWM进行速度调控
  digitalWrite(LeftFrontBWD, LOW); // 若LeftFrontFWD不支持PWM，则设为低电平
  digitalWrite(LeftBackFWD, 1); // 左后轮，前进方向，利用PWM进行速度调控
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


void strafeRight() 
{
  //右移
  digitalWrite(RightFrontFWD, 1); // 右前轮，后进方向，利用PWM进行速度调控
  digitalWrite(RightFrontBWD, LOW);
  digitalWrite(RightBackFWD, 1); // 右后轮，后退方向，利用PWM进行速度调控
  digitalWrite(RightBackBWD, LOW);

  digitalWrite(LeftFrontFWD, 1); // 左前轮，前退方向，利用PWM进行速度调控
  digitalWrite(LeftFrontBWD, LOW);
  digitalWrite(LeftBackFWD, LOW);
  digitalWrite(LeftBackBWD, 1); // 左后轮，前进方向，利用PWM进行速度调控
}

void strafeLeft() 
{ 
   //左移
  digitalWrite(RightFrontFWD, LOW);
  digitalWrite(RightFrontBWD, 1); // 右前轮，前退方向，利用PWM进行速度调控
  digitalWrite(RightBackFWD, LOW);
  digitalWrite(RightBackBWD, 1); // 右后轮，后进方向，利用PWM进行速度调控

  digitalWrite(LeftFrontFWD, LOW);
  digitalWrite(LeftFrontBWD, 1); // 左前轮，后退方向，利用PWM进行速度调控
  digitalWrite(LeftBackFWD, 1); // 左后轮，前退方向，利用PWM进行速度调控
  digitalWrite(LeftBackBWD, LOW);
}

void rightward() 
{
   //右上
  digitalWrite(RightFrontFWD, LOW);
  digitalWrite(RightFrontBWD, LOW); // 右前轮，前退方向，利用PWM进行速度调控
  digitalWrite(RightBackFWD, 1);
  digitalWrite(RightBackBWD, LOW); // 右后轮，后进方向，利用PWM进行速度调控

  digitalWrite(LeftFrontFWD, 1);
  digitalWrite(LeftFrontBWD, LOW); // 左前轮，后退方向，利用PWM进行速度调控
  digitalWrite(LeftBackFWD, LOW); // 左后轮，前退方向，利用PWM进行速度调控
  digitalWrite(LeftBackBWD, LOW);
}

void rightdown() 
{ 
   //右下
  digitalWrite(RightFrontFWD, 1);
  digitalWrite(RightFrontBWD, LOW); // 右前轮，前退方向，利用PWM进行速度调控
  digitalWrite(RightBackFWD, LOW);
  digitalWrite(RightBackBWD, LOW); // 右后轮，后进方向，利用PWM进行速度调控

  digitalWrite(LeftFrontFWD, LOW);
  digitalWrite(LeftFrontBWD, LOW); // 左前轮，后退方向，利用PWM进行速度调控
  digitalWrite(LeftBackFWD, LOW); // 左后轮，前退方向，利用PWM进行速度调控
  digitalWrite(LeftBackBWD, 1);
}

void leftward() { 
   //左上
  digitalWrite(RightFrontFWD, LOW);
  digitalWrite(RightFrontBWD, 1); // 右前轮，前退方向，利用PWM进行速度调控
  digitalWrite(RightBackFWD, LOW);
  digitalWrite(RightBackBWD, LOW); // 右后轮，后进方向，利用PWM进行速度调控

  digitalWrite(LeftFrontFWD, LOW);
  digitalWrite(LeftFrontBWD, LOW); // 左前轮，后退方向，利用PWM进行速度调控
  digitalWrite(LeftBackFWD, 1); // 左后轮，前退方向，利用PWM进行速度调控
  digitalWrite(LeftBackBWD, LOW);
}

void leftdown() { 
   //左下
  digitalWrite(RightFrontFWD, LOW);
  digitalWrite(RightFrontBWD, LOW); // 右前轮，前退方向，利用PWM进行速度调控
  digitalWrite(RightBackFWD, LOW);
  digitalWrite(RightBackBWD, 1); // 右后轮，后进方向，利用PWM进行速度调控

  digitalWrite(LeftFrontFWD, LOW);
  digitalWrite(LeftFrontBWD, 1); // 左前轮，后退方向，利用PWM进行速度调控
  digitalWrite(LeftBackFWD, LOW); // 左后轮，前退方向，利用PWM进行速度调控
  digitalWrite(LeftBackBWD, LOW);
}

// 获取超声波传感器距离
long getDistance() {
    digitalWrite(Trigpin, HIGH);
    delayMicroseconds(20);
    digitalWrite(Trigpin, LOW);
    delayMicroseconds(10);
    Time_Echo_us = pulseIn(Echopin, HIGH, 60000); // 设置超时时间为60000微秒
    if(Time_Echo_us > 1) {
        return (Time_Echo_us * 34 / 100) / 2;
    } else {
        return 0; // 如果读取失败，返回0
    }
}

void ObstacleAvoidance(){
    unsigned long Time_Echo_us = 0;
    unsigned long Len_mm = getDistance();
    Serial.print("Len_mm: ");
    Serial.println(Len_mm);
    delay(100);

    if(Len_mm >= 150)
    {
      moveForward();
    }

    if(Len_mm < 150)
    {

      stopMoving();
      delay(50);
      moveBackward();//后退
      delay(800);
      rotateLeft();//左移
      delay(1500);
    }
}

void Follow(){
  unsigned long UT_distance = getDistance();
  Serial.print(UT_distance,DEC);
  Serial.println("mm");
 delay(100);
  if(UT_distance < 150 && UT_distance>0)
  {
    moveBackward();
  }

  if(150 <= UT_distance && UT_distance  <= 200)
  {
    stopMoving();
  }

  if(UT_distance  >= 200)
  {
    moveForward();
  }
}

void Tracking(){
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
    moveForward();
  }

  if (Left_Tra_Value >= Black_Line && Left_Tra_Value > Right_Tra_Value)
  {
    rotateLeft();//左移
  }

  if (Right_Tra_Value >= Black_Line && Right_Tra_Value > Left_Tra_Value)
  {
    rotateRight();//右移
  }

  if (Left_Tra_Value >= Black_Line && Center_Tra_Value >= Black_Line && Right_Tra_Value >= Black_Line)
  {
    stopMoving();
  }

  if (Left_Tra_Value < Black_Line && Center_Tra_Value < Black_Line && Right_Tra_Value < Black_Line)
  {
    stopMoving();
  }
}

void arm_control(){

  while(AngleI)
  {
    angle1 += 10;
    if(angle1 > 180)
    {
    angle1 =180;
    }
    myServo1.write(angle1);
    delay(200); // 等待舵机到达指定位置
    Serial.print("Angle1: ");
    Serial.println(angle1); 
  }

  while(AngleK)
  {
    angle1 -= 10;
    if(angle1 < 0)
    {
      angle1 =0;
    }
    myServo1.write(angle1);
    delay(200); // 等待舵机到达指定位置
    Serial.print("Angle1: ");
    Serial.println(angle1);
  }

  while(AngleJ == true)
  {
    angle += 10;
    if(angle > 150)
    {
      angle = 150;
    }
    myServo.write(angle);
    delay(200); // 等待舵机到达指定位置
    Serial.print("Angle: ");
    Serial.println(angle);
  }
      
  while(AngleL == true)
  {
    angle -= 10;
    if(angle < 0)
    {
      angle = 0;
    }
    myServo.write(angle);
    delay(200); // 等待舵机到达指定位置
    Serial.print("Angle: ");
    Serial.println(angle);
  }

  while(Angle5 == true)
  {
    angle2 += 10;
    if(angle2 > 80)
    {
      angle2 = 80;
    }
    myServo2.write(angle2);
    delay(200); // 等待舵机到达指定位置
    Serial.print("Angle2: ");
    Serial.println(angle2);
  }

  while(Angle6 == true)
  {
    angle2 -= 10;
    if(angle2 < 0)
    {
      angle2 = 0;
    }
    myServo2.write(angle2);
    delay(200); // 等待舵机到达指定位置
    Serial.print("Angle2: ");
    Serial.println(angle2);
    }       
}

// 回调类：处理 BLE 连接和断开事件
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
    Serial.println("Device connected!");
    stopMoving();
  }

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    Serial.println("Device disconnected!");
    pServer->startAdvertising(); // 重新开始广播
  }
};

// 回调类：处理 BLE 数据写入事件
class MyCharacteristicCallbacks : public BLECharacteristicCallbacks{
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    if (value.length() > 0) {
      char cmd = value[0];
      Serial.print("Received value: ");
      Serial.println(cmd);

      // 执行对应的指令
      switch (cmd) {
        case 'W':
          if(model_var == 1) moveForward();
          pCharacteristic->setValue("W");
          break;
        case 'S':
          if(model_var == 1) moveBackward();
          pCharacteristic->setValue("S");
          break;
        case 'A':
          if(model_var == 1) rotateLeft();
          pCharacteristic->setValue("A");
          break;
        case 'D':
          if(model_var == 1) rotateRight();
          pCharacteristic->setValue("D");
          break;
        case 'B':
          if(model_var == 1) {
            stopMoving();
            AngleI = false;
            AngleK = false;
            AngleJ = false;
            AngleL = false;
            Angle5 = false;
            Angle6 = false;
          }
          pCharacteristic->setValue("B");
          break;

        case 'R':
          if(model_var == 1) leftward();
          pCharacteristic->setValue("R");
          break;
        case 'T':
          if(model_var == 1) rightward();
          pCharacteristic->setValue("T");
          break;
        case 'Y':
          if(model_var == 1) leftdown();
          pCharacteristic->setValue("Y");
          break;
        case 'U':
          if(model_var == 1) rightdown() ;
          pCharacteristic->setValue("U");
          break;
        case 'Q':
          if(model_var == 1) strafeLeft();
          pCharacteristic->setValue("Q");
          break;
        case 'E':
          if(model_var == 1) strafeRight();
          pCharacteristic->setValue("E");
          break;

        case 'I':
          if(model_var == 1) AngleI = true;
          // {
          //   AngleI = true;
          //   while(AngleI)
          //   {
          //     angle1 += 10;
          //     if(angle1 > 180)
          //     {
          //       angle1 =180;
          //     }
          //     myServo1.write(angle1);
          //     delay(200); // 等待舵机到达指定位置
          //     Serial.print("Angle1: ");
          //     Serial.println(angle1); 
          //   }
          // }
              pCharacteristic->setValue("I");
              break;

        case 'K':
          if(model_var == 1) AngleK = true;
          // {
          //   AngleK = true;
          //   while(AngleK == true)
          //   {
          //     angle1 -= 10;
          //     if(angle1 < 0)
          //     {
          //       angle1 =0;
          //     }
          //     myServo1.write(angle1);
          //     delay(200); // 等待舵机到达指定位置
          //     Serial.print("Angle1: ");
          //     Serial.println(angle1);
          //   }
          // }
              pCharacteristic->setValue("K");
              break;

        case 'J':
          if(model_var == 1) AngleJ = true;
          //{
          //   AngleJ = true;
          //   while(AngleJ == true)
          //   {
          //     angle += 10;
          //     if(angle > 150)
          //     {
          //       angle = 150;
          //     }
          //     myServo.write(angle);
          //     delay(200); // 等待舵机到达指定位置
          //     Serial.print("Angle: ");
          //     Serial.println(angle);
          //   }
          // }
              pCharacteristic->setValue("J");
              break;

        case 'L':
          if(model_var == 1) AngleL = true; 
          //{
          //   AngleL = true;
          //   while(AngleL == true)
          //   {
          //     angle -= 10;
          //     if(angle < 0)
          //     {
          //       angle = 0;
          //     }
          //     myServo.write(angle);
          //     delay(200); // 等待舵机到达指定位置
          //     Serial.print("Angle: ");
          //     Serial.println(angle);
          //   }
          // }
              pCharacteristic->setValue("L");
              break;

        case '5':
          if(model_var == 1) Angle5 = true;
          //{
          //    Angle5 = true;
          //    while(Angle5 == true)
          //   {
          //     angle2 += 10;
          //     if(angle2 > 80)
          //     {
          //       angle2 = 80;
          //     }
          //     myServo2.write(angle2);
          //     delay(200); // 等待舵机到达指定位置
          //     Serial.print("Angle2: ");
          //     Serial.println(angle2);
          //   }
          // }
              pCharacteristic->setValue("5");
              break;

        case '6':
          if(model_var == 1) Angle6 = true;
          // {
          //    Angle6 = true;
          //    while(Angle6 == true)
          //   {
          //     angle2 -= 10;
          //     if(angle2 < 0)
          //     {
          //       angle2 = 0;
          //     }
          //     myServo2.write(angle2);
          //     delay(200); // 等待舵机到达指定位置
          //     Serial.print("Angle2: ");
          //     Serial.println(angle2);
          //   }
          // }
             pCharacteristic->setValue("6");
              break;

        case '1':
          model_var = 1;
          stopMoving();
          pCharacteristic->setValue("model_var = 1");
          break;
        case '2':
          model_var = 2;
          pCharacteristic->setValue("model_var = 2");
          break;
        case '3':
          model_var = 3;
          pCharacteristic->setValue("model_var = 3");
          break;
        case '4':
          model_var = 4;
          pCharacteristic->setValue("model_var = 4");
          break;

        default:
          model_var = 1;
          stopMoving();
          pCharacteristic->setValue("Invalid command, stopped.");
          break;
      }
      delay(50);
    }
  }
};

void setup() {
  Serial.begin(115200);

  // 初始化 BLE
  BLEDevice::init("ESP32_Car");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // 创建服务和特性
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pCharacteristic->setCallbacks(new MyCharacteristicCallbacks());
  pCharacteristic->setValue("Ready for commands");

  // 启动服务
  pService->start();

  // 开始广播
  pServer->getAdvertising()->start();
  Serial.println("BLE advertising started...");

  // 初始化引脚
  myServo.attach(2);  // 将舵机的信号线连接到ESP32的GPIO 
  myServo1.attach(21);  // 将舵机的信号线连接到ESP32的GPIO 
  myServo2.attach(22);  // 将舵机的信号线连接到ESP32的GPIO 

  pinMode(Trigpin,OUTPUT);
  pinMode(Echopin,INPUT);
  
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
  // 如果设备未连接，进入低功耗模式
  if (!deviceConnected) {
    Serial.println("Device not connected, entering light sleep...");
    delay(1000); // 模拟低功耗等待
  }
  if(model_var == 2){
    ObstacleAvoidance();
  }else if(model_var == 3){
    Follow();
  }else if(model_var == 4){
    Tracking();
  }else if(model_var == 1){
    arm_control();
    //Serial.println(AngleI);
  }
}

