#include <Arduino.h>

// ESP32 ADC1 Pins (safe to use during WiFi operation):
// GPIO32, GPIO33, GPIO34, GPIO35, GPIO36, GPIO37, GPIO38, GPIO39
// ADC1_0=GPIO36, ADC1_3=GPIO39, ADC1_4=GPIO32, ADC1_5=GPIO33, ADC1_6=GPIO34, ADC1_7=GPIO35
#define ANALOG_PIN 34  // GPIO34 (ADC1_6) - Change this to your sensor pin

// ADC Resolution: 12-bit = 0-4095, 3.3V reference on ESP32
#define ADC_MAX_VALUE 4095
#define ESP32_VREF 3.3

void readAnalogSensor() {
    int rawValue = analogRead(ANALOG_PIN);
    
    // Convert raw ADC value to voltage
    float voltage = (rawValue / (float)ADC_MAX_VALUE) * ESP32_VREF;
    
    Serial.print("Raw ADC: ");
    Serial.print(rawValue);
    Serial.print(" (0-4095) | Voltage: ");
    Serial.print(voltage, 2);
    Serial.println(" V");
}

void setup() {
    Serial.begin(115200);
    while (!Serial); // Wait for Serial Monitor to open
    
    Serial.println("ADC Node Initializing...");
    
    // Set ADC resolution (default is 12-bit)
    analogReadResolution(12);
    
    Serial.println("ADC ready on GPIO34");
}

void loop() {
    readAnalogSensor();
    delay(1000); // Read every 1 second
}
