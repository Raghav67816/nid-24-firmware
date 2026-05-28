#include <Arduino.h>

int statePin = 7;
bool is_connected = false;

void setup(){

  Serial.begin(9600);

  pinMode(statePin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // turn of the built in LED by default
  digitalWrite(LED_BUILTIN, LOW);

  // attachInterrupt(digitalPinToInterrupt(statePin), handle_state_interrupt, CHANGE);
}

void loop(){
  int state = digitalRead(statePin);
  if(state == HIGH){
    digitalWrite(LED_BUILTIN, HIGH);
  }

  if(state == LOW){
    digitalWrite(LED_BUILTIN, LOW);
  }
  Serial.write("data", sizeof("data"));

  delay(100);
}
