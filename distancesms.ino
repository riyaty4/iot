#include <NewPing.h>



 
 #include <SoftwareSerial.h>
//#include <dht.h>


#define maxd 400 // Analog Pin sensor is connected to
 
//dht DHT;

SoftwareSerial mySerial(9, 10);

//define pin numbers
const int trigPin = 6;
const int echoPin = 7;
NewPing sonar(trigPin, echoPin,maxd);

//define variables
double duration;
double distance;

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}


void loop()
{
// Clears the trigPin
digitalWrite(trigPin, LOW);
//delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
//delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance = sonar.ping_cm();

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
//if(distance!=0)
Serial.println(distance);
if(distance==2 || distance ==3 || distance == 6)
Serial.println("clog");
   switch(Serial.read())
  {
    case 's':
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
   //  delay(1000);  // Delay of 1 second
     mySerial.println("AT+CMGS=\"+919315377071\"\r"); // Replace x with mobile number
   //  delay(1000);
     
      if(distance==7 || distance ==8 || distance == 9)
     mySerial.println("clog :(");
   //  mySerial.println(distance);// The SMS text you want to send
    else
    mySerial.println(" no clog :)");
   //  delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
    //  delay(1000);
      break;



      
    case 'r':
      mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
      delay(1000);
      break;
  }

//Wait 5 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.
}

 
