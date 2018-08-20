/*

  Practice 2 
  Bio-Robotics 
  Fi-UNAM

*/

#define pin_contact   2
#define pin_temp      A0
#define pin_photora   A1 
#define pin_photord   A2
#define pin_infrared  A3

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete


void setup() {
  // put your setup code here, to run once:
  pinMode(pin_contact,INPUT);
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
    if(inputString=="shs photora"){
      Serial.print("photora ");
      photora();
    }
    if(inputString=="shs photord"){
      Serial.print("photord ");
      photord();
    }
    if(inputString=="shs temp"){
      Serial.print("temp ");
      temp();
    }
    if(inputString=="shs infrared"){
      Serial.print("infrared ");
      infrared();
    }
    else{
      Serial.print("Error: No sensor ");
      Serial.print(inputString);
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
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
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
  temperatura = digitalRead(pin_temp);
  Serial.println(temperatura);  
  delay(1); 
}

void photora(){
  float photora = 0;
  photora = digitalRead(pin_photora);
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
  infrared = digitalRead(pin_infrared);
  Serial.println(infrared);
  delay(1);   
}
