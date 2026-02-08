#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6gZK1ax2M"
#define BLYNK_TEMPLATE_NAME "soil moisture"
#define BLYNK_AUTH_TOKEN "u0LPdEnWGnbiEB2o4ySVyNYOXZJs1qln"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// WiFi
char ssid[] = "Home";
char pass[] = "567891234";

// Timer Blynk
BlynkTimer timer;

// Pin sensor
#define SOIL_PIN A0

int soilValue;
int soilPercent;

// =======================
// FUNGSI KIRIM DATA
// =======================
void sendSoilData() {
  soilValue = analogRead(SOIL_PIN);

  // Konversi ke persen (kalibrasi nanti)
  soilPercent = map(soilValue, 1023, 0, 0, 100);

  // Kirim ke Blynk
  Blynk.virtualWrite(V0, soilPercent);

  // Debug
  Serial.print("ADC: ");
  Serial.print(soilValue);
  Serial.print(" | Moisture: ");
  Serial.print(soilPercent);
  Serial.println("%");
}

// =======================
// SETUP
// =======================
void setup() {
  Serial.begin(9600);
  delay(1000); // beri waktu boot

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    yield();   // WAJIB agar WDT tidak reset
  }

  Blynk.config(BLYNK_AUTH_TOKEN);
  Blynk.connect();

  timer.setInterval(3000L, sendSoilData);

  Serial.println("ESP8266 Soil Moisture Monitoring");
}

// =======================
// LOOP
// =======================
void loop() {
  Blynk.run();
  timer.run();
}