#include <IRremote.h>

#define IR_PIN 11
#define MOTION_PIN 2
#define LDR_PIN A0
#define MODE_BUTTON 8
#define BUZZER 9
#define SYS_LED 10
#define GREEN_LED 12
#define YELLOW_LED 13
#define MOTION_LED 14 // Motion detection indicator LED

#define LED1 3  // Dining
#define LED2 4
#define LED3 5
#define LED4 6
#define LED5 7

IRrecv irrecv(IR_PIN);
decode_results results;

// System states
bool autoMode = true;
bool diningOffLast = false;
bool sysLedState = false;
bool buttonPrev = HIGH;
bool isNight = false;
unsigned long lastBlink = 0;
unsigned long lastMotion = 0;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

  pinMode(MOTION_PIN, INPUT);
  pinMode(MODE_BUTTON, INPUT_PULLUP);
  pinMode(LDR_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(SYS_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(MOTION_LED, OUTPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  // Initial day/night check
  int lightValue = analogRead(LDR_PIN);
  isNight = lightValue < 500;
  autoMode = isNight;
  updateModeLEDs();

  // System power ON beep
  beep(2, 100);
}

void loop() {
  // System LED blink
  if (millis() - lastBlink >= 500) {
    sysLedState = !sysLedState;
    digitalWrite(SYS_LED, sysLedState);
    lastBlink = millis();
  }

  // Day/night check every 5 sec
  static unsigned long lastLdrCheck = 0;
  if (millis() - lastLdrCheck > 5000) {
    int lightValue = analogRead(LDR_PIN);
    bool nightNow = lightValue < 500;
    if (nightNow != isNight) {
      isNight = nightNow;
      beep(1, 200); // Day/night change
      autoMode = isNight; // Switch mode automatically
      updateModeLEDs();
    }
    lastLdrCheck = millis();
  }

  // Mode button
  bool buttonState = digitalRead(MODE_BUTTON);
  if (buttonPrev == HIGH && buttonState == LOW) {
    autoMode = !autoMode;
    beep(1, 100);
    updateModeLEDs();
    delay(200);
  }
  buttonPrev = buttonState;

  // ---------------- AUTO MODE ----------------
  if (autoMode && isNight) {
    if (digitalRead(MOTION_PIN) == HIGH) {
      digitalWrite(MOTION_LED, HIGH); // Motion indicator ON
      beep(1, 100);
      if (!diningOffLast) {
        turnAllLEDs(HIGH);
        diningOffLast = true;
      } else {
        digitalWrite(LED1, LOW); // Dining OFF
        diningOffLast = false;
        beep(1, 200);
      }
      lastMotion = millis();
      delay(1000);
    } else {
      digitalWrite(MOTION_LED, LOW); // Motion indicator OFF
    }
  }

  // ---------------- REMOTE CONTROL ----------------
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    switch (results.value) {
      case 0xFF30CF: toggleLED(LED1); beep(1,50); break; // Dining
      case 0xFF18E7: toggleLED(LED2); beep(1,50); break;
      case 0xFF7A85: toggleLED(LED3); beep(1,50); break;
      case 0xFF10EF: toggleLED(LED4); beep(1,50); break;
      case 0xFF38C7: toggleLED(LED5); beep(1,50); break;
      case 0xFF5AA5: autoMode = !autoMode; beep(1,100); updateModeLEDs(); break; // Mode toggle
    }
    irrecv.resume();
  }
}

// ------------------ Functions ------------------
void updateModeLEDs() {
  digitalWrite(GREEN_LED, autoMode);    // Green = AUTO
  digitalWrite(YELLOW_LED, !autoMode);  // Yellow = MANUAL
}

void toggleLED(int pin) {
  digitalWrite(pin, !digitalRead(pin));
}

void turnAllLEDs(bool state) {
  digitalWrite(LED1, state);
  digitalWrite(LED2, state);
  digitalWrite(LED3, state);
  digitalWrite(LED4, state);
  digitalWrite(LED5, state);
}

// Beep function: count = number of beeps, duration = ms per beep
void beep(int count, int duration) {
  for(int i=0; i<count; i++){
    digitalWrite(BUZZER,HIGH);
    delay(duration);
    digitalWrite(BUZZER,LOW);
    delay(50);
  }
}
