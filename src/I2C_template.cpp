#include <Arduino.h>
#include <Wire.h>

// ESP32-C6 Xiao Form Factor I2C Pins: SDA = GPIO 5, SCL = GPIO 6
// DO NOT CHANGE THESE - Xiao form factor is hardwired to these pins
#define I2C_SDA 5
#define I2C_SCL 6

void scanI2CBus() {
    byte error, address;
    int nDevices = 0;

    Serial.println("\n--- Scanning I2C Bus ---");

    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            Serial.print("I2C device found at address 0x");
            if (address < 16) Serial.print("0");
            Serial.print(address, HEX);
            Serial.println("  !");
            nDevices++;
        } else if (error == 4) {
            Serial.print("Unknown error at address 0x");
            if (address < 16) Serial.print("0");
            Serial.println(address, HEX);
        }
    }

    if (nDevices == 0) {
        Serial.println("No I2C devices found. Check your wiring (SDA/SCL) and Power!\n");
    } else {
        Serial.println("Scan complete.\n");
    }
}

void setup() {
    // Standard Baud Rate for ESP32
    Serial.begin(115200);
    while (!Serial); // Wait for Serial Monitor to open

    Serial.println("IoT Node Initializing...");

    // Initialize I2C with specific pins
    Wire.begin(I2C_SDA, I2C_SCL);

    // Run the scanner immediately to verify hardware
    scanI2CBus();

    // --- SENSOR INITIALIZATION BLOCK ---
    // BME680 (your I2C sensor) initialization:
    // #include <Adafruit_BME680.h>
    // Adafruit_BME680 bme;
    // if (!bme.begin(0x76)) { Serial.println("BME680 Not Found"); }
    // if (!bme.performReading()) { Serial.println("BME680 reading failed"); }
}

void loop() {
    // --- DATA COLLECTION BLOCK ---
    // Record environmental measurements here.
    
    Serial.println("Reading sensors...");
    
    // Placeholder for your data logic
    float temp = 25.0; // Replace with actual sensor read
    float humidity = 50.0;

    Serial.print("Temp: "); Serial.print(temp); Serial.println(" C");
    Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");

    // --- TRANSMISSION BLOCK ---
    // This is where you'll call your ThingSpeak upload function.

    delay(15000); // ThingSpeak free tier requires 15s between updates
}