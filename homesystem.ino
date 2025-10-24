#include <IRremote.h>

#define IR_RECEIVE_PIN 11
#define MOTION_PIN 2
#define LDR_PIN A0
#define BUTTON_PIN 8
#define BUZZER_PIN 9

#define SYSTEM_LED 10
#define AUTO_LED 12
#define MANUAL_LED 13
#define MOTION_LED A1

// Room LEDs (you can connect later)
#define LED_ROOM1 3
#define LED_ROOM2 4
#define LED_ROOM3 5
#define LED_ROOM4 6
#define LED_DINING 7

// Remote button codes (change if needed)
#define REMOTE_ROOM1 0xFF30CF
#define REMOTE_ROOM2 0xFF18E7
#define REMOTE_ROOM3 0xFF7A85
#define REMOTE_ROOM4 0xFF10EF
#define REMOTE_DINING 0xFF38C7
#define REMOTE_MODE 0xFF5AA5

bool autoMode = true;
bool motionDetected = false;
bool lightsOn = false;
unsigned long lastMotionTime = 0;
bool diningOff = false;
bool prevButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  pinMode(MOTION_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SYSTEM_LED, OUTPUT);
  pinMode(AUTO_LED, OUTPUT);
  pinMode(MANUAL_LED, OUTPUT);
  pinMode(MOTION_LED, OUTPUT);

  pinMode(LED_ROOM1, OUTPUT);
  pinMode(LED_ROOM2, OUTPUT);
  pinMode(LED_ROOM3, OUTPUT);
  pinMode(LED_ROOM4, OUTPUT);
  pinMode(LED_DINING, OUTPUT);

  allLightsOff();
  digitalWrite(AUTO_LED, HIGH);
  digitalWrite(MANUAL_LED, LOW);
  beep(2, 100); // startup
}

void loop() {
  // Blink system LED
  static unsigned long lastBlink = 0;
  if (millis() - lastBlink > 500) {
    digitalWrite(SYSTEM_LED, !digitalRead(SYSTEM_LED));
    lastBlink = millis();
  }

  // Read LDR
  int ldrValue = analogRead(LDR_PIN);
  bool isNight = (ldrValue < 500);

  // Mode switch
  bool buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW && prevButtonState == HIGH) {
    autoMode = !autoMode;
    digitalWrite(AUTO_LED, autoMode);
    digitalWrite(MANUAL_LED, !autoMode);
    beep(1, 100);
    delay(300);
  }
  prevButtonState = buttonState;

  // IR Remote handling
  if (IrReceiver.decode()) {
    unsigned long code = IrReceiver.decodedIRData.decodedRawData;
    handleRemote(code);
    IrReceiver.resume();
  }

  // Motion detection (IR proximity)
  int motion = digitalRead(MOTION_PIN);
  if (motion == HIGH && autoMode && isNight) {
    digitalWrite(MOTION_LED, HIGH);
    if (!motionDetected) {
      motionDetected = true;
      handleMotionEvent();
    }
  } else if (motion == LOW) {
    digitalWrite(MOTION_LED, LOW);
    motionDetected = false;
  }
}

void handleMotionEvent() {
  static bool firstTrigger = true;
  beep(1, 80);

  if (firstTrigger) {
    allLightsOn();
    firstTrigger = false;
  } else {
    // turn off only dining light
    digitalWrite(LED_DINING, LOW);
    beep(1, 200);
    firstTrigger = true;
  }
}

void handleRemote(unsigned long code) {
  beep(1, 50);
  switch (code) {
    case REMOTE_ROOM1: toggleLight(LED_ROOM1); break;
    case REMOTE_ROOM2: toggleLight(LED_ROOM2); break;
    case REMOTE_ROOM3: toggleLight(LED_ROOM3); break;
    case REMOTE_ROOM4: toggleLight(LED_ROOM4); break;
    case REMOTE_DINING: toggleLight(LED_DINING); break;
    case REMOTE_MODE:
      autoMode = !autoMode;
      digitalWrite(AUTO_LED, autoMode);
      digitalWrite(MANUAL_LED, !autoMode);
      beep(2, 80);
      break;
  }
}

void toggleLight(int pin) {
  digitalWrite(pin, !digitalRead(pin));
}

void allLightsOn() {
  digitalWrite(LED_ROOM1, HIGH);
  digitalWrite(LED_ROOM2, HIGH);
  digitalWrite(LED_ROOM3, HIGH);
  digitalWrite(LED_ROOM4, HIGH);
  digitalWrite(LED_DINING, HIGH);
  lightsOn = true;
}

void allLightsOff() {
  digitalWrite(LED_ROOM1, LOW);
  digitalWrite(LED_ROOM2, LOW);
  digitalWrite(LED_ROOM3, LOW);
  digitalWrite(LED_ROOM4, LOW);
  digitalWrite(LED_DINING, LOW);
  lightsOn = false;
}

void beep(int count, int duration) {
  for (int i = 0; i < count; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(duration);
    digitalWrite(BUZZER_PIN, LOW);
    delay(80);
  }
}
