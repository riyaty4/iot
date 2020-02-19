
#include "DHT.h"
#include <SPI.h>
#include <Ethernet.h>
#include <WiFi.h>
byte mac[6];// = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //Setting MAC Address

//#define DHTPIN 2

//#define DHTTYPE DHT11
SoftwareSerial mySerial(9, 10);
//DHT dht(DHTPIN,DHTTYPE);

//define pin numbers
const int trigPin = 6;
const int echoPin = 7;
NewPing sonar(trigPin, echoPin,maxd);


//float humidityData;
//float temperatureData;

//define variable
float duration;
float distance;


char server[] = "<Your Local IP>";
IPAddress ip(192,168,0,177); 
EthernetClient client; 

/* Setup for Ethernet and RFID */

void setup() {
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
  if (Ethernet.begin(WiFi.macAddress(mac) == 0)) {
  Serial.println("Failed to configure Ethernet using DHCP");
  Ethernet.begin(mac, ip);
  }
  delay(1000);
}
//------------------------------------------------------------------------------


/* Infinite Loop */
void loop(){
  digitalWrite(trigPin, LOW);
delayMicroseconds(2);

 //Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
//delay(15000);
// Calculating the distance
//distance = sonar.ping_cm();
distance= duration*0.034/2;
  Sending_To_phpmyadmindatabase(); 
  delay(30000); // interval
}


  void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
 {
   if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET /testcode/dht.php?humidity=");
    client.print("GET /testcode/dht.php?humidity=");     //YOUR URL
    Serial.println(humidityData);
    client.print(humidityData);
    client.print("&temperature=");
    Serial.println("&temperature=");
    client.print(temperatureData);
    Serial.println(temperatureData);
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: <Your Local IP>");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 }
