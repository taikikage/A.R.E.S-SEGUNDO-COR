///"A.R.E.S"

// Definición de pines para la ESP32-S3 S N
#define TRIG_1 4
#define ECHO_1 5
#define BOMBILLO 14 // Pin para el LED para el bombillo de alerta

//--------- Configuración de la ESP32-S3 ------
void setup() {
  Serial.begin(9600);
  // Configuración de pines b
  pinMode(TRIG_1, OUTPUT);
  pinMode(ECHO_1, INPUT);
  pinMode(BOMBILLO, OUTPUT); 
  // Bombillo Apagado
  digitalWrite(BOMBILLO, LOW);
}

void loop() {
  // Lectura del sensor
  int s1 = medir_distancia(TRIG_1, ECHO_1);
  // Impresión de resultado
  imprimir_lectura(s1);

  // Se encendera el bombillo si hay algo a menos de 10 cm
  evaluar_alerta(s1);

  delay(200); 
}

//--------- Función para medir la distancia en cm ------
int medir_distancia(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH); // Espera de 10 microsegundos
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duracion = pulseIn(echo, HIGH, 30000); // Tiempo del eco (timeout ~30ms)
  if (duracion == 0) return -1; // Retorna -1 si está fuera de rango o falla
  int distancia = duracion * 0.0343 / 2; // Cálculo de la distancia en cm
  return distancia;
}

//--------- Función para imprimir lectura ------
void imprimir_lectura(int d1) {
  Serial.print("Distancia: ");
  Serial.print(d1);
  Serial.println(" cm");
}

//--------- Función para evaluar la alerta ------
void evaluar_alerta(int d1) {
  // Se enciende el bombillo si se detecta un objeto a menos de 10 cm
  if (d1 > 0 && d1 < 10) {
    digitalWrite(BOMBILLO, HIGH); // Encender alerta
  } else {
    digitalWrite(BOMBILLO, LOW);  // Bombillo apagado
  }
}