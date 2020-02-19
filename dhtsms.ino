

 
 #include <SoftwareSerial.h>
#include <dht.h>


#define dht_apin A0 // Analog Pin sensor is connected to
 
dht DHT;

SoftwareSerial mySerial(9, 10);

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
}


void loop()
{
   if (mySerial.available()>0)
   Serial.write(mySerial.read());
      DHT.read11(dht_apin);
   // Serial.print(); 
    Serial.println("C  ");
    
    delay(5000);
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     mySerial.println("AT+CMGS=\"+918505822661\"\r"); // Replace x with mobile number
     delay(1000);
     mySerial.println("current temperature=");
     mySerial.println(DHT.temperature);// The SMS text you want to send
     mySerial.println("current humidity=");
     mySerial.println(DHT.humidity);
     delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
      break;



      
    case 'r':
      mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
      delay(1000);
      break;
  }

//Wait 5 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.
}

 
