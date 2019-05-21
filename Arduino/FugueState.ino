int incomingByte = 0;   // for incoming serial data

int modVal;

int statusFlag=10; // Last Status Byte was 0: NoteOn 1: NoteOff 2: CC

int action=5;

byte note;
byte velocity;

int midiChannel = 0;

boolean noteOn1 = false;
boolean noteOn2 = false;
boolean noteOn3 = false;
boolean noteOn4 = false;
boolean noteOn5 = false;
boolean noteOn6 = false;



void setup() {

  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
  TCCR0B = _BV(CS00);

  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM12) | _BV(WGM10);
  TCCR1B = _BV(CS00);

  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS00);

  pinMode(5, OUTPUT);//Timer 0
  pinMode(6, OUTPUT);

  pinMode(9, OUTPUT);//Timer 1
  pinMode(10, OUTPUT);

  pinMode(11, OUTPUT);  //Timer 2A
  pinMode(3, OUTPUT);   //Timer 2B
  Serial.begin(31250);
}

void loop() {

  if(Serial.available() > 0)
  {
    incomingByte = Serial.read();

    if (incomingByte == (144 + midiChannel)) {
      statusFlag = 0;
      action = 0;
    }

    else if (incomingByte == (128 + midiChannel)) {
      statusFlag = 1;
      action = 0;
    }

    else if (incomingByte == (176 + midiChannel)) {
      statusFlag = 2;
      action = 0;
    }

    else if (incomingByte > 127) {
    }

    else if (action == 0 && statusFlag == 0) {
      note = incomingByte;
      action = 1;
    }
    else if (action == 0 && statusFlag == 1) {
      note = incomingByte;
      action = 1;
    }
    else if (action == 1 && statusFlag == 0) {
      if (note == 60) {
        noteOn1 = true;
        OCR0A = incomingByte + 128;
      }
      else if (note == 61) {
        noteOn2 = true;
        OCR0B = incomingByte + 128;
        //bitWrite(PORTD, 5, 1);
      }
      else if (note == 62) {
        noteOn3 = true;
        OCR1A = incomingByte + 128;
      }
      else if (note == 63) {
        noteOn4 = true;
        OCR1B = 255;
      }
      else if (note == 64) {
        noteOn5 = true;
        OCR2A = incomingByte + 128;
      }
      else if (note == 65) {
        noteOn6 = true;
        OCR2B = incomingByte + 128;
      }
      action =0;
    }
    else if (action == 1 && statusFlag == 1) {

      if (note == 60) {
        noteOn1 = false;
        OCR0A = 0;
      }
      else if (note == 61) {
        noteOn2 = false;
        OCR0B = 0;
        //bitWrite(PORTD, 5, 0);
      }
      else if (note == 62) {
        noteOn3 = false;
        OCR1A = 0;
      }
      else if (note == 63) {
        noteOn4 = false;
        OCR1B = 0;
      }
      else if (note == 64) {
        noteOn5 = false;
        OCR2A = 0;
      }
      else if (note == 65) {
        noteOn6 = false;
        OCR2B = 0;
      }
      action = 0;
    }
    else {
    }
  }
}
/*
    if (incomingByte == (176 + midiChannel)){
 action = 0;
 statusFlag = 1; // (mod wheel A)
 }
 else if (incomingByte == (176 + midiChannel)){
 action = 0;
 statusFlag = 2; // (mod wheel A)
 }
 else if (incomingByte > 127) {
 }
 else if (action == 0 && statusFlag == 1 && incomingByte == 1){
 action = 1;
 }
 else if (action == 0 && statusFlag == 2 && incomingByte == 1){
 action = 1;
 }
 else if (action == 1 && statusFlag == 1) {
 modVal = 127 + incomingByte;
 //analogWrite (5, modVal);
 OCR1B = modVal;
 action = 0;
 }
 else if (action == 1 && statusFlag == 2) {
 modVal = 127 + incomingByte;
 //analogWrite (6, modVal);
 OCR1A = modVal;
 action = 0;
 }
 
/*
 if (incomingByte == (144 + midiChannelA)){
 digitalWrite (13, HIGH);
 }
 else if (incomingByte == (128 + midiChannelA)){
 digitalWrite (13, LOW);
 }
 */

















