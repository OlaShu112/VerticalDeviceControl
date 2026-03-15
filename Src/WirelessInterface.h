#ifndef WIRELESS_INTERFACE_H
#define WIRELESS_INTERFACE_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

// Replace with your Wi-Fi credentials
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

class WirelessInterface {
private:
    WiFiServer server;
    WiFiClient client;
    String lastCommand;  // Stores the last received command

public:
    // Constructor: initialize Wi-Fi server on port 80
    WirelessInterface() : server(80), lastCommand("") {}

    // Initialize Wi-Fi and start server
    void begin() {
        Serial.println("Connecting to Wi-Fi...");
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("\nWi-Fi connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());

        server.begin();
        Serial.println("Server started on port 80");
    }

    // Check if a new command has been received
    bool available() {
        if (!client || !client.connected()) {
            client = server.available();
        }

        if (client && client.connected() && client.available()) {
            lastCommand = client.readStringUntil('\n');
            lastCommand.trim();  // Remove extra spaces/newlines
            Serial.print("Received command: ");
            Serial.println(lastCommand);
            return true;
        }
        return false;
    }

    // Get the last received command
    String readCommand() {
        return lastCommand;
    }

    // Send status string to connected client
    void sendStatus(String status) {
        if (client && client.connected()) {
            client.println(status);
            client.flush();
            Serial.print("Sent status: ");
            Serial.println(status);
        }
    }
};

#endif