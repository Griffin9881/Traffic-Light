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
    // PLAY: OFF
    case 41:
      setLED(0, 0, 0);
      break;
    // WHITE: ALL ON
    case 44:
      setLED(1, 1, 1);
      break;
    // YELLOW ONLY
    case 45:
      setLED(0, 1, 0);
      break;
    // BLINK YELLOW
    case 49:
      setLED(0, 1, 0);
      PT_WAIT_UNTIL(pt, millis() - timestamp > 1000 || interruptFlag);
      timestamp = millis();
      setLED(0, 0, 0);
      PT_WAIT_UNTIL(pt, millis() - timestamp > 1000 || interruptFlag);
      timestamp = millis();
      break;
    // BLINK RED
    case 54:
      setLED(0, 0, 1);
      PT_WAIT_UNTIL(pt, millis() - timestamp > 1000 || interruptFlag);
      timestamp = millis();
      setLED(0, 0, 0);
      PT_WAIT_UNTIL(pt, millis() - timestamp > 1000 || interruptFlag);
      timestamp = millis();
      break;
    // BLINK GREEN
    case 55:
      setLED(1, 0, 0);
      PT_WAIT_UNTIL(pt, millis() - timestamp > 1000 || interruptFlag);
      timestamp = millis();
      setLED(0, 0, 0);
      PT_WAIT_UNTIL(pt, millis() - timestamp > 1000 || interruptFlag);
      timestamp = millis();
      break;
    // RED ONLY
    case 58:
      setLED(0, 0, 1);
      break;
    // GREEN ONLY
    case 59:
      setLED(1, 0, 0);
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