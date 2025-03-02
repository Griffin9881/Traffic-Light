// #include <IRremote.hpp>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <pt.h>

#define GREEN_PIN 10
#define YELLOW_PIN 11
#define RED_PIN 12
#define RECV_PIN 13

IRrecv receiver(RECV_PIN);
decode_results results;

static struct pt ledThread, remoteThread;
volatile bool interruptFlag = false;

void setLED(int green, int yellow, int red) {
      digitalWrite(GREEN_PIN, green);
      digitalWrite(YELLOW_PIN, yellow);
      digitalWrite(RED_PIN, red);
}

void setup() {
  Serial.begin(9600);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  PT_INIT(&ledThread);
  PT_INIT(&remoteThread);
  receiver.enableIRIn();
}

void loop()
{
  remoteController(&remoteThread);
  ledController(&ledThread);
}

static int ledController(struct pt *pt) {
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  switch (receiver.decodedIRData.command) {
    // ON: NORMAL CYCLE
    case 40:
      setLED(1, 0, 0);
      PT_WAIT_UNTIL(pt, millis() - timestamp > 20000 || interruptFlag);
      timestamp = millis();
      setLED(0, 1, 0);
      PT_WAIT_UNTIL(pt, millis() - timestamp > 5000 || interruptFlag);
      timestamp = millis();
      setLED(0, 0, 1);
      PT_WAIT_UNTIL(pt, millis() - timestamp > 25000 || interruptFlag);
      timestamp = millis();
      setLED(0, 0, 0);
      break;
    // WHITE: ALL ON
    case 44:
      setLED(1, 1, 1);
      break;
    // PLAY: OFF
    case 41:
      setLED(0, 0, 0);
      break;
    // RED ONLY
    case 58:
      setLED(0, 0, 1);
      break;
    // GREEN ONLY
    case 59:
      setLED(1, 0, 0);
      break;
    // YELLOW ONLY
    case 45:
      setLED(0, 1, 0);
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
  interruptFlag = false;
  PT_END(pt);
}

static int remoteController(struct pt *pt) {
  PT_BEGIN(pt);
  if (receiver.decode()) {
    interruptFlag = true;
    receiver.resume();
  }
  PT_END(pt);
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