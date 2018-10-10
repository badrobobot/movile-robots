// Arduino usable pins for interrupts 2, 3
const byte interruptPin2 = 2; // INT.0
const byte interruptPin3 = 3; // INT.1

volatile byte state = LOW;
// Variables for counting M1 and M2 steps
volatile int  leftSteps;
volatile int  rightSteps;
// Variables for controlling speed of the motors
volatile byte leftPWM = 127;
volatile byte rightPWM = 127;
volatile byte averagePWM = 180;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin2, INPUT);
  pinMode(interruptPin3, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), leftEncoderInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin3), rightEncoderInterrupt, CHANGE);
  /* ISR modes
   * LOW to trigger the interrupt whenever the pin is low,
   * CHANGE to trigger the interrupt whenever the pin changes value
   * RISING to trigger when the pin goes from low to high,
   * FALLING for when the pin goes from high to low.
  */
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, state);
}

void leftEncoderInterrupt(){
  if(leftSteps!=0){ 
    if(leftSteps>0){ 
      analogWrite(pwm1_pin,averagePWM+1);
      analogWrite(pwm2_pin,averagePWM-1);
    }else if (leftSteps=rightSteps){
      analogWrite(pwm1_pin,averagePWM);
      analogWrite(pwm2_pin,averagePWM);
    }
    leftSteps--;    
  }else{
    //Stops the Motor if there is no more steps
    analogWrite(pwm1_pin,127);
  }   
}

void rightEncoderInterrupt(){
  if(rightSteps!=0){ 
    if(rightSteps>0){ 
      analogWrite(pwm1_pin,averagePWM-1);
      analogWrite(pwm2_pin,averagePWM+1);
    }else if (leftSteps=rightSteps){
      analogWrite(pwm1_pin,averagePWM);
      analogWrite(pwm2_pin,averagePWM);
    }
    rightSteps--;    
  }else{
    //Stops the Motor if there is no more steps
    analogWrite(pwm2_pin,127);
  }   
}


void move_robot(int dis, int ang){
  if( dis==0 && ang==0){
    // STOP
    analogWrite(pwm1_pin,127);
    analogWrite(pwm2_pin,127);
  } else if(dis>0 && ang==0){
    // FOWARD
    analogWrite(pwm1_pin,180);
    analogWrite(pwm2_pin,180);
    dist2steps(dis);
        
  } else if(dis<0 && ang==0){
    // BACKWARDS
    analogWrite(pwm1_pin,75);
    analogWrite(pwm2_pin,75);
    dist2steps(not_data(dis));
    
  } else if(dis==0 && ang>0){
    // CLOCKWISE
    analogWrite(pwm1_pin,167);
    analogWrite(pwm2_pin,87);
    encoder_steps_spin(ang);
     
  } else if(dis==0 && ang<0){
    // COUNTER CLOCKWISE 
    analogWrite(pwm1_pin,87);
    analogWrite(pwm2_pin,167);
    rad2steps(not_data(ang));
  }  
}

// if data is negative become positive
int not_data(int data){
  int notData = 0; 
  if(data<0){
    notData = -1*data; 
    return notData;
  } else {
    return data;
  }
}

// Convert distance in cm to steps
void dist2steps(float dis){
  leftSteps = 0;
  rightSteps = 0;
  leftSteps = (int) dis*45.47;
  rightSteps = leftSteps;
}

// Convert radians to steps
int rad2steps(float ang){
  leftSteps = 0;
  rightSteps = 0;
  leftSteps = (int) ang*95.49;
  rightSteps = leftSteps;
}
