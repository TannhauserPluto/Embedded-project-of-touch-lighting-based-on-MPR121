#include <Wire.h>
#include <Adafruit_MPR121.h>

Adafruit_MPR121 cap = Adafruit_MPR121();
int lastTouched = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("MPR121 Touch Sensor Test");

  if (!cap.begin(0x5A)) { // I2C地址0x5A
    Serial.println("MPR121 not found!");
    while (1);
  }

  // === MPR121参数配置 ===
  // 1. 提高充电电流至32μA（增强低阻导电膜灵敏度）
  cap.writeRegister(0x5C, 0x30); 

  // 2. 设置触摸和释放阈值（数值越小越敏感）
  cap.setThresholds(300, 150); // 触摸阈值=10，释放阈值=5（ESP32代码中阈值为10）

  Serial.println("MPR121 ready!");
}

void loop() {
  // 读取电极0（E0）的滤波后电容值（数值越小，触摸越强）
  int touchValue = cap.filteredData(0); 
  Serial.print("Touch Value: ");
  Serial.println(touchValue);

  // 判断是否触摸（与ESP32逻辑一致，值越小表示触摸越强）
  if (touchValue < 220) { // 测试值 没接地
    Serial.println("TOUCHED!");
  } else {
    Serial.println("No touch");
  }

  delay(500); 
}