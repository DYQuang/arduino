#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
const int buzze = 13;
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {6, 7, 8, 9};
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

const char password[] = "1234"; // Mật khẩu bạn muốn sử dụng
char enteredPassword[5] = ""; // Biến để lưu mật khẩu người dùng nhập

LiquidCrystal_I2C lcd(0x27, 16, 2); // Địa chỉ I2C của màn hình và kích thước

void setup(){
  Serial.begin(9600);
  lcd.init(); // Khởi tạo màn hình LCD
  lcd.backlight(); // Bật đèn nền màn hình
  lcd.setCursor(0, 0); // Đặt con trỏ văn bản ở hàng 0, cột 0
  lcd.print("Enter password:"); // Hiển thị thông báo nhập mật khẩu
  pinMode(buzze,OUTPUT);
  digitalWrite(buzze,LOW);
}

void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey){
    if (customKey == 'E') {
      if (strcmp(enteredPassword, password) == 0) {
        lcd.clear(); // Xóa nội dung màn hình
        lcd.setCursor(0, 0);
        lcd.print("Password correct!"); // Hiển thị thông báo đúng mật khẩu
        Serial.println("Yes"); // In ra cổng Serial
        digitalWrite(buzze,HIGH);
        delay(50);
        digitalWrite(buzze,LOW);
        delay(50);
        digitalWrite(buzze,HIGH);
        delay(50);
        digitalWrite(buzze,LOW);
        // Thực hiện hành động khi mật khẩu đúng
      } else {
        lcd.clear(); // Xóa nội dung màn hình
        lcd.setCursor(0, 0);
        lcd.print("Password incorrect!"); // Hiển thị thông báo sai mật khẩu
        Serial.println("No"); // In ra cổng Serial
        digitalWrite(buzze,HIGH);
        delay(500);
        digitalWrite(buzze,LOW);
        // Thực hiện hành động khi mật khẩu sai
      }
      memset(enteredPassword, 0, sizeof(enteredPassword)); // Xóa mật khẩu người dùng nhập
      delay(2000); // Đợi 2 giây để đọc thông báo
      lcd.clear(); // Xóa nội dung màn hình
      lcd.setCursor(0, 0);
      lcd.print("Enter password:"); // Hiển thị lại thông báo nhập mật khẩu
    } else {
      if (strlen(enteredPassword) < sizeof(enteredPassword) - 1) {
        enteredPassword[strlen(enteredPassword)] = customKey; // Thêm ký tự vào mật khẩu
        lcd.setCursor(strlen(enteredPassword) - 1, 1); // Đặt con trỏ văn bản ở hàng 1, cột tương ứng
        digitalWrite(buzze,HIGH);
        delay(50);
        digitalWrite(buzze,LOW);
        lcd.print('*'); // Hiển thị dấu '*' thay thế cho ký tự
      }
    }
  }
}
