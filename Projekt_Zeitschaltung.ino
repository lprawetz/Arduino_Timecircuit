#include <EEPROM.h>

int seconds;
int minutes;
int deci_minutes;
int hours;
int deci_hours;

int WorkButton;
int stop_SaveButton;
int FunButton;

int ResetButtonTimer = 0;

void setup() {
//Laden der gespeicherten Werte beim Arduinostart  
  seconds = EEPROM.read(0);
  minutes = EEPROM.read(1);
  deci_minutes = EEPROM.read(2);
  hours = EEPROM.read(3);
  deci_hours = EEPROM.read(4);
  
  WorkButton = 0;
  stop_SaveButton = 0;
  FunButton = 0;

//Buttons
  pinMode(A0, INPUT); //Buttonr (links) zur Aktivierung von "Work"
  pinMode(A1, INPUT); //Buttonr (mitte) zur Aktivierung von "Stopp_Save"
  pinMode(A2, INPUT); //Buttonr (rechts) zur Aktivierung von "Fun"
  pinMode(A3, INPUT); //Reset Timer
//Ziffern
  pinMode(2, OUTPUT); //Ziffer links
  pinMode(3, OUTPUT); //Ziffer mitte links
  pinMode(4, OUTPUT); //Ziffer mitte rechts
  pinMode(5, OUTPUT); //Ziffer rechts
//Numberen  
  pinMode(6, OUTPUT); //Strich oben
  pinMode(7, OUTPUT); //Strich oben rechts
  pinMode(8, OUTPUT); //Strich unten rechts
  pinMode(9, OUTPUT); //Strich unten
  pinMode(10, OUTPUT);//Strich unten links
  pinMode(11, OUTPUT);//Strich oben links
  pinMode(12, OUTPUT);//Strich mitte
  pinMode(13, OUTPUT);//Punkt
}
/////////////////////////////////////////////////////

void loop() {
  Serial.print("Sec: ");                //Der Serial Block wurde nur zur Bugsuche verwendet
  Serial.println(ResetButtonTimer);
  Serial.print("Min: ");
  Serial.println(minutes);

  Digit1();
  delay(5);
  LED_OFF();
  Digit2();
  delay(5);
  LED_OFF();
  Digit3();
  delay(5);
  LED_OFF();  
  Digit4();
  delay(5);
  LED_OFF();
  
  ButtonCall();

  if (WorkButton == 1)
  {
    Work();
  }
  if (FunButton == 1)
  {
    Fun();
  }
  if (stop_SaveButton == 1)
  {
    StopAndSave();
  }
  //Reset Timer
  if (digitalRead(A3) == 1)   
  {
    seconds = 0;
    minutes = 0;
    deci_minutes = 0;
    hours = 0;
    deci_hours = 0;  
  }
}

//////////////////////////////////////////////////////

//Bündelt die drei darunter liegenden Funktionen 
//in der Funktion ButtonCall
void ButtonCall()
{
  StartWork();
  StartFun();               
  StopSave();
}

//Buttondruck schaltet auf den jeweiligen Programmzustand
void StartWork()
{
  if (digitalRead(A0) == 1)
  {
    WorkButton = 1;
    FunButton = 0;
    stop_SaveButton = 0;
  }
}

void StartFun()
{
  if (digitalRead(A2) == 1)
  {
    WorkButton = 0;            
    FunButton = 1;                    
    stop_SaveButton = 0;
  }  
}

void StopSave()
{
  if (digitalRead(A1) == 1)
  { 
    WorkButton = 0;
    FunButton = 0;
    stop_SaveButton = 1;
  }
}

//////////////////////////////////////////////////////

// Aufwärtszähler
void Work()
{
  if (WorkButton == 1)
  {
    seconds = (seconds + 1);
    if (seconds == 60)
    {
      minutes = (minutes + 1);
      seconds = 0;
    }
    if (minutes == 10)
    {
      deci_minutes = (deci_minutes + 1);
      minutes = 0;
    }                                                       
    if (deci_minutes == 6)
    {
      hours = (hours + 1);
      deci_minutes = 0;
    }
    if (hours == 10)
    {
      deci_hours = (deci_hours + 1);
      hours = 0;
    }
  }
}

// Abwärtszähler
void Fun()
{
  if (FunButton == 1)
  {
    if (seconds >= 1)
    {
      seconds = (seconds - 1);
    }
    if ((seconds == 0) && (minutes >= 1))
    {
      minutes = (minutes - 1);
      seconds = 59;
    }
    if ((minutes == 0) && (deci_minutes >= 1))
    {
      deci_minutes = (deci_minutes - 1);
      minutes = 9;
    }                                                       
    if ((deci_minutes == 0) && (hours >= 1))
    {
      hours = (hours - 1);
      deci_minutes = 5;
    }
    if ((hours == 0) && (deci_hours >= 1))
    {
      deci_hours = (deci_hours - 1);
      hours = 9;
    }
    if ((seconds == 0) && (minutes == 0) && (deci_minutes == 0) && (hours == 0) && (deci_hours == 0))
    {
      FunButton = 0;
      LED_OFF();
      delay(5000);
    }
  }
}

//Speichert die Vaiablen (seconds, usw.) im EEPROM-Speicher des Arduinos
//Die Zahlen 0-4 bezeichnen die Speicherplätze für die Werte.
void StopAndSave()
{
  EEPROM.write(0 ,seconds);
  EEPROM.write(1 ,minutes);
  EEPROM.write(2 ,deci_minutes);    
  EEPROM.write(3 ,hours);           
  EEPROM.write(4 ,deci_hours);
  stop_SaveButton = 0;
}

//-----------------------Hardwareschnittstelle-----------------------

//Verknüpfungen der Zeitvariablen-Werte mit der LED-Ziffer-Darstellung
//Die Zifferndarstellung ist weiter unten im letzten Abschnitt implementiert.
void Sec()
{
  switch (seconds)
  {
    case 0:
      Number_0();
      break;
    case 1:
      Number_1();
      break;
    case 2:
      Number_2();
      break;
    case 3:
      Number_3();
      break;
    case 4:
      Number_4();
      break;
    case 5:
      Number_5();
      break;
    case 6:
      Number_6();
      break;
    case 7:
      Number_7();
      break;
    case 8:
      Number_8();
      break;
    case 9:
      Number_9();
      break; 
   }
}

void Min()
{
  switch (minutes)
  {
    case 0:
      Number_0();
      break;
    case 1:
      Number_1();
      break;
    case 2:
      Number_2();
      break;
    case 3:
      Number_3();
      break;
    case 4:
      Number_4();
      break;
    case 5:
      Number_5();
      break;
    case 6:
      Number_6();
      break;
    case 7:
      Number_7();
      break;
    case 8:
      Number_8();
      break;
    case 9:
      Number_9();
      break; 
   }
}

void DecMin()
{
  switch (deci_minutes)
  {
    case 0:
      Number_0();
      break;
    case 1:
      Number_1();
      break;
    case 2:
      Number_2();
      break;
    case 3:
      Number_3();
      break;
    case 4:
      Number_4();
      break;
    case 5:
      Number_5();
      break;
   }
}


void Hrs()
{
  switch (hours)
  {
    case 0:
      Number_0();
      break;
    case 1:
      Number_1();
      break;
    case 2:
      Number_2();
      break;
    case 3:
      Number_3();
      break;
    case 4:
      Number_4();
      break;
    case 5:
      Number_5();
      break;
    case 6:
      Number_6();
      break;
    case 7:
      Number_7();
      break;
    case 8:
      Number_8();
      break;
    case 9:
      Number_9();
      break; 
   }
}


void DecHrs()
{
  switch (deci_hours)
  {
    case 0:
      Number_0();
      break;
    case 1:
      Number_1();
      break;
    case 2:
      Number_2();
      break;
    case 3:
      Number_3();
      break;
    case 4:
      Number_4();
      break;
    case 5:
      Number_5();
      break;
    case 6:
      Number_6();
      break;
    case 7:
      Number_7();
      break;
    case 8:
      Number_8();
      break;
    case 9:
      Number_9();
      break; 
   }
}

//--------------------------------------------------------------------

// Ansteuerung der LED-Ziffern (ziffer1 = rechts, ziffer4 = links)
void Digit1()
{
  //Ziffern  
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(13, LOW); //Nicht gesetzter Punkt
  //Nummern
  Min();
}


void Digit2()
{
  //Ziffern  
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(13, LOW); //Nicht gesetzter Punkt
  //Nummern
  DecMin();
}

void Digit3()
{
  //Ziffern  
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(2, HIGH);
  digitalWrite(13, HIGH); //Gesetzter Punkt
  //Nummern
  Hrs();
}

void Digit4()
{
  //Ziffern  
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(2, LOW);
  digitalWrite(13, LOW); //Nicht gesetzter Punkt
  //Nummern
  DecHrs();
}

void LED_OFF()
{
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
  digitalWrite(13, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);  
}

//--------------------------------------------------------------------

// 7-Segment-LED-Numberen-Darstellung von 1-9
void Number_0()
{
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
}

void Number_1()
{
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
}

void Number_2()
{
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
}

void Number_3()
{
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
}

void Number_4()
{
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
}

void Number_5()
{
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
}


void Number_6()
{
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
}

void Number_7()
{
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
}


void Number_8()
{
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
}

void Number_9()
{
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
}
