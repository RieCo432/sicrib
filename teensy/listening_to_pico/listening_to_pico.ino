#define HWSerial Serial2
#define NUM_BINS 10

float bins[NUM_BINS];

void setup() {
  HWSerial.setTX(8);
  HWSerial.setRX(7);
  HWSerial.begin(115200);

  Serial.begin(2000000);

}

void loop() {
  if (HWSerial.available() > 0) {
    String str = HWSerial.readStringUntil('\n');
    char * rec = str.c_str();
    //fscanf(rec, "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f", bins[0], bins[1], bins[2], bins[3], bins[4], bins[5], bins[6], bins[7], bins[8], bins[9]);
    char * strtokIndex;
    
    //Serial.println(rec);
    strtokIndex = strtok(rec, ",");
    bins[0] = atof(strtokIndex);
    strtokIndex = strtok(NULL, ",");
    bins[1] = atof(strtokIndex);
    strtokIndex = strtok(NULL, ",");
    bins[2] = atof(strtokIndex);
    strtokIndex = strtok(NULL, ",");
    bins[3] = atof(strtokIndex);
    strtokIndex = strtok(NULL, ",");
    bins[4] = atof(strtokIndex);
    strtokIndex = strtok(NULL, ",");
    bins[5] = atof(strtokIndex);
    strtokIndex = strtok(NULL, ",");
    bins[6] = atof(strtokIndex);
    strtokIndex = strtok(NULL, ",");
    bins[7] = atof(strtokIndex);
    strtokIndex = strtok(NULL, ",");
    bins[8] = atof(strtokIndex);
    strtokIndex = strtok(NULL, "\n");
    bins[9] = atof(strtokIndex);

    Serial.print(bins[0]);
    Serial.print(", ");
    Serial.print(bins[1]);
    Serial.print(", ");
    Serial.print(bins[2]);
    Serial.print(", ");
    Serial.print(bins[3]);
    Serial.print(", ");
    Serial.print(bins[4]);
    Serial.print(", ");
    Serial.print(bins[5]);
    Serial.print(", ");
    Serial.print(bins[6]);
    Serial.print(", ");
    Serial.print(bins[7]);
    Serial.print(", ");
    Serial.print(bins[8]);
    Serial.print(", ");
    Serial.println(bins[9]);
    
  }
  if (Serial.available() > 0) {
    Serial.println(Serial.readStringUntil('\n'));
  }

}
