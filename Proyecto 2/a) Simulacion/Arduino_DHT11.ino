//Incluimos las librerias
#include "DHTesp.h"
#include "BluetoothSerial.h"


//Declaramos el variable que almacena el pin a conectar el DHT11
int pinDHT = 15;
//Iniciamos el DHT11
DHTesp dht;
//Iniciamos el Bluetooth
BluetoothSerial SerialBT;


void setup() {
  Serial.begin(115200);
  //Inicializamos el dht
  dht.setup(pinDHT, DHTesp::DHT11);
  //Inicializamos el Bluetooth
  SerialBT.begin("BluetoothESP32");
}
void loop() {
  //Obtenemos el arreglo de datos (humedad y temperatura)
  TempAndHumidity data = dht.getTempAndHumidity();
  //Mostramos los datos de la temperatura y humedad por Monitor Serie
  Serial.println("Temperatura: " + String(data.temperature, 2) + "°C");
  Serial.println("Humedad: " + String(data.humidity, 1) + "%");
  Serial.println("---");
  delay(1000);

  // Enviamos los datos por Bluetooth
  if (SerialBT.hasClient()) {
    SerialBT.println("Temperatura: " + String(data.temperature, 2) + "°C");
    SerialBT.println("Humedad: " + String(data.humidity, 1) + "%");
    SerialBT.println("---");
  }

}
