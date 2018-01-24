//T_crossroads_trafficlights_prototype_001
//by Simon Andreas Huber
//17.01.2018

#include <stdio.h>
#include <math.h>
#include <stdarg.h>



int wl[9] = {0,0,0,0,0,0,0,0,0}; //waiting list
int ret_comb[3];


int SH_CP = 13; //defining pins
int ST_CP = 12;
int DS = 11;

int nr_shift_register = 3; //number of shift registers
int comb = 0;

int input_state_line_1_new = HIGH; //var for timekiller
int input_state_line_1_old = HIGH;
int input_state_line_2_new = HIGH;
int input_state_line_2_old = HIGH;
int input_state_line_3_new = HIGH;
int input_state_line_3_old = HIGH;
int input_state_line_4_new = HIGH;
int input_state_line_4_old = HIGH;
int input_state_line_5_new = HIGH;
int input_state_line_5_old = HIGH;
int input_state_line_6_new = HIGH;
int input_state_line_6_old = HIGH;
int input_state_line_7_new = HIGH;
int input_state_line_7_old = HIGH;
int input_state_line_8_new = HIGH;
int input_state_line_8_old = HIGH;
int input_state_line_9_new = HIGH;
int input_state_line_9_old = HIGH;
  

void delwl(int del_line){
    //can remove lines form waiting list
      for (int n = 0; n < 9; n++) {
        if (del_line == wl[n]) {
          wl[n] = 0;
          break;
        }
      }
      for (int n = 0; n < 8; n++) {
          if (0 == wl[n]) {
            wl[n] = wl[n+1];
            wl[n+1] = 0;
      }
    }
}

void addwl(int add_line){
    //can add lines to the wating list
      for (int n = 0; n < 9; n++) {
        if (add_line == wl[n]) {
          break;
      }
        if (0 == wl[n]) {
          wl[n] = add_line;
          break;
      }
    }
}

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



void timekiller(unsigned long ms) {

    unsigned long time = millis() + ms;
    
    do {//I use a do while loop to ensure the code is executed at lest one time
      
      input_state_line_1_new = digitalRead(0);
      input_state_line_2_new = digitalRead(1);
      input_state_line_3_new = digitalRead(2);
      input_state_line_4_new = digitalRead(3);
      input_state_line_5_new = digitalRead(4);
      input_state_line_6_new = digitalRead(5);
      input_state_line_7_new = digitalRead(6);
      input_state_line_8_new = digitalRead(7);
      input_state_line_9_new = digitalRead(8);
      
      if((input_state_line_1_old == HIGH) && (input_state_line_1_new == LOW)) {
        addwl(1);
      }
      if((input_state_line_2_old == HIGH) && (input_state_line_2_new == LOW)) {
        addwl(2);
      }
      if((input_state_line_3_old == HIGH) && (input_state_line_3_new == LOW)) {
        addwl(3);
      }
      if((input_state_line_4_old == HIGH) && (input_state_line_4_new == LOW)) {
        addwl(4);
      }
      if((input_state_line_5_old == HIGH) && (input_state_line_5_new == LOW)) {
        addwl(5);
      }
      if((input_state_line_6_old == HIGH) && (input_state_line_6_new == LOW)) {
        addwl(6);
      }
      if((input_state_line_7_old == HIGH) && (input_state_line_7_new == LOW)) {
        addwl(7);
      }
      if((input_state_line_8_old == HIGH) && (input_state_line_8_new == LOW)) {
        addwl(8);
      }
      if((input_state_line_9_old == HIGH) && (input_state_line_9_new == LOW)) {
        addwl(9);
      }
    
      input_state_line_1_old = input_state_line_1_new;
      input_state_line_2_old = input_state_line_2_new;
      input_state_line_3_old = input_state_line_3_new;
      input_state_line_4_old = input_state_line_4_new;
      input_state_line_5_old = input_state_line_5_new;
      input_state_line_6_old = input_state_line_6_new;
      input_state_line_7_old = input_state_line_7_new;
      input_state_line_8_old = input_state_line_8_new;
      input_state_line_9_old = input_state_line_9_new;
    
    } while(millis() < time);
  }

int controller(){
  //finds the optimal combination of lines to get green simultaneous from lines combinations.
  //For this descision it uses:
  //all line combinations (lc) (all meaningfull combinations of lines),
  //the waiting list (wl) (list of lines with waiting cars/pedestrians, the first in the list is the one wating the longest),
  //the traffic volume (tv) (list of all lines, first is the one with statisticly has most traffic, this list is fictional like ervery thing here ;)).

    //declare variables
    const int lc[8][3] = { {1,2,6}, {1,6,8}, {2,3,9}, {2,4,6}, {2,3,4}, {4,5,6}, {4,5,7}, {7,8,9} }; //lines combination
    const int tv[9] = {4,5,3,1,6,2,7,8,9}; //traffic volume
    int lc_refrence =  511; //shows which combs for lc which are active and inactive
    int lc_refrence_len = 8;

    int line_inside = 0;
    for (int i = 0; i < 9; i++) {  //go through wl
      if (wl[i] == 0) {
        break;
      }
      line_inside = 0;  //checking if line form wl is in lc
      for (int k = 0; k < 8; k++) {
        if ((lc_refrence & (1 << k)) == (1 << k)) {
        for (int n = 0; n < 3; n++) {
          if (lc[k][n] == wl[i]) {
            line_inside = 1;
          }
          if (line_inside ==  1) {
            break;
          }
        }
      }
        if (line_inside ==  1) {
          break;
        }
      }
      if (line_inside == 1) {
        for (int p = 0; p < 8; p++) { //isolating combs without line inside
          if (lc[p][0] != wl[i] && lc[p][1] != wl[i] && lc[p][2] != wl[i] && (lc_refrence & (1 << p)) == (1 << p)) {
            lc_refrence = (lc_refrence & (511 - (1 << p)));
            lc_refrence_len--;
          }
        }
      }

      if (lc_refrence_len == 1) {
          for (int z = 0; z < 8; z++) {
            if ((lc_refrence & (1 << z)) == (1 << z)) {
              for (int o = 0; o < 3; o++) {
                ret_comb[o] = lc[z][o];
              }
              return 1;
            }
        }
      }
    }

    for (int i = 0; i < 9; i++) {  //go through tv
      line_inside = 0;  //checking if line form tv is in lc
      for (int k = 0; k < 8; k++) {
        if ((lc_refrence & (1 << k)) == (1 << k)) {
        for (int n = 0; n < 3; n++) {
          if (lc[k][n] == tv[i]) {
            line_inside = 1;
          }
          if (line_inside ==  1) {
            break;
          }
        }
      }
        if (line_inside ==  1) {
          break;
        }
      }
      if (line_inside == 1) {
        for (int p = 0; p < 8; p++) { //isolating combs without line inside
          if (lc[p][0] != tv[i] && lc[p][1] != tv[i] && lc[p][2] != tv[i] && (lc_refrence & (1 << p)) == (1 << p)) {
            lc_refrence = (lc_refrence & (511 - (1 << p)));
            lc_refrence_len--;
          }
        }
      }

      if (lc_refrence_len == 1) {
          for (int z = 0; z < 8; z++) {
            if ((lc_refrence & (1 << z)) == (1 << z)) {
              for (int o = 0; o < 3; o++) {
                ret_comb[o] = lc[z][o];
              }
              return 0;
            }
        }
      }
    }

}


void executter(){

    controller();
     
    int pin;

    for (int i = 0; i < 3; i++) {//red LOW for lines 1-6 and red LOW for lines 7-9

      if (ret_comb[i] < 7) {
        pin = (ret_comb[i]*3) -1;
      }
      if (ret_comb[i] > 6) {
        pin = (ret_comb[i]*2) +5;
      }
      digWr(pin, 0);

    }

    for (int i = 0; i < 3; i++) {//orange HIGH for lines 1-6 and green HIGH for lines 7-9

      if (ret_comb[i] < 7) {
        pin = (ret_comb[i]*3) -2;
      }
      if (ret_comb[i] > 6) {
        pin = (ret_comb[i]*2) +4;
      }
      digWr(pin, 1);

    }
    timekiller(2000);

    for (int i = 0; i < 3; i++) {//orange LOW for lines 1-6

      if (ret_comb[i] < 7) {
        pin = (ret_comb[i]*3) -2;
      } else {
        continue;
      }
      digWr(pin, 0);

    }

    for (int i = 0; i < 3; i++) {//green HIGH for of lines 1-6

      if (ret_comb[i] < 7) {
        pin = (ret_comb[i]*3) -3;
      } else {
        continue;
      }
      digWr(pin, 1);

    }

    timekiller(5000);

    while(((wl[0] == 0) || (wl[0] == 4) || (wl[0] == 5) || (wl[0] == 6)) && ((wl[1] == 0) || (wl[1] == 4) || (wl[1] == 5) || (wl[1] == 6)) && ((wl[2] == 0) || (wl[2] == 4) || (wl[2] == 5) || (wl[2] == 6)) && (ret_comb[0] == 4) && (ret_comb[1] == 5) && (ret_comb[2] == 6)){
      timekiller(27);
  }

          
    for (int i = 0; i < 3; i++) {//green LOW for lines 1-6 and green LOW for lines 7-9

      if (ret_comb[i] < 7) {
        pin = (ret_comb[i]*3) -3;
      }
      if (ret_comb[i] > 6) {
        pin = (ret_comb[i]*2) +4;
      }
      digWr(pin, 0);

    }

    for (int i = 0; i < 3; i++) {//orange HIGH for lines 1-6

      if (ret_comb[i] < 7) {
        pin = (ret_comb[i]*3) -2;
      } else {
        continue;
      }
      digWr(pin, 1);

    }


    for (int n = 0; n < 2; n++) {//green LOW and HIGH flash for lines 7-9

    for (int i = 0; i < 3; i++) {//green HIGH for lines 7-9

      if (ret_comb[i] > 6) {
        pin = (ret_comb[i]*2) +4;
      } else {
        continue;
      }
      digWr(pin, 1);

    }

    timekiller(500);

    for (int i = 0; i < 3; i++) {//green LOw for lines 7-9

      if (ret_comb[i] > 6) {
        pin = (ret_comb[i]*2) +4;
      } else {
        continue;
      }
      digWr(pin, 0);

    }

    timekiller(500);

    }

    for (int i = 0; i < 3; i++) {//orange LOW for lines 1-6

      if (ret_comb[i] < 7) {
        pin = (ret_comb[i]*3) -2;
      } else {
        continue;
      }
      digWr(pin, 0);

    }

    for (int i = 0; i < 3; i++) {//red HIGH for lines 1-6 and red HIGH for lines 7-9

      if (ret_comb[i] < 7) {
        pin = (ret_comb[i]*3) -1;
      }
      if (ret_comb[i] > 6) {
        pin = (ret_comb[i]*2) +5;
      }
      digWr(pin, 1);
    }

   for (int i = 0; i < 3; i++) {//delwl comb

      delwl(ret_comb[i]);
    }

    timekiller(3000);
}
  
void setup() {  
  
  pinMode(SH_CP, OUTPUT);
  pinMode(ST_CP, OUTPUT);
  pinMode(DS, OUTPUT);
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);

  delay(5000);
  shiftOut(DS, SH_CP, MSBFIRST, 255);
  shiftOut(DS, SH_CP, MSBFIRST, 255);
  shiftOut(DS, SH_CP, MSBFIRST, 255);
  digitalWrite(ST_CP, HIGH); digitalWrite(ST_CP, LOW);
  delay(5000);
  shiftOut(DS, SH_CP, MSBFIRST, 170);
  shiftOut(DS, SH_CP, MSBFIRST, 73);
  shiftOut(DS, SH_CP, MSBFIRST, 36);
  digitalWrite(ST_CP, HIGH); digitalWrite(ST_CP, LOW);
  delay(5000);


}

void loop() {
  executter();
  
}
