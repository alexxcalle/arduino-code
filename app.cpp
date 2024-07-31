#include <DHT.h>

// Definición de pines
#define DHTPIN 9
#define DHTTYPE DHT11
#define MQ135PIN 11
#define MQ7PIN 10
#define LED_VERDE 6
#define LED_AMARILLO 5
#define LED_ROJO 4
#define BUZZER 8
#define SWITCH 7

// Inicialización del sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Variables para almacenar lecturas de sensores
float temperatura, humedad, co2, co;

// Variable para almacenar el índice de calidad ambiental
int indiceCalidad;

void setup() {
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(SWITCH, INPUT_PULLUP);
  
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(SWITCH) == LOW) {
    leerSensores();
    indiceCalidad = calcularIndiceCalidad();
    activarIndicadores();
    imprimirLecturas();
  } else {
    apagarIndicadores();
  }
  
  delay(2000);
}

void leerSensores() {
  temperatura = dht.readTemperature();
  humedad = dht.readHumidity();
  co2 = map(analogRead(MQ135PIN), 0, 1023, 400, 5000); // Mapeo aproximado a ppm de CO2
  co = map(analogRead(MQ7PIN), 0, 1023, 0, 1000);      // Mapeo aproximado a ppm de CO
}

int calcularIndiceCalidad() {
  int indiceCO2 = map(co2, 400, 2000, 0, 50);  // CO2 tiene más peso
  int indiceCO = map(co, 0, 9, 0, 20);         // CO tiene menos peso
  int indiceTemp = map(constrain(temperatura, 20, 25), 20, 25, 0, 15);
  int indiceHum = map(constrain(humedad, 30, 60), 30, 60, 0, 15);
  
  return constrain(indiceCO2 + indiceCO + indiceTemp + indiceHum, 0, 100);
}

void activarIndicadores() {
  if (indiceCalidad < 50 && co2 < 1000 && co < 9) {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_AMARILLO, LOW);
    digitalWrite(LED_ROJO, LOW);
    noTone(BUZZER);
  } else if (indiceCalidad < 75 && co2 < 2000 && co < 35) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARILLO, HIGH);
    digitalWrite(LED_ROJO, LOW);
    noTone(BUZZER);
  } else {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARILLO, LOW);
    digitalWrite(LED_ROJO, HIGH);
    tone(BUZZER, 1000, 100);
  }
}

void apagarIndicadores() {
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_ROJO, LOW);
  noTone(BUZZER);
}

void imprimirLecturas() {
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" °C, Humedad: ");
  Serial.print(humedad);
  Serial.print(" %, CO2: ");
  Serial.print(co2);
  Serial.print(" ppm, CO: ");
  Serial.print(co);
  Serial.print(" ppm, Índice de calidad: ");
  Serial.println(indiceCalidad);
}