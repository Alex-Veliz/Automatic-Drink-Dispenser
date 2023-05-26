#include <SoftwareSerial.h>
#include <Servo.h>

//Blue is 10 11 is orange
SoftwareSerial hc06(11, 10);

#define OJ 2
#define COKE 3
#define RUM 4
#define VODKA 5

//Servos and Belts
Servo ojServo1, cokeServo2, rumServo3, vodkaServo4, ice_Dispencer, Mixer;
Servo jBelt, jBelt2, aBelt, aBelt2;

char previousChoice = '0';
char choice = '0';
int combo = 0;
int counter = 0;
bool ice = false;

//Laser State
int laserStateOJ;// = digitalRead(OJ);
int laserStateCoke;// = digitalRead(COKE);
int laserStateRum;// = digitalRead(RUM);
int laserStateVodka;// = digitalRead(VODKA);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  hc06.begin(9600);

  //Servo Attachments
  ojServo1.attach(A0);
  cokeServo2.attach(A1);
  rumServo3.attach(A2);
  vodkaServo4.attach(A3);
  ice_Dispencer.attach(A4);
  Mixer.attach(A5);

  //Servo Initial Positions
  ojServo1.write(80);
  cokeServo2.write(70);
  rumServo3.write(80);
  vodkaServo4.write(70);
  ice_Dispencer.write(160);

  //State Pinmode
  pinMode(OJ, INPUT);
  pinMode(COKE, INPUT);
  pinMode(RUM, INPUT);
  pinMode(VODKA, INPUT);

  //Belt Attachments
  jBelt.attach(A6);
  aBelt.attach(A7);
  jBelt.write(90);
  aBelt.write(90);

  ice = false;
}


void loop() {
  //jBelt.write(110);
  //aBelt.write(75);
  //jBelt.write(90);
  //aBelt.write(90);
  Mixer.write(90);

  if (hc06.available() > 0) {
    choice = hc06.read();

    //Serial.println(previousChoice);
    //Serial.println(previousChoice);
    //Serial.println(choice);
    choicemaker(previousChoice, choice);
    if (previousChoice != choice) {
      previousChoice = choice;
    }
  }

  laserStateOJ = digitalRead(OJ);
  laserStateCoke = digitalRead(COKE);
  laserStateRum = digitalRead(RUM);
  laserStateVodka = digitalRead(VODKA);

  /*if (laserStateOJ == LOW)
    {
    Serial.println("Not Detected");
    jBelt.write(90);
    }
    else {
    Serial.println("Detected");
    jBelt.write(110);
    }*/
}

void choicemaker(char prevChoice, char Choice) {
  switch (prevChoice)
  {
    //0 Ice
    case'0':
      if (Choice == '5')
      {
        ice = true;
        //delay(5000);
        jBelt.write(90);
        ice_Dispencer.write(120);
        delay(250);
        ice_Dispencer.write(160);
        delay(10000);
        jBelt.write(110);

        //aBelt.write(75);
        //Combo(0, ice);
        previousChoice = '0';
        choice = '0';
      }
      else if (Choice == '6') {
        ice = false;
        //Combo(0, ice);
        previousChoice = '0';
        choice = '0';
      }
      break;

    //1 Coke
    case'1':
      if (Choice == '0')
      {
        Serial.println("Just Coke");
        Combo(1, ice);
        //
        previousChoice = '0';
        choice = '0';
      }
      else if (Choice == '2')
      {
        Serial.println("Coke + OJ");
        Combo(5, ice);

        previousChoice = '0';
        choice = '0';
      }
      else if (Choice == '3')
      {
        Serial.println("Coke + Rum");
        Combo(6, ice);

        previousChoice = '0';
        choice = '0';
      }
      else if (Choice == '4')
      {
        Serial.println("Coke + Vodka");
        Combo(7, ice);

        previousChoice = '0';
        choice = '0';
      }
      break;

    //2 OJ
    case'2':
      if (Choice == '0')
      {
        Combo(2, ice);
        previousChoice = '0';
        choice = '0';
      }
      else if (Choice == '1')
      {
        Serial.println("OJ + Coke");
        Combo(5, ice);

        previousChoice = '0';
        choice = '0';
      }
      else if (Choice == '3')
      {
        Serial.println("OJ + Rum");
        Combo(8, ice);

        previousChoice = '0';
        choice = '0';
      }
      else if (Choice == '4')
      {
        Serial.println("OJ + Vodka");
        Combo(9, ice);

        previousChoice = '0';
        choice = '0';
      }
      break;

    //3 Rum
    case'3':
      if (Choice == '0')
      {
        Serial.println("Just Rum");
        Combo(3, ice);
        //
        previousChoice = '0';
        choice = '0';
      }
      else if (Choice == '1')
      {
        Serial.println("Rum + Coke");
        Combo(6, ice);

        previousChoice = '0';
        choice = '0';
      }
      else if (Choice == '2')
      {
        Serial.println("Rum + OJ");
        Combo(8, ice);

        previousChoice = '0';
        choice = '0';
      }
      else if (Choice == '4')
      {
        Serial.println("Rum + Vodka");
        Combo(10, ice);

        previousChoice = '0';
        choice = '0';
      }
      break;

    //4 Vodka
    case'4':
      if (Choice == '0')
      {
        Serial.println("Just Vodka");
        Combo(4, ice);

        previousChoice = '0';
        choice = '0';
      }
      else if (Choice == '1')
      {
        Serial.println("Vodka + Coke");
        Combo(7, ice);

        previousChoice = '0';
        choice = '0';
      }
      else if (Choice == '2')
      {
        Serial.println("Vodka + OJ");
        Combo(9, ice);

        previousChoice = '0';
        choice = '0';
      }
      else if (Choice == '3')
      {
        Serial.println("Vodka + Rum");
        Combo(10, ice);
        previousChoice = '0';
        choice = '0';
      }
      break;
  }
}

//Combo 1 Just Coke
//Combo 2 Just OJ
//Combo 3 Just Rum
//Combo 4 Just Vodka
//Combo 5 CokeOJ
//Combo 6 CokeRum
//Combo 7 Coke Vodka
//Combo 8 rumOJ
//Combo 9 ScrewDriver
//Combo 10 RumVodka

void Combo(int c, bool I)
{
  switch (I) {
    case true:
      if (c == 1) {
        //Serial.println("Combo 1 with ice");
        hc06.print("b");
        delay(5000);
        justCoke();
        hc06.print("a");
      }
      else if (c == 2) {
        //Serial.println("Combo 2 with ice");
        hc06.print("b");
        delay(5000);
        justOJ();
        hc06.print("a");
      }
      else if (c == 3) {
        //Serial.println("Combo 3 with ice");
        hc06.print("b");
        delay(5000);
        justRum();
        hc06.print("a");
      }
      else if (c == 4) {
        //Serial.println("Combo 4 with ice");
        hc06.print("b");
        delay(5000);
        justVodka();
        hc06.print("a");
      }
      else if (c == 5) {
        //Serial.println("Combo 5 with ice");
        hc06.print("b");
        delay(5000);
        cokeOJ();
        hc06.print("a");
      }
      else if (c == 6) {
        //Serial.println("Combo 6 with ice");
        hc06.print("b");
        delay(5000);
        cokeRum();
        hc06.print("a");
      }
      else if (c == 7) {
        //Serial.println("Combo 7 with ice");
        hc06.print("b");
        delay(5000);
        cokeVodka();
        hc06.print("a");
      }
      else if (c == 8) {
        //Serial.println("Combo 8 with ice");
        hc06.print("b");
        delay(5000);
        rumOJ();
        hc06.print("a");
      }
      else if (c == 9) {
        //Serial.println("Combo 9 with ice");
        hc06.print("b");
        delay(5000);
        screwdiver();
        hc06.print("a");
      }
      else if (c == 10) {
        //Serial.println("Combo 10 with ice");
        hc06.print("b");
        delay(5000);
        rumVodka();
        hc06.print("a");
      }
      //delay(60000);
      //Mixer.write(80);
      //delay(5000);
      //Mixer.write(90);
      break;

    case false:
      if (c == 1) {
        Serial.println("Combo 1 with NO ice");
        hc06.print("b");
        justCoke();
        hc06.print("a");
      }
      else if (c == 2) {
        //Serial.println("Combo 2 with NO ice");
        hc06.print("b");
        justOJ();
        hc06.print("a");
      }
      else if (c == 3) {
        //Serial.println("Combo 3 with NO ice");
        hc06.print("b");
        justRum();
        hc06.print("a");
      }
      else if (c == 4) {
        //Serial.println("Combo 4 with NO ice");
        hc06.print("b");
        justVodka();
        hc06.print("a");
      }
      else if (c == 5) {
        //Serial.println("Combo 5 with NO ice");
        hc06.print("b");
        cokeOJ();
        hc06.print("a");
      }
      else if (c == 6) {
        //Serial.println("Combo 6 with NO ice");
        hc06.print("b");
        cokeRum();
        hc06.print("a");
      }
      else if (c == 7) {
        //Serial.println("Combo 7 with NO ice");
        hc06.print("b");
        cokeVodka();
        hc06.print("a");
      }
      else if (c == 8) {
        //Serial.println("Combo 8 with NO ice");
        hc06.print("b");
        rumOJ();
        hc06.print("a");
      }
      else if (c == 9) {
        //Serial.println("Combo 9 with NO ice");
        hc06.print("b");
        screwdiver();
        hc06.print("a");
      }
      else if (c == 10) {
        //Serial.println("Combo 10 with NO ice");
        hc06.print("b");
        rumVodka();
        hc06.print("a");
      }
      //delay(60000);
      //Mixer.write(80);
      //delay(5000);
      //Mixer.write(90);
      break;
  }
}

void justCoke() {
  if (laserStateCoke == LOW) {
    jBelt.write(90);
    cokeServo2.write(160);  //going outward
    delay(2000);
    cokeServo2.write(70);  // going inward
    delay(2000);
  }
}

void justOJ() {
  if (laserStateOJ == LOW) {
    Serial.println("NOW");
    delay(10000);
    jBelt.write(90);
    ojServo1.write(150);  //going outward
    delay(2000);
    ojServo1.write(80);  // going inward
    delay(2000);
    jBelt.write(110);
  }
}

void justRum() {
  if (laserStateRum == LOW) {
    aBelt.write(90);

    rumServo3.write(160);  //going outward
    delay(2000);
    rumServo3.write(80);  // going inward
    delay(2000);
  }
}

void justVodka() {
  if (laserStateVodka == LOW) {
    aBelt.write(90);

    vodkaServo4.write(155);  //going outward
    delay(2000);
    vodkaServo4.write(70);  // going inward
    delay(2000);
  }
}

void cokeOJ() {
  if (laserStateCoke == LOW) {
    jBelt.write(90);

    cokeServo2.write(160);  //going outward
    delay(2000);
    cokeServo2.write(70);  // going inward
    delay(2000);
  }
  if (laserStateOJ == LOW) {
    jBelt.write(90);

    ojServo1.write(150);  //going outward
    delay(2000);
    ojServo1.write(80);  // going inward
    delay(2000);
  }
}

void cokeRum() {
  if (laserStateRum == LOW) {
    aBelt.write(90);

    rumServo3.write(160);  //going outward
    delay(2000);
    rumServo3.write(80);  // going inward
    delay(2000);
  }
  if (laserStateCoke == LOW) {
    jBelt.write(90);

    cokeServo2.write(160);  //going outward
    delay(2000);
    cokeServo2.write(70);  // going inward
    delay(2000);
  }
}

void cokeVodka() {
  if (laserStateCoke == LOW) {
    jBelt.write(90);

    cokeServo2.write(160);  //going outward
    delay(2000);
    cokeServo2.write(70);  // going inward
    delay(2000);
  }
  if (laserStateVodka == LOW) {
    aBelt.write(90);

    vodkaServo4.write(155);  //going outward
    delay(2000);
    vodkaServo4.write(70);  // going inward
    delay(2000);
  }
}

void rumOJ() {
  if (laserStateRum == LOW) {
    aBelt.write(90);

    rumServo3.write(160);  //going outward
    delay(2000);
    rumServo3.write(80);  // going inward
    delay(2000);
  }
  if (laserStateOJ == LOW) {
    jBelt.write(90);

    ojServo1.write(150);  //going outward
    delay(2000);
    ojServo1.write(80);  // going inward
    delay(2000);
  }
}

void screwdiver() {
  if (laserStateOJ == LOW) {
    jBelt.write(90);
    ojServo1.write(150);  //going outward
    delay(2000);
    ojServo1.write(80);  // going inward
    delay(2000);
  }
  if (laserStateVodka == LOW) {
    aBelt.write(90);

    vodkaServo4.write(155);  //going outward
    delay(2000);
    vodkaServo4.write(70);  // going inward
    delay(2000);
  }
}

void rumVodka() {
  if (laserStateRum == LOW) {
    aBelt.write(90);

    rumServo3.write(160);  //going outward
    delay(2000);
    rumServo3.write(80);  // going inward
    delay(2000);
  }
  if (laserStateVodka == LOW) {
    aBelt.write(90);

    vodkaServo4.write(155);  //going outward
    delay(2000);
    vodkaServo4.write(70);  // going inward
    delay(2000);
  }
}
