#include <Servo.h>

Servo servo1;  // Đối tượng cho servo 1
Servo servo2;  // Đối tượng cho servo 2
Servo servo3;  // Đối tượng cho servo 3
Servo servo4;  // Đối tượng cho servo 4


int potPin1 = A0; // Chân analog đọc giá trị từ biến trở 1
int potPin2 = A1; // Chân analog đọc giá trị từ biến trở 2
int potPin3 = A2; // Chân analog đọc giá trị từ biến trở 3
int potPin4 = A3; // Chân analog đọc giá trị từ biến trở 4


int angle1 = 0;   // Góc quay của servo 1
int angle2 = 0;   // Góc quay của servo 2
int angle3 = 0;   // Góc quay của servo 3
int angle4 = 0;   // Góc quay của servo 4

void setup() {
  servo1.attach(9); // Chân điều khiển servo 1
  servo2.attach(10); // Chân điều khiển servo 2
  servo3.attach(11); // Chân điều khiển servo 3
  servo4.attach(8);

  Serial.begin(9600);
}

void loop() {
  int potValue1 = analogRead(potPin1);
  int potValue2 = analogRead(potPin2);
  int potValue3 = analogRead(potPin3);
  int potValue4 = analogRead(potPin4);

  angle1 = map(potValue1, 0, 1023, 0, 180);
  angle2 = map(potValue2, 0, 1023, 0, 180);
  angle3 = map(potValue3, 0, 1023, 0, 180);
  angle4 = map(potValue4, 0, 1023, 0, 180);

  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);
  servo4.write(angle4);

  Serial.print("Potentiometer 1 Value: ");
  Serial.println(potValue1);
  Serial.print("Servo 1 Angle: ");
  Serial.println(angle1);

  Serial.print("Potentiometer 2 Value: ");
  Serial.println(potValue2);
  Serial.print("Servo 2 Angle: ");
  Serial.println(angle2);

  Serial.print("Potentiometer 3 Value: ");
  Serial.println(potValue3);
  Serial.print("Servo 3 Angle: ");
  Serial.println(angle3);

  Serial.print("Potentiometer 4 Value: ");
  Serial.println(potValue4);
  Serial.print("Servo 4 Angle: ");
  Serial.println(angle4 );


  delay(15);
}
