#include <stdint.h>

// Used Pin Array
uint8_t up[]={5, 4, 3, 2};
uint8_t down[]={ 6, 7, 8, 9, 10, 11, 15, 16 }; //5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

uint8_t chartab[] = {
  0b01110111, //0
  0b00010010, //1
  0b01011101, //2
  0b01011011, //3
  0b00111010, //4
  0b01101011, //5
  0b01101111, //6
  0b01010010, //7
  0b01111111, //8
  0b01111010, //9
  0b01111110, //A
  0b00101111, //b
  0b01100101, //C
  0b00011111, //d
  0b01101101, //E
  0b01101100 //F
};

void setup() {
  for(int i=0; i<sizeof(up); i++){
    pinMode(up[i], INPUT);
  }
  for(int i=0; i<sizeof(down); i++){
    pinMode(down[i], INPUT);
  }
}

void pinOn(uint8_t digit, uint8_t segment){
  pinMode(digit, OUTPUT);
  digitalWrite(digit, HIGH);
  pinMode(segment, OUTPUT);
  digitalWrite(segment, LOW);
}
void pinOff(uint8_t digit, uint8_t segment){
  pinMode(segment,INPUT);
  pinMode(digit, INPUT);
}

void writeDigit(uint8_t digit, uint8_t val){
  uint8_t bits=chartab[val];
  for(uint8_t i=0; i<=7; i++){
    if((1<<i) & bits) {
        pinOn(up[digit], down[i]);
        delay(1);
        pinOff(up[digit], down[i]);
    }
  }
}

void writeHex(int val){
  uint8_t llbits=chartab[val & 0xf];
  uint8_t lhbits=chartab[(val >> 4) & 0xf];
  uint8_t hlbits=chartab[(val >> 8) & 0xf];
  uint8_t hhbits=chartab[(val >> 12) & 0xf];
  for(uint8_t i=0; i<=7; i++){
    if((1<<i) & llbits) pinOn(up[0], down[i]);
    if((val > 0xf) && ((1<<i) & lhbits)) pinOn(up[1], down[i]);
    if((val > 0xff) && ((1<<i) & hlbits)) pinOn(up[2], down[i]);
    if((val > 0xfff) && ((1<<i) & hhbits)) pinOn(up[3], down[i]);
    delay(1);
    pinOff(up[0], down[i]);
    pinOff(up[1], down[i]);
    pinOff(up[2], down[i]);
    pinOff(up[3], down[i]);
  }
}


void loop() {
  for(int num=0; num<=0x3fff; num++){
      writeHex(num);
  }
}
