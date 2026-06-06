#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Ultrasonic.h>
#include <Servo.h>

/************ WiFi ************/
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

/************ MQTT ************/
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

/************ Pins (ESP8266) ************/
#define TRIG_PIN   D5
#define ECHO_PIN   D6

#define RED_LED    D1
#define GREEN_LED  D2
#define BLUE_LED   D3

#define SERVO_PIN  D7
#define BUTTON_PIN D0

#define LDR_PIN    A0

#define LIGHT1     D8
#define LIGHT2     D4

#define MAX_CARS 5
#define DETECTION_DISTANCE 20

/************ Objects ************/
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);
Servo gateServo;

/************ Variables ************/
uint8_t carsInParking = 0;
uint16_t blockedCars = 0;
bool vehicleDetected = false;
unsigned long lastPublish = 0;

/************ WiFi ************/
void setupWifi()
{
  delay(10);
  Serial.println("Connecting WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());
}

/************ MQTT ************/
void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Topic: ");
  Serial.println(topic);
}

void reconnectMQTT()
{
  while (!client.connected())
  {
    String clientId = "ESP8266-Parking-";
    clientId += String(random(1000));

    if (client.connect(clientId.c_str()))
    {
      Serial.println("MQTT connected");
    }
    else
    {
      delay(3000);
    }
  }
}

/************ Publish ************/
void publishData()
{
  client.publish("parking/cars", String(carsInParking).c_str(), true);
  client.publish("parking/blocked", String(blockedCars).c_str(), true);
}

/************ Gate ************/
void openGate()
{
  digitalWrite(BLUE_LED, HIGH);
  gateServo.write(180);
  delay(2500);
  gateServo.write(90);
  digitalWrite(BLUE_LED, LOW);
}

/************ Lights ************/
void updateLights()
{
  int ldrValue = analogRead(LDR_PIN);
  int lightPercent = map(ldrValue, 1023, 0, 100, 0);

  if (lightPercent < 80)
  {
    digitalWrite(LIGHT1, HIGH);
    digitalWrite(LIGHT2, HIGH);
  }
  else
  {
    digitalWrite(LIGHT1, LOW);
    digitalWrite(LIGHT2, LOW);
  }
}

/************ Entry ************/
void processEntry()
{
  if (carsInParking >= MAX_CARS)
  {
    blockedCars++;
    publishData();

    for (int i = 0; i < 6; i++)
    {
      digitalWrite(RED_LED, !digitalRead(RED_LED));
      delay(300);
    }

    digitalWrite(RED_LED, HIGH);
    return;
  }

  carsInParking++;
  publishData();

  digitalWrite(GREEN_LED, HIGH);
  openGate();
  digitalWrite(GREEN_LED, LOW);

  Serial.println("Car Entered");
}

/************ Exit ************/
void processExit()
{
  if (carsInParking > 0)
  {
    carsInParking--;
    publishData();
    openGate();
    Serial.println("Car Left");
  }
}

/************ Setup ************/
void setup()
{
  Serial.begin(115200);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  pinMode(LIGHT1, OUTPUT);
  pinMode(LIGHT2, OUTPUT);

  pinMode(BUTTON_PIN, INPUT);

  gateServo.attach(SERVO_PIN);
  gateServo.write(90);

  setupWifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  digitalWrite(RED_LED, HIGH);
}

/************ Loop ************/
void loop()
{
  if (!client.connected())
    reconnectMQTT();

  client.loop();

  updateLights();

  // EXIT button
  if (digitalRead(BUTTON_PIN) == HIGH)
  {
    delay(50);
    if (digitalRead(BUTTON_PIN) == HIGH)
    {
      processExit();
      while (digitalRead(BUTTON_PIN));
    }
  }

  int distance = ultrasonic.read();

  if (distance < DETECTION_DISTANCE && !vehicleDetected)
  {
    vehicleDetected = true;
    processEntry();
  }

  if (distance > 30)
  {
    vehicleDetected = false;
  }

  if (millis() - lastPublish > 10000)
  {
    lastPublish = millis();
    publishData();
  }
}
