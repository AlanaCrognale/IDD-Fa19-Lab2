
#include "pitches.h"
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define ENC_A 6 //these need ato be digital input pins
#define ENC_B 7

// notes in the melody:
int melodyWin[] = {NOTE_C3,NOTE_E3,NOTE_G3,NOTE_C4,0};
int melodyLose[] = {NOTE_C3,NOTE_E2,NOTE_DS2,NOTE_C2,0};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {4,4,4,1,1};

int start;
int buttonOne;
int buttonTwo;
int buttonThree;
int difficulty;
int order[100];
int response[100];
bool flag;
int i;
int index;
int seconds;


void setup() {
  randomSeed(analogRead(0));//randomize seed for simon says pattern
  buttonOne = 0;
  buttonTwo = 0;
  buttonThree = 0;
  start = 0;
  flag = true;
  index = 0;
  seconds = 0;
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Turn the knob");

  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(10,LOW);
  digitalWrite(9,LOW);
  digitalWrite(8,LOW);
  pinMode(10,INPUT);
  pinMode(9,INPUT);
  pinMode(8,INPUT);
}

void loop() {
  buttonOne = digitalRead(8);
  buttonTwo = digitalRead(9);
  buttonThree = digitalRead(10);
  static unsigned int counter4x = 0;      //the SparkFun encoders jump by 4 states from detent to detent
  static unsigned int counter = 0;
  static unsigned int prevCounter = 0;
  int tmpdata;
 
  if (start == 0){//setting seconds/difficulty
  tmpdata = read_encoder();
  if( tmpdata) {
    counter4x += tmpdata;
    counter = counter4x/4;
    if (prevCounter != counter){
      lcd.clear();
      lcd.print(counter);
      lcd.print(" seconds");
      }
    prevCounter = counter;
    }
   if (buttonOne){ //press button to set time/difficulty
    start = 1;
    }
    difficulty = counter;
    if (counter >=100){ //in case someone sets timer to 100+
      int diffulty = 100;
     }
  }
  else if (start == 1){ //randomized pattern is displayed
    delay(500);
    pinMode(10,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(8,OUTPUT);

    for (int i = 0; i < difficulty; i++) {
      order[i]= random(8,11);
      digitalWrite(order[i],HIGH);
      delay(500);
      digitalWrite(order[i],LOW);
      delay(500);
    }
  
    if (order[difficulty-1] != 0 ){ //once pattern has fully been displayed, move to next state
      start = 2;
    } 
  }
  else if (start == 2){//timer countdown for to memorize
  int currentSec= millis();
  if (currentSec - seconds >= 1000) {
   lcd.clear();
   lcd.print(counter);
   lcd.print(" seconds left");
    seconds = currentSec;
    counter = counter - 1;
  }
  
   pinMode(10,INPUT);
   pinMode(9,INPUT);
   pinMode(8,INPUT);
   
   if (buttonOne){ //ready to play
     lcd.clear();
     lcd.print("Begin! ");
     delay(500);
     start = 3;
   }
  
    if (counter == 65535){ //no button pressed, time out - LOSE
      start = 5;
    }
  }
  else if (start == 3){//record user input
    if (buttonOne){
      delay(250);
      response[index] = 8;
      index = index + 1;
       }
    if (buttonTwo){
      delay(250);
      response[index] = 9;
      index = index + 1;
    }
    if (buttonThree){
      delay(250);
      response[index] = 10;
      index = index + 1;
    }
    
    if (index == difficulty){ //once buttons have been pressed
      for (int i = 0; i < difficulty; i++){
        if (order[i] != response[i]){
          flag = false; //incorrect pattern
        }
      }
      if (flag){
        start = 6; //correct pattern
      }
      else{
        start = 4; //incorrect pattern
      }
    }
  }
  else if (start == 4){ //incorrect pattern pressed - LOSE
    lcd.noDisplay();
    delay(500);
    lcd.display();
    lcd.clear();
    lcd.print("Wrong pattern, ");
    lcd.setCursor(0,1);
    lcd.print("you lose!");
    delay(500);

    for (int thisNote = 0; thisNote < 5; thisNote++) {//play losing melody
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote]; //FOR LAB: changed from 1000 to 500
    tone(2, melodyLose[thisNote], noteDuration);        //FOR LAB: playing stars wars song (check which one though)

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(2);
    }
  }
  else if (start == 5){ //ran out of time before pressing button to 'begin'
    lcd.noDisplay();
    delay(500);
    lcd.display();
    lcd.clear();
    lcd.print("Time's up,");
    lcd.setCursor(0, 1);
    lcd.print("you lose!");
    delay(500); 
    
    for (int thisNote = 0; thisNote < 5; thisNote++) {//play losing melody
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote]; //FOR LAB: changed from 1000 to 500
    tone(2, melodyLose[thisNote], noteDuration);        //FOR LAB: playing stars wars song (check which one though)

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(2);
   }
  }
  else if (start == 6){ //correct pattern - WIN
    lcd.noDisplay();
    delay(500);
    lcd.display();
    lcd.clear();
    lcd.print("Congrats, ");
    lcd.setCursor(0, 1);
    lcd.print("you win!");
    delay(500);
    for (int thisNote = 0; thisNote < 5; thisNote++) {
      // to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurations[thisNote]; //FOR LAB: changed from 1000 to 500
      tone(2, melodyWin[thisNote], noteDuration);        //FOR LAB: playing stars wars song (check which one though)

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(2);
    } 
  }
}


/* returns change in encoder state (-1,0,1) */
int read_encoder()
{
  static int enc_states[] = {
    0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0  };
  static byte ABab = 0;
  ABab *= 4;                   //shift the old values over 2 bits
  ABab = ABab%16;      //keeps only bits 0-3
  ABab += 2*digitalRead(ENC_A)+digitalRead(ENC_B); //adds enc_a and enc_b values to bits 1 and 0
  return ( enc_states[ABab]);
}
