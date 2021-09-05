#include <TFT_eSPI.h>
#include "Application.h"
#include "I2S/I2SSampler.h"
#include "UI/UI.h"
#include "AudioProcessing/Processor.h"

#define GPIO_BUTTON 0

// Task to process samples
void processing_task(void *param)
{
  Application *application = (Application *)param;
  const TickType_t xMaxBlockTime = pdMS_TO_TICKS(100);
  while (true)
  {
    // wait for some samples to process
    uint32_t ulNotificationValue = ulTaskNotifyTake(pdTRUE, xMaxBlockTime);
    if (ulNotificationValue > 0)
    {
      application->process_samples();
    }
  }
}

Application::Application(TFT_eSPI &display, int window_size)
{
  m_window_size = window_size;
  m_ui = new UI(display, window_size);
  m_processor = new Processor(window_size);
  m_sampler = new I2SSampler();
  pinMode(GPIO_BUTTON, INPUT_PULLUP);
}

void Application::begin(const i2s_config_t &i2s_config, const i2s_pin_config_t &i2s_pins)
{
  // set up the processing
  TaskHandle_t processing_task_handle;
  xTaskCreatePinnedToCore(processing_task, "Processing Task", 4096, this, 2, &processing_task_handle, 0);

  // start sampling from i2s device
  m_sampler->start(I2S_NUM_0, i2s_pins, i2s_config, m_window_size, processing_task_handle);
}

void Application::process_samples()
{
  // grab the samples
  int16_t *samples = m_sampler->getCapturedAudioBuffer();
  m_processor->update(samples);
  m_ui->update(m_processor->m_fft_input, m_processor->m_energy);
}

void Application::loop()
{
  if (digitalRead(GPIO_BUTTON) == 0)
  {
    m_ui->toggle_display();
    // delay to allow for the touch to finish
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

