#define SENSOR_PIN D2

volatile unsigned long counter = 0;
unsigned long lastTime = 0;
float rpm = 0;

void IRAM_ATTR countPulse() {
  counter++;   // tambah 1 setiap magnet lewat
}

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), countPulse, FALLING);

  Serial.println("Test Counter Hall Effect");
}

void loop() {

  if (millis() - lastTime >= 1000) {   // hitung tiap 1 detik

    noInterrupts();
    unsigned long pulse = counter;
    counter = 0;
    interrupts();

    rpm = pulse * 60.0;   // asumsi 1 magnet = 1 putaran

    Serial.print("Pulsa per detik: ");
    Serial.print(pulse);
    Serial.print(" | RPM: ");
    Serial.println(rpm);

    lastTime = millis();
  }
}