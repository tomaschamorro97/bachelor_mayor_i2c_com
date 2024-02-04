#include "dis7seg.h";
#include <Wire.h>;
#include "Adafruit_Si7021.h"

int variador_motor;
int variador_rgb;
int rpm_motor;
int cen_temp;
int dec_temp;
int uds_temp;
int dec_hum;
int uds_hum;
int temphorno;
int humhorno;
int tr_dechum = 7;
int tr_udhum = 6;
int tr_centem = 5;
int tr_dectem = 4;
int tr_udstem = 3;
int on_off = 53;
int print1borrar;
int print2borrar;
int sensor_pos = 37;

Adafruit_Si7021 sensor = Adafruit_Si7021();



Display disp_rpm(22,23,24,25,26,27,28,LOW);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Wire.begin();
  // wait for serial port to open
  while (!Serial) {
    delay(10);
  }

  Serial.println("Prueba Si7021!");
  
  if (!sensor.begin()) {
    Serial.println("No se encontró sensor Si7021!");
    while (true)
      ;
  }

  Serial.print("Se encontró Modelo");
  switch(sensor.getModel()) {
    case SI_Engineering_Samples:
      Serial.print("SI muestra de ingeniería"); break;
    case SI_7013:
      Serial.print("Si7013"); break;
    case SI_7020:
      Serial.print("Si7020"); break;
    case SI_7021:
      Serial.print("Si7021"); break;
    case SI_UNKNOWN:
    default:
      Serial.print("Unknown");
  }
  Serial.print(" Rev(");
  Serial.print(sensor.getRevision());
  Serial.print(")");
  Serial.print(" Serial #"); Serial.print(sensor.sernum_a, HEX); Serial.println(sensor.sernum_b, HEX);
}

void descom_temphum(){
  temphorno = sensor.readTemperature();
  humhorno = sensor.readHumidity();
    if (temphorno>=100)
      {
      cen_temp = (temphorno / 100);
      dec_temp = (temphorno % 100)/10;
      uds_temp = (temphorno % 100)%10;
      }
      else
      {
      cen_temp = 0;
      dec_temp = (temphorno /10);
      uds_temp = (temphorno % 10);
      }

    if (humhorno==100)
    {
     humhorno=99; 
    }
    if (humhorno > 9)
    {
    dec_hum = humhorno / 10;
    uds_hum = humhorno % 10;
    }
    else
    {
    dec_hum = 0;
    uds_hum = humhorno;
    }
  return cen_temp,dec_temp,uds_temp,dec_hum,uds_hum;
   
}

void mostrar()
{
    descom_temphum();
    
    disp_rpm.print(uds_temp);
    digitalWrite(tr_udstem, HIGH);   
    digitalWrite(tr_dectem, LOW);
    digitalWrite(tr_centem, LOW);
    digitalWrite(tr_udhum, LOW);
    digitalWrite(tr_dechum, LOW);
    delay(1);
    digitalWrite(tr_udstem, LOW); 
    delay(1);

    disp_rpm.print(dec_temp);
    digitalWrite(tr_udstem, LOW);   
    digitalWrite(tr_dectem, HIGH);
    digitalWrite(tr_centem, LOW);
    digitalWrite(tr_udhum, LOW);
    digitalWrite(tr_dechum, LOW);
    delay(1);
    digitalWrite(tr_dectem, LOW); 
    delay(1);
    
    if (temphorno>=100)
    {
    disp_rpm.print(cen_temp);
    digitalWrite(tr_udstem, LOW);   
    digitalWrite(tr_dectem, LOW);
    digitalWrite(tr_centem, HIGH);
    digitalWrite(tr_udhum, LOW);
    digitalWrite(tr_dechum, LOW);
    delay(1);
    digitalWrite(tr_centem, LOW); 
    delay(1);
    }
    
    disp_rpm.print(uds_hum);
    digitalWrite(tr_udstem, LOW);   
    digitalWrite(tr_dectem, LOW);
    digitalWrite(tr_centem, LOW);
    digitalWrite(tr_udhum, HIGH);
    digitalWrite(tr_dechum, LOW);
    delay(1);
    digitalWrite(tr_udhum, LOW); 
    delay(1);


    disp_rpm.print(dec_hum);
    digitalWrite(tr_udstem, LOW);   
    digitalWrite(tr_dectem, LOW);
    digitalWrite(tr_centem, LOW);
    digitalWrite(tr_udhum, LOW);
    digitalWrite(tr_dechum, HIGH);
    delay(1);
    digitalWrite(tr_dechum, LOW); 
    delay(1);
    

}

void loop() {
  //delay(200);
  //print1borrar = (cen_temp*100)+(dec_temp*10)+uds_temp;
  //print2borrar = (dec_hum*10)+uds_hum;
  //Serial.println(print1borrar);
  //Serial.println(print2borrar);

  while (digitalRead(53) == HIGH && digitalRead(37) == HIGH) 
  {
  descom_temphum();
  Serial.print("Humedad:    ");
  Serial.println(sensor.readHumidity(), 2);
  Serial.print("\tTemperatura: ");
  Serial.println(sensor.readTemperature(), 2);
  variador_motor = analogRead(0);
  variador_rgb = analogRead(1);
  variador_motor = map(variador_motor,0,1023,0,255);
  variador_rgb = map(variador_rgb,0,1023,0,255);
  Wire.beginTransmission(1);
  Wire.write(temphorno); 
  Wire.write(variador_motor);   
  Wire.write(variador_rgb);        
  Wire.endTransmission(); 
  mostrar();
  }

 
}
