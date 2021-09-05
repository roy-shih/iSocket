#include <Arduino.h>
#include <TFT_eSPI.h>
#include <driver/i2s.h>
#include "Application.h"
#include <WiFiManager.h>
#include "AutoOTA.h"

// approx 30ms of audio @ 16KHz
#define WINDOW_SIZE 512

// i2s config for reading from both m5stack mic
i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 2,
    .dma_buf_len = 1024,
};

// i2s pins
i2s_pin_config_t i2s_pins = {
    .bck_io_num = GPIO_NUM_15,
    .ws_io_num = GPIO_NUM_2,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = GPIO_NUM_13};

Application *application;

void setup()
{
  Serial.begin(115200);
  TFT_eSPI *display = new TFT_eSPI();
  display->begin();
  display->setRotation(1);
  
  WiFi.mode(WIFI_STA);
   WiFiManager wm;
   bool res;
   res = wm.autoConnect("iSOC wifimanager","00000000"); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
    }
  AutoOTA();
  application = new Application(*display, WINDOW_SIZE);
  application->begin(i2s_config, i2s_pins);
}

void loop()
{
  // service the application
  application->loop();
}