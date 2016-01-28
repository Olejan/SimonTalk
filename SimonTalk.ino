/*
Creating Date 38.01.2016
Created by Oleg Glytenko
Email: buran1td@mail.ru
*/


/*
Blue - E - 329.628 Hz - 1517
Yellow - C# - 277.18 Hz - 1804
Red - A - 440 Hz - 1136
Green - E - 164.81 Hz - 3034
*/
const int pinRedKey = 6;
const int pinGreenKey = 7;
const int pinYellowKey = 8;
const int pinBlueKey = 9;
const int pinRedLed = 10;
const int pinGreenLed = 11;
const int pinYellowLed = 12;
const int pinBlueLed = 13;
const int pinBeep = 5;

int Arr[256]; // игровой массив
int CurPos = 0; // текущая позиция курсора в Arr
int CurDur = 500;
int CurPauseDur = 100;
int Muse[4] = {440, 165, 277, 330};

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
  pinMode(pinBeep, OUTPUT);
  for(int i = 120; i <= 165; i+=3)
  {
    tone(pinBeep, i, 35);
    delay(35);
  }
  delay(500);
}

void loop()
{
  // put your main code here, to run repeatedly:
  randomSeed(analogRead(0)); // init random
  int arrSize = sizeof(Arr)/sizeof(Arr[0]);
  for(int i=0; i<arrSize; i++)// населяем массив
  {
    Arr[i] = (int)random(0,4);
  }
  while(CurPos < arrSize)
  {
    for(int i = 0; i <= CurPos; i++)// ход компьютера
    {
      play(Arr[i]);// играем звук и цвет
    }
    for(int i = 0; i <= CurPos; i++)// ход игрока
    {
      while(1)
      {
        int key = getKey(key);// читаем кнопку
        if(key == 0)continue;
        int curdata = key - pinRedKey;
        if(curdata != Arr[i])// если тон и цвет не совпали
        {
          failGame();
          goto newgame;
        }
        play(curdata);
        break;
      }
    }
    delay(1000);
    CurPos++;
    if(CurPos % 2 == 0) changeDuration();
  }
  winGame();
  newgame:
  initVars();
}
void changeDuration()
{
  int i = CurPos / 2;
  if(i == 1)
  {
    CurDur = 400;
    CurPauseDur = 80;
  }
  else if(i == 2)
  {
    CurDur = 300;
    CurPauseDur = 60;
  }
  else if(i == 3)
  {
    CurDur = 250;
    CurPauseDur = 50;
  }
  else if(i == 4)
  {
    CurDur = 200;
    CurPauseDur = 40;
  }
  else if(i == 5)
  {
    CurDur = 150;
    CurPauseDur = 30;
  }
  else
  {
    CurDur = 100;
    CurPauseDur = 25;
  }
}
void initVars()
{
  CurPos = 0;
  CurDur = 500;
  CurPauseDur = 100;
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
void play(int data)
{
  digitalWrite(data+pinRedLed, HIGH);
  tone(pinBeep, Muse[data]/*, CurDur*/);
  delay(CurDur);
  digitalWrite(data+pinRedLed, LOW);
  noTone(pinBeep);
  delay(CurPauseDur);
}
void failGame()
{
  digitalWrite(pinRedLed, HIGH);
  digitalWrite(pinGreenLed, HIGH);
  digitalWrite(pinYellowLed, HIGH);
  digitalWrite(pinBlueLed, HIGH);
  for(int i = 165; i >= 120; i-=3)
  {
    tone(pinBeep, i, 50);
    delay(50);
  }
  digitalWrite(pinRedLed, LOW);
  digitalWrite(pinGreenLed, LOW);
  digitalWrite(pinYellowLed, LOW);
  digitalWrite(pinBlueLed, LOW);
  noTone(pinBeep);
  delay(1000);
}
void winGame()
{
  for(int i = 0; i < 4; i++)
  {
    digitalWrite(pinRedLed, HIGH);
    digitalWrite(pinGreenLed, HIGH);
    digitalWrite(pinYellowLed, HIGH);
    digitalWrite(pinBlueLed, HIGH);
    tone(pinBeep, 440, 500);
    delay(300);
    digitalWrite(pinRedLed, LOW);
    digitalWrite(pinGreenLed, LOW);
    digitalWrite(pinYellowLed, LOW);
    digitalWrite(pinBlueLed, LOW);
    delay(300);
  }
  noTone(pinBeep);
}

