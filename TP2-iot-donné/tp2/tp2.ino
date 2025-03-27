#include "DHT.h"
#define DHTPIN 26
#include "WiFi.h" // Librairie pour l'utilisation du WiFi
#include <HTTPClient.h> // Librairie pour le client http
#define DHTTYPE DHT11

const char* ssid="Kirikou";
const char* password="12345687";

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  Serial.println("");
  
  WiFi.mode(WIFI_STA); // Configurer en Station WiFi
 
  WiFi.disconnect(); 
   
  WiFi.begin(ssid,password); // Demande de connexion au réseau WiFi
  while(WiFi.status() != WL_CONNECTED)
    { Serial.println("Tentative de connexion...");
      delay(1000);
    }
    Serial.println("");
   Serial.println("Connecté au réseau WiFi !");
   Serial.println("");
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  Serial.begin(115200); // Pour afficher via la liaison série
  Serial.println("");
  }

  HTTPClient http;

 http.begin("http://api.openweathermap.org/data/2.5/weather?lat=43.43&lon=3.22&units=metric&APPID=bbe8de220dc94177c87706a77dd7d933");
 int HttpRetCode = http.GET();

 if(HttpRetCode > 0)
 {
  Serial.println("Données reçues...");
  String Contents = http.getString();
  Serial.println(HttpRetCode);
  Serial.println(Contents);
  http.end();
 }
 delay(5000);
  
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidité: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(F("  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(F("\n"));

}
