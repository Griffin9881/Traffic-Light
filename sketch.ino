// #include <IRremote.hpp>
#include <IRremote.h>
#include <IRremoteInt.h>

int RECV_PIN = 13;
IRrecv receiver(RECV_PIN);
decode_results results;

 // name your pins:
int green = 10;
int yellow = 11;
int red = 12;

// the setup routine runs once when you press reset:
void setup() {               
  // initialize the digital pin as an output.
  Serial.begin(9600);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  receiver.enableIRIn();
}
// int  var = 0; //defines and sets initial value for variables used below
// int var1 = 0; //defines and sets initial value for variables used below

// the loop routine runs over and over again forever:
void loop()
{
  // Checks received an IR signal
  if (receiver.decode()) {
    translateIR();
    receiver.resume();  // Receive the next value
  }
}

void translateIR() {
  // Takes command based on IR code received
  switch (receiver.decodedIRData.command) {
    case 162:
      digitalWrite(red, LOW);
      digitalWrite(yellow, LOW);
      digitalWrite(green, HIGH);   
      delay(20000);               // holds the green light on for 20 seconds
      digitalWrite(green, LOW);    // turns the green light off
      delay(600);               // slight pause between lights
      digitalWrite(yellow, HIGH);  //turns the yellow light on
      delay(4000); //holds the yellow light for 4 seconds (watch out for that red-light camera!)
      digitalWrite(yellow, LOW); //turns the yellow light off
      delay(600);  //slight pause between lights
      digitalWrite(red, HIGH);  //turns the red light on
      delay(20000);  //holds the red light on for 20 seconds
      digitalWrite(red, LOW);  //turns the red light off
      delay(600);  //slight pause between lights
      break;
    case 226:
    digitalWrite(green, HIGH);
      digitalWrite(yellow, HIGH);
      digitalWrite(red, HIGH);
      break;
    case 34:
      break;
    case 2:
      break;
    case 194:
      break;
    case 224:
      break;
    case 168:
      break;
    case 144:
      break;
    case 104:
      break;
    case 152:
      break;
    case 176:
      break;
    case 48:
      break;
    case 24:
      break;
    case 122:
      break;
    case 16:
      break;
    case 56:
      break;
    case 90:
      break;
    case 66:
      break;
    case 74:
      break;
    case 82:
      break;
    default:
      break;
  }
}

// sets initial value for pins so that lights start as "off" 
// digitalWrite(green, LOW);
// digitalWrite(yellow, LOW);
// digitalWrite(red, LOW);
// if(receiver.decode(&results)){}
// if(results.value == 0xFFA25D){
//   // repeats normal cycle 25 times
//   digitalWrite(green, HIGH);   // turns the green light on
//   delay(20000);               // holds the green light on for 20 seconds
//   digitalWrite(green, LOW);    // turns the green light off
//   delay(600);               // slight pause between lights
//   digitalWrite(yellow, HIGH);  //turns the yellow light on
//   delay(4000); //holds the yellow light for 4 seconds (watch out for that red-light camera!)
//   digitalWrite(yellow, LOW); //turns the yellow light off
//   delay(600);  //slight pause between lights
//   digitalWrite(red, HIGH);  //turns the red light on
//   delay(20000);  //holds the red light on for 20 seconds
//   digitalWrite(red, LOW);  //turns the red light off
//   delay(600);  //slight pause between lights
//   var++;}  //adds 1 to variable "var" for repeat count
 
//   // after 25 cycles above, the light switches to "power outage mode", flashing red
//   delay(600); //slight delay
//   var1=0; //resets variable "var1" to 0
//   while(var1 < 120) {
//     // repeats power outage cycle 120 times - 2 minutes
//    digitalWrite(red, HIGH);
//    delay(600);
//    digitalWrite(red, LOW);
//    delay(400);
//    var1++;}
// var = 0
 
//  //switches to "late night cycle" flashing yellow for 2 minutes, similar to flashing red above
//  var1=0;
//   while(var1 < 120) {
//    digitalWrite(yellow, HIGH);
//    delay(600);
//    digitalWrite(yellow, LOW);
//    delay(400);
//    var1++;}
//    var = 0;
 //goes back to normal cycle at top and repeats forever 