#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "ACS712.h"

// Khai báo LCD: địa chỉ 0x27, 16 cột, 2 dòng
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Cảm biến dòng ACS712 30A gắn vào chân A1
ACS712 sensor(ACS712_30A, A1);

// Biến toàn cục
const int cambien = A0; // chân đo áp chia áp
int zero;
float I_TB, tong;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(cambien, INPUT);

  Serial.println("Đảm bảo không có dòng qua cảm biến để cân bằng");
  lcd.setCursor(0, 0);
  lcd.print("Dang can bang...");
  delay(1000);

  Serial.println("Calibrating...");
  zero = sensor.calibrate();
  Serial.println("Cal xong. Zero = " + String(zero));

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cal xong!");
  delay(1000);

  // In tiêu đề cố định LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("V:        V");
  lcd.setCursor(0, 1);
  lcd.print("I:        A");
}

void loop() {
  // Đọc giá trị ADC từ điện áp chia áp
  int adcValue = analogRead(cambien);
  float vol_out = adcValue * 5.0 / 1023.0;
  float vol_in = vol_out / (930.0 / (9860.0 + 930.0)); // chia áp
  float voltage_display = vol_in - 1.0; // loại bỏ offset nếu có

  // Đo dòng điện trung bình từ cảm biến
  tong = 0;
  for (int i = 0; i < 100; i++) {
    tong += sensor.getCurrentDC();
  }
  I_TB = tong / 100.0;

  // In Serial Monitor
  Serial.print("V = "); Serial.print(voltage_display, 2); Serial.print(" V   ");
  Serial.print("I = "); Serial.print(I_TB, 2); Serial.println(" A");

  // Hiển thị lên LCD (không clear toàn bộ, chỉ ghi đè)
  lcd.setCursor(3, 0); // sau "V: "
  lcd.print("       "); // xóa dữ liệu cũ
  lcd.setCursor(3, 0);
  lcd.print(voltage_display, 2);

  lcd.setCursor(3, 1); // sau "I: "
  lcd.print("       ");
  lcd.setCursor(3, 1);
  lcd.print(I_TB, 2);

  delay(1000);
}
