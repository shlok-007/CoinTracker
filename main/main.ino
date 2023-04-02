#include <Wire.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF
#define BROWN   0xFB00
#define DARKBROWN 0x8041

TFT_ILI9163C display = TFT_ILI9163C(10, 8, 9);

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Replace with your Coin Gecko API key
const char* api_key = "your_API_KEY";

// Set the Crypto ID (you can find it in the Coin Gecko API documentation)
const char* crypto_id = "bitcoin";

// Set the API endpoint
const char* api_endpoint = "/coins/markets?vs_currency=usd&ids=";

void setup() {
  Serial.begin(115200);
  delay(100);

  // Connect to Wi-Fi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Failed to initialize OLED display.");
    while (1);
  }

  // Clear the display buffer
  display.clearDisplay();

  // Set the text size and color
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // Set the cursor position
  display.setCursor(0, 0);
}

void loop() {
  // Create a secure client to connect to the Coin Gecko API
  WiFiClientSecure client;
  client.setInsecure();

  // Connect to the Coin Gecko API
  if (!client.connect("api.coingecko.com", 443)) {
    Serial.println("Connection failed.");
    return;
  }

  // Build the API URL
  String url = String(api_endpoint) + String(crypto_id);

  // Send the HTTP request
  client.println(String("GET ") + url + " HTTP/1.1");
  client.println(String("Host: ") + "api.coingecko.com");
  client.println(String("Connection: close"));
  client.println(String("X-CoinAPI-Key: ") + api_key);
  client.println();

  // Wait for the response
  while (!client.available());

  // Read the response into a string
  String response = client.readString();

  // Parse the JSON data
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, response);

  if (error) {
    Serial.println("Failed to parse JSON data.");
    return;
  }

  // Extract the relevant data from the JSON document
  float price = doc[0]["current_price"];

  // Display the data on the OLED display
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Bitcoin Price:");
  display.print("$");
  display.println(price, 2);
  display.display();

  // Wait for 5 seconds before updating the display
  delay(1500);
}
