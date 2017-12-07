#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

char c = '0'; // Status da segurança 0 = ok

bool digitando = false;
const int TAMANHO_SENHA = 5;
char senha[TAMANHO_SENHA] = {};
int quantDigitados = 0;
const char* SENHA_GRAVADA = "12345";

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {5, 4, 3, A0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
#define BUZZER 2
long time = 0;
int intervalo = 10000; //10s para digital senha.

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
#define rs A1
#define en 9
#define d4 A2
#define d5 A3
#define d6 10
#define d7 11
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  // Inicia comunicação como slave com endereço 8
  Wire.begin(8);
  // Registra callback para ser chamado quando receber mensagem
  Wire.onRequest(requestEvent);

  pinMode(A0, INPUT);
  pinMode(BUZZER, OUTPUT);
  
  iniciarLCD();
  
  Serial.begin(9600);
  Serial.print("Ok");
}

void loop() {
  validarDigitacaoSenha();
  delay(100);
}

void requestEvent() {
  Wire.write(c);
  //c = '9';
}
