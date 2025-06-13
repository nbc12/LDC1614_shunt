#include <RAK12029_LDC1614.h>

#define N_SAMPLES         4320
#define SAMPLE_PERIOD_MS  1000
#define GETCHANNEL        LDC1614_CHANNEL_3

RAK12029_LDC1614_Inductive ldc;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  Serial.println("Trying to connect to LDC1614...");
  ldc.LDC1614_init();
  if (ldc.LDC1614_single_channel_config(GETCHANNEL, 7.0))
  {
    Serial.println("can't detect sensor!");
    while (1) delay(100);
  }
  Serial.println("Waiting 10 seconds...");
  delay(1000);
}


unsigned long counter = 0;
void loop() {
  // put your main code here, to run repeatedly:
  u16 value = 0;
  ldc.IIC_read_16bit(LDC1614_READ_DEVICE_ID, &value);
  if (counter == N_SAMPLES) {
    Serial.println("Finished sampling");
    while (1) {
      delay(100);
    }
  }
  if (value == 0x3055)
  {
    u32 ChannelData = 0;
    /*Get channel 0 result and parse it.*/
    delay(SAMPLE_PERIOD_MS);
    if (ldc.LDC1614_get_channel_result(GETCHANNEL, &ChannelData) == 0)
    {
      /*sensor result value.you can make a lot of application according to its changes.*/
      if (0 != ChannelData)
      {
        Serial.print(counter);
        Serial.print(", ");
        Serial.println(ChannelData / 1000);
        counter++;
      }
    }
  }
  else
  {
    Serial.println("I2C communication failed, please reset the sensor!");
    delay(500);
  }
}
