#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiManager.h>

#ifndef min
#define min(x,y) (((x)<(y))?(x):(y))
#endif
#ifndef max
#define max(x,y) (((x)>(y))?(x):(y))
#endif
#include <ArduinoJson.h>

#define WU_API_KEY "KEY"
#define WU_LOCATION "60201"
#define WUNDERGROUND "api.wunderground.com"
#define DELAY_NORMAL    (5*60*1000) // call every 5 minutes

const char WUNDERGROUND_REQ[] =
  "GET /api/" WU_API_KEY "/conditions/q/" WU_LOCATION ".json HTTP/1.1\r\n"
  "User-Agent: ESP8266/0.1\r\n"
  "Accept: */*\r\n"
  "Host: " WUNDERGROUND "\r\n"
  "Connection: close\r\n"
  "\r\n";


void setup() {
  // put your setup code here, to run once:
  WiFiManager wifiManager;
 wifiManager.autoConnect("AutoConnectAP");
 // We will wait until setup is complete then continue


  Serial.println("Connection Established");

  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  if ((millis() - time_delay) > DELAY_NORMAL) {
      WiFiClient httpclient;
      const int httpPort = 80;
      if (!httpclient.connect(WUNDERGROUND, httpPort)) {
        Serial.println(F("connection failed"));
        time_delay = millis();
        return;
      }
      httpclient.print(WUNDERGROUND_REQ);
      httpclient.flush();
      int respLen = 0;
      bool skip_headers = true;
      while (httpclient.connected() || httpclient.available()) {
        if (skip_headers) {
          String aLine = httpclient.readStringUntil('\n');
          //Serial.println(aLine);
          // Blank line denotes end of headers
          if (aLine.length() <= 1) {
            skip_headers = false;
          }
        }
        else {
          int bytesIn;
          bytesIn = httpclient.read((uint8_t *)&respBuf[respLen], sizeof(respBuf) - respLen);
          Serial.print(F("bytesIn ")); Serial.println(bytesIn);
          if (bytesIn > 0) {
            respLen += bytesIn;
            if (respLen > sizeof(respBuf)) respLen = sizeof(respBuf);
          }
          else if (bytesIn < 0) {
            Serial.print(F("read error "));
            Serial.println(bytesIn);
          }
        }
        delay(1);
      }
      httpclient.stop();
      respBuf[respLen++] = '\0';
      Serial.print(F("respLen "));
      Serial.println(respLen);
      showWeather(respBuf);
      time_delay = millis();
    }
}

bool showWeather(char *json)
{
  StaticJsonBuffer<3 * 1024> jsonBuffer;

  // Skip characters until first '{' found
  // Ignore chunked length, if present
  char *jsonstart = strchr(json, '{');
  //Serial.print(F("jsonstart ")); Serial.println(jsonstart);
  if (jsonstart == NULL) {
    Serial.println(F("JSON data missing"));
    return false;
  }
  json = jsonstart;

  // Parse JSON
  JsonObject& root = jsonBuffer.parseObject(json);
  if (!root.success()) {
    Serial.println(F("jsonBuffer.parseObject() failed"));
    return false;
  }

  // Extract weather info from parsed JSON
  JsonObject& current = root["current_observation"];
  temp_c = current["temp_c"];
  Serial.print(temp_c, 1); Serial.print(F(" C, "));
  const char *humi = current[F("relative_humidity")];
  Serial.print(humi);   Serial.println(F(" RH"));
  weather_g = current["weather"];
  //weather_g = weather;
  Serial.println(weather_g);
  const char *pressure_mb = current["pressure_mb"];
  Serial.println(pressure_mb);
  const char *observation_time = current["observation_time_rfc822"];
  Serial.println(observation_time);

  // Extract local timezone fields
  const char *local_tz_short = current["local_tz_short"];
  Serial.println(local_tz_short);
  const char *local_tz_long = current["local_tz_long"];
  Serial.println(local_tz_long);
  const char *local_tz_offset = current["local_tz_offset"];
  Serial.println(local_tz_offset);
  return true;
}
