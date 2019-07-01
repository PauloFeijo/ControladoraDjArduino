const int QTDPOTENC = 6;
const int QTDBUT = 6;

const int INITMIDI = 176;

int valuePotenc[QTDPOTENC];
int lastValuePotenc[QTDPOTENC];

int valueBut[QTDBUT];
int lastValueBut[QTDBUT];

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < QTDBUT; i++) {
    pinMode(i+2, INPUT_PULLUP);
  }  
}

void loop() { 
  for (int i = 0; i < QTDPOTENC; i++) {
    valuePotenc[i] = analogRead(i) / 8;

    if (valuePotenc[i] != lastValuePotenc[i]){
      msgMIDI(INITMIDI + i, valuePotenc[i]); 
      lastValuePotenc[i] = valuePotenc[i];  
    }
  }

  for (int i = 0; i < QTDBUT; i++) {
    valueBut[i] = digitalRead(i+2);

    if (valueBut[i] != lastValueBut[i]){
      msgMIDI(INITMIDI + QTDPOTENC + i, valueBut[i]); 
      lastValueBut[i] = valueBut[i];  
    }
  }  

  delay(10);
}

void msgMIDI(byte cmd, byte data) {
  Serial.write(cmd);
  Serial.write(1);
  Serial.write(data);
}
