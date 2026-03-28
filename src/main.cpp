#include <Arduino.h>

#define LED_PIN 21 // Xiao ESP32-C6 form factor LED pin

void setup() {
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(115200);
}

void loop() {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED ON - System Ready");
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED OFF");
    delay(1000);
}