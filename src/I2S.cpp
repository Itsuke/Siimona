#include "I2S.hpp"

I2S::I2S() {
  BITS_PER_SAMPLE = I2S_BITS_PER_SAMPLE_16BIT;
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 16000,
    .bits_per_sample = BITS_PER_SAMPLE,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = 60,
    .use_apll = false
  };
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  const i2s_pin_config_t pin_config = {
    .bck_io_num = 33,// 33,
    .ws_io_num = 25,// 25,
    .data_out_num = -1,
    .data_in_num = 32// 32
  };
  i2s_set_pin(I2S_NUM_0, &pin_config);
}

int I2S::Read(char* data, int numData) {
  size_t bytesIn = 0;
  return i2s_read(I2S_NUM_0, (char *)data, numData, &bytesIn, portMAX_DELAY);
}

int I2S::GetBitPerSample() {
  return (int)BITS_PER_SAMPLE;
}