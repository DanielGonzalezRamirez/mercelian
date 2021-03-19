#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#define LED 2

#define Valve01 4   //D2 is GPIO4 (PWM)
#define Valve02 12  //D6 is GPIO12 (PWM)
#define Valve03 14  //D5 is GPIO14 (PWM)
#define Valve04 15  //D8 is GPIO15 (PWM)

//WiFi Connection configuration
const char *ssid = "ssid";
const char *password = "pass";
const char *apssid = "espap";

IPAddress ip(192,168,31,4);
IPAddress gt(192,168,31,1);
IPAddress sn(255,255,255,0);

Servo valve_01;  // create servo object to control a servo (valve)
Servo valve_02;  // create servo object to control a servo (valve)
Servo valve_03;  // create servo object to control a servo (valve)
Servo valve_04;  // create servo object to control a servo (valve)

ESP8266WebServer server(80);  //Creates webserver on port 80

int V01_pos = 0;  // variable to store the servo position
int V02_pos = 0;  // variable to store the servo position
int V03_pos = 0;  // variable to store the servo position
int V04_pos = 0;  // variable to store the servo position

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(9600);
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());

  pinMode(LED, OUTPUT);

  valve_01.attach(Valve01); // attaches the valve on D2 to the servo object
  valve_02.attach(Valve02); // attaches the valve on D6 to the servo object
  valve_03.attach(Valve03); // attaches the valve on D5 to the servo object
  valve_04.attach(Valve04); // attaches the valve on D8 to the servo object
  
  //Connect to wifi Network
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password); //Connect to WiFi router
  Serial.println("");

  // Wait for connection
  Serial.print("Connecting:  ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to ESP

  // Setup ESP AP
  WiFi.softAPConfig(ip, gt, sn);
  WiFi.softAP(apssid, password);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  valve_01.write(V01_pos);
  if (V01_pos == 0){
    V01_pos = 180;
    digitalWrite(LED, LOW);
  }
  else{
    V01_pos = 0;
    digitalWrite(LED, HIGH);
  }
  delay(1000);
}
