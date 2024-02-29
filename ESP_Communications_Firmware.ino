/*******************************************************************
 * Title: ESP_Communictations_Firmware
 * Author: Sebastian Barney
 * Version: 1.0
 * Date: 2024-02-27
 *
 * Description:
 * This program is the basic firmware for the ESP32 in the Robit.
 ******************************************************************/





#include <Wifi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <.env.h>



WebServer server(80);

//Starts the ESP32 as a Web Server.
void startWebServer(){

    WiFi.begin(SSID, Password);
    Serial.println("Connecting to Wifi...");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    if (!MDNS.begin(host)) {
        Serial.println("Error setting up MDNS responder!");
        while (1) {
            delay(1000);
        }
    }

    Serial.println("mDNS responder started");

  // Setup route to login page
    server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", loginIndex);
    });

  // Setup route to server index page
    server.on("/serverIndex", HTTP_GET, []() {
        server.sendHeader("Connection", "close");
        server.send(200, "text/html", serverIndex);
    });


    server.begin();
}
void setup() {

    //Initializes the Serial output to 115200.
    Serial.begin(115200);

    //Starts the WebServer.
    startWebServer();


}