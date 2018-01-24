#include <stdarg.h>

//digitalWrite_shift_register_74HC595
//by Simon Andreas Huber
//22.12.2017

//note: first pin is 0

int SH_CP = 13; //defining pins
int ST_CP = 12;
int DS = 11;

int nr_shift_register = 3; //number of shift registers
int comb = 0;

void digWr(int pin_nr, boolean state){
  if(state == HIGH){
    comb = comb | (1 << pin_nr);
  } else {
    comb = comb & ((1 << (nr_shift_register*8)) -1 -(1 << pin_nr));
  }
  for(int n = (nr_shift_register - 1); n >= 0 ;n--){
    shiftOut(DS, SH_CP, MSBFIRST, 255 & (comb >> (8*n)));
  }
    digitalWrite(ST_CP, HIGH); digitalWrite(ST_CP, LOW);
  }

void setup() {
  pinMode(SH_CP, OUTPUT);
  pinMode(ST_CP, OUTPUT);
  pinMode(DS, OUTPUT);

}

void loop() {

  for(int i = 0; i < 24; i++){ //example
  
    digWr(i, HIGH);
    delay(50);
    digWr(i, LOW);
    delay(50);
    
  }
  
}

