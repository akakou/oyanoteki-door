#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

int pir = 12;
const char* ssid     = "";
const char* password = "";
static WiFiUDP wifiUdp; 

void setup()
{
    pinMode(pir, INPUT);
    Serial.begin(9600);
    delay(10);
    
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
}


IPAddress ip;
String a,b,c,d;
void loop()
{
  if(digitalRead(pir)){
    Serial.println("ON");
    //IPアドレスをイイ感じにする
    ip = WiFi.localIP();
    a = ip[0];
    b = ip[1];
    c = ip[2];
    d = a + '.' + b + '.' + c + '.' + "255";
    Serial.println(d);

    
    //dをstring→charにする
    int d_length = d.length()+1;
    char IP[d_length];
    d.toCharArray(IP,d_length);

    
    //できたcharをぶち込む
    wifiUdp.beginPacket(IP,5000); 
    wifiUdp.write('a');
    wifiUdp.endPacket();  

    
  }else{
    Serial.println("Off");
    }
    Serial.println("END");
}
