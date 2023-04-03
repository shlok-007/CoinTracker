#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>  // Library used for parsing Json from the API responses
#include <SPI.h>
#include <TFT_eSPI.h>

#define BLACK 0X0000
#define WHITE 0xFFFF

char ssid[] = "BEAST_OP";       // network SSID (name)
char password[] = "Shlok@*!))";  // network key

WiFiClientSecure client;    // Create a WiFi client object

// Just the base of the URL you want to connect to
#define TEST_HOST "api.coingecko.com"

// #define TEST_HOST_FINGERPRINT "B3 DD 76 06 D2 B5 A8 B4 A1 37 71 DB EC C9 EE 1C EC AF A3 8A"  //    SHA-1
#define TEST_HOST_FINGERPRINT "3A BB E6 3D AF 75 6C 50 16 B6 B8 5F 52 01 5F D8 E8 AC BE 27 7C 50 87 B1 27 A6 05 63 A8 41 ED 8A"  //    SHA-256

TFT_eSPI display = TFT_eSPI();


void setup() {


  display.init();

  display.setRotation(6);
  display.fillScreen(BLACK);
  display.fillRect(2, 1, 128, 128, BLACK);


  Serial.begin(115200);

  // Connect to the WiFI
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  // Serial.print("Connecting Wifi: ");
  // Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    // Serial.print(".");
    delay(500);
  }
  // Serial.println("");
  // Serial.println("WiFi connected");
  // Serial.println("IP address: ");
  // IPAddress ip = WiFi.localIP();
  // Serial.println(ip);

  //--------

  // client.setFingerprint(TEST_HOST_FINGERPRINT);
  client.setInsecure(); //Fingerprint wasn't able to be verified so, we removed the check

  DynamicJsonDocument doc(192) ;
  doc = makeHTTPRequest();

  // infoScreen( doc, display, "Bitcoin" );
  // Serial.println(doc["market_data"]["current_price"]["usd"]);
  // String temp1 = doc["market_data"];
  // float temp1 = doc["market_data"]["price_change_percentage_24h_in_currency"]["usd"];
  // float temp1 = doc['community_score'];
  // float temp1 = doc[0]["current_price"];
  // float temp2 = doc[0]["price_change_percentage_24h"];
  // String id = doc[0]["id"];
  float pr = doc["bitcoin"]["usd"];
  float cap = doc["bitcoin"]["usd_24h_vol"];
  // Serial.println(id);
  Serial.println(pr);
  Serial.println(cap);
  // Serial.println(typeof(doc["market_data"]["current_price"]["usd"]));
  // Serial.println(doc);



  // float ethereum_usd = doc["ethereum"]["usd"]; // 3961.66
  // float ethereum_eur = doc["ethereum"]["eur"]; // 3261.73

  // long bitcoin_usd = doc["bitcoin"]["usd"]; // 48924
  // long bitcoin_eur = doc["bitcoin"]["eur"]; // 40281

  // Serial.print("ethereum_usd: ");
  // Serial.println(ethereum_usd);
  // Serial.print("ethereum_eur: ");
  // Serial.println(ethereum_eur);

  // Serial.print("bitcoin_usd: ");
  // Serial.println(bitcoin_usd);
  // Serial.print("bitcoin_eur: ");
  // Serial.println(bitcoin_eur);
}

DynamicJsonDocument makeHTTPRequest() {

  DynamicJsonDocument doc(192);
  // Opening connection to server
  if (!client.connect(TEST_HOST, 443))
  {
    // Serial.println(F("Connection failed"));
    return doc;
  }

  yield();

  // Send HTTP request
  client.print(F("GET "));
  // This is the second half of a request (everything that comes after the base URL)
  // client.print("/api/v3/coins/bitcoin?localization=false&tickers=false&market_data=true&community_data=false&developer_data=false&sparkline=false");
  client.print("/api/v3/simple/price?ids=bitcoin&vs_currencies=usd&include_market_cap=true&include_24hr_vol=true&include_24hr_change=true");
  // client.print("/api/v3/simple/price?ids=ethereum%2Cbitcoin&vs_currencies=usd%2Ceur");
  
  client.println(F(" HTTP/1.1"));

  //Headers
  client.print(F("Host: "));
  client.println(TEST_HOST);

  client.println(F("Cache-Control: no-cache"));

  if (client.println() == 0)
  {
    // Serial.println(F("Failed to send request"));
    return doc;
  }
  // delay(100);

  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0)
  {
    // Serial.print(F("Unexpected response: "));
    // Serial.println(status);
    return doc;
  }

  // Skiping HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders))
  {
    // Serial.println(F("Invalid response"));
    return doc;
  }

  //to ignore random characters before the json
  while (client.available() && client.peek() != '{')
  {
    char c = 0;
    client.readBytes(&c, 1);
    // Serial.print(c);
    // Serial.println("BAD");
  }

  // DynamicJsonDocument doc(192);

  DeserializationError error = deserializeJson(doc, client);

  if (!error) return doc; 
  
  else {
    // Serial.print(F("deserializeJson() failed: "));
    // Serial.println(error.f_str());
    return doc;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}