#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 5); // CE, CSN on Blue Pill
const uint64_t address = 0xF0F0F0F0E1LL;
int counter = 0;

void setup()
{
  Serial.begin(115200);
  radio.begin();                  // Starting the Wireless communication
  radio.openWritingPipe(address); // Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  // You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          // This sets the module as transmitter
  pinMode(LED_BUILTIN, OUTPUT);
}

struct MyData
{
  int counter;
  float temperature;
  float humidity;
  float altitude;
  float pressure;
};
MyData data;

void loop()
{
  counter++;
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  Serial.println("ko");
  data.counter = counter;
  bool result = radio.write(&data, sizeof(MyData));
  if (result)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  Serial.println(result);
}
