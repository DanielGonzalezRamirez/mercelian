#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

// LED GPIO
#define LED 2 // Internal LED GPIO

// Replace with your network credentials (STATION)
const char* ssid = "ssid";
const char* password = "pass";

void ICACHE_FLASH_ATTR simple_cb(u8 *macaddr, u8 *data, u8 len)
{
  int i;
  int len_mac = 6;
  
  char sender_mac[3];
  Serial.print("Sender MAC address: ");
  for (i = 0; i < len_mac; i++)
  {
    sprintf(sender_mac, "%02X:", macaddr[i]);
    Serial.print(sender_mac);
  }
  Serial.print("\n");
  Serial.println(data[0]);
} 

void setup()
{
  // Initialize Serial Monitor
  delay(500);
  Serial.begin(9600); Serial.println();
  // Prints MAC address for Access Point and Station modes 
  Serial.print("AP MAC: "); Serial.println(WiFi.softAPmacAddress());
  Serial.print("STA MAC: "); Serial.println(WiFi.macAddress());
  // Calls the ESP-NOW initialization function until the connection is initialized
  Serial.println(esp_now_init());
  // Calls the ESP-NOW role set funtion until role is set
  Serial.println(esp_now_set_self_role(2));
  Serial.println("Slave configured");

  pinMode(LED, OUTPUT);
  esp_now_register_recv_cb(simple_cb);
}

void loop()
{
  // //***RECEPCIÓN DE LA COMUNICACIÓN ESP-NOW***//
  // esp_now_register_recv_cb([](uint8_t *mac, uint8_t *data, uint8_t len) {
  //   char MACmaestro[6];
  //   sprintf(MACmaestro, "%02X:%02X:%02X:%02X:%02X:%02X",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
  //   Serial.print("Recepcion desde ESP MAC: "); Serial.print(MACmaestro);
  //   Serial.println("Switch pressed...");
  // });
}
