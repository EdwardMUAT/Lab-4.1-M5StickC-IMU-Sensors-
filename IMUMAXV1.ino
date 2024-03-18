/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5StickC-Plus sample source code
*                          配套  M5StickC-Plus 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/m5stickc_plus
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/m5stickc_plus
*
* Describe: IMU.
* Date: 2021/9/14
*******************************************************************************
*/






#include <M5StickCPlus.h>

#define LED_PIN 10

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float maxX = 0.0F;
float maxY = 0.0F;
float maxZ = 0.0F;

float magSq = 0.0F;

float mag = 0.0F;

float maxMag = 0.0F;

/* After M5StickC Plus is started or reset
  the program in the setUp () function will be run, and this part will only be
  run once. 在 M5StickC Plus
  启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。 */
void setup() {
    M5.begin();             // Init M5StickC Plus.  初始化 M5StickC Plus
    M5.Imu.Init();          // Init IMU.  初始化IMU
    M5.Lcd.setRotation(3);  // Rotate the screen. 将屏幕旋转
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(3);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
  //  M5.Lcd.setCursor(80, 15);  // set the cursor location.  设置光标位置
   // M5.Lcd.println("IMU TEST");
   // M5.Lcd.setCursor(30, 30);
  //  M5.Lcd.println("  X       Y       Z");
  //  M5.Lcd.setCursor(30, 50);
   // M5.Lcd.println("  maxX       maxY       maxZ");
}

/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
在setup()函数中的程序执行完后，会接着执行loop()函数中的程序
loop()函数是一个死循环，其中的程序会不断的重复运行 */
void loop() {

    static float temp = 0;
    M5.update();  // Read the press state of the key.  读取按键 A, B, C 的状态
    if (M5.BtnA
            .wasReleased()) {  // If the button A is pressed.  如果按键 A 被按下
        maxMag = 0.0F;
        }
    M5.IMU.getAccelData(&accX, &accY, &accZ);
    M5.IMU.getTempData(&temp);
   

   float xSq = sq(accX);
   float ySq = sq(accY);
   float zSq = sq(accZ);

    magSq = xSq + ySq + zSq;

    mag = sqrt(magSq);

if (mag > maxMag){
  maxMag = mag;

}

    M5.Lcd.setCursor(30, 30);
    M5.Lcd.printf("%5.2f", mag);

    M5.Lcd.setCursor(30, 60);
    M5.Lcd.printf("%5.2f", maxMag);

  if (mag > 5) {
      for( int i = 0; i< 5; i++){
        digitalWrite(LED_PIN, LOW);
        delay(500);
        digitalWrite(LED_PIN, HIGH);
        delay(500);
      }
  }

    delay(10);
}
