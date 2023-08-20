int sensor=A0;//Kết nối NTC với chân A0
int ledpin=10;//LED được nối tới chân D11
int val=0;//biến val
void setup()
{
	pinMode(ledpin,OUTPUT);//Cấu hình ledpin là chân xuất
	Serial.begin(9600);//Tốc độ baud 9600
}
void loop()
{
	val=analogRead(sensor);//val sẽ có giá trị 0-1023 tương ứng với điện áp tại A0
	val = 220 - val/2;
  if(val < 0) //Khi val <0 thì gán 0 cho val
    val = 0;
	Serial.println(val); //in giá trị val ra màn hình monitor serial
	analogWrite(ledpin,val);// PWM LED
	delay(100);//dừng chương trình 100ms
}
