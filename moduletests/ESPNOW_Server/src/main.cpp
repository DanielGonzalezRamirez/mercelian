#include <Arduino.h>
#include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>
#include <espnow.h>
// extern "C" {
//   #include <espnow.h>
// }


// Replace with your network credentials (STATION)
const char* ssid = "Plata_New";
const char* password = "64Do94Da96Di";

bool InitializeESPNOW(void);
bool SetRoleESPNOW(int);

void setup(){
  // Initialize Serial Monitor
  delay(500);
  Serial.begin(9600); Serial.println();
  // Prints MAC address for Access Point and Station modes 
  Serial.print("AP MAC: "); Serial.println(WiFi.softAPmacAddress());
  Serial.print("STA MAC: "); Serial.println(WiFi.macAddress());
  // Sets the WiFi operating mode
  wifi_set_opmode(3); // Station + SoftAP
  Serial.println(wifi_get_opmode());
  // Calls the ESP-NOW initialization function until the connection is initialized
  Serial.println(esp_now_init());
  Serial.println(esp_now_set_self_role(3));
  // while (InitializeESPNOW());
  Serial.println("Conexion ESPNOW iniciada");
  // Calls the ESP-NOW role set funtion until role is set
  // while (SetRoleESPNOW(3)); // Replace role as needed (see function comments)
  Serial.println("Rol ESPNOW asignado");

}

void loop(){}

bool InitializeESPNOW(){
  // Initializes the ESP-NOW protocol
  bool flag = true;
  if (esp_now_init() != 0){
    Serial.println("Conexion ESPNOW no iniciada");
    Serial.println(esp_now_init());
    delay(500);
    ESP.restart();
    flag = false;
  }
  return flag;
}

bool SetRoleESPNOW(int role){
  // Sets the ESP-NOW role from the parameter
  // role = 0, 1, 2, 3 : Idle, Master, Slave, Combo
  bool flag = true;
  if (esp_now_set_self_role(role) != 0){
    Serial.println("Rol ESPNOW no asignado");
    flag = false;
  }
  return flag;
}


// void setup() {
//   // Initialize Serial Monitor
//   delay(1000);
//   Serial.begin(9600);
//   Serial.print("ESP Board MAC Address:  ");
//   Serial.println(WiFi.macAddress());

//   // Set the device as a Station and Soft Access Point simultaneously
//   WiFi.mode(WIFI_AP_STA);
  
//   // Set device as a Wi-Fi Station
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Setting as a Wi-Fi Station..");
//   }
//   Serial.print("Station IP Address: ");
//   Serial.println(WiFi.localIP());
//   Serial.print("Wi-Fi Channel: ");
//   Serial.println(WiFi.channel());

//   // Init ESP-NOW
//   initEspNow();
  
//   // Once ESPNow is successfully Init, we will register for recv CB to
//   // get recv packer info
//   esp_now_register_recv_cb(OnDataRecv);

//   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
//     request->send_P(200, "text/html", index_html);
//   });
   
//   events.onConnect([](AsyncEventSourceClient *client){
//     if(client->lastId()){
//       Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
//     }
//     // send event with message "hello!", id current millis
//     // and set reconnect delay to 1 second
//     client->send("hello!", NULL, millis(), 10000);
//   });
//   server.addHandler(&events);
//   server.begin();
// }

// void initEspNow() {
//   if (esp_now_init()!=0) {
//     Serial.println("*** ESP_Now init failed");
//     ESP.restart();
//   }
// }
 
// void loop() {
//   static unsigned long lastEventTime = millis();
//   static const unsigned long EVENT_INTERVAL_MS = 5000;
//   if ((millis() - lastEventTime) > EVENT_INTERVAL_MS) {
//     events.send("ping",NULL,millis());
//     lastEventTime = millis();
//   }
// }