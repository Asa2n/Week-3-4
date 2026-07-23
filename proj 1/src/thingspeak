#include <WiFi.h>
#include "ThingSpeak.h"

char ssid[] = "vivo X200 FE";                    
char pass[] = "0987612345";                         
unsigned long myChannelNumber = 3428790;            // เลข ID Channel ของคุณ
const char * myWriteAPIKey = "OQ9KI1PGCVCDXZ8R";    // API KEY ของคุณ

int keyIndex = 0;

WiFiClient  client;

// ประกาศฟังก์ชันไว้ด้านบนเพื่อให้คอมไพเลอร์รู้จัก (ใน PlatformIO จำเป็นต้องทำ)
void wifi_reconnect();
void thingspeak_multi_write();
void thingspeak_single_write(byte ch, int value);

void setup() 
{
  Serial.begin(115200);  // Initialize serial
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() 
{
  // 1. ตรวจสอบก่อนเสมอว่า WiFi ยังต่ออยู่ไหม ถ้าหลุดให้ต่อใหม่
  wifi_reconnect();

  // 2. สุ่มค่าและเตรียมข้อมูล
  ThingSpeak.setField(1, random(100));
  ThingSpeak.setField(2, random(200));
  
  // 3. ส่งข้อมูลไป ThingSpeak
  thingspeak_multi_write();
  
  // 4. รอ 15 วินาที (ตามกฎข้อบังคับของ ThingSpeak Free Account)
  delay(15000); 
}

void wifi_reconnect() 
{
  if (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED) 
    {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
}

void thingspeak_single_write(byte ch, int value) 
{
  int x = ThingSpeak.writeField(myChannelNumber, ch, value, myWriteAPIKey);
  if (x == 200) 
  {
    Serial.println("Channel " + String(ch) + " update value " + String(value) + " successful.");
  }
  else 
  {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
}

void thingspeak_multi_write() 
{
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) 
  {
    Serial.println("Multichannel update successful.");
  }
  else 
  {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
}