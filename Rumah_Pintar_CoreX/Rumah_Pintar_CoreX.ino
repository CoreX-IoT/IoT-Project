/*
URL Project: https://github.com/CoreX-IoT/IoT-Project/tree/production/Rumah_Pintar_CoreX
Autor: Duwipangga
Page: https://corex.id/project/Rumah_pintar_coreX
Tutorial: https://blog.corex.id/membuat-smart-home-menggunakan-corex
*/

#include <CoreX.h>
#include <DHT.h>
#include "Connection.h"
#define DHTTYPE DHT22
#define R1 2
#define R2 0
#define R3 16
#define R4 17
#define pinData 4

int temperature;
int humidity;

const char* AUTH_TOKEN = "LLmOwlLhF9RpS1S";
const char* DEVICE_ID = "o6XnDS6TK";

const char ssid[] = "Wokwi-GUEST";
const char pass[] = "";
CoreXTimer timer; 

DHT dht(pinData,DHTTYPE); 

void receive(String &bucket, String &data) {
    if(data=="R1-1"){digitalWrite(R1,1);} 
    else if(data=="R1-0"){digitalWrite(R1,0);}
    else if(data=="R2-1"){digitalWrite(R2,1);}
    else if(data=="R2-0"){digitalWrite(R2,0);}
    else if(data=="R3-1"){digitalWrite(R3,1);}
    else if(data=="R3-0"){digitalWrite(R3,0);}
    else if(data=="R4-1"){digitalWrite(R4,1);}
    else if(data=="R4-0"){digitalWrite(R4,0);}
}

void send() {
  corex.send("KELEMBABAN", String(humidity));     // send data kelembaban ke bucket "kelembaban".
  corex.send("SUHU", String(temperature));     // send data temperatur ke bucket "temperatur".
}

void setup() {
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);

  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  corex.begin(net);
  dht.begin();
  corex.onMessage(receive);       // Lakukan receive pada fungsi receive().

  timer.setInterval(3000, send);     // Lakukan send setiap 3000 milidetik.

  setupCoreX();
}

void loop() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  timer.run();

  corex.loop();
  // Periksa apakah perangkat masih terhubung.
  if (!corex.connected()) {
    setupCoreX();
  }

  //==LETAKAN KODE PROGRAM DISINI UNTUK DILAKUKAN PROSES==//
}
