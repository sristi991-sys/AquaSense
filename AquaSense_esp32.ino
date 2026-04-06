#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// Your existing defines
#define WIFI_SSID "wifi name"
#define WIFI_PASSWORD "passsword"
#define API_KEY "AIzaSyCvzCLr0pLdT2-W4vcRUavuA2tZWR2rkqo"
#define DATABASE_URL "https://aquasense-d8d8f-default-rtdb.asia-southeast1.firebasedatabase.app/"

#define PH_PIN        35
#define TDS_PIN       34
#define TURBIDITY_PIN 32

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Timing
unsigned long sendDataPrevMillis = 0;
const long interval = 5000; // Send every 5 seconds
bool signupOK = false;

// Calibration values (adjust these for your sensors)
#define VREF          3.3
#define ADC_RESOLUTION 4096.0

// TDS calibration
#define TDS_FACTOR    0.7

// pH calibration (adjust based on your sensor)
#define PH_OFFSET     0.0

// ─── Sensor Reading Functions ───────────────────────────────────────

float readPH() {
  int rawValue = 0;
  for (int i = 0; i < 10; i++) {
    rawValue += analogRead(PH_PIN);
    delay(10);
  }
  rawValue /= 10;

  float voltage = rawValue * (VREF / ADC_RESOLUTION);
  // Standard pH sensor formula (adjust slope/offset for your sensor)
  float ph = 3.5 * voltage + PH_OFFSET;
  return ph;
}

float readTDS() {
  int rawValue = 0;
  for (int i = 0; i < 10; i++) {
    rawValue += analogRead(TDS_PIN);
    delay(10);
  }
  rawValue /= 10;

  float voltage = rawValue * (VREF / ADC_RESOLUTION);
  // TDS formula
  float tdsValue = (133.42 * pow(voltage, 3)
                  - 255.86 * pow(voltage, 2)
                  + 857.39 * voltage) * TDS_FACTOR;
  return tdsValue;
}

float readTurbidity() {
  int rawValue = 0;
  for (int i = 0; i < 10; i++) {
    rawValue += analogRead(TURBIDITY_PIN);
    delay(10);
  }
  rawValue /= 10;

  float voltage = rawValue * (VREF / ADC_RESOLUTION);
  // Turbidity in NTU (formula for common turbidity sensors)
  float ntu = -1120.4 * pow(voltage, 2) + 5742.3 * voltage - 4352.9;
  if (ntu < 0) ntu = 0;
  return ntu;
}

// ─── Setup ──────────────────────────────────────────────────────────

void setup() {
  Serial.begin(115200);

  // Set ADC resolution to 12-bit (0-4095)
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db); // For 3.3V range

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected! IP: " + WiFi.localIP().toString());

  // Firebase config
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  // Anonymous sign-up
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase sign-up OK");
    signupOK = true;
  } else {
    Serial.printf("Sign-up failed: %s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

// ─── Loop ───────────────────────────────────────────────────────────

void loop() {
  if (Firebase.ready() && signupOK &&
      (millis() - sendDataPrevMillis > interval || sendDataPrevMillis == 0)) {

    sendDataPrevMillis = millis();

    // Read sensors
    float ph        = readPH();
    float tds       = readTDS();
    float turbidity = readTurbidity();

    Serial.printf("pH: %.2f | TDS: %.2f ppm | Turbidity: %.2f NTU\n",
                  ph, tds, turbidity);

    // Send to Firebase RTDB
    if (Firebase.RTDB.setFloat(&fbdo, "/aquasense/ph", ph)) {
      Serial.println("pH sent ✓");
    } else {
      Serial.println("pH failed: " + fbdo.errorReason());
    }

    if (Firebase.RTDB.setFloat(&fbdo, "/aquasense/tds", tds)) {
      Serial.println("TDS sent ✓");
    } else {
      Serial.println("TDS failed: " + fbdo.errorReason());
    }

    if (Firebase.RTDB.setFloat(&fbdo, "/aquasense/turbidity", turbidity)) {
      Serial.println("Turbidity sent ✓");
    } else {
      Serial.println("Turbidity failed: " + fbdo.errorReason());
    }

    // Optional: send timestamp
    Firebase.RTDB.setInt(&fbdo, "/aquasense/timestamp", millis() / 1000);
  }
}
