#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 7
#define CSN_PIN 8

RF24 radio(CE_PIN, CSN_PIN);
const uint64_t pipe = 0xE8E8F0F0E1LL;

7const int pingPin = 2;
const int echoPin = 3;

long duration;
struct Type_of_distance {
  long inches;
  long cm;
};

Type_of_distance TD;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe (pipe);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  TD.inches = microsecondsToInches(duration);
  TD.cm = microsecondsToCentimeters(duration);


  Serial.print(TD.inches);
  Serial.print("in, ");
  Serial.print(TD.cm);
  Serial.print("cm");
  Serial.println();
  radio.write(&TD, sizeof(TD));
  delay(100);
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
