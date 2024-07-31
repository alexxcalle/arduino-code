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
float temperatura, humedad, calidadAire, monoxidoCarbono;

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
  // Verificar si el switch está encendido
  if (digitalRead(SWITCH) == LOW) {
    // Leer sensores
    temperatura = dht.readTemperature();
    humedad = dht.readHumidity();
    calidadAire = analogRead(MQ135PIN);
    monoxidoCarbono = analogRead(MQ7PIN);
    
    // Calcular índice de calidad (ejemplo simplificado)
    indiceCalidad = calcularIndiceCalidad();
    
    // Activar indicadores según el índice de calidad
    if (indiceCalidad < 33) {
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_AMARILLO, LOW);
      digitalWrite(LED_ROJO, LOW);
      noTone(BUZZER);
    } else if (indiceCalidad < 42) {
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
    
    // Imprimir lecturas en el monitor serial
    imprimirLecturas();
    
  } else {
    // Apagar todos los indicadores si el switch está apagado
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARILLO, LOW);
    digitalWrite(LED_ROJO, LOW);
    noTone(BUZZER);
  }
  
  delay(2000); // Esperar 2 segundos antes de la siguiente lectura
}

int calcularIndiceCalidad() {
  // Este es un cálculo simplificado. Ajusta según tus necesidades específicas.
  int indice = map(calidadAire, 0, 1023, 0, 33) +
               map(monoxidoCarbono, 0, 1023, 0, 33) +
               map(temperatura, 15, 35, 0, 17) +
               map(humedad, 30, 70, 0, 17);
  return constrain(indice, 0, 100);
}

void imprimirLecturas() {
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" °C, Humedad: ");
  Serial.print(humedad);
  Serial.print(" %, Calidad del aire: ");
  Serial.print(calidadAire);
  Serial.print(", CO: ");
  Serial.print(monoxidoCarbono);
  Serial.print(", Índice de calidad: ");
  Serial.println(indiceCalidad);
}