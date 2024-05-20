#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

const int LED_PIN = 15;  // Pin del LED
bool ledState = false;   // Estado inicial del LED (apagado)
String receivedString;   // Variable para almacenar el comando recibido

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_LED_Control");  // Nombre del dispositivo Bluetooth

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Asegúrate de que el LED esté apagado al inicio

  Serial.println("El dispositivo se ha iniciado, ahora puedes conectarlo por Bluetooth!");
}

void loop() {
  while (SerialBT.available()) {
    char c = SerialBT.read();
    receivedString += c;
    if (c == '\n') {  // Se ha recibido el comando completo
      Serial.print("Comando recibido: ");
      Serial.println(receivedString);

      if (receivedString.startsWith("On")) {  // Enciende el LED
        ledState = true;
        digitalWrite(LED_PIN, HIGH);
        SerialBT.println("LED encendido");
      } else if (receivedString.startsWith("Off")) {  // Apaga el LED
        ledState = false;
        digitalWrite(LED_PIN, LOW);
        SerialBT.println("LED apagado");
      } else {
        SerialBT.println("Comando invalido. Usar 'On' para encender y 'Off' para apagar el LED.");
      }

      receivedString = "";  // Limpia la cadena para el siguiente comando
    }
  }
  delay(20);  // Pequeño retardo para evitar el uso excesivo de la CPU
}
