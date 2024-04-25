#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <Servo.h>
#define RX_PIN 4
#define TX_PIN 5 
#define WIFI_SSID "iPhone"
#define WIFI_PASSWORD "123456789"
#define FIREBASE_HOST "https://doan2-3723f-default-rtdb.firebaseio.com/"
#define FIREBASE_AAUTH "lBLjbbreZIXnjDlqVU3Z5LYFkdZcNQFQBiLUKtvY"
FirebaseData firebaseData;
String path="/";
FirebaseJson json;
bool stringComplete = false;
SoftwareSerial mySerial(RX_PIN,TX_PIN);
//StaticJsonDocument<100> doc;
String getValue(String data, char separator, int index){
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
      if (data.charAt(i) == separator || i == maxIndex) {
          found++;
          strIndex[0] = strIndex[1] + 1;
          strIndex[1] = (i == maxIndex) ? i+1 : i;
      }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Firebase.begin(FIREBASE_HOST, FIREBASE_AAUTH);
  Firebase.reconnectWiFi(true);

  if (!Firebase.beginStream(firebaseData, path)) {
    Serial.println("REASON:" + firebaseData.errorReason());
    Serial.println();
  }

  Serial.print("Connected with IP:");
  Serial.println(WiFi.localIP());
  Serial.println();

}
void loop() {
  String soluong1, chotrong1, soluong2, chotrong2, soluong3, chotrong3,tinhtrang1,tinhtrang2,tinhtrang3;

  if (mySerial.available()) {
    String data = mySerial.readString();
    Serial.println(data); // In ra chuỗi dữ liệu
    soluong1 = getValue(data, ';', 0); // Tách phần tử thứ 0 theo ký tự phân cách ';'
    chotrong1 = getValue(data, ';', 1);
    soluong2 = getValue(data, ';', 2);
    chotrong2 = getValue(data, ';', 3);
    soluong3 = getValue(data, ';', 4);
    chotrong3 = getValue(data, ';', 5);
    tinhtrang1=getValue(data,';',6);
    tinhtrang2=getValue(data,';',7);
    tinhtrang3=getValue(data,';',8);// Tách phần tử thứ 8 theo ký tự phân cách ';'
  Firebase.setInt(firebaseData, "/SOLUONG_1", soluong1.toInt());
  Firebase.setInt(firebaseData, "/SOLUONG_2", soluong2.toInt());
  Firebase.setInt(firebaseData, "/SOLUONG_3", soluong3.toInt());
  Firebase.setInt(firebaseData, "/CHOTRONG_1", chotrong1.toInt());
  Firebase.setInt(firebaseData, "/CHOTRONG_2", chotrong2.toInt());
  Firebase.setInt(firebaseData, "/CHOTRONG_3", chotrong3.toInt());
  Firebase.setInt(firebaseData, "/TINHTRANG_1", tinhtrang1.toInt());
  Firebase.setInt(firebaseData, "/TINHTRANG_2", tinhtrang2.toInt());
  Firebase.setInt(firebaseData, "/TINHTRANG_3", tinhtrang3.toInt());
 
}
}

