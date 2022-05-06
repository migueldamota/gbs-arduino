void setup() { 
Serial.begin(9600); 
} 
void loop() { 
if(Serial.available()>0) 
{ 
String value = Serial.readStringUntil('#'); 
//Serial.println(value); 
if(value.length()==7) 
{ 
String angle = value.substring(0, 3); 
String strength = value.substring(3, 6); 
String button = value.substring(6, 8); 

// Serial.print("angle: ");Serial.print(angle);Serial.print('\t'); 
// Serial.print("strength: ");Serial.print(strength);Serial.print('\t'); 
// Serial.print("button: ");Serial.print(button);Serial.println(""); 

if (strength.toInt() > 95) 
{ 
  Serial.println("1"); 
} 

if (strength.toInt() < 96 && strength.toInt() > 50) 
{ 
  Serial.println("2"); 
} 
  
if (strength.toInt() < 51) 
{ 
  Serial.println("3"); 
} 
Serial.flush(); 
value=""; 

} 
} 
} 
