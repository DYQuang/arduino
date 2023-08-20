#include <SoftwareSerial.h>

SoftwareSerial sim800lSerial(3, 2); // RX, TX pins

void setup() {
  Serial.begin(9600);
  sim800lSerial.begin(9600);

  // Đợi module SIM800L khởi động
  delay(2000);
  Serial.println("Module SIM800L da san sang!");
}

void loop() {
  // Gọi điện
  callNumber("0344794464"); // Thay thế +1234567890 bằng số điện thoại cần gọi

  // Đợi 10 giây để thực hiện cuộc gọi
  delay(10000);

  // Kết thúc cuộc gọi (nếu cuộc gọi đang hoạt động)
  endCall();

  delay(5000); // Đợi 5 giây trước khi thực hiện lần lặp tiếp theo
}

void callNumber(const char* phoneNumber) {
  sim800lSerial.println("ATD" + String(phoneNumber) + ";");
  delay(1000);
}

void endCall() {
  sim800lSerial.println("ATH");
  delay(1000);
}
