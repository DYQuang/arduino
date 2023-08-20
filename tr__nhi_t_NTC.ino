// Khai báo chân kết nối cảm biến NTC
const int ntcPin = A0;

// Giá trị R1 và beta của NTC (cần chỉnh theo thông số của cảm biến)
const float R1 = 10000.0;   // Giá trị điện trở tại nhiệt độ reference
const float beta = 3950.0;  // Hệ số beta của NTC

// Giá trị điện trở tại nhiệt độ reference và nhiệt độ reference
const float T0 = 298.15;    // 25°C đổi sang Kelvin

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Đọc giá trị analog từ cảm biến NTC
  int rawValue = analogRead(ntcPin);

  // Chuyển giá trị analog sang giá trị điện trở
  float resistance = R1 * (1023.0 / rawValue - 1.0);

  // Tính nhiệt độ dựa trên mô hình Steinhart-Hart
  float temperature = 1.0 / (1.0 / T0 + 1.0 / beta * log(resistance / R1));

  // Chuyển nhiệt độ từ Kelvin sang Celsius
  temperature -= 273.15;

  // In ra giá trị nhiệt độ
  Serial.print("Nhiệt độ: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(1000); // Đợi 1 giây trước khi đọc lại giá trị nhiệt độ
}
