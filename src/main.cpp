#define ESP_DRD_USE_SPIFFS true

#include <Arduino.h>
#include <Wire.h>
#include <LTR390.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <FS.h>
#include <SPIFFS.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <DHT.h>
// #include <driver/adc.h>  // Try to read battery
// #include <esp_adc_cal.h>

const int PIN_LED = 2;
const int PIN_SWITCH_POWER = 25;
const int PIN_SWITCH_READ = 26;

#define DHTPIN 5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  15 * 60  /* Time ESP32 will go to sleep (in seconds) */

#define JSON_CONFIG_FILE "/config.json"

#define I2C_ADDRESS 0x53
LTR390 ltr390(I2C_ADDRESS);

AsyncWebServer server(80);
AsyncEventSource events("/events");

//flag for saving data
bool shouldSaveConfig = false;

// Weather Underground
bool USE_WU = false;
char WU_ID[50] = "";
char WU_KEY[50] = "";
const char* WUHOST      = "rtupdate.wunderground.com"; //"weatherstation.wunderground.com";
const int WUHTTPSPORT   = 443;
// Weather Cloud
bool USE_WC = false;
char WC_ID[50] = "";
char WC_KEY[50] = "";

float luxReading=0.0;
float uvReading=0.0;
float tempFReading=0.0;
float dewTempFReading=0.0;
float humidityReading=0.0;
const float minLuxForSleep=5.0;

unsigned long lastReading = 0;
const unsigned long timerReading = 5L * 1000L;
unsigned long lastSubmit = 0;
const unsigned long timerSubmit = 30L * 1000L;

void saveConfigFile()
{
  Serial.println(F("Saving config"));
  StaticJsonDocument<512> json;
  json["USE_WU"] = USE_WU;
  json["WU_ID"] = WU_ID;
  json["WU_KEY"] = WU_KEY;
  json["USE_WC"] = USE_WC;
  json["WC_ID"] = WC_ID;
  json["WC_KEY"] = WC_KEY;

  File configFile = SPIFFS.open(JSON_CONFIG_FILE, "w");
  if (!configFile)
  {
    Serial.println("failed to open config file for writing");
  }

  serializeJsonPretty(json, Serial);
  if (serializeJson(json, configFile) == 0)
  {
    Serial.println(F("Failed to write to file"));
  }
  configFile.close();
}

bool loadConfigFile()
{
  if (SPIFFS.exists(JSON_CONFIG_FILE))
  {
    //file exists, reading and loading
    Serial.println("reading config file");
    File configFile = SPIFFS.open(JSON_CONFIG_FILE, "r");
    if (configFile)
    {
      Serial.println("opened config file");
      StaticJsonDocument<512> json;
      DeserializationError error = deserializeJson(json, configFile);
      serializeJsonPretty(json, Serial);
      if (!error)
      {
        Serial.println("\nparsed json");

        USE_WU = json["USE_WU"].as<bool>();
        strcpy(WU_ID, json["WU_ID"]);
        strcpy(WU_KEY, json["WU_KEY"]);
        USE_WC = json["USE_WC"].as<bool>();
        strcpy(WC_ID, json["WC_ID"]);
        strcpy(WC_KEY, json["WC_KEY"]);

        return true;
      }
      else
      {
        Serial.println("failed to load json config");
      }
    }
  }
  //end read
  return false;
}

void saveConfigCallback()
{
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void configModeCallback(WiFiManager *myWiFiManager)
{
  Serial.println("Entered Conf Mode");

  Serial.print("Config SSID: ");
  Serial.println(myWiFiManager->getConfigPortalSSID());

  Serial.print("Config IP Address: ");
  Serial.println(WiFi.softAPIP());
}

void sleepNow () {
  Serial.println("### SLEEPING FOR " + String(TIME_TO_SLEEP) +"s ###");
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}

void connectWifi(bool forceConfig, bool sleepOnFail)
{
  // Setup wifi and manager
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  wm.setSaveConfigCallback(saveConfigCallback);
  wm.setAPCallback(configModeCallback);

  // Create custom data for configuration
  char *customHtml;
  if (USE_WU) customHtml = "type=\"checkbox\" checked"; else customHtml = "type=\"checkbox\"";
  WiFiManagerParameter wu_chk("USE_WU", "Use Weather Underground?", "T", 2, customHtml); 
  WiFiManagerParameter wu_id_txt("WU_ID", "Weather Underground ID", WU_ID, 50);
  WiFiManagerParameter wu_key_txt("WU_KEY", "Weather Underground Key", WU_KEY, 50);
  if (USE_WC) customHtml = "type=\"checkbox\" checked"; else customHtml = "type=\"checkbox\"";
  WiFiManagerParameter wc_chk("USE_WC", "Use Weather Cloud?", "T", 2, customHtml); 
  WiFiManagerParameter wc_id_txt("WC_ID", "Weather Cloud ID", WC_ID, 50);
  WiFiManagerParameter wc_key_txt("WC_KEY", "Weather Cloud Key", WC_KEY, 50);
  wm.addParameter(&wu_chk);
  wm.addParameter(&wu_id_txt);
  wm.addParameter(&wu_key_txt);
  wm.addParameter(&wc_chk);
  wm.addParameter(&wc_id_txt);
  wm.addParameter(&wc_key_txt);
  if (forceConfig) {
    if (!wm.startConfigPortal("UVLux-Setup"))
    {
      Serial.println("failed to connect and hit timeout");
      delay(5000);
      if (sleepOnFail) sleepNow();
      ESP.restart();
    }
  }
  else {
    if (!wm.autoConnect("UVLux-Setup"))
    {
      Serial.println("Failed to connect and hit timeout");
      delay(5000);
      if (sleepOnFail) sleepNow();
      ESP.restart();
    }
  }
  // Would be set with the callback saveConfigCallback
  if (shouldSaveConfig) {
    USE_WU = (strncmp(wu_chk.getValue(), "T", 1) == 0);
    strncpy(WU_ID, wu_id_txt.getValue(), sizeof(WU_ID));
    strncpy(WU_KEY, wu_key_txt.getValue(), sizeof(WU_KEY));
    USE_WC = (strncmp(wc_chk.getValue(), "T", 1) == 0);
    strncpy(WC_ID, wc_id_txt.getValue(), sizeof(WC_ID));
    strncpy(WC_KEY, wc_key_txt.getValue(), sizeof(WC_KEY));
    saveConfigFile();
  }
}

void connectSPIFFS() {
  if (SPIFFS.begin(false) || SPIFFS.begin(true))
  {
    Serial.println("SPIFFS Connected!");
  } else {
    Serial.println("SPIFFS FAILED to mount!");
    delay(5000);
    ESP.restart();
  }
}

void switchLTR390Mode(ltr390_mode_t mode) {
  switch (mode) {
    case LTR390_MODE_ALS: // Lux
      ltr390.setMode(LTR390_MODE_ALS);
      ltr390.setGain(LTR390_GAIN_1);  // LTR390_GAIN_3
      ltr390.setResolution(LTR390_RESOLUTION_18BIT);
      break;
    case LTR390_MODE_UVS: // UV Index
      ltr390.setMode(LTR390_MODE_UVS);
      ltr390.setGain(LTR390_GAIN_18);  // LTR390_GAIN_18
      ltr390.setResolution(LTR390_RESOLUTION_20BIT);
      break;
  }
}

void connectLTR390() {
  Wire.begin();
  if(!ltr390.init()){
    Serial.println("LTR390 not connected!");
    delay(5000);
    ESP.restart();
  }
  switchLTR390Mode(LTR390_MODE_ALS);
}

void takeReading(float *lux, float *uv) {
  while (true) {
    if (!ltr390.newDataAvailable()) continue;
    if (ltr390.getMode() == LTR390_MODE_ALS) {
      digitalWrite(LED_BUILTIN, HIGH);
      *lux = ltr390.getLux();
      switchLTR390Mode(LTR390_MODE_UVS);
    } else if (ltr390.getMode() == LTR390_MODE_UVS) {
      digitalWrite(LED_BUILTIN, LOW);
      *uv = ltr390.getUVI();
      switchLTR390Mode(LTR390_MODE_ALS);
      break;
    }
  }
}

void takeTempReading(float *tempF, float *dewTempF, float *humidity) {
  *tempF = dht.readTemperature(true);
  *humidity = dht.readHumidity();
  if (isnan(*tempF) || isnan(*humidity)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  *dewTempF = (dht.convertFtoC(*tempF) - (100 - *humidity) / 5.0) * 9/5 + 32;
  //float hi = dht.computeHeatIndex(t, h, true);
}

String convertJSON(float *lux, float *uv, float *tempF, float *dewTempF, float *humidity) {
  StaticJsonDocument<512> json;
  json["uvindex"] = *uv;
  json["lux"] = *lux;
  json["wm2"] = *lux * 0.0079;
  json["tempC"] = dht.convertFtoC(*tempF);
  json["dewTempC"] = dht.convertFtoC(*dewTempF);
  json["humidity"] = *humidity;
  String result;
  serializeJson(json, result);
  return result;
}

void setupWebserver() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });
  server.serveStatic("/", SPIFFS, "/");
  server.on("/readings", HTTP_GET, [](AsyncWebServerRequest *request){
    String json = convertJSON(&luxReading, &uvReading, &tempFReading, &dewTempFReading, &humidityReading);
    request->send(200, "application/json", json);
    json = String();
  });
  events.onConnect([](AsyncEventSourceClient *client){
    client->send("hello!", NULL, millis(), 10000);
  });
  server.addHandler(&events);
  AsyncElegantOTA.begin(&server); // Add OTA update to web server
  server.begin();
}

void uploadDataToWU(float *lux, float *uv, float *tempF, float *dewTempF, float *humidity){
  WiFiClientSecure client;
  client.setInsecure();
  // Use WiFiClientSecure class to create SSL connection
  Serial.println("Connecting to   : " + String(WUHOST));
  if (!client.connect(WUHOST, WUHTTPSPORT)) {
    Serial.println("Connection failed");
    return;
  }
  String url = "/weatherstation/updateweatherstation.php?ID=" + String(WU_ID) + 
                                        "&PASSWORD=" + String(WU_KEY) + 
                                        "&dateutc=now" + 
                                        "&solarradiation=" + String(*lux * 0.0079) + 
                                        "&UV="+ String(*uv) + 
                                        "&tempf=" + String(*tempF) + 
                                        "&dewptf=" + String(*dewTempF) + 
                                        "&humidity=" + String(*humidity) +
                                        "&action=updateraw&realtime=1";
  if (*lux < minLuxForSleep)
    url += "&rtfreq=" + String(TIME_TO_SLEEP);
  else
    url += "&rtfreq=" + String(timerSubmit / 1000);
  Serial.println("Requesting      : "+url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + WUHOST + "\r\n" +
              "User-Agent: UVLux-Sensor\r\n" +
               "Connection: close\r\n\r\n");
  Serial.print("Request sent    : ");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("Headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  boolean Status = false;
  if (line == "success") {
    line = "Server confirmed all data received";
    Status = true;
  }
  if (line == "INVALIDPASSWORDID|Password or key and/or id are incorrect") line = "Invalid PWS/User data entered in the ID and PASSWORD or GET parameters";
  if (line == "RapidFire Server") line = "The minimum GET parameters of ID, PASSWORD, action and dateutc were not set correctly";
  Serial.println("Server Response : " + line);
  Serial.println("Status          : Closing connection");
}

void uploadDataToWC(float *lux, float *uv, float *tempF, float *dewTempF, float *humidity){
  Serial.println("Status          : Uploaded f-all");
}

bool resetButtonPressed() {
  return digitalRead(PIN_SWITCH_READ) == 1;
}

void setup()
{
  pinMode(PIN_LED, OUTPUT);

  pinMode(PIN_SWITCH_READ, INPUT_PULLDOWN);
  pinMode(PIN_SWITCH_POWER, OUTPUT);
  digitalWrite(PIN_SWITCH_POWER, HIGH);

  Serial.begin(115200);
  delay(10);

  connectSPIFFS();
  connectLTR390();
  dht.begin();
  
  // Take a reading because we might want to disable a Wifi reconnect loop if it's dark
  takeReading(&luxReading, &uvReading);

  digitalWrite(PIN_LED, HIGH); // Switch LED on for the duration of the WiFi startup

  bool forceConfig = !loadConfigFile(); // Force config if config file error

  if (!forceConfig && resetButtonPressed()) forceConfig = true; // If button is pressed start config

  connectWifi(forceConfig, (luxReading < minLuxForSleep));

  digitalWrite(PIN_LED, LOW);

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  setupWebserver();
}

void loop()
{
  if (digitalRead(PIN_SWITCH_READ)) {
    ESP.restart(); // Restart if button pressed. If kept long enough to be caught in Setup() then start config.
  }
  if ((millis() - lastReading) > timerReading) {
    // Send Events to the client with the Sensor Readings Every 10 seconds
    takeReading(&luxReading, &uvReading);
    takeTempReading(&tempFReading, &dewTempFReading, &humidityReading);
    // Upload reading to any listening web browsers
    String reading = convertJSON(&luxReading, &uvReading, &tempFReading, &dewTempFReading, &humidityReading);
    Serial.println(reading);
    events.send("ping",NULL,millis());
    events.send(reading.c_str(),"new_readings" ,millis());
    lastReading = millis();
    // Check if data should be submitted to online weather
    if ((millis() - lastSubmit) > timerSubmit) {
      lastSubmit = millis();
      if (USE_WU)
        uploadDataToWU(&luxReading, &uvReading, &tempFReading, &dewTempFReading, &humidityReading);
      if (USE_WC)
        uploadDataToWC(&luxReading, &uvReading, &tempFReading, &dewTempFReading, &humidityReading);
      if (luxReading < minLuxForSleep) sleepNow();
    }
  }
}

// float readBattery() {
//   uint32_t value = 0;
//   int rounds = 11;
//   esp_adc_cal_characteristics_t adc_chars;
//   //battery voltage divided by 2 can be measured at GPIO34, which equals ADC1_CHANNEL6
//   adc1_config_width(ADC_WIDTH_BIT_12);
//   adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
//   switch(esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars)) {
//     case ESP_ADC_CAL_VAL_EFUSE_TP:
//       Serial.println("Characterized using Two Point Value");
//       break;
//     case ESP_ADC_CAL_VAL_EFUSE_VREF:
//       Serial.printf("Characterized using eFuse Vref (%d mV)\r\n", adc_chars.vref);
//       break;
//     default:
//       Serial.printf("Characterized using Default Vref (%d mV)\r\n", 1100);
//   }
//   //to avoid noise, sample the pin several times and average the result
//   for(int i=1; i<=rounds; i++) {
//     value += adc1_get_raw(ADC1_CHANNEL_6);
//   }
//   value /= (uint32_t)rounds;
//   //due to the voltage divider (1M+1M) values must be multiplied by 2
//   //and convert mV to V
//   return esp_adc_cal_raw_to_voltage(value, &adc_chars)*2.0/1000.0;
// }