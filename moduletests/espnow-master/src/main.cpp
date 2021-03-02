#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

// Switch GPIO
#define SWITCH_GPIO 5 // GPIO5 -> D1

// Replace with your network credentials (STATION)
const char* ssid = "Plata_New";
const char* password = "64Do94Da96Di";

// Definition of MAC address of slave, channel and key for communication
uint8_t mac_addr_slave[6] = {0x3E, 0x61, 0x05, 0xD1, 0x76, 0xCE};
uint8_t channel=1;
uint8_t key[0]={}; //no hay clave
uint8_t key_len=sizeof(key);

uint8_t action = 1; // 0 = close, 1 = open

void ICACHE_RAM_ATTR sendmessage();

void ICACHE_FLASH_ATTR simple_cb(u8 *macaddr, u8 status)
{
  int i;
  int len_mac = 6;
  
  char sender_mac[3];
  Serial.print("Response MAC address: ");
  for (i = 0; i < len_mac; i++)
  {
    sprintf(sender_mac, "%02X:", macaddr[i]);
    Serial.print(sender_mac);
  }
  Serial.print("\n");
  Serial.print("Status: "); Serial.println(status);

  if (status != 0)
  {
    sendmessage();
  }
} 

void ICACHE_RAM_ATTR sendmessage()
{
  Serial.println("Button press sent...");
  uint8_t message[1] = {action};
  esp_now_send(mac_addr_slave, message, 1);
  esp_now_register_send_cb(simple_cb);
  if (action == 0)
  {
    action = 1;
  }
  else
  {
    action = 0;
  }
  // Delay for communication stability
  // int now = millis();
  // while(millis() - now < 2000);
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
  Serial.println(esp_now_set_self_role(1)); // role = 1 -> Master

  Serial.print("Key size: "); Serial.println(key_len);
  esp_now_add_peer(mac_addr_slave,2,channel,key,key_len);

  // ETS_GPIO_INTR_ENABLE();
  // ETS_GPIO_INTR_ATTACH(sendmessage, 0);
  pinMode(SWITCH_GPIO, INPUT);
  attachInterrupt(digitalPinToInterrupt(SWITCH_GPIO), sendmessage, RISING);
}

void loop()
{
  // pressed = digitalRead(SWITCH_GPIO);
  // uint8_t message[1] = {0};
  // if (pressed == HIGH)
  // {
  //   message[0] = 1;
  //   esp_now_send(mac_addr_slave, message, 1);
  //   Serial.println("Button press sent...");
  // }
  // // delay(1000);
}