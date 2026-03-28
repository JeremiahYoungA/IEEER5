#include <Arduino.h>

// ESP32-C6 Xiao ADC1 Pins (safe to use during WiFi operation):
// GPIO0, GPIO1, GPIO2, GPIO3, GPIO4, GPIO5, GPIO6, GPIO7, GPIO8, GPIO9
// Your available pins on Xiao: GPIO0-4 and GPIO8-9 (5 & 6 used by I2C)
// Analog Sensors on Your Board:
//   INA169 current sensor → Pick an ADC pin (GPIO0-4 recommended)
//   SPW2430 microphone → Pick an ADC pin (GPIO0-4 recommended)  
//   CO Sensor → Pick an ADC pin (GPIO0-4 recommended)
#define ANALOG_PIN 0  // GPIO0 (ADC1_0) - Change to your actual sensor pin

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
