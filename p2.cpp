#include <LiquidCrystal.h>

const int RED_LED = 2;
const int GREEN_LED = 3;
const int PIR = 10;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int timesincelast = 5000;
int incidencias = 0;
int value = 0;
int green_status = 0;

char buffer[20];

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(PIR, INPUT);
  lcd.setCursor(0, 0);
  lcd.write("INCIDENCIAS 000");
}

void loop()
{
  value = digitalRead(PIR);
  if (value == HIGH) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
 	incidencias++;
    sprintf(buffer, "INCIDENCIAS %03d", incidencias);
    lcd.setCursor(0, 0);
  	lcd.write(buffer);
    delay(5000);
  } else {
    green_status = green_status ^ 1;
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, green_status);
    delay(200);
  }

  timesincelast += 500;
}