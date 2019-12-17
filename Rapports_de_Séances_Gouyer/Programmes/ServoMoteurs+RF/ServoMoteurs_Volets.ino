//Non terminé
#include <Servo.h>
Servo servoD;
Servo servoG;

float angleG;
float angleD;


int const moteur=11;
int const altitude=6;
int const roulis=9;
int val;
int const led=10;
int const lex=10;
float tempsun;
float tempsdeux;
float tempstrois;
float SortieMoteur;
float SortieAltitude;
float SortieRoulis;


void setup() {
  Serial.begin(9600);
  Serial.println("enmarche");
  pinMode(moteur, INPUT);
  pinMode(altitude, INPUT);
  pinMode(roulis, INPUT);
  pinMode(led,OUTPUT);
  Serial.println("ok");
  servoD.attach(3);
  servoG.attach(5);
  servoD.write(90);// paralleles avec l'aile
  servoG.write(90);

}

void loop() {
  //RF
  tempsun= pulseIn(moteur, HIGH);
  Serial.println("temps moteur");
  Serial.println(tempsun);
  
  tempsdeux= pulseIn(altitude, HIGH);
  Serial.println("temps altitude");
  Serial.println(tempsdeux);
  
  tempstrois= pulseIn(roulis, HIGH);
  Serial.println("temps roulis");
  Serial.println(tempstrois);

  if (1450>tempsdeux or tempsdeux>1550){
    SortieAltitude=(1-(tempsdeux-1020)/835)*255;
  }
  if ((1450<tempsdeux) and (tempsdeux<1550)){//pas de mouvement
    SortieAltitude=127.5;
  }

  if (1400>tempstrois or tempstrois>1470){
    SortieRoulis=(1-(tempstrois-1070)/831)*255;

  }
   if ((1450<tempstrois) and(tempstrois<1550)){
    SortieRoulis=127.5;
  }

  SortieMoteur=(1-(tempsun-1040)/843)*255;
  if (SortieMoteur<20){//moteur à l'arret
    SortieMoteur=0;
  }
  if (SortieMoteur>240){
    SortieMoteur=255;
  }
  
  Serial.println("PMW moteur:");
  Serial.println(SortieMoteur);
  analogWrite(led,SortieMoteur); 

  Serial.println("PMW roulis:");
  Serial.println(SortieRoulis);
  Serial.println("PMW altitude:");
  Serial.println(SortieAltitude);
  Serial.println("PMW moteur:");
  Serial.println(SortieMoteur);
  analogWrite(led,SortieMoteur); 

  Serial.println("PMW roulis:");
  Serial.println(SortieRoulis);
  Serial.println("PMW altitude:");
  Serial.println(SortieAltitude);

  angleG=SortieRoulis/255*180;
  angleD=SortieRoulis/255*180;
  Serial.println("angleDroit:");
  Serial.println(angleD);
  Serial.println("angleGauche:");
  Serial.println(angleG);
  //Volets
  servoD.write(angleD);
  servoG.write(angleG);

}


  
