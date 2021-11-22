#include <Arduino.h>
#include <ESP32QRCodeReader.h>
#include <ESP32Servo.h>

Servo myservo;

int servoPin = 15;

ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);

String mypayload = "";

void onQrCodeTask(void *pvParameters)
{
  struct QRCodeData qrCodeData;

  while (true)
  {
    if (reader.receiveQrCode(&qrCodeData, 100))
    {
      Serial.println("Found QRCode");
      if (qrCodeData.valid)
      {
        mypayload = String((const char *)qrCodeData.payload);
        Serial.print("Payload: ");
        Serial.println(mypayload);
      }
      else
      {
        Serial.print("Invalid: ");
        Serial.println((const char *)qrCodeData.payload);
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);
  myservo.attach(servoPin, 1000, 2000);

  reader.setup();

  Serial.println("Setup QRCode Reader");

  reader.beginOnCore(1);

  Serial.println("Begin on Core 1");

  xTaskCreate(onQrCodeTask, "onQrCode", 4 * 1024, NULL, 4, NULL);
}

void loop()
{
  delay(100);

  if (mypayload == ""){
    
    myservo.write(180);
    delay(5000);                  
    myservo.write(0);
    mypayload = "";                 
    }

  else if (mypayload == ""){

    myservo.write(180);
    delay(5000);                  
    myservo.write(0);
    mypayload = "";
    }

  else if (mypayload == ""){
    myservo.write(180);
    delay(5000);                  
    myservo.write(0);
    mypayload = "";
    }

  else if (mypayload == ""){
    myservo.write(180);
    delay(5000);                  
    myservo.write(0);
    mypayload = "";
    }
}
