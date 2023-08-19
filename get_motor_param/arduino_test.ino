const int encAPin = 2;   // Pin A encoder
const int encBPin = 3;   // Pin B encoder
const int pwmPin = 9;    // PWM output pin

volatile int encoderPosition = 0;
int lastEncAState = LOW;
int lastEncBState = LOW;

const int startCommand = 30;  // Minimum command value to start moving

void setup() {
  pinMode(encAPin, INPUT_PULLUP);
  pinMode(encBPin, INPUT_PULLUP);
  pinMode(pwmPin, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(encAPin), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encBPin), updateEncoder, CHANGE);
  
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    int targetPWM = Serial.parseInt();
    analogWrite(pwmPin, targetPWM);

    float speed = encoderPosition;
    
    Serial.print(speed);
    Serial.print(',');
    Serial.println(targetPWM);

    if (speed > 0 && targetPWM >= startCommand) {
      Serial.println(startCommand);
    }

    delay(50); // Delay for stability
  }
}

void updateEncoder() {
  int newEncAState = digitalRead(encAPin);
  int newEncBState = digitalRead(encBPin);
  
  if ((lastEncAState == LOW) && (newEncAState == HIGH)) {
    if (newEncBState == LOW) {
      encoderPosition++;
    } else {
      encoderPosition--;
    }
  }
  
  lastEncAState = newEncAState;
}
