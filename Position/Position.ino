//Start Define PINS
//define Encoder pins for Encoder A and Encoder B
#define encoderPinA D1
#define encoderPinB D2

//Start define Driver(L298N) pins for Enable and IN1 and IN2
#define ENA  D5
#define IN1  D6
#define IN2  D7
//End Define PINS

void ICACHE_RAM_ATTR readEncoder();
volatile int counter = 0;
float PPR = 150;
float MSR = 6.7;
float lastTime = 0;
float eintegral = 0;
float der = 0;
float laste;
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);

  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  attachInterrupt(digitalPinToInterrupt(5),readEncoder, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  long currentTime = micros();
  float deltaTime = ((float) (currentTime-lastTime))/1.0e6;
  lastTime = currentTime;
  int motorposition = counter;
  float SP = 270;
  SP = SP * 3;

  float kp = 2.6;
  float ki = 2.55;
  float kd = 0.3;

  float e = SP - motorposition;

  der = (e - laste)/deltaTime;
  eintegral = eintegral + e*deltaTime;
  float u = kp*e + ki*eintegral + kd*(der);

  float laste = e;
// setting a maximum for u
  if(u>80)
  {
    u = 80;
  }

  if(u<-80)
  {
    u = -80;
  }

  int pwr = (int) u;

  if(pwr>0)
  {
    
    digitalWrite(IN2,HIGH);
    digitalWrite(IN1,LOW);
    analogWrite(ENA,pwr);

  }
  else if(pwr<0)
  {
    digitalWrite(IN2,LOW);
    digitalWrite(IN1,HIGH);
    analogWrite(ENA,abs(pwr));
  }
  else if(pwr == 0)
  {
    // Or dont turn
    
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    analogWrite(ENA,abs(pwr));
    
  }

  // Serial.print("pose :");
  Serial.print(motorposition/3);

  Serial.println();
delay(20);
}



void readEncoder(){
  // Read encoder
  // metod 1
  // Read encoder A when ENCA rises
  // int StateENCA = digitalRead(encoderPinA);
  // int StateENCB = digitalRead(encoderPinB);

  // if(StateENCA != StateENCB){
  //   counter++;
  // }
  // else{
  //   counter--;
  // }

  //metod2
  // Read encoder B when ENCA rises
  int b = digitalRead(encoderPinB);
  int increment = 0;
  if(b>0){
    // If B is high, increment forward
    increment = 1;
  }
  else{
    // Otherwise, increment backward
    increment = -1;
  }
  counter = counter + increment;

  ////test pulse with serial print
  // Serial.print(counter);
  // Serial.println();

}