#include <Arduino.h>
#include <WiFi.h>

// 1. ตั้งค่า Wi-Fi (ต้องใช้ Wi-Fi วงเดียวกันกับคอมพิวเตอร์ที่รัน Node-RED)
const char* ssid = "vivo X200 FE";
const char* password = "0987612345";

// 2. ตั้งค่า Node-RED Server
const char* server_ip = "10.86.61.162"; // เปลี่ยนเป็น IP Address ของเครื่องคอมพิวเตอร์คุณ
const uint16_t server_port = 5060;       // Port 2000 ตรงตามที่ตั้งไว้ใน Node-RED

WiFiClient client;

void setup() {
  Serial.begin(115200);

  // เริ่มการเชื่อมต่อ Wi-Fi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // ตรวจสอบว่ามีการพิมพ์ข้อความเข้ามาทาง Serial Monitor หรือไม่
  if (Serial.available() > 0) {
    // อ่านข้อความที่เราพิมพ์จนกว่าจะกด Enter
    String inputData = Serial.readStringUntil('\n'); 
    inputData.trim(); // ตัดช่องว่างส่วนเกินออก

    // ถ้ามีข้อความถูกพิมพ์เข้ามาจริงๆ (ไม่ได้กด Enter เปล่าๆ)
    if (inputData.length() > 0) {
      Serial.print("Connecting to Node-RED... ");
      
      // ให้ Client พยายามเชื่อมต่อไปที่คอมพิวเตอร์
      if (client.connect(server_ip, server_port)) {
        Serial.println("Success!");
        
        // ส่งข้อความที่เราเพิ่งพิมพ์เข้าไป (เช่น "30,45")
        client.print(inputData); 
        Serial.println("Sent from manual input: " + inputData);
        
        // ส่งเสร็จแล้วปิดการเชื่อมต่อ
        client.stop(); 
      } else {
        Serial.println("Failed to connect to server.");
      }
      Serial.println("-------------------------");
    }
  }
}