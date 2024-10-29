#include <LiquidCrystal.h>

const int RED_LED = 2;
const int BUZZER = 3;
const int SENSOR_HUMEDAD = 0;
const int SENSOR_TEMPERATURA = 1;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int red_status = 0;

char buffer[20];

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  lcd.setCursor(0, 0);
  lcd.write("TEMP    HUMED");
}

void loop()
{
  red_status = red_status ^ 1;
  digitalWrite(RED_LED, red_status);
  
  int humedad = analogRead(SENSOR_HUMEDAD);
  humedad = map(humedad, 0, 875, 0, 100);
  
  
  int temp_analog = analogRead(SENSOR_TEMPERATURA);
  int temp = map(temp_analog, 20, 357, -40, 125);
  
  if (temp < 0 or temp > 10) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);
  } else if (humedad < 80 or humedad > 90) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);
  } else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);
  }
  
  sprintf(buffer, "%3dC      %2d%%  ", temp, humedad);
  lcd.setCursor(0,0);
  lcd.write("TEMP    HUMED   ");
  lcd.setCursor(0,1);
  lcd.write(buffer);
}