#include <Arduino.h>
#include <WiFi.h>

// --- WiFi Credentials ---
// FILL THESE IN ON COMPETITION DAY
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// WiFi status tracking
bool wifiConnected = false;
unsigned long lastWiFiCheck = 0;
const unsigned long WIFI_CHECK_INTERVAL = 30000; // Check every 30 seconds

void connectToWiFi() {
    Serial.println("\n--- Attempting WiFi Connection ---");
    Serial.print("Connecting to SSID: ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    int attempts = 0;
    int maxAttempts = 20; // 10 seconds timeout (500ms per attempt)

    while (WiFi.status() != WL_CONNECTED && attempts < maxAttempts) {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n✓ WiFi Connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        Serial.print("Signal Strength: ");
        Serial.print(WiFi.RSSI());
        Serial.println(" dBm");
        wifiConnected = true;
    } else {
        Serial.println("\n✗ WiFi Connection Failed");
        Serial.print("Status Code: ");
        Serial.println(WiFi.status());
        wifiConnected = false;
    }
}

void maintainWiFiConnection() {
    // Check WiFi status periodically, reconnect if needed
    unsigned long now = millis();
    
    if (now - lastWiFiCheck >= WIFI_CHECK_INTERVAL) {
        lastWiFiCheck = now;
        
        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("\n⚠ WiFi Connection Lost - Reconnecting...");
            connectToWiFi();
        }
    }
}

bool isWiFiConnected() {
    return (WiFi.status() == WL_CONNECTED);
}

void setup() {
    Serial.begin(115200);
    while (!Serial); // Wait for Serial Monitor to open

    Serial.println("IoT WiFi Node Initializing...");

    // Attempt initial WiFi connection
    connectToWiFi();
}

void loop() {
    // Keep WiFi alive
    maintainWiFiConnection();

    // --- DATA TRANSMISSION BLOCK ---
    // This is where you'll upload to ThingSpeak
    // Example pattern:
    // if (isWiFiConnected()) {
    //     thingspeak.setField(1, temp_value);
    //     thingspeak.writeFields();
    // } else {
    //     Serial.println("Cannot upload - WiFi offline");
    // }

    delay(1000);
}
