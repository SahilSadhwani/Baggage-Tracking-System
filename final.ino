  #include <SoftwareSerial.h>
SoftwareSerial SoftSerial(10, 11); // RX, TX
 
void setup()
{
  SoftSerial.begin(9600);
  SoftSerial.println("AT+SAPBR=3,1,\"APN\",\"internet\"");
  delay(100);
  SoftSerial.println("AT+SAPBR=1,1");
  delay(1500);
}
 
void loop()
{
  SoftSerial.println("AT+SAPBR=3,1,\"APN\",\"internet\"");
  delay(100);
  SoftSerial.println("AT+SAPBR=1,1");
  delay(1500);
  
  SoftSerial.println("AT+CIPGSMLOC=1,1");
  while(!SoftSerial.find("+CIPGSMLOC: 0,")) { }
  String longitude = readValue();
  String latitude = readValue();
  SoftSerial.println("AT+HTTPINIT");
  delay(100);
  SoftSerial.println("AT+HTTPPARA=\"URL\",\"http://api.thingspeak.com/update?key=ZQQH2OUCI7Z51D0O&field1=" + latitude + "&field2=" + longitude + "\"");
  delay(200);
  SoftSerial.println("AT+HTTPACTION=0");
  delay(5000);
  SoftSerial.println("AT+HTTPTERM");
  delay(54700);
  SoftSerial.println("AT+SAPBR=0,1");
} 
 
String readValue()
{
  String value = "";
  unsigned int i = 0;
  while(i++ < 60000)
  {
    if(SoftSerial.available())
    {
      char c = SoftSerial.read();
      if(c == ',') break;
      value += c;
    }
  }
  if(i < 60000) return value; else return "";
}
