int waterPump = 2;

void setup(){
    Serial.begin(9600);
    pinMode(waterPump, OUTPUT);
}

void loop(){
    int sensorValue = analogRead(A0);
    Serial.println(sensorValue);

    if (sensorValue > 350){
        digitalWrite(waterPump, LOW);
    }
    else{
        digitalWrite(waterPump, HIGH);
    }
    delay(100);
}