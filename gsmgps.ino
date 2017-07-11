#include <SoftwareSerial.h>
#include <AltSoftSerial.h>
#include <TinyGPS++.h>

String number1="+919164011519";
String number2="+917892098221";
String number3="+918848337736";
String st="http://maps.google.com/?q=";

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
AltSoftSerial gpsSerial;//(RX 8, TX 9);

// The serial connection to the GSM device
SoftwareSerial mySerial(2,3);//(RXPin, TXPin)

int flag=0;

void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  delay(1000);
  if (mySerial.available()>0)
  {
    Serial.println(mySerial.readString());
  }
  gpsSerial.begin(9600); 
   
}

void loop()
{
  while (gpsSerial.available())
  {
    if (gps.encode(gpsSerial.read()))
    {
      Gpslocate();
    }
    flag=0;
  }    

  if (millis() > 5000 && gps.charsProcessed() < 10 && flag==0)
  {
    Serial.println(F("No GPS detected: check wiring."));
    flag=1;
  }
}

