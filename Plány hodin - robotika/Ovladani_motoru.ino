#include <Servo.h>

const int NUM = 4;
int controlPot[NUM] = {A0};
Servo serva[NUM];

void addPot(){
  for (int i = 0; i < NUM; i++) {
    pinMode(controlPot[i], INPUT);
  }
}

void addServo(Servo &s, int servoPin, int startPos) {
  s.attach(servoPin);
  s.write(startPos);
}

int readAverage(int pin, int samples) {
  analogRead(pin);
  long sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(pin);
  }
  return int(sum / samples);
}

void updateServo(int idx, int angLow, int angHigh, int sampleCount) {
  if (idx < 0 || idx >= NUM) return;

  int samples = sampleCount;
  if (samples <= 0) samples = 1; 

  int raw = readAverage(controlPot[idx], samples);            
  int angle = map(raw, 0, 1023, angLow, angHigh);         
  serva[idx].write(angle);

  Serial.print("Servo ");
  Serial.print(idx);
  Serial.print(" pocet vzorku=");
  Serial.print(samples);
  Serial.print(" hrube=");
  Serial.print(raw);
  Serial.print(" uhel=");
  Serial.println(angle);
}

void setup() {
  Serial.begin(9600);
  addPot();
  addServo(serva[0], 3, 0);
  delay(1000);
}

void loop() {
  updateServo(0, 0, 180, 6);
  delay(10);
}
