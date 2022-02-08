#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <DHT.h>




float humidityData;
float temperatureData;


const char* ssid = "ssid Name";// 
const char* password = "ssid pass";
//WiFiClient client;
char server[] = "Your Local IP";   //eg: 192.168.0.222
const char* serverName = "url-to-store-data-to-sql.php";
String apiKeyValue = "apiKeyValue";
String sensorName = "DHT22";
String sensorLocation = "sensorLocation";


#define DHTPIN 5

#define DHTTYPE DHT22

DHT dht(DHTPIN,DHTTYPE);

WiFiClient client;    


void setup()
{
 Serial.begin(115200);
  delay(10);
  dht.begin();
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
//  server.begin();
  Serial.println("Server started");
  Serial.print(WiFi.localIP());
  delay(1000);
  Serial.println("connecting...");
 }
void loop()
{ if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
  // Your Domain name with URL path or IP address with path
    http.begin(serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName
                          + "&location=" + sensorLocation + "&value1=" + String(dht.readTemperature())
                          + "&value2=" + String( dht.readHumidity()) + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    int httpResponseCode = http.POST(httpRequestData);
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }


    
  
  humidityData = dht.readHumidity();
  temperatureData = dht.readTemperature(); 
  delay(900000); // interval
 }
