#include <WiFi.h>
#include <Firebase_ESP_Client.h>

// WiFi
#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// Firebase
#define API_KEY "AIzaSyDTAas1droAkeShhrnvoJhDCc74uJQQhEA"
#define DATABASE_URL "https://esp32-parking-8feef-default-rtdb.firebaseio.com/"

// IR sensors
#define IR1 25
#define IR2 26
#define IR3 27

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

int last1 = -1, last2 = -1, last3 = -1;

void setup() {
  Serial.begin(115200);

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);

  // WiFi connect
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");

  // Firebase config
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  // Anonymous login (IMPORTANT FIX)
  auth.user.email = "";
  auth.user.password = "";

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {

  int s1 = (digitalRead(IR1) == LOW) ? 1 : 0;
  int s2 = (digitalRead(IR2) == LOW) ? 1 : 0;
  int s3 = (digitalRead(IR3) == LOW) ? 1 : 0;

  // 🔥 only send if changed (optimization)
  if (s1 != last1) {
    Firebase.RTDB.setInt(&fbdo, "/parking/slot1", s1);
    last1 = s1;
  }

  if (s2 != last2) {
    Firebase.RTDB.setInt(&fbdo, "/parking/slot2", s2);
    last2 = s2;
  }

  if (s3 != last3) {
    Firebase.RTDB.setInt(&fbdo, "/parking/slot3", s3);
    last3 = s3;
  }

  Serial.printf("S1:%d S2:%d S3:%d\n", s1, s2, s3);

  delay(1000);
}
