#include <Password.h> //http://www.arduino.cc/playground/uploads/Code/Password.zip
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip

#define relay 10

Password password = Password( "123456" );

const byte ROWS = 4; // Four rows
const byte COLS = 4; //  columns

// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = { 9,8,7,6 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 5,4,3,2, };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.

// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){

  Serial.begin(9600);
  
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
  
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
}

void loop(){
  keypad.getKey();
}

//take care of some special events
void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
    case PRESSED:
	Serial.print("Pressed: ");
	Serial.println(eKey);
	switch (eKey){
	  case '*': checkPassword(); break;
	  case '#': resetar(); break;
	  default: password.append(eKey);
     }
  }
}

void checkPassword(){
  if (password.evaluate()){
    Serial.println("Success");
    //Add code to run if it works
    resetar();
    digitalWrite(relay, LOW);
    delay(1500);
    digitalWrite(relay, HIGH);
  }else{
    //add code to run if it did not work
    Serial.println("Wrong");
    resetar();
  }
}

void resetar(){
  password.reset();
}
