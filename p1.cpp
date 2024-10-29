#include <LiquidCrystal.h>

const int Trigger = 2;   //Pin digital 2 para el Trigger del sensor
const int Echo = 3;   //Pin digital 3 para el Echo del sensor
const int Light = 10;

int light_status = 0;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación
  lcd.begin(16, 2);
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  pinMode(Light, OUTPUT); // led como salida
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
}

void loop()
{

  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  
  Serial.print("Distancia: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();
  if (d < 20) {
    light_status = light_status ^ 1;
    digitalWrite(Light, light_status);
    lcd.setCursor(0,0);
    lcd.write("INGRESE CLAVE: ");
  } else {
    digitalWrite(Light, 0);
    light_status = 0;
    lcd.setCursor(0,0);
    lcd.clear();
  }
  delay(100);          //Hacemos una pausa de 100ms
}
