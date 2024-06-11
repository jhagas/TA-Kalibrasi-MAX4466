const int sampleWindow = 10;
int const AMP_PIN = A0;
unsigned int sample;

void setup() {
  Serial.begin(9600);
}

unsigned int signalMaxAT = 0;

void loop() {
  unsigned long startMillis = millis();
  unsigned int peakToPeak = 0;  // peak-to-peak level
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // collect data for 50 mS and then plot data
  while (millis() - startMillis < sampleWindow) {
    sample = analogRead(AMP_PIN);
    if (sample < 1024)  // toss out spurious readings
    {
      if (sample > signalMax) {
        signalMax = sample;  // save just the max levels
      } else if (sample < signalMin) {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude

  if (peakToPeak > signalMaxAT) {
    Serial.println(peakToPeak);
    signalMaxAT = peakToPeak;
  }
}