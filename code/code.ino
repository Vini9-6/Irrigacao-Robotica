/* 

Código do sistema de irrigação, sem o tipo de planta 
defifida e com apenas um sensor.

[exlicação das funções do arduino]

[explicação das funções da biblioteca LiquidCrystal.h]

*/

#include <LiquidCrystal.h>

//Configuração dos pinos LCD
LiquidCrystal LCD (7, 6, 5, 4, 3, 2); // RS, E, D4, D6 , D7, respectivamente

//Definição dos pinos
int SensorUmidade = A0; // pino analógico
int Rele = 8;           // pino digital

// Definiçõa do limimte do estado seco do sensor de umidade
int UmidadeLimite = 500;

int ValorUmidade;

void setup() {
  // Definições no código que rodarão apenas uma vez

  Serial.Begin(9600); // [Coloque uma explicação aqui]

  // Configuração do pino relé como saída (irá executar o comando recebido)
  pinMode(Rele,OUTPUT);
  // Inicialmente o relé será desativado
  digitalWrite(Rele,HIGHT);

  // Iniciação do LCD com 16 colunas e 2 linhas (máximo), sendo a primeira posição 0
  LCD.begin(16,2);
  //Mensagem inicial
  LCD.setCursor(0,0); // Posição da sentença a ser escrita, na linha 0 no inicio da coluna (0)
  LCD.print("Sistema  de irrigacao"); // Imprime no LCD
  LCD.setCursor(0,1); // inicio da linha 1
  LCD.print("Iniciando"); // Imprime no LCD
  
  delay(2000); // Espera 2 segundos, para posiibilitar a leitura
  LCD.clear(); // Limpa o LCD

}

void loop() {
  // Aqui o código repetirá indefinidas vezes

  // Leitura da umidade do solo
  ValorUmidade = analogRead(SensorUmidade); // Como a porta é analogica, a leitura também será analógica

  // Mostrar o valor da umimdade no LCD
  LCD.setCursor(0,0);
  LCD.print("Umidade do solo:"); 

  LCD.setCursor("0,1");
  LCD.print(ValorUmidade);

  LCD.clear();

  // Verificação se o solo está seco
  if(ValorUmidade > UmidadeLimite){
    // Se o solo estiver seco o relé será ativado
    digitalWrite(rele,LOW); // Relé ligado


    LCD.clear();
    LCD.setCursor(0,1);
    LCD.print("Irrigando");
  }else{
    // Se o solo estiver úmimdo, desligará o Relé
    digitalWrite(Rele,HIGHT); // Relé deligado

    LCD.clear();
    LCD.setCursor(0,1);
    LCD.print("Solo Umido");
  }

  // Espera 2 segundos para a próxima leitura
  delay(2000);

}
