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

int curKey = 0;
int Arr[256]; // игровой массив
int CurPos = 0; // текущая позиция курсора в Arr
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

  /*for(int i = 0; i < 330; i++)
  {
    delayMicroseconds(1517);
    digitalWrite(pinBeep, HIGH);
    delayMicroseconds(1517);
    digitalWrite(pinBeep, LOW);
  }
  for(int i = 0; i < 277; i++)
  {
    delayMicroseconds(1804);
    digitalWrite(pinBeep, HIGH);
    delayMicroseconds(1804);
    digitalWrite(pinBeep, LOW);
  }
  for(int i = 0; i < 440; i++)
  {
    delayMicroseconds(1136);
    digitalWrite(pinBeep, HIGH);
    delayMicroseconds(1136);
    digitalWrite(pinBeep, LOW);
  }
  for(int i = 0; i < 165; i++)
  {
    delayMicroseconds(3034);
    digitalWrite(pinBeep, HIGH);
    delayMicroseconds(3034);
    digitalWrite(pinBeep, LOW);
  }*/
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
  }
  newgame:
  CurPos = 0;
  /*failGame();
  winGame();
  
  delay(2000);
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
void play(int data)
{
  digitalWrite(data+pinRedLed, HIGH);
  tone(pinBeep, Muse[data], 500);
  delay(500);
  digitalWrite(data+pinRedLed, LOW);
  noTone(pinBeep);
  delay(100);
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

