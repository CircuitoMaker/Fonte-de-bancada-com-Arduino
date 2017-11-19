/*
 * CircuitoMaker.com
 * ATinny85 8 MHz interno 
 * ATtiny85 I2C pinos:
 * ATtiny85 Pino 5 = SDA
 * ATtiny85 Pino 7 = SCK
 * ATinny85 Pino 2 = Sensor de tensão
 */

#include <TinyWireM.h>               // Biblioteca I2C para Attiny
#include <LiquidCrystal_attiny.h>    // Para controle do LCD MODIFICADA PARA O ATtiny85
LiquidCrystal_I2C lcd(0x3f, 16, 2);  // Endereço I2C e tipo de display (16x2) 

float tensao; // variavel que vai receber a voltagem da bateria
char linha1[]={'F','o','n','t','e',' ','d','e',' ','b','a','n','c','a','d','a'}; // Primeira linha do LCD
char linha2[]={'T','e','n','s','a','o',':',' '};                                 // Segunda  linha do LCD
char data[5];


void setup() {
 lcd.init();                           // Inicializa o LCD
 lcd.backlight();                      // Ativa a luz do LCD
 imprime();                            // Escreve mensagem no LCD
}

void loop() {

LeTensao();
lcd.setCursor(8,1); // Posiciona o cursor para escrever o valor da tensão lida

dtostrf(tensao,4,2,data);
for (int x=0; x<= 3;x++)
{
  lcd.print(data[x]);
  }
  
if(tensao >= 10.00){lcd.print(data[4]);}

lcd.print(" ");
lcd.print("V");  // V = volts
lcd.print(" ");
delay(500);     // Tempo de "atualização" do display

}


void imprime()
{
  for (int x=0; x<=15; x++){
   lcd.setCursor(x,0);
   lcd.print(linha1[x]);
  }
  
  for (int x=0; x<=7; x++){
   lcd.setCursor(x,1);
   lcd.print(linha2[x]);
  }
 
  }// fim imprime()


void LeTensao()
{
// formula de cálculo da tensão da bateria com base no divisor resistivo formado pelos resistores R1 e R2
const float R1 = 470.0;
const float R2 = 270.0;
const float  k = (R1 + R2) / R2;   
float vout=(float(analogRead(2)) / 1023) * 5;
tensao = (vout * k);
}

