//Start Define PINS
//define Encoder pins for Encoder A and Encoder B
#define encoderPinA D1
#define encoderPinB D2

//Start define Driver(L298N) pins for Enable and IN1 and IN2
#define ENA  D5
#define IN1  D6
#define IN2  D7
//End Define PINS
//IS Ram dosent recegnise Interruption and we shoud use this line
void ICACHE_RAM_ATTR readEncoder();
//Start Define Global variables
// used in an interrupt for read encoder
// Use the "volatile" directive for variables
volatile int counter = 0;
int lastCounter = 0;
//Time used in velocity compute
unsigned long lastTime = 0;
//pulse per one round
float PPR = 150;
//motor shaft rotation & Gear ratio
float MSR = 6.7;
//Start define low pass Filter value
float Filter_RPM = 0;
float lastFilter_RPM = 0;
float lastRPM = 0;
float laste = 0;
//End define low pass Filter value
// for motor direction
int DirMotor;
//set point
float SP = 0;
float eintegral = 0;
float der = 0;
void setup() {

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
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA,255);
  // Compute velocity with readEncoder function
  long currentTime = micros();
  float deltaTime = ((float) (currentTime-lastTime))/1.0e6;
  float velocity = (counter - lastCounter)/deltaTime;
  lastCounter = counter;
  lastTime = currentTime;

  // Convert velocity(count/s) to RPM
  //RPM = (count/s) * (round/pulses per one round) * (one output shaft rotation/motor shaft rotation) * (60s/1m) 
  float RPM =fabs(velocity * (1/PPR) * (1/MSR) * (60));

   //set our low pass Filter in our plant
 Filter_RPM = 0.7284*lastFilter_RPM + 0.1357*RPM + 0.1357*lastRPM;
 lastFilter_RPM = Filter_RPM;
 lastRPM = RPM;      

  Serial.print(Filter_RPM);
  Serial.println();
 SP = 55 ;

 //setting max speed for security of motor
 if(SP>55)
 {
  SP = 55;
 }
 if(SP<-55)
 {
  SP = -55;
 }
 //setting motor direction
if(SP > 0){
      DirMotor = 1;
    }
    else if(SP < 0){
      DirMotor = -1;
      SP = fabs(SP);
    }
    else{
      DirMotor = 0;
    }

// PID section
    float kp = 6;
    float ki = 12;
    float kd = 0.8;
    float e = SP - Filter_RPM;


    der = (e - laste)/deltaTime;


    eintegral = eintegral + e*deltaTime;

    float u = kp*e + ki*eintegral + kd*(der);

    int pwr = (int) fabs(u);

    laste = e;


    // using setmotor function for setting motor parameter and moving
    setMotor(DirMotor,pwr,ENA,IN1,IN2);

  delay(20);
}

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2)
{
    analogWrite(pwm,pwmVal); // Motor speed

    if(dir == 1){ 
    // Turn one way
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
  }
  else if(dir == -1){
    // Turn the other way
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
}
else{
    // Or dont turn
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);    
  }
}


void readEncoder(){

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
