boolean stringComplete = false;
String  inputString = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("None")
  
  if(stringComplete){
    if(inputString == "AA"){ digitalWrite(13,1); Serial.println("AA"); }
    if(inputString == "BB"){ digitalWrite(13,0); Serial.println("BB"); }
    else{
      Serial.println(inputString);  
    }
    inputString = "";
    stringComplete = false;
  }
  //Serial.println("HOLA MAN");
  
}


 
void serialEvent(){
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == 'X') {
       
    }else{
      inputString += inChar;  
    }
  }
}
