/*This projects is an avanced access control.
 * First of all the secret code is table.
 * If you write a wrong acces code the buzzer will start to beep.
 * To put it in silence you must write sorry. 
*/

//For the LCD screen(16x2)
#include <LiquidCrystal.h>

//For the keypad(4x4)
#include <Key.h>
#include <Keypad.h>

//I declarate the buzzer
int BUZZERPIN=16;         //Where is colocated the pin
int buzzerFrequency=220;  //Frequency of A

//I declate the keypad

const byte ROWS=4;
const byte COLUMNS=4;

char keys[ROWS][COLUMNS]= {
  {'A','H','B','S'},
  {'E','O','R','L'},
  {'Z','X','Y','M'},
  {'Q','U','N','T'}
};

byte pinsRow[ROWS]={11,10,9,8};           //Where are colocated the pins
byte pinsColumn[COLUMNS]={12,13,14,15};   //Where are colocated the pins

Keypad keyBoard= Keypad(makeKeymap(keys), pinsRow, pinsColumn, ROWS, COLUMNS);

char key;
char code[5];
char secretCode[5]="TABLE";
char silence[5]="SORRY";
byte number=0;

//I declarate the LCD screen
LiquidCrystal lcd(7,6,5,4,3,2);     //Where are colocated the pins



void setup() {
  lcd.begin(16,2); //Inicializated the LCD
}

void loop() {
  lcd.setCursor(0,0);                                       //I put the start position in LCD
  lcd.write("Insert the code:");
  lcd.setCursor(0,1);                                       //Change the line
  key=keyBoard.getKey();  
  if (key){                                                 //Write the code LCD
    code[number]=key;
    number++;
    lcd.print(key);
  }
  if (number==4){                                           //It start the comparation
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    for (int i=0; i<=number; i++) lcd.write(code[i]);       //It write again the code
    lcd.setCursor(0,1);
    if (!strcmp(code,secretCode)){                          //It sais if the code is true and turn off the buzzer
      lcd.print("Correct");
      noTone(BUZZERPIN);
    }
    if (!strcmp(code, silence)){                            //It turn off the buzzer
      lcd.print ("Silenced");
      noTone(BUZZERPIN);
    }
    else{                                                   //It sais that the code is false and turn on the buzzer
      lcd.print("You wrong");
     tone(BUZZERPIN, buzzerFrequency);
     }
    delay(2000);
    lcd.clear();                                            //Clear the LCD
  }
}
