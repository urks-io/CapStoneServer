#include <Adafruit_Sensor.h>



#include <DHT.h>
#include <DHT_U.h>
#define DHTTYPE DHT11   // DHT 11

#include "WiFi.h"
#include <WiFiUdp.h>  
#include <OSCMessage.h>


const char * ssid = "Greenhouse";
const char * password = "BigBoi69";

int sensorValue = 0;
int sensorPin = 22; //
#define dht_pin 22 
#define DHTPIN 22 
DHT dht(DHTPIN, DHTTYPE);

IPAddress outIp(75, 164, 38, 239); //public ip of the computer running max
const unsigned int outPort = 9999;
WiFiUDP Udp;

void setup(){
    Serial.begin(115200);
      dht.begin();
     delay(500);
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);
    WiFi.mode(WIFI_STA);
    Udp.begin(outPort);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop(){

    sensorValue = analogRead(sensorPin);
    
  // Serial.println("sensor = ");
//    Serial.println(sensorValue);
  //  DHT.read11(dht_pin);
    
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float urkstemp = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(urkstemp) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(sensorValue, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(urkstemp);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
    delay(1000); //Reduce Time for Quick Reply 
    OSCMessage msg("/urkstemp");
    msg.add(urkstemp);
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp); // send the bytes to the SLIP stream
    Udp.endPacket(); // mark the end of the OSC Packet
    msg.empty(); // free space occupied by message
    delay(2);

}
