#include <ArduinoJson.h>

// Wifi
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

WiFiClient client;
HTTPClient http;
#define USE_SERIAL Serial

String urlSimpan = "http://192.168.22.25/uas_mm2/data/simpan?tinggiAir=";

String respon, statusSimpan, kontrolRelay;

#define WIFI_SSID "Bas"
#define WIFI_PASSWORD "12345678"

// Sensor Ultrasonik
#define echoPin D1
#define trigPin D2

int tinggiBendungan = 20, tinggiAir = 0, tinggiLimpasan = 0;

#define pinPompa D5
#define relay_off HIGH
#define relay_on LOW

void setup() {
  Serial.begin(115200);

  USE_SERIAL.begin(115200);
  USE_SERIAL.setDebugOutput(false);

  for(uint8_t t = 4; t > 0; t--) {
      USE_SERIAL.printf("[SETUP] Tunggu %d...\n", t);
      USE_SERIAL.flush();
      delay(1000);
  }

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  pinMode(pinPompa, OUTPUT);
  digitalWrite(pinPompa, relay_off);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  for (int u = 1; u <= 5; u++)
  {
    if ((WiFiMulti.run() == WL_CONNECTED))
    {
      USE_SERIAL.println("Terhubung ke wifi");
      USE_SERIAL.flush();
      delay(1000);
    }
    else
    {
      Serial.println("Wifi belum terhubung");
      delay(1000);
    }
  }

  delay(1000);
}

void loop() {
  int durasi, jarak;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durasi = pulseIn(echoPin, HIGH);
  jarak = (durasi / 2) / 29.1;

  if (jarak < 0) {
    jarak = 0;
  }

  tinggiAir = tinggiBendungan - jarak;
  tinggiLimpasan = tinggiAir - 8;

  Serial.print("Tinggi air : ");
  Serial.print(tinggiAir);
  Serial.println(" cm");

  Serial.print("Tinggi limpasan air : ");
  Serial.print(tinggiLimpasan);
  Serial.println(" cm");

  Serial.println();
    
  kirimDatabase();

  if (kontrolRelay == "ON") {
    Serial.println("Pompa menyala");
    digitalWrite(pinPompa, relay_on);
  } else {
    Serial.println("Pompa mati");
    digitalWrite(pinPompa, relay_off);
  }

  Serial.println();
  delay(1000);
}

void kirimDatabase() {
  if ((WiFiMulti.run() == WL_CONNECTED))
  {
    USE_SERIAL.print("[HTTP] Memulai...\n");
    
    http.begin( urlSimpan + (String) tinggiAir + "&tinggiLimpasan=" + (String) tinggiLimpasan );
    
    USE_SERIAL.print("[HTTP] Kirim data ke database ...\n");
    int httpCode = http.GET();

    if(httpCode > 0)
    {
      USE_SERIAL.printf("[HTTP] kode response GET : %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) // kode 200 
      {
        respon = http.getString();
        USE_SERIAL.println("Respon : " + respon);
        Serial.println();
        delay(200);

        int str_len = respon.length() + 1;
        char json[str_len];
        
        respon.toCharArray(json, str_len);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, json);
      
        String stsSmp = doc["status"];
        String kontrol = doc["alamat"];

        statusSimpan = stsSmp;
        kontrolRelay = kontrol;

        Serial.println("Status kirim data : " + statusSimpan);
        Serial.println("Kontrol relay : " + kontrolRelay);

        Serial.println();
      }
    }
    else
    {
      USE_SERIAL.printf("[HTTP] GET kirim data gagal, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}
