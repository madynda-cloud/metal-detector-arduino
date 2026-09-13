#define CAPACITOR_PIN A5
#define BUZZER_PIN 9
#define PULSE_PIN A4
#define LED_PIN 10

const int NUM_SAMPLES = 256;
const int PULSE_COUNT = 3;

long sumExpect = 0;
long ignoredSums = 0;
long buzzerPeriod = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PULSE_PIN, OUTPUT);
  digitalWrite(PULSE_PIN, LOW);
  pinMode(CAPACITOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int minValue = 1023;
  int maxValue = 0;
  long unsigned int sum = 0;

  for (int i = 0; i < NUM_SAMPLES; i++) {
    resetCapacitor();

    // Read the charge of the capacitor
    int value = analogRead(CAPACITOR_PIN);
    minValue = min(value, minValue);
    maxValue = max(value, maxValue);
    sum += value;

    updateBuzzerAndLED();
  }

  // Remove spikes by subtracting minimum and maximum values
  sum -= minValue;
  sum -= maxValue;

  if (sumExpect == 0) {
    sumExpect = sum << 6; // Set sumExpect to expected value
  }

  long int avgSum = (sumExpect + 32) >> 6;

  long int difference = sum - avgSum;

  if (abs(difference) < avgSum >> 10) {
    sumExpect = sumExpect + sum - avgSum;
    ignoredSums = 0;
  } else {
    ignoredSums++;
  }

  if (ignoredSums > 64) {
    sumExpect = sum << 6;
    ignoredSums = 0;
  }

  if (difference == 0) {
    buzzerPeriod = 1000000;
  } else {
    buzzerPeriod = avgSum / (2 * abs(difference));
  }
}

void resetCapacitor() {
  pinMode(CAPACITOR_PIN, OUTPUT);
  digitalWrite(CAPACITOR_PIN, LOW);
  delayMicroseconds(20);
  pinMode(CAPACITOR_PIN, INPUT);
  applyPulses();
}

void applyPulses() {
  for (int i = 0; i < PULSE_COUNT; i++) {
    digitalWrite(PULSE_PIN, HIGH);
    delayMicroseconds(3);
    digitalWrite(PULSE_PIN, LOW);
    delayMicroseconds(3);
  }
}

void updateBuzzerAndLED() {
  long unsigned int currentTime = millis();
  char buzzerState = 0;

  if (currentTime < buzzerPeriod + 10 || currentTime > buzzerPeriod + buzzerPeriod) {
    if (difference > 0) {
      buzzerState = 1;
    } else if (difference < 0) {
      buzzerState = 2;
    }
    buzzerPeriod = currentTime;
  }

  if (buzzerPeriod > 300) {
    buzzerState = 0;
  }

  if (buzzerState == 0) {
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  } else if (buzzerState == 1) {
    tone(BUZZER_PIN, 2000);
    digitalWrite(LED_PIN, HIGH);
  } else if (buzzerState == 2) {
    tone(BUZZER_PIN, 500);
    digitalWrite(LED_PIN, HIGH);
  }
}