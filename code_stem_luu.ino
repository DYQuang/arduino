#include <SoftwareSerial.h>
#include <Arduino.h>
#define TRIGGER_PIN 7
#define ECHO_PIN 8

const int RX_PIN = 3;
const int TX_PIN = 2;
const int valwatersensor = A0;
const int vallightsensor = A1;
const int batteryVoltagePin = A2;
const int voltageThreshold = 600;
const int relayPin = 9;
const int ledred = 13;
const int buzzePin = 12;
const int ledgreen = 11;
const int ledyellow = 10;
float batteryVoltage;

SoftwareSerial sim800l(RX_PIN, TX_PIN);
void setup()
{
  Serial.begin(9600);
  while (!Serial); // Chờ Serial kết nối

  sim800l.begin(9600);
  delay(2000);

  // Thử kết nối với module SIM800L
  sim800l.println("AT");
  delay(100);
  if (sim800l.available())
  {
    Serial.println("Module SIM800L đã sẵn sàng!");
  }
  else
  {
    Serial.println("Lỗi kết nối với module SIM800L!");
  }

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(ledred, OUTPUT);
  pinMode(ledgreen, OUTPUT);
  pinMode(ledyellow, OUTPUT);
  pinMode(buzzePin, OUTPUT);
  digitalWrite(ledred, LOW);
  digitalWrite(ledgreen, LOW);
  digitalWrite(ledyellow, LOW);
  digitalWrite(buzzePin, LOW);
}

void loop()
{
  long duration, distance_cm, speed;
  int watersensor = analogRead(valwatersensor);
  int lightsensor = analogRead(vallightsensor);
  int batteryVoltageValue = analogRead(batteryVoltagePin);
  batteryVoltage = batteryVoltageValue * (5.0 / 1023.0) * (12.0 / 2.0);

  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance_cm = duration * 0.034 / 2;

  delay(1000);
  long new_duration = pulseIn(ECHO_PIN, HIGH);
  long new_distance_cm = new_duration * 0.034 / 2;

  speed = abs(new_distance_cm - distance_cm);
  Serial.print("Tốc độ nước dâng lên: ");
  Serial.println(speed);
  Serial.print("Mực nước: ");
  Serial.print(watersensor);
  Serial.println(" cm");
  Serial.print("Giá trị ánh sáng: ");
  Serial.println(lightsensor);
  Serial.print("Điện áp: ");
  Serial.println(batteryVoltage);

  checklightsensor();
  checkBatteryVoltage();
  canhbao();
  delay(100);
}

void sendMessage(String message) 
{
  // Gửi tin nhắn về điện thoại qua module SIM800L
  sim800l.println("AT+CMGF=1"); // Chế độ gửi tin nhắn văn bản
  delay(100);
  sim800l.print("AT+CMGS=\"");
  sim800l.print("0344794464");
  sim800l.println("\"");
  delay(100);
  sim800l.print(message); // Nội dung tin nhắn
  delay(100);
  sim800l.write(26); // Gửi ký tự Ctrl+Z để hoàn tất tin nhắn
  delay(1000); // Chờ 1 giây trước khi lặp lại
}

void checklightsensor()
{
  int lightsensor = analogRead(vallightsensor);
  if (lightsensor < 200)
  {
    digitalWrite(relayPin, HIGH);
  }
  else
  {
    digitalWrite(relayPin, LOW);
  }
}

void checkBatteryVoltage()
{
  if (batteryVoltage < 6)
  {
    digitalWrite(ledyellow, HIGH);
    digitalWrite(ledgreen, LOW);
    sendMessage("DIẸN AP AC QUY XUONG THAP NHANH XHONG HAY THE");
    delay(1000); // Chờ 1 giây trước khi lặp lại
  }
  else
  {
    digitalWrite(ledyellow, LOW);
    digitalWrite(ledgreen, HIGH);
  }
}

void canhbao()
{
  int watersensor = analogRead(valwatersensor);
  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance_cm = duration * 0.034 / 2;
  long new_duration = pulseIn(ECHO_PIN, HIGH);
  long new_distance_cm = new_duration * 0.034 / 2;
  long speed = abs(new_distance_cm - distance_cm);

  if (watersensor > 600 && speed < 50)
  {
    sendMessage("CANH BAO MUC NUOC DAN LEN NHANH CHONG SO TANG");
    callNumber("0344794464");
    delay(15000);
    endCall();

    delay(1000);
    digitalWrite(ledred, HIGH);
    digitalWrite(buzzePin, HIGH);
    delay(1000);
    digitalWrite(ledred, LOW);
    digitalWrite(buzzePin, LOW);
    delay(1000);
  
  }
}

void callNumber(const char* phoneNumber) 
{
  sim800l.println("ATD" + String(phoneNumber) + ";");
  delay(1000);
}
void endCall() 
{
  sim800l.println("ATH");
  delay(1000);
}
