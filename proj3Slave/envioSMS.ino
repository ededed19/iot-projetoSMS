void acionarBuzzer(){
  tone(BUZZER, 1000);
}

void desativarBuzzer() {
  noTone(BUZZER);
}

void validarDigitacaoSenha() {
  char key = keypad.getKey();
  
  if (key) {
    if (key == '*') {
      quantDigitados = 0;
      digitando = true;
      //Serial.println("Iniciando digitação da senha...");
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Digitando senha!");
      return;
    }
    if (digitando && key != '#') {
      senha[quantDigitados++] = key;
      if(quantDigitados == TAMANHO_SENHA) {
        quantDigitados = 0;
      }
      Serial.write(senha, TAMANHO_SENHA);
      //Serial.write(10);
    }
    if (key == '#') {
      digitando = false;
      //Serial.println("Encerrou");
      if (strcmp(senha, SENHA_GRAVADA) == 0) {
        //Serial.println("Senha correta");
        desativarBuzzer();
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Senha correta");
        c = '0';

        delay(3000);
        iniciarLCD();
      } else {
        //Serial.println("Senha INCORRETA!!!");
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Senha INCORRETA!");
        c = '1';
        
        acionarBuzzer();
        delay(500);
      }
    }
  }

  if (digitando) {
    if (millis() - time > intervalo) {
      acionarBuzzer();
      c = '1';
    }
  } else {
    time = millis();
  }

  delay(100);
}

void iniciarLCD() {
  lcd.begin(16, 2);
  lcd.print("Casa: SEGURA");
}
