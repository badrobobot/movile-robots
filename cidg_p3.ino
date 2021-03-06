  #define pwm1_pin    10
  #define pwm2_pin    11
  #define motor1_pin  8 
  #define motor2_pin  9
  
  #define encoder1A   2
  #define encoder1B   4
  #define encoder2A   3
  #define encoder2B   5
  
  #define sent1_pin   6
  #define sent2_pin   7 
  

// define variables for serial comunication
String inputString = "";         // a String to hold incoming data
String inputPWM = "";
String distancia = ""; 
String angulo = ""; 
char lastChar = 'x';
int espacios = 0;
int pwmValue=0; 
boolean stringComplete = false;  // whether the string is complete
boolean lastIsNumber = false;
boolean isFirstNumber = true;
// define variables for encoders 
int m1State;
int m1LastState;
int m2State;
int m2LastState;
int counterm1;
int counterm2;
void setup() {
  // put your setup code here, to run once:
  pinMode(pwm1_pin , OUTPUT);
  pinMode(motor1_pin, OUTPUT);
  pinMode(sent1_pin, OUTPUT);
  pinMode(motor2_pin, OUTPUT);
  pinMode(pwm2_pin , OUTPUT);
  pinMode(sent2_pin, OUTPUT);
  pinMode(encoder1A, INPUT);
  pinMode(encoder1B, INPUT);
  pinMode(encoder2A, INPUT);
  pinMode(encoder2B, INPUT);
   
  // Start serial communication 
  Serial.begin(9600);
  // Start with off motors 
  analogWrite(pwm1_pin,127);
  analogWrite(pwm2_pin,127);
  // Set initial rotation direction
  digitalWrite(motor1_pin,HIGH);
  digitalWrite(motor2_pin,HIGH);
  // Read encoder initial state
  m1LastState = digitalRead(encoder1A);
  m2LastState = digitalRead(encoder1B);
    
}

void loop() {
  
  if(stringComplete){
    
    if(inputString=="A1 speed "){
      pwmValue = inputPWM.toInt();
      analogWrite(pwm1_pin, pwmValue+127);
    }
    else if(inputString=="A2 speed "){
      pwmValue = inputPWM.toInt();
      analogWrite(pwm2_pin, pwmValue+127);
    }
    else if(inputString=="A1 on left"){
      
    }
    else if(inputString=="A1 on right"){
    
    }
    else if(inputString=="A1 off"){
    
    }
    else if(inputString=="A2 on left"){
    
    }
    else if(inputString=="A2 on right"){
    
    }
    else if(inputString=="A2 off"){
    
    }else if(inputString=="MV  "){
      int dis = distancia.toInt();
      int ang = angulo.toInt();      
      Serial.print("MOVER");
      mover(dis,ang);
    }else{
      Serial.print("Error: ");
      Serial.print(inputString);
      Serial.println("no se reconoce como comando");
    }

    inputString = "";
    inputPWM = "";
    distancia = "";
    angulo = "";
    espacios = 0;
    lastChar = 'x';
    lastIsNumber = false;
    stringComplete = false;
    
  }
}


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      espacios = 0;
    }else{
      if(isDigit(inChar) || inChar=='-'){
        if(espacios==2){
          angulo += inChar;
        }else{
          distancia += inChar;
        }
        
      }else{
        inputString += inChar;
        if(inChar==' '){
          espacios++;
        } 
      }
    }
    lastChar = inChar;
  }
}


void mover(int dis, int ang){
  int pasosM1 = 0;
  int pasosM2 = 0;
  if( dis==0 && ang==0){
    // STOP
    analogWrite(pwm1_pin,127);
    analogWrite(pwm2_pin,127);
  } else if(dis>0 && ang==0){
    // FOWARD
    analogWrite(pwm1_pin,180);
    analogWrite(pwm2_pin,180);
    encoder_steps_walk(dis);
    analogWrite(pwm1_pin,127);
    analogWrite(pwm2_pin,127);
        
  } else if(dis<0 && ang==0){
    // BACKWARDS
    analogWrite(pwm1_pin,75);
    analogWrite(pwm2_pin,75);
    encoder_steps_walk(not_data(dis));
    analogWrite(pwm1_pin,127);
    analogWrite(pwm2_pin,127);
    
  } else if(dis==0 && ang>0){
    // CLOCKWISE
    analogWrite(pwm1_pin,167);
    analogWrite(pwm2_pin,87);
    encoder_steps_spin(ang);
    analogWrite(pwm1_pin,127);
    analogWrite(pwm2_pin,127);
     
  } else if(dis==0 && ang<0){
    // COUNTER CLOCKWISE 
    analogWrite(pwm1_pin,87);
    analogWrite(pwm2_pin,167);
    encoder_steps_spin(not_data(ang));
    analogWrite(pwm1_pin,127);
    analogWrite(pwm2_pin,127);
  }  
}

int not_data(int data){
  int notData = 0; 
  if(data<0){
    notData = -1*data; 
    return notData;
  } else {
    return data;
  }
}

void encoder_steps_walk(float dis){
  int z = 0; // Total Steps  
  int temp_steps = 0; // Now Steps
  z = (int) dis*45.47;

  while(z != 0){
    m1State = digitalRead(encoder1A);
    if(m1State != m1LastState){
      m1LastState = m1State;
      z--; 
    } 
  } // Exit While
}

int encoder_steps_spin(float ang){
  int z = 0; 
  z = (int) ang*95.49; 
  
  while(z != 0){
    m1State = digitalRead(encoder1A);
    if(m1State != m1LastState){
      m1LastState = m1State;
      z--; 
    } 
  } // Exit While
}
 
void encoders_calibration(){
  // Counts the numbers of steps in a revolution of the wheel 
  m1State = digitalRead(encoder1A);
  if(m1LastState!=m1State){
    counterm1++;
    m1LastState = m1State;
    Serial.println(counterm1);
  }
}

void encoders_scan(){
  // Display the outputs of the encoders 
  Serial.print(digitalRead(encoder1A));
  Serial.print(digitalRead(encoder2A));
  Serial.print(" ");
  Serial.print(digitalRead(encoder1B));
  Serial.println(digitalRead(encoder2B));
}

void encoderCuadratureM1(){
  // 
  if(m1State != m1LastState){
    if(digitalRead(encoder2A) != m1State){
      
    }
  }
  Serial.print(digitalRead(encoder1A));
  Serial.print(digitalRead(encoder1B));
  Serial.print("    ");
  Serial.print(digitalRead(encoder2A));
  Serial.println(digitalRead(encoder2B));
}

void encoderIncremental(){

}
