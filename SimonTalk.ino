
const int pinRedKey = 6;
const int pinGreenKey = 7;
const int pinYellowKey = 8;
const int pinBlueKey = 9;
const int pinRedLed = 10;
const int pinGreenLed = 11;
const int pinYellowLed = 12;
const int pinBlueLed = 13;

int curKey = 0;
int Arr[256];

void setup() {
  // put your setup code here, to run once:
//randomSeed(analogRead(0));
pinMode(pinRedKey, INPUT);
pinMode(pinGreenKey, INPUT);
pinMode(pinYellowKey, INPUT);
pinMode(pinBlueKey, INPUT);
pinMode(pinRedLed, OUTPUT);
pinMode(pinGreenLed, OUTPUT);
pinMode(pinYellowLed, OUTPUT);
pinMode(pinBlueLed, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  randomSeed(analogRead(0)); // init random
  for(int i=0;i<256;i++)
  {
    Arr[i] = (int)random(0,4);
  }
  for(int i=0;i<10;i++)
  {
    digitalWrite(Arr[i]+pinRedLed, HIGH);
    delay(500);
    digitalWrite(Arr[i]+pinRedLed, LOW);
    delay(100);
  }
  delay(2000);/*
  for(;;);
  for(int i=pinRedKey;i<=pinBlueKey;i++)
  {
    int key = getKey(i);
    if(key != curKey)
    {
      curKey = key;
      switchLed(key);
    }
  }*/
}

int getKey(int prevKey)
{
  int key = 0;
  delay(5);
  if(digitalRead(pinRedKey) == LOW) key = pinRedKey;
  else if(digitalRead(pinGreenKey) == LOW) key = pinGreenKey;
  else if(digitalRead(pinYellowKey) == LOW) key = pinYellowKey;
  else if(digitalRead(pinBlueKey) == LOW) key = pinBlueKey;
  //if(key == prevKey)return 0;
  return key;
}
void switchLed(int pinkey)
{
  digitalWrite(pinRedLed, LOW);
  digitalWrite(pinGreenLed, LOW);
  digitalWrite(pinYellowLed, LOW);
  digitalWrite(pinBlueLed, LOW);
  if(pinkey != 0)
    digitalWrite(pinkey + 4, HIGH);
}

