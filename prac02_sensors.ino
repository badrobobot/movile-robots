/*
  Practice 2 
  Bio-Robotics 
  Fi-UNAM
  ASK THEN READ AND PRINT
  
*/

#define pin_contact   2
#define pin_temp      A0
#define pin_photora   A1 
#define pin_photord   A2
#define pin_infrared  A3
const int a = 50;
const int b = 50;

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete


void setup() {
  // put your setup code here, to run once:
  pinMode(pin_contact,INPUT_PULLUP);
  pinMode(pin_photord,INPUT);
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (stringComplete) {
    //Print the input from serial 
    //Serial.println(inputString);
    
    //Print the corresponding sensor
    if(inputString=="shs contact"){
      Serial.print("contact ");
      contact();
    }
    else if(inputString=="shs photora"){
      Serial.print("photora ");
      photora();
    }
    else if(inputString=="shs photord"){
      Serial.print("photord ");
      photord();
    }
    else if(inputString == "shs temp"){
      Serial.print("temp ");
      temp();
    }
    else if(inputString == "shs infrared"){
      Serial.print("infrared ");
      infrared();
    }
    else{
      Serial.print("Error no sensor:");
      Serial.print(inputString);
      Serial.print(" ");
    }
    // clear the string:
    inputString = "";
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
    }else{
      // add it to the inputString:
      inputString += inChar;
    }
  }
}


void contact() {
  boolean contact = 0;
  contact = digitalRead(pin_contact);
  Serial.println(contact);  
  delay(1); 
}

void temp(){
  float temperatura = 0;
  temperatura = 5000*10*digitalRead(pin_temp)/1024;
  Serial.println(temperatura);  
  delay(1); 
}

void photora(){
  float photora = 0;
  photora = analogRead(pin_photora);
  Serial.println(photora);
  delay(1);   
}

void photord(){
  boolean photord = 0;
  photord  = digitalRead(pin_photord);
  Serial.println(photord);
  delay(1);   
}

void infrared(){
  float infrared = 0;
  infrared = a*pow(analogRead(pin_infrared),b);
  Serial.println(infrared);
  delay(1);   
}

float calibrate_infrarred(int n)
{
  long suma=0;
  for(int i=0;i<n;i++)
  {
    suma=suma+analogRead(A0);
  }  
  float adc=suma/n;
  float distancia_cm = 17569.7 * pow(adc, -1.2062);
  return(distancia_cm);
}

