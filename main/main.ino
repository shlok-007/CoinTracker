#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>  // Library used for parsing Json from the API responses
#include <SPI.h>
#include <TFT_eSPI.h>

char ssid[] = "BEAST_OP";       // network SSID (name)
char password[] = "Shlok@*!))";  // network key

WiFiClientSecure client;    // Create a WiFi client object

// Just the base of the URL you want to connect to
#define TEST_HOST "api.coingecko.com"

// #define TEST_HOST_FINGERPRINT "B3 DD 76 06 D2 B5 A8 B4 A1 37 71 DB EC C9 EE 1C EC AF A3 8A"  //    SHA-1
#define TEST_HOST_FINGERPRINT "3A BB E6 3D AF 75 6C 50 16 B6 B8 5F 52 01 5F D8 E8 AC BE 27 7C 50 87 B1 27 A6 05 63 A8 41 ED 8A"  //    SHA-256


void setup() {

  Serial.begin(115200);

  // Connect to the WiFI
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  //--------

  // client.setFingerprint(TEST_HOST_FINGERPRINT);
  client.setInsecure(); //Fingerprint wasn't able to be verified so, we removed the check

  DynamicJsonDocument doc = makeHTTPRequest();

  float ethereum_usd = doc["ethereum"]["usd"]; // 3961.66
  float ethereum_eur = doc["ethereum"]["eur"]; // 3261.73

  long bitcoin_usd = doc["bitcoin"]["usd"]; // 48924
  long bitcoin_eur = doc["bitcoin"]["eur"]; // 40281

  Serial.print("ethereum_usd: ");
  Serial.println(ethereum_usd);
  Serial.print("ethereum_eur: ");
  Serial.println(ethereum_eur);

  Serial.print("bitcoin_usd: ");
  Serial.println(bitcoin_usd);
  Serial.print("bitcoin_eur: ");
  Serial.println(bitcoin_eur);
}

DynamicJsonDocument makeHTTPRequest() {

  // Opening connection to server
  if (!client.connect(TEST_HOST, 443))
  {
    Serial.println(F("Connection failed"));
    return;
  }

  yield();

  // Send HTTP request
  client.print(F("GET "));
  // This is the second half of a request (everything that comes after the base URL)
  client.print("/api/v3/simple/price?ids=ethereum%2Cbitcoin&vs_currencies=usd%2Ceur");
  client.println(F(" HTTP/1.1"));

  //Headers
  client.print(F("Host: "));
  client.println(TEST_HOST);

  client.println(F("Cache-Control: no-cache"));

  if (client.println() == 0)
  {
    Serial.println(F("Failed to send request"));
    return;
  }
  // delay(100);

  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0)
  {
    Serial.print(F("Unexpected response: "));
    Serial.println(status);
    return;
  }

  // Skiping HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders))
  {
    Serial.println(F("Invalid response"));
    return;
  }

  //to ignore random characters before the json
  while (client.available() && client.peek() != '{')
  {
    char c = 0;
    client.readBytes(&c, 1);
    Serial.print(c);
    Serial.println("BAD");
  }

  DynamicJsonDocument doc(192);

  DeserializationError error = deserializeJson(doc, client);

  if (!error) return doc; 
  
  else {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return doc;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}