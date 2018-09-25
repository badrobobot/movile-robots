/*
  Practice 2 
  Bio-Robotics 
  Fi-UNAM
  ASK THEN READ AND PRINT
  
*/

#define pin_contact   2
#define pin_temp      A0
#define pin_photora   A1 
#define pin_photord   3
#define pin_infrared  A3
const float a1 = 0.987;
const float a0 = 0.655;

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
      Serial.println(" ");
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
  Serial.println(analogRead(pin_temp));  
  //temperatura = ((5.0*analogRead(pin_temp)/1024)-0.5)*100;
  temperatura = ((5000.0*analogRead(pin_temp)/1024)-500)*0.1;
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
  //infrared = a*pow(analogRead(pin_infrared),b);
  infrared = analogRead(pin_infrared);
  if(infrared>=80 && infrared<=500){
    //infrared = (4800)/(infrared-20)+1;
    //infrared = a0+infrared*a1;
    //Serial.println(infrared);
  int n=10;
  float suma=0;
  for(int i=0;i<n;i++)
  {
    suma=suma+analogRead(A0);
  }  
  float adc=suma/n;
  float distancia_cm = 8374.874951 * pow(adc, -1.095903);
  distancia_cm=a0+a1*distancia_cm;
  Serial.println(distancia_cm);
  
  } else{
    Serial.println(0);  
  }    
  delay(1);   
}
