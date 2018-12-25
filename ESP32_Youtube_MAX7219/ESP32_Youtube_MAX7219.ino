/*
 *  ESP32 Youtube display with MAX7219
 *
 *  Created on: 2018/12/25
 *      Author: John
 */

#include "ESP32_Youtube_MAX7219.h"

LedMatrix ledMatrix = LedMatrix(NUMBER_OF_DEVICES, CS_PIN);

DynamicJsonBuffer jsonBuffer;

int first_display = 1;
int count = 0;
String youtubeSubscriber = "";
String LedMatrixText = "";

void setup()
{
  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

  ledMatrix.init();
  ledMatrix.setIntensity(0x03);
  ledMatrix.setAlternateDisplayOrientation(); // devices 90° right - comment out, if not needed
  ledMatrix.setText("");
  ledMatrix.clear();
}

void loop()
{
  count++;
  ledMatrix.scrollTextLeft();
  ledMatrix.drawText();
  ledMatrix.commit();

  if (count == NUMBER_OF_DEVICES * 8)
  {
    LedMatrixText = "@"; //display logo
    youtubeSubscriber = getYoutubeSubscriber();

    for (int j = 0; youtubeSubscriber.length() + j < LED_MAX_NUMBER; j++) //display Subscriber null number with " "
    {
      LedMatrixText += " ";
    }

    for (int i = 0; i < LED_MAX_NUMBER; i++) //display Subscriber number
    {
      LedMatrixText += youtubeSubscriber.charAt(i);
    }

    Serial.println(LedMatrixText);
    ledMatrix.setText(LedMatrixText);
    if (first_display == 0)
    {
      delay(60000); //Delay one minute
    }
    else
    {
      first_display = 0;
    }
    count = 0;
  }
}

String getYoutubeSubscriber()
{
  String returnString = "";
  if ((WiFi.status() == WL_CONNECTED))
  { //Check the current connection status

    HTTPClient http;
    String http_string = "https://www.googleapis.com/youtube/v3/channels?part=statistics&id=";
    http_string += String(channel_id);
    http_string += "&key=";
    http_string += String(api_key);

    http.begin(http_string);   //Specify the URL
    int httpCode = http.GET(); //Make the request

    if (httpCode > 0)
    { //Check for the returning code

      String payload = http.getString();
      Serial.println("http code------------------------------------------------------------------------");
      Serial.println(httpCode);
      Serial.println("payload------------------------------------------------------------------------");
      Serial.println(payload);
      JsonObject &JsonrRespons = jsonBuffer.parseObject(payload);
      String subscriber = JsonrRespons["items"][0]["statistics"]["subscriberCount"];
      returnString = subscriber;
      Serial.println("subscriberCount : " + subscriber);
    }

    else
    {
      Serial.println("Error on HTTP request");
    }

    http.end(); //Free the resources
    return returnString;
  }
}
