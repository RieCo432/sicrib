#define HWSerial Serial2

void setup() {
  HWSerial.setTX(8);
  HWSerial.setRX(7);
  HWSerial.begin(115200);

  Serial.begin(2000000);

}

void loop() {
  if (HWSerial.available() > 0) {
    String rec = HWSerial.readStringUntil('\n');
    int final = rec.toFloat();
    Serial.println(rec);
  }
  if (Serial.available() > 0) {
    Serial.println(Serial.readStringUntil('\n'));
  }

}
