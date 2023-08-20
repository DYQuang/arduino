#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Địa chỉ I2C của màn hình LCD và kích thước 16x2

byte ten[] = {0x00, 0x00, 0x04, 0x02, 0x1F, 0x02, 0x04, 0x00};
byte nguoi[] = {0x0E, 0x0E, 0x0E, 0x04, 0x1F, 0x04, 0x0A, 0x0A};
byte tim1[] = {0x00, 0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00};
byte tim2[] = {0x00, 0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00};

void setup() {
  Serial.begin(9600);
  lcd.init();  // Khởi tạo màn hình LCD
  lcd.backlight();  // Bật đèn nền cho LCD
  lcd.createChar(0, ten);
  lcd.createChar(1, nguoi);
  lcd.createChar(2, tim1);
  lcd.createChar(3, tim2);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gui cau");
  lcd.setCursor(0, 1);
  lcd.print("To muon noi rang...");
  delay(3000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.write(byte(1));
  lcd.setCursor(15, 0);
  lcd.write(byte(1));
  lcd.setCursor(14, 0);
  lcd.write(byte(2));
  
  for (int i = 1; i < 14; i++) {
    lcd.setCursor(i, 0);
    lcd.write(byte(0));
    delay(500);
    lcd.setCursor(i, 0);
    lcd.print(' ');
  }
  
  for (int j = 1; j < 15; j++) {
    lcd.setCursor(j, 0);
    lcd.write(byte(3));
    delay(200);
  }
  
  lcd.setCursor(3, 1);
  lcd.print("I Love You");
}

void loop() {
  
}
