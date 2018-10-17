  #include <NewPing.h>
 
  #define pwm1_pin    10 // LLANDA DERECHA
  #define pwm2_pin    11
  #define motor1_pin  6 
  #define motor2_pin  8
  
  #define encoder1A   3
  #define encoder1B   4
  #define encoder2A   2
  #define encoder2B   5
  
  #define leftTrigPin   0
  #define leftEchoPin   1
  //#define rightTrigPin  7
  //#define rightEchoPin  9

  #define leftPush    7
  #define rightPush   9
  
  #define MAX_DISTANCE 5

  // Definicion de constantes
  #define ADELANTE mover(AVANCE, 0.0)
  #define ADELANTE2 mover(AVANCE*5, 0.0)  
  #define ATRAS mover(-AVANCE*10, 0.0)
  #define GIRO_IZQ mover(0.0, -GIRO)
  #define GIRO_DER mover(0.0, GIRO)
  #define ALTO mover(0.0,0.0)
  
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

  void setup() {
  
  // put your setup code here, to run once:
  pinMode(pwm1_pin , OUTPUT);
  pinMode(motor1_pin, OUTPUT);
  pinMode(motor2_pin, OUTPUT);
  pinMode(pwm2_pin , OUTPUT);
  pinMode(encoder1A, INPUT);
  pinMode(encoder1B, INPUT);
  pinMode(encoder2A, INPUT);
  pinMode(encoder2B, INPUT);
  pinMode(leftPush,INPUT_PULLUP);
  pinMode(rightPush,INPUT_PULLUP);
   
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

// Algoritmo de evasión de obstáculos
void loop(){
  int estado = 0;
  int Si,Sd;
  float AVANCE=1;
  float GIRO=45;
  // Estado inicial
  estado = 0;
  // Loop infinito
  while(1){
    // Se leen los sensores
    Si = shs(1);
    Sd = shs(2);
    Serial.print("Estado Presente: ");
    Serial.println(estado);
    Serial.print("Si: ");
    Serial.println(Si);
    Serial.print("Sd: ");
    Serial.println(Sd);
    switch (estado){
      case 0: // est0
          if (!Si){
              if (!Sd){
                estado = 0;
                ADELANTE;
                Serial.println("ADELANTE");
              }else{
                estado = 1;
                ALTO;
                Serial.println("ALTO");
              }
          }else{
            if (!Sd){
              estado = 3;
              ALTO;
              Serial.println("ALTO");
            }else{
              estado = 5;
              ALTO;
              Serial.println("ALTO");
            }
          }
          break;

    case 1: // est1
      estado = 2;
      ATRAS;
      Serial.println("ATRAS");
      break;

    case 2: // est2
      estado = 0;
      GIRO_IZQ;
      Serial.println("GIRO_IZQ");
      break;
      
    case 3: // est3
      estado = 4;
      ATRAS;
      Serial.println("ATRAS");
      break;
      
    case 4: // est4
      estado = 0;
      GIRO_DER;
      Serial.println("GIRO_DER");
      break;
      
    case 5: // est5
      estado = 6;
      ATRAS;
      Serial.println("ATRAS");
      break;
      
    case 6: // est6
      estado = 7;
      GIRO_IZQ;
      Serial.println("GIRO_IZQ");
      break;
      
    case 7: // est7
      estado = 8;
      GIRO_IZQ;
      Serial.println("GIRO_IZQ");
      break;
      
    case 8: // est8
      estado = 9;
      ADELANTE2;
      Serial.println("ADELANTE");
      break;
      
    case 9: // est9
      estado = 10;
      ADELANTE2;
      Serial.println("ADELANTE");
      break;
      
    case 10: // est10
      estado = 11;
      GIRO_DER;
      Serial.println("GIRO_DER");
      break;
      
    case 11: // est11
        estado = 0;
        GIRO_DER;
        Serial.println("GIRO_DER");
        break;
        
} // end case
} // end while
} // end Main (loop)


boolean shs(int contacto){
  int temp;
  if(contacto==1){
    temp = digitalRead(rightPush);
  }else if(contacto==2){
    temp = digitalRead(leftPush);
  }
  
  return temp; 
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
      if(isDigit(inChar) || inChar=='-' || inChar=='.'){
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


void mover(float dis, float ang){
  if(dis>0){
      analogWrite(pwm1_pin,180);
      analogWrite(pwm2_pin,180);
      encoder_steps_walk(dis);
      analogWrite(pwm1_pin,127);
      analogWrite(pwm2_pin,127);  
    }else if(dis<0){
      analogWrite(pwm1_pin,75);
      analogWrite(pwm2_pin,75);
      encoder_steps_walk(not_data(dis));
      analogWrite(pwm1_pin,127);
      analogWrite(pwm2_pin,127);
    } else if(dis==0){
      analogWrite(pwm1_pin,127);
      analogWrite(pwm2_pin,127);
    }

    if(ang>0){
      analogWrite(pwm1_pin,167);
      analogWrite(pwm2_pin,87);
      encoder_steps_spin(ang);
      analogWrite(pwm1_pin,127);
      analogWrite(pwm2_pin,127);  
    }else if(ang<0){
      analogWrite(pwm1_pin,87);
      analogWrite(pwm2_pin,167);
      encoder_steps_spin(not_data(ang));
      analogWrite(pwm1_pin,127);
      analogWrite(pwm2_pin,127);
    } else if(ang==0){
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
  //z = (int) ang*95.49*2; 
  z = (int) ang*1.66*1.8;
  while(z != 0){
    m1State = digitalRead(encoder1A);
    if(m1State != m1LastState){
      m1LastState = m1State;
      z--; 
    } 
  } // Exit While
}
 
