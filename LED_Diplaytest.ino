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

void setPin(uint8_t digit, uint8_t segment){
  pinMode(digit, OUTPUT);
  digitalWrite(digit, HIGH);
  pinMode(segment, OUTPUT);
  digitalWrite(segment, LOW);
  delay(1);
  pinMode(segment,INPUT);
  pinMode(digit, INPUT);
}

void writeDigit(uint8_t digit, uint8_t val){
  uint8_t bits=chartab[val];
  for(uint8_t i=0; i<=7; i++){
    if((1<<i) & bits) setPin(up[digit], down[i]);
  }
}

void loop() {
  for(int num=0; num<=3999; num++){
    for(int digit=0, count=num; digit<4; digit++, count/=10){
      if(!(digit==3 && num<1000)) writeDigit(digit, count%10);
    }
  }
}
