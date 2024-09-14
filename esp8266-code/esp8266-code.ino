// Code NodeMCU ESP8266 V.3 Lolin ShieldBase

#include "DHT.h"
#include <ESP8266WiFi.h>
#include <WifiClient.h>
#include <ThingSpeak.h>

#define trigPin D6
#define echoPin D7
#define DHTPIN D8
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

int soilPin = A0;
int rainPin = D4;

const char* ssid = "Veendy-Suseno";
const char* password = "Admin12345";

WiFiClient client;
unsigned long myChannelNumber = 796481;
const char* myWriteAPIKey = "S3CO1YQPOTQCJURV";

void setup(){
    Serial.begin(9600);
    dht.begin();
    pinMode(soilPin, INPUT);
    pinMode(rainPin, INPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    delay(10);

    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi Connected");
    // Print the IP Address
    Serial.println(WiFi.localIP());
    ThingSpeak.begin(client);
}

void loop(){
    int temperatureValue = dht.readTemperature();
    int humidityValue = dht.readHumidity();
    int soilValue = analogRead(soilPin);
    int soilMoistureValue = (100 - ((soilValue / 1023.00) * 100));
    int rainValue = digitalRead(rainPin);

    long duration, distanceValue;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distanceValue = ((duration / 2) / 29.1);

    Serial.print("Air Temperature = ");
    Serial.print(temperatureValue);
    Serial.print(" C");
    Serial.print(" Air Humidity = ");
    Serial.print(humidityValue);
    Serial.print(" % RH");
    Serial.print(" Soil-Moisture = ");
    Serial.print(soilMoistureValue);
    Serial.print(" %");
    Serial.print(" Soil Value = ");
    Serial.println(soilValue);
    Serial.print("Weather Conditions = ");
    Serial.println(rainValue);
    Serial.print("Water Status = ");
    Serial.println(distanceValue);

    ThingSpeak.setField(1, temperatureValue);
    ThingSpeak.setField(2, humidityValue);
    ThingSpeak.setField(3, soilMoistureValue);
    ThingSpeak.setField(4, rainValue);
    ThingSpeak.setField(5, distanceValue);
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    delay(15000); // 15 seconds default ThingSpeak Free
}
