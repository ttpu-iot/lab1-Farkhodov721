
#include <Arduino.h>

// ============================================================
// SELECT WHICH EXERCISE TO RUN (uncomment only ONE)
// ============================================================
// #define EXERCISE_1  // Blink RED LED
// #define EXERCISE_2  // Button toggles GREEN
// #define EXERCISE_3  // Read light sensor
// #define EXERCISE_4  // Light sensor -> LED band
// #define EXERCISE_5  // Snapshot on button
#define EXERCISE_6  // Minimal serial control

// Compile-time check: ensure exactly one exercise is defined
#define COUNT_EXERCISES ( \
  (defined(EXERCISE_1) ? 1 : 0) + \
  (defined(EXERCISE_2) ? 1 : 0) + \
  (defined(EXERCISE_3) ? 1 : 0) + \
  (defined(EXERCISE_4) ? 1 : 0) + \
  (defined(EXERCISE_5) ? 1 : 0) + \
  (defined(EXERCISE_6) ? 1 : 0) \
)

#if COUNT_EXERCISES == 0
  #error "Please define exactly ONE exercise (EXERCISE_1 through EXERCISE_6)"
#elif COUNT_EXERCISES > 1
  #error "Please define only ONE exercise at a time"
#endif

// Pin definitions
const int RED_PIN = 15;     // RED LED on D15
const int GREEN_PIN = 4;    // GREEN LED on D4
const int BLUE_PIN = 22;    // BLUE LED on D22
const int YELLOW_PIN = 23;  // YELLOW LED on D23
const int BUTTON_PIN = 14;  // Button on D14
const int LIGHT_PIN = 33;   // Light sensor on D33

// Light sensor thresholds for Exercise 4 (LED band)
const int LIGHT_THRESHOLD_BLUE = 1024;    // 0-1023 → BLUE
const int LIGHT_THRESHOLD_GREEN = 2048;   // 1024-2047 → GREEN
const int LIGHT_THRESHOLD_YELLOW = 3072;  // 2048-3071 → YELLOW
                                           // 3072-4095 → RED

#ifdef EXERCISE_1
unsigned long lastBlinkTime = 0;
#endif

#ifdef EXERCISE_2
bool greenState = false;
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
#endif

#ifdef EXERCISE_3
unsigned long lastLightReadTime = 0;
#endif

#ifdef EXERCISE_4
unsigned long lastLightReadTime = 0;
#endif

#ifdef EXERCISE_5
bool buttonHandled = false;
unsigned long lastSnapshotTime = 0;
#endif 

void setup() {
  Serial.begin(115200);
  
  // Initialize pins based on which exercise is active
#if defined(EXERCISE_1) || defined(EXERCISE_4)
  pinMode(RED_PIN, OUTPUT);
  digitalWrite(RED_PIN, LOW);
#endif

#if defined(EXERCISE_2) || defined(EXERCISE_4)
  pinMode(GREEN_PIN, OUTPUT);
  digitalWrite(GREEN_PIN, LOW);
#endif

#if defined(EXERCISE_4) || defined(EXERCISE_6)
  pinMode(BLUE_PIN, OUTPUT);
  digitalWrite(BLUE_PIN, LOW);
#endif

#if defined(EXERCISE_4) || defined(EXERCISE_5)
  pinMode(YELLOW_PIN, OUTPUT);
  digitalWrite(YELLOW_PIN, LOW);
#endif

#if defined(EXERCISE_2) || defined(EXERCISE_5)
  pinMode(BUTTON_PIN, INPUT_PULLUP);
#endif
}

#ifdef EXERCISE_1
void handleRedBlink() {
  // Exercise 1: Blink RED LED
  if (millis() - lastBlinkTime >= 500) {
    static bool redState = false;
    redState = !redState;
    digitalWrite(RED_PIN, redState);
    Serial.println(redState ? "RED ON" : "RED OFF");
    lastBlinkTime = millis();
  }
}
#endif

#ifdef EXERCISE_2
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
#endif

#ifdef EXERCISE_3
void handleLightSensor() {
  // Exercise 3: Read light sensor every 500ms
  if (millis() - lastLightReadTime >= 500) {
    int lightValue = analogRead(LIGHT_PIN);
    Serial.print("raw=");
    Serial.println(lightValue);
    lastLightReadTime = millis();
  }
}
#endif

#ifdef EXERCISE_4
void handleLightSensorBand() {
  // Exercise 4: Light sensor -> LED band
  if (millis() - lastLightReadTime >= 500) {
    int lightValue = analogRead(LIGHT_PIN);
    
    // Turn off all LEDs first
    digitalWrite(BLUE_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(RED_PIN, LOW);
    
    // Turn on the appropriate LED based on light value
    if (lightValue < LIGHT_THRESHOLD_BLUE) {
      digitalWrite(BLUE_PIN, HIGH);
      Serial.println("band=BLUE");
    } else if (lightValue < LIGHT_THRESHOLD_GREEN) {
      digitalWrite(GREEN_PIN, HIGH);
      Serial.println("band=GREEN");
    } else if (lightValue < LIGHT_THRESHOLD_YELLOW) {
      digitalWrite(YELLOW_PIN, HIGH);
      Serial.println("band=YELLOW");
    } else {
      digitalWrite(RED_PIN, HIGH);
      Serial.println("band=RED");
    }
    
    lastLightReadTime = millis();
  }
}
#endif

#ifdef EXERCISE_5
void handleSnapshot() {
  // Exercise 5: Snapshot on button press
  if (digitalRead(BUTTON_PIN) == LOW && !buttonHandled && 
      (millis() - lastSnapshotTime) > 500) {
    int lightValue = analogRead(LIGHT_PIN);
    Serial.print("snapshot=");
    Serial.println(lightValue);
    
    // Flash YELLOW LED for 100ms to acknowledge
    digitalWrite(YELLOW_PIN, HIGH);
    delay(100);
    digitalWrite(YELLOW_PIN, LOW);
    
    buttonHandled = true;
    lastSnapshotTime = millis();
  } else if (digitalRead(BUTTON_PIN) == HIGH) {
    buttonHandled = false;
  }
}
#endif

#ifdef EXERCISE_6
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
#endif

void loop() {
#ifdef EXERCISE_1
  handleRedBlink();
#endif

#ifdef EXERCISE_2
  handleButtonToggle();
#endif

#ifdef EXERCISE_3
  handleLightSensor();
#endif

#ifdef EXERCISE_4
  handleLightSensorBand();
#endif

#ifdef EXERCISE_5
  handleSnapshot();
#endif

#ifdef EXERCISE_6
  handleSerialControl();
#endif
}