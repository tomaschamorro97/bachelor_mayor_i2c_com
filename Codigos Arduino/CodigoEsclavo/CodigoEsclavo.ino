#include <Wire.h>;
int variador_motor;
int variador_rgb;
int temphorno;

void setup() {
  Wire.begin(1);                  
  Wire.onReceive(receiveEvent); 
  Serial.begin(9600);
}

void loop() {
}

void receiveEvent( )
{
  while(Wire.available()) 
  {
    temphorno = Wire.read();
    variador_motor = Wire.read();
    variador_rgb = Wire.read();
    Serial.println(variador_motor);
    Serial.println(variador_rgb);
    analogWrite(6,variador_motor);
    while (temphorno<90) {
      if (variador_rgb<80)
      {
        analogWrite(11,255); //Estos son los valores para amarillo azufre R: 255, G: 245, B: 66
        analogWrite(10,245);
        analogWrite(9,66);
        
      }
      if (variador_rgb>=80&&variador_rgb<160)
      {
        analogWrite(11,222); //Estos son los valores para naranja salmon R: 222, G: 82, B: 71
        analogWrite(10,82);
        analogWrite(9,71);
        
      }
      if (variador_rgb>=160)
      {
        analogWrite(11,171); //Estos son los valores para rojo vivo R: 171, G: 31, B: 28
        analogWrite(10,31);
        analogWrite(9,28);
        
      }
    }
  }
 }
