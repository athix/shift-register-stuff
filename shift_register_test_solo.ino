//pin connections- the #define tag will replace all instances of "latchPin" in your code with A1 (and so on)
#define clockPin A0
#define latchPin A1
#define dataPin A2
#define MINREF 1
#define MAXREF 100
#define ROC 15

int x;
int refresh = MAXREF;
int rateOfChange = -(ROC);

//storage variable
byte dataToSend;
byte reversedDataToSend;

void setup() {
  //set pins as output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  if(refresh < MINREF) {
    refresh = MINREF;
    rateOfChange = ROC;
  }
  if(refresh > MAXREF) {
    refresh = MAXREF;
    rateOfChange = -(ROC);
  }
  // Set data to write
  dataToSend = 1;
  reversedDataToSend = 128;

  // Output
  writeLeds(dataToSend, reversedDataToSend);
  delay(refresh);

  // Loop other LEDs
  for(x=0; x<7; x++) {
    dataToSend = (dataToSend << 1);
    reversedDataToSend = (reversedDataToSend >> 1);
    writeLeds(dataToSend, reversedDataToSend);
    delay(refresh);
  }

  // Skip the last LED as it will be lit by the next cycle
  for(x=0; x<6; x++) {
    dataToSend = (dataToSend >> 1);
    reversedDataToSend = (reversedDataToSend << 1);
    writeLeds(dataToSend, reversedDataToSend);
    delay(refresh);
  }
  refresh = refresh + rateOfChange;
}

void writeLeds(byte ledData1, byte ledData2) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, ledData1);
  shiftOut(dataPin, clockPin, LSBFIRST, ledData2);
  digitalWrite(latchPin, HIGH);
}
