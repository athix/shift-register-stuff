//pin connections- the #define tag will replace all instances of "latchPin" in your code with A1 (and so on)
#define clockPin A0
#define latchPin A1
#define dataPin A2
#define MINREF 100
#define MAXREF 500
#define ROC 50

int x;
int refresh = MAXREF;
int rateOfChange = -(ROC);

//storage variable
byte dataToSend;

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

  // Output
  writeLeds(dataToSend);
  delay(refresh);

  // Loop other LEDs
  for(x=0; x<7; x++) {
    dataToSend = (dataToSend << 1);
    writeLeds(dataToSend);
    delay(refresh);
  }

  // Skip the last LED as it will be lit by the next cycle
  for(x=0; x<6; x++) {
    dataToSend = (dataToSend >> 1);
    writeLeds(dataToSend);
    delay(refresh);
  }
  refresh = refresh + rateOfChange;
}

void writeLeds(byte ledData) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, ledData);
  digitalWrite(latchPin, HIGH);
}
