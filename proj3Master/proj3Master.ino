#include <Wire.h>
#include <UIPEthernet.h>
#include <RestClient.h>

const byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x06 };
// IPAddress ipFixo(192, 168, 3, 46);
EthernetClient ethclient;
const char* parametros = "sid=AC031b2ade1deb64695b5adb7ac314db9f&token=8ab99b6a27930dfff8fe84bcf311b3e3&to=5511980230867&from=14159688707&body=ATEN%C3%87%C3%83O%3A%20CASA%20INVADIDA%21%21%21";
RestClient client = RestClient("192.168.3.186", 3000, ethclient);

String response = "";

char cAnterior = '0';

void setup() {
#ifndef IPFIXO
  Ethernet.begin(mac);
#else
  Ethernet.begin(mac, ipFixo);
#endif
  // Ingressar no bus como Master
    
  Serial.begin(9600);
  Serial.print("[Master] Ok");
  Wire.begin();
}

// A função loop neste exemplo irá transmitir um contador incrementado a cada meio segundo
void loop() {
  // Pedir 6 bytes do slave de endereço 8
  Wire.requestFrom(8, 1);

  // O slave pode não enviar todos os bytes requisitados
  // Então lemos os dados em um loop ao invés de assumir o tamanho
  while (Wire.available()) {
    // ler o byte como char
    char c = Wire.read();
    Serial.println(c);
    if ( c == '1' && c != cAnterior) {
      cAnterior = c;
      enviarSMS();
    }
  }

  delay(100);
}

void enviarSMS() {
  Serial.println("[Master] Enviando SMS");
  int statusCode = client.post("/sms", parametros, &response);
  //delay(100);
}
