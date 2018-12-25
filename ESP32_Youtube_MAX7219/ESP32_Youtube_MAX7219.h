#include <SPI.h>
#include "LedMatrix.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char *ssid = "xxxxxxx";        // wifi ssid
const char *password = "xxxxxxxxxxxxx"; //wifi password

const char *channel_id = "xxxxxxxxxxxxxxxxxxxxx"; //youtube channel id
const char *api_key = "xxxxxxxxxxxxxxxxxx";       //google api key

#define NUMBER_OF_DEVICES 4 //number of led matrix connect in series
#define CS_PIN 5            //spi slave select pin
#define CLK_PIN 18          //spi clock pin
#define MISO_PIN 19         //we do not use this pin just fill to match constructor
#define MOSI_PIN 23
#define LED_MAX_NUMBER 6 //led display max number with logo

String getYoutubeSubscriber(); //get youtube subscriber use google api
