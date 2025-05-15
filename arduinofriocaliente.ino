#include <LiquidCrystal.h> // Import the LCD library

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int frio = 9;
int caliente = 8;
void mostrarTexto(String linea1, String linea2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(linea1);
  lcd.setCursor(0, 1);
  lcd.print(linea2);
  delay(1000);
}

void parpadear(int pin){
  for (int i = 0; i < 5; i++) {
    encender(pin);
    delay(500);
    apagar(pin);
  }

}

           



int my_random(int seed) {
  int random = ((seed + 31289) * 2342341) % 101; 
  return random;
}

void encender(int pin) {
  digitalWrite(pin, HIGH);
}

void apagar(int pin) {
  digitalWrite(pin, LOW);
}

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);  
  lcd.begin(16, 2);      
  Serial.begin(9600);    
}

void loop() {
  encender(9);
  mostrarTexto("Comenzar Juego","Y/N");

  if (Serial.available() > 0) {
    String opt = Serial.readStringUntil('\n'); 
    opt.trim(); 

    if (opt.equalsIgnoreCase("Y")) {
   

      mostrarTexto("Adivina", "El Numero");
      
      // Usa millis() como semilla semialeatoria
      int numero = my_random(millis() % 1000); 
      mostrarTexto("Azul Frio","");
      encender(frio);
      delay(1000);
      apagar(frio);
      mostrarTexto("Rojo Caliente","");
      encender(caliente);
      delay(1000);
      apagar(caliente);
      
     while (true) {
      apagar(frio);
      apagar(caliente);
      mostrarTexto("Di un", String(numero));

      while (Serial.available() == 0); // Espera a que el usuario escriba

      String guess = Serial.readStringUntil('\n');
      guess.trim();
      int guessInt = guess.toInt();

      int diferencia = abs(guessInt - numero);

      if (guessInt == numero) {
        mostrarTexto("Ganaste", ":):):):)");
        parpadear(frio);
        parpadear(caliente);
        break;
      } 
      else if (diferencia <= 5) {
        mostrarTexto("Muy Caliente", "");
        parpadear(caliente);
      } 
      else if (diferencia <= 10) {
        mostrarTexto("Caliente", "");
        encender(caliente);
      } 
      else if (diferencia <= 20) {
        mostrarTexto("Templado", "");
      } 
      else if (diferencia <= 30) {
        mostrarTexto("Frio", "");
        encender(frio);
      } 
      else if (diferencia <= 50) {
        mostrarTexto("Congelado", "");
        parpadear(frio);
      } 
      else {
        mostrarTexto("Ni te", "acercas");
      }
    } 
    }

    lcd.clear();
  }

  delay(1000);
}
