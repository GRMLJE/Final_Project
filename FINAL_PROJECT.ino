int sw1=53,sw4=52,sw3=50,led1=23,led2=22,pwmA=5,pwmB=6,inA1=3,inA2=4,inB1=7,inB2=8,swZ=50;
bool STATE1=LOW,STATE2=LOW,STATE3=LOW;
#define echoPin 11 //triger i echo pin 
#define trigPin 10 //za senzor visine

#define S0 49   //pinovi za senzor boje
#define S1 48
#define S2 47
#define S3 46
#define sensorOut 45

int redMin = 67; // Red minimum value
int redMax = 217; // Red maximum value
int greenMin = 77; // Green minimum value
int greenMax = 252; // Green maximum value
int blueMin = 57; // Blue minimum value
int blueMax = 186; // Blue maximum value

int redPW = 0;
int greenPW = 0;
int bluePW = 0;
int redValue;
int greenValue;
int blueValue;

long duration;
int distance;
void setup() {
  pinMode(sw1,INPUT_PULLUP); //crveni
  pinMode(sw3,INPUT_PULLUP); //dole
  pinMode(sw4,INPUT_PULLUP); //gore
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(pwmA,OUTPUT);
  pinMode(pwmB,OUTPUT);
  pinMode(inA1,OUTPUT);
  pinMode(inA2,OUTPUT);
  pinMode(inB1,OUTPUT);
  pinMode(inB2,OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
  interrupts();
}
  


void loop() {

if(digitalRead(sw3)==0){
  digitalWrite(inA1,LOW);
  digitalWrite(inA2,HIGH);
  analogWrite(pwmA,150);
}else if(digitalRead(sw4)==0){
  digitalWrite(inA1,HIGH);
  digitalWrite(inA2,LOW);
  analogWrite(pwmA,150);
}else{
  digitalWrite(inA1,LOW);
  digitalWrite(inA2,LOW);
  analogWrite(pwmA,0);
}

height_sens();
blueValue = NULL;
redValue = NULL;
greenValue = NULL;

if(digitalRead(sw1)==0){
 color_sens();

//auto funkcija za kat 1 
if(redValue>greenValue && redValue>blueValue && redValue > 60){
    KAT1();
}
else if(redValue>100 && greenValue>100 && blueValue>100){
    KAT2();   
}else if(redValue<50 && greenValue<50 && blueValue<50){
    KAT3();  
}else{
  ZERO();
}

}
Serial.print(blueValue);
Serial.print(redValue);
Serial.print(greenValue);
Serial.print("\t");
blueValue = NULL;
redValue = NULL;
greenValue = NULL;



}
  

int getRedPW() {
 

  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  int PW;

  PW = pulseIn(sensorOut, LOW);

  return PW;
 
}
 

int getGreenPW() {
 

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  int PW;

  PW = pulseIn(sensorOut, LOW);

  return PW;
 
}
 

int getBluePW() {
 

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  int PW;

  PW = pulseIn(sensorOut, LOW);

  return PW;
 
}

void KAT1(){
      while(distance!=4){
      
       //kontorla dizalice
       digitalWrite(inA1, distance < 4 ? LOW : HIGH);
       digitalWrite(inA2, distance < 4 ? HIGH : LOW);
       analogWrite(pwmA,150);
       //
       //ponovno citanje sensora visine
        height_sens();
       //
    }
       digitalWrite(inA1,LOW);
       digitalWrite(inA2,LOW);
       analogWrite(pwmA,0);
  }

    

void KAT2(){
       while(distance!=8){
          //kontorla dizalice
          digitalWrite(inA1, distance < 8 ? LOW : HIGH);
          digitalWrite(inA2, distance < 8 ? HIGH : LOW);
          analogWrite(pwmA,150);
          //
          
          //ponovno citanje sensora visine
           height_sens();
          //
      }
          digitalWrite(inA1,LOW);
          digitalWrite(inA2,LOW);
          analogWrite(pwmA,0);
  }
  
void KAT3(){
          while(distance!=14){
          //kontorla dizalice
          digitalWrite(inA1, distance < 14 ? LOW : HIGH);
          digitalWrite(inA2, distance < 14 ? HIGH : LOW);
          analogWrite(pwmA,150);
          //
          
          //ponovno citanje sensora visine
           height_sens();
          //
      }
          digitalWrite(inA1,LOW);
          digitalWrite(inA2,LOW);
          analogWrite(pwmA,0);
  }
void ZERO(){
  while(distance!=1189){
          //kontorla dizalice
          digitalWrite(inA1, distance < 8 ? LOW : HIGH);
          digitalWrite(inA2, distance < 8 ? HIGH : LOW);
          analogWrite(pwmA,150);
          //
          
          //ponovno citanje sensora visine
           height_sens();
          //
      }
          digitalWrite(inA1,LOW);
          digitalWrite(inA2,LOW);
          analogWrite(pwmA,0);
  }

void color_sens(){
  redPW = getRedPW();
  redValue = map(redPW, redMin,redMax,255,0);
  delay(200);
  
  greenPW = getGreenPW();
  greenValue = map(greenPW, greenMin,greenMax,255,0);
  delay(200);
  
  bluePW = getBluePW();
  blueValue = map(bluePW, blueMin,blueMax,255,0);
  delay(200);
 
}

void height_sens(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance);
}