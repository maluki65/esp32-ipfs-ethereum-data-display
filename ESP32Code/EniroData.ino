#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// WiFi credentials
const char* ssid = "yourSSID";
const char* password = "yourPassword";

// Pinata API credentials and endpoint
const char* pinataUrl = "https://api.pinata.cloud/pinning/pinJSONToIPFS";
const char* pinataApiKey = "yourPinataAPIKey";
const char* pinataSecretKey = "yourPinataSecretKey";

// DHT22 setup
#define DHTPIN 4       // Pin where the DHT22 is connected
#define DHTTYPE DHT22  // DHT 22 type
DHT dht(DHTPIN, DHTTYPE);

// GPS setup
TinyGPSPlus gps;
SoftwareSerial gpsSerial(16, 17); // RX, TX (Adjust pins as per your ESP32 wiring)

void setup() {
    Serial.begin(115200); // Start Serial Monitor
    gpsSerial.begin(9600); // Start GPS module communication
    dht.begin();           // Initialize DHT sensor

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi!");
}

void loop() {
    // Read data from the DHT22 sensor
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Ensure valid sensor readings
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        delay(1000);
        return;
    }

    // Read GPS data
    String location = "0.0,0.0"; // Default value in case no GPS data is available
    while (gpsSerial.available() > 0) {
        if (gps.encode(gpsSerial.read())) {
            if (gps.location.isUpdated()) {
                location = String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
            }
        }
    }

    // Display the sensor readings
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("Humidity: ");
    Serial.println(humidity);
    Serial.print("Location: ");
    Serial.println(location);

    // Check WiFi connection before sending data
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        // Begin HTTP POST request to the Pinata API
        http.begin(pinataUrl);
        http.addHeader("Content-Type", "application/json");
        http.addHeader("pinata_api_key", pinataApiKey);
        http.addHeader("pinata_secret_api_key", pinataSecretKey);

        // Create JSON payload
        String jsonData = "{\"temperature\":" + String(temperature) +
                          ",\"humidity\":" + String(humidity) +
                          ",\"location\":\"" + location + "\"}";

        // Send POST request
        int httpResponseCode = http.POST(jsonData);

        // Handle HTTP response
        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println("Response from Pinata:");
            Serial.println(response);
        } else {
            Serial.print("Error on sending POST, HTTP response code: ");
            Serial.println(httpResponseCode);
        }

        http.end(); // Close HTTP connection
    } else {
        Serial.println("WiFi not connected, skipping HTTP request...");
    }

    delay(60000); // Wait for one minute before sending the next request
}


//With mock data 
/*#include <WiFi.h>
#include <HTTPClient.h>

// WiFi credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

// Pinata API credentials
const char* pinataApiKey = "your_pinata_api_key";
const char* pinataApiSecret = "your_pinata_api_secret";

// Pinata endpoint for pinning JSON to IPFS
const char* pinataUrl = "https://api.pinata.cloud/pinning/pinJSONToIPFS";

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Mock data
    float humidity = 60.5;  // Example humidity in %
    float temperature = 24.7;  // Example temperature in °C
    String gpsLocation = "1.2921° S, 36.8219° E";  // Example GPS location (latitude, longitude)

    // Create JSON payload
    String jsonPayload = "{";
    jsonPayload += "\"pinataOptions\": {},";
    jsonPayload += "\"pinataContent\": {";
    jsonPayload += "\"humidity\": " + String(humidity) + ",";
    jsonPayload += "\"temperature\": " + String(temperature) + ",";
    jsonPayload += "\"gps\": \"" + gpsLocation + "\"";
    jsonPayload += "}";
    jsonPayload += "}";

    // Send data to Pinata
    if (sendDataToPinata(jsonPayload)) {
      Serial.println("Data uploaded to IPFS successfully!");
    } else {
      Serial.println("Failed to upload data to IPFS.");
    }
  } else {
    Serial.println("WiFi disconnected!");
  }

  delay(60000);  // Send data every 60 seconds
}

bool sendDataToPinata(String payload) {
  HTTPClient http;

  // Set up HTTP POST request
  http.begin(pinataUrl);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("pinata_api_key", pinataApiKey);
  http.addHeader("pinata_secret_api_key", pinataApiSecret);

  // Send the request
  int httpResponseCode = http.POST(payload);

  // Process the response
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Response from Pinata:");
    Serial.println(response);
    http.end();
    return true;
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    http.end();
    return false;
  }
}*/
