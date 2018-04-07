#include <stdarg.h>

//digitalWrite_shift_register_74HC595
//by Simon Andreas Huber
//22.12.2017

//note: first pin is 0

int SH_CP = 13; //defining pins
int ST_CP = 12;
int DS = 11;

const int nr_shift_register = 3; //number of shift registers
int comb[nr_shift_register];


void digWr_exec(int pin_nr_exec, int state_exec, int nr_shift_register_exec){

  if(state_exec == 1){
    comb[nr_shift_register_exec] = comb[nr_shift_register_exec] | (1 << pin_nr_exec);
  } else {
    comb[nr_shift_register_exec] = comb[nr_shift_register_exec] & (255 -(1 << pin_nr_exec));
  }
}

void digWr(int pin_nr, int state){

  for (int i = 0; i < nr_shift_register; i++) {
    if (pin_nr >= (i*8) && pin_nr < ((i+1)*8) ) {
      digWr_exec( pin_nr - (i*8), state, i);
      break;
    }
}
    for(int n = (nr_shift_register - 1); n >= 0 ;n--){
      shiftOut(DS, SH_CP, MSBFIRST,comb[n]);
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

