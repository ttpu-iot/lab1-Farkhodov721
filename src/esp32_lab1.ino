
#include <Arduino.h>


const int RED_PIN = 15;     // RED LED on D15
const int GREEN_PIN = 4;    // GREEN LED on D4
const int BLUE_PIN = 22;    // BLUE LED on D22
const int YELLOW_PIN = 23;  // YELLOW LED on D23
const int BUTTON_PIN = 14;  // Button on D14
const int LIGHT_PIN = 33;   // Light sensor on D33


bool greenState = false;
bool lastButtonState = HIGH;
unsigned long lastBlinkTime = 0;
unsigned long lastLightReadTime = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; 

void setup() {

  Serial.begin(115200);
  

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  

  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
}

void handleRedBlink() {

  if (millis() - lastBlinkTime >= 500) {
    static bool redState = false;
    redState = !redState;
    digitalWrite(RED_PIN, redState);
    Serial.println(redState ? "RED ON" : "RED OFF");
    lastBlinkTime = millis();
  }
}

void handleButtonToggle() {
  // Exercise 2: Button toggles GREEN LED with debouncing
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && lastButtonState == HIGH) {
      greenState = !greenState;
      digitalWrite(GREEN_PIN, greenState);
      Serial.print("GREEN=");
      Serial.println(greenState);
    }
  }
  
  lastButtonState = reading;
}

void handleLightSensor() {
  // Exercise 3: Read light sensor every 500ms
  if (millis() - lastLightReadTime >= 500) {
    int lightValue = analogRead(LIGHT_PIN);
    Serial.print("raw=");
    Serial.println(lightValue);
    
    // Exercise 4: Light sensor LED band
    digitalWrite(BLUE_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(RED_PIN, LOW);
    
    if (lightValue < 1024) {
      digitalWrite(BLUE_PIN, HIGH);
      Serial.println("band=BLUE");
    } else if (lightValue < 2048) {
      digitalWrite(GREEN_PIN, HIGH);
      Serial.println("band=GREEN");
    } else if (lightValue < 3072) {
      digitalWrite(YELLOW_PIN, HIGH);
      Serial.println("band=YELLOW");
    } else {
      digitalWrite(RED_PIN, HIGH);
      Serial.println("band=RED");
    }
    
    lastLightReadTime = millis();
  }
}

void handleSnapshot() {
  // Exercise 5: Snapshot on button press with debouncing
  static bool buttonHandled = false;
  static unsigned long lastSnapshotTime = 0;
  
  if (digitalRead(BUTTON_PIN) == LOW && !buttonHandled && 
      (millis() - lastSnapshotTime) > 500) {
    int lightValue = analogRead(LIGHT_PIN);
    Serial.print("snapshot=");
    Serial.println(lightValue);
    
   
    digitalWrite(YELLOW_PIN, HIGH);
    delay(100);
    digitalWrite(YELLOW_PIN, LOW);
    
    buttonHandled = true;
    lastSnapshotTime = millis();
  } else if (digitalRead(BUTTON_PIN) == HIGH) {
    buttonHandled = false;
  }
}

void handleSerialControl() {
  // Exercise 6: Minimal serial control
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    if (command == 'B') {
      digitalWrite(BLUE_PIN, HIGH);
      Serial.println("BLUE=1");
    } else if (command == 'b') {
      digitalWrite(BLUE_PIN, LOW);
      Serial.println("BLUE=0");
    }
  }
}

void loop() {
  handleRedBlink();        // Exercise 1
  handleButtonToggle();    // Exercise 2
  handleLightSensor();     // Exercise 3 & 4
  handleSnapshot();        // Exercise 5
  handleSerialControl();   // Exercise 6
}