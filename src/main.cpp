#include "mbed.h"
#include "melodies.h"
#include "fur_elise.h"

// speaker sound effect demo using PWM hardware output
PwmOut speaker(PB_0);
DigitalIn s1(PA_1);
DigitalIn s2(PA_2);
DigitalIn s3(PA_3);
DigitalIn s4(PA_4);
DigitalIn mode(PA_5);

DigitalOut  myled(PC_13);

int scale=10;

void note(float fr,float time){

    //int scale=10;
    
    if (fr>0 && time>0) {
      speaker.period(1.0/fr); // 500hz period
      speaker.write(0.5); //50% duty cycle - max volume
    };
    wait(time/scale);
    speaker.write(0.0);
};

void play_music(int *notes, int *durations, int notes_count) {
  for (int i=0; i<notes_count; i++) {
    note((float)notes[i],(float)durations[i]);
  };
};

int main()
{

    int last_note = 0;
    int duty_cycles = 0;
    
    myled = 0;
 
    note(NOTE_C5,SIXTEENTHNOTE);
    note(NOTE_D5,SIXTEENTHNOTE);
    note(NOTE_E5,SIXTEENTHNOTE);
    note(NOTE_F5,SIXTEENTHNOTE);


    while(1) {

    if (mode==1) {

      if (s1 && s2 && s3 && s4) {
        speaker.write(0.0);
        last_note = 0;
      } else {
        duty_cycles = 0;
        if (last_note==0) { 
          speaker.write(0.5); 
        };
      };
      
      if (s1==0) {
          if (last_note!=1) {
            speaker.period(1.0/NOTE_C5);
            last_note=1;
          };
      } else if (s2==0) {
          if (last_note!=2) {
            speaker.period(1.0/NOTE_E5);
            last_note=2;
          };
      } else if (s3==0) {
          if (last_note!=3) {
            speaker.period(1.0/NOTE_F5);
            last_note=3;
          };
      } else if (s4==0) {
          if (last_note!=4) {
            speaker.period(1.0/NOTE_G5);
            last_note=4;
          };
      };
    } else {
      // Music mode activated
      if (s1==0) {
        play_bethoven();
        duty_cycles = 0;
      } else if (s2==0) {
        play_music(elka_notes, elka_durations, sizeof(elka_notes)/sizeof(elka_notes[0]));
        duty_cycles = 0;
      } else if (s3==0) {
        play_music(jingle_notes, jingle_durations, sizeof(jingle_notes)/sizeof(jingle_notes[0]));
        duty_cycles = 0;
      } else if (s4==0) {
        play_music(gusi_notes, gusi_durations, sizeof(gusi_notes)/sizeof(gusi_notes[0]));
        duty_cycles = 0;
      };
    };
     duty_cycles++;
     if (duty_cycles>6000) {
       note(NOTE_F5,SIXTEENTHNOTE);
       note(NOTE_E5,SIXTEENTHNOTE);
       note(NOTE_D5,SIXTEENTHNOTE);
       note(NOTE_C5,SIXTEENTHNOTE);
       duty_cycles=0;
       myled = 1;
       HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,PWR_STOPENTRY_WFE);
     };

     wait(0.05);
  };
};