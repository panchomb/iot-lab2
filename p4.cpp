const int BLUE_LED = 2;
const int RED_LED = 3;
const int BUZZER = 4;
const int SENSOR_HUMEDAD = 0;

int alert_status = 0;
int idle = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop()
{
  int humedad = analogRead(SENSOR_HUMEDAD);
  humedad = map(humedad, 0, 1024, 100, 0);
  
  Serial.print("HUMEDAD: ");
  Serial.println(humedad);
  
  if (idle) {
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);
    Serial.println("MODO IDLE");
    delay(15000);
    idle = 0;
  } else {
    if (humedad < 20) {
      digitalWrite(BLUE_LED, HIGH);
      digitalWrite(RED_LED, LOW);
      digitalWrite(BUZZER, LOW);
      // activar bomba de agua
      Serial.println("MODO RIEGO - HUMEDAD: ");
      Serial.println(humedad);
      delay(10000);
      idle = 1;
    } else if (humedad >= 50) {
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(BUZZER, alert_status);

      alert_status = alert_status ^ 1;
      digitalWrite(RED_LED, alert_status);

      Serial.println("ALERTA");

      delay(500);
    } else {
      digitalWrite(RED_LED, LOW);
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(BUZZER, LOW);
      Serial.println("normal");
      delay(1000);
    }
  }
}