  #include <NewPing.h>
 
  #define pwm1_pin    10 // LLANDA DERECHA
  #define pwm2_pin    11
  #define motor1_pin  6 
  #define motor2_pin  8
  
  #define encoder1A   3
  #define encoder1B   4
  #define encoder2A   2
  #define encoder2B   5
  
  #define pin_scd     7
  #define pin_sci     9
  #define pin_ssd     A0
  #define pin_ssi     A1
  #define pin_ssc     A2
  #define pin_A       A3
  #define pin_B       A5
  #define pin_C       A4

  // Definicion de constantes
  #define ADELANTE mover(AVANCE, 0.0)
  #define ADELANTE2 mover(AVANCE*3, 0.0)  
  #define ATRAS mover(-AVANCE*10, 0.0)
  #define GIRO_IZQ mover(0.0, -GIRO)
  #define GIRO_DER mover(0.0, GIRO)
  #define ALTO mover(0.0,0.0)
  
  String inputString = "";         // a String to hold incoming data
  String distancia = ""; 
  String angulo = ""; 
  int espacios = 0;
  boolean stringComplete = false;  // whether the string is complete

  // define variables for encoders 
  int m1State;
  int m1LastState;
  int m2State;
  int m2LastState;

  // Parametros Hardware 
  int par_ssd = 200;
  int par_ssi = 200;
  int par_ssc = 500;

  // Variables para seguidor luz
  long fraccion ;
  
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
  pinMode(pin_sci,INPUT_PULLUP);
  pinMode(pin_scd,INPUT_PULLUP);
   
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
  // 
}


int estado = 0;
boolean Ssi, Ssd, Ssc, Sci, Scd;
float AVANCE=1;
float GIRO=45;
int A, B, C;
  
// Algoritmo de evasión de obstáculos
void loop(){

    
    //while(1){
      //GIRO_IZQ ;
      //Serial.println(analogRead(A2));
    //}
    
    
    //Seccion de lectura de comendas
    if(stringComplete){
        if(inputString=="MV "){
          //pwmValue = inputPWM.toFloat();
          //analogWrite(pwm1_pin, pwmValue+127);
        } else if(inputString=="ssd"){
          Serial.println(analogRead(pin_ssd));
        } else if(inputString=="ssi"){
          Serial.println(analogRead(pin_ssi));
        } else if(inputString=="ssc"){
          Serial.println(analogRead(pin_ssc));
        } else if(inputString=="sci"){
          Serial.println(digitalRead(pin_sci));
        } else if(inputString=="scd"){
          Serial.println(digitalRead(pin_scd));
        } else if(inputString=="A"){
          Serial.println(analogRead(pin_A));
        } else if(inputString=="B"){
          Serial.println(analogRead(pin_B));
        } else if(inputString=="C"){
          Serial.println(analogRead(pin_C));
        } else if(inputString=="SSI"){
          Serial.println(Ssi);
        } else if(inputString=="SSD"){
          Serial.println(Ssd);
        } else if(inputString=="SSC"){
          Serial.println(Ssc);
        }
        else{
        Serial.print("Error: ");
        Serial.print(inputString);
        Serial.println("no se reconoce como comando");
        }

    inputString = "";
    distancia = "";
    angulo = "";
    espacios = 0;
    stringComplete = false;  
    } //  Fin del string completo


  // Se leen los sensores
  Sci = ssh("sci");
  Scd = ssh("scd");
  if(ssh("ssi")>=par_ssi){ Ssi=1; }else{ Ssi=0; }
  if(ssh("ssd")>=par_ssd){ Ssd=1; }else{ Ssd=0; }
  if(ssh("ssc")>=par_ssc){ Ssc=1; }else{ Ssc=0; }
  A   = abs (ssh("A") - 1024);
  B   = abs (ssh("B") - 1024);
  C   = abs (ssh("C") - 1024);

  // Algoritmo para seguir la luz 
  if(fraccion>7){
      arrenge();
      fraccion = 0;
      Serial.println("ASDJLKJKLASDDASDD");
  }

  // Algoritmo de objeto en centro
  if(Ssc){
    estado = 5;
    ALTO;
  }


  //Aumenta contador 
  fraccion++;
  
  // Maquina de estados 
    switch (estado){
      case 0: // est0
          Serial.println("ESTADO CERO");
          if (!Sci && !Ssi){
              if (!Scd && !Ssd){
                estado = 0;
                ADELANTE;
                Serial.println("ADELANTE");
              }else{
                estado = 1;
                ALTO;
                Serial.println("ALTO");
              }
          }else{
            if (!Scd && !Ssd){
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

  // Loop infinito
} // end Main (loop)


int ssh(String contacto){
  int temp;
  if(contacto=="scd"){
    temp = digitalRead(pin_scd);
  }else if(contacto=="sci"){
    temp = digitalRead(pin_sci);
  }else if(contacto=="ssd"){
    temp = analogRead(pin_ssd);
  }else if(contacto=="ssi"){
    temp = analogRead(pin_ssi);
  }else if(contacto=="ssc"){
    temp = analogRead(pin_ssc);
  }else if(contacto=="A"){
    temp = analogRead(pin_A);
  }else if(contacto=="B"){
    temp = analogRead(pin_B);
  }else if(contacto=="C"){
    temp = analogRead(pin_C);
  }
  return temp; 
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

void arrenge(){ 
  if(A>B && A>C)
  {
    if(B>C)
    {
      // A, B
      mover(0,-15);
    }
    else
    {
      //A, C
      mover(0,15);
    }
  }
  else if (B>A && B>C)
  {
    if(A>C)
    {
      //B, A
      mover(0,-80);
    }
    else
    {
      //B, C
      mover(0,-150);
    }
  }
    else if (C>A && C>B)
  {
    if(A>B)
    {
     //C, A
      mover(0,80);
    }
    else
    {
      //C,B
      Serial.print("C");
      Serial.print(",");
      Serial.println("B");
      mover(0,150);
    }
  }
}
 

void serialEvent(){
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
}
}
