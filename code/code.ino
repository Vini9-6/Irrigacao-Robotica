/*
  ============================================
  SISTEMA DE IRRIGAÇÃO AUTOMÁTICA - v2.0
  ============================================

  Projeto para canteiro com 3 sensores de umidade.
  Utiliza média aritmética das leituras para maior precisão.

  FUNÇÕES DO ARDUINO UTILIZADAS:
  - pinMode(pino, modo): Define se o pino é entrada (INPUT) ou saída (OUTPUT)
  - digitalWrite(pino, valor): Escreve HIGH (5V) ou LOW (0V) no pino digital
  - analogRead(pino): Lê valor analógico de 0 a 1023 (0V a 5V)
  - delay(ms): Pausa a execução pelo tempo em milissegundos
  - Serial.begin(baud): Inicializa comunicação serial com velocidade definida
  - Serial.println(): Imprime dados no Monitor Serial com quebra de linha

  FUNÇÕES DA BIBLIOTECA LiquidCrystal.h:
  - LCD.begin(colunas, linhas): Inicializa o LCD com dimensões especificadas
  - LCD.setCursor(coluna, linha): Move o cursor para posição indicada (0-indexed)
  - LCD.print(texto): Escreve texto ou valor na posição atual do cursor
  - LCD.clear(): Limpa toda a tela e move cursor para posição (0,0)
*/

#include <LiquidCrystal.h>

// ============ CONFIGURAÇÃO DOS PINOS ============

// Pinos do LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal LCD(7, 6, 5, 4, 3, 2);

// Pinos dos sensores de umidade (analógicos)
const int SensorUmidade1 = A0;
const int SensorUmidade2 = A1;
const int SensorUmidade3 = A2;

// Pino do módulo relé (digital)
const int Rele = 8;

// ============ CONFIGURAÇÃO DE PARÂMETROS ============

// Limite de umidade: valores ACIMA indicam solo seco
// Sensor: FC-28 / YL-38 / YL-69 - Higrômetro de Solo (resistivo)
// Funciona por condução: duas hastes metálicas detectam umidade
// - Solo úmido: água conduz entre as hastes = valor BAIXO (0-400)
// - Solo seco: sem condução = valor ALTO (600-1023)
// AJUSTE ESTE VALOR conforme calibração do seu sensor
const int UmidadeLimite = 500;

// ============ VARIÁVEIS GLOBAIS ============

int valorSensor1;
int valorSensor2;
int valorSensor3;
int mediaUmidade;

// ============ FUNÇÃO SETUP ============

void setup()
{
  // Inicializa comunicação serial para debug no Monitor Serial
  Serial.begin(9600);

  // Configura o pino do relé como saída
  pinMode(Rele, OUTPUT);

  // Desativa o relé inicialmente (HIGH = relé desligado em módulos com lógica invertida)
  digitalWrite(Rele, HIGH);

  // Inicializa o LCD com 16 colunas e 2 linhas
  LCD.begin(16, 2);

  // ===== MENSAGEM DE BOAS-VINDAS =====
  LCD.setCursor(0, 0);
  LCD.print("  Bem-vindo ao  ");
  LCD.setCursor(0, 1);
  LCD.print(" Irriga Smart! ");
  delay(2000);

  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("  Iniciando...");
  LCD.setCursor(0, 1);
  LCD.print("   Sensores OK");
  delay(1500);

  LCD.clear();

  // Mensagem no Serial Monitor
  Serial.println("=================================");
  Serial.println("Sistema de Irrigacao Iniciado");
  Serial.println("3 Sensores Ativos - Media Ativa");
  Serial.println("=================================");
}

// ============ FUNÇÃO LOOP ============

void loop()
{
  // Leitura dos 3 sensores de umidade
  valorSensor1 = analogRead(SensorUmidade1);
  valorSensor2 = analogRead(SensorUmidade2);
  valorSensor3 = analogRead(SensorUmidade3);

  // Calcula a média aritmética das leituras
  mediaUmidade = (valorSensor1 + valorSensor2 + valorSensor3) / 3;

  // Converte para porcentagem (0-100%) - valores invertidos
  // 0 = muito seco, 100 = muito úmido
  int porcentagem = map(mediaUmidade, 1023, 0, 0, 100);
  porcentagem = constrain(porcentagem, 0, 100);

  // Exibe informações no Serial Monitor
  Serial.print("S1: ");
  Serial.print(valorSensor1);
  Serial.print(" | S2: ");
  Serial.print(valorSensor2);
  Serial.print(" | S3: ");
  Serial.print(valorSensor3);
  Serial.print(" | Media: ");
  Serial.print(mediaUmidade);
  Serial.print(" | ");
  Serial.print(porcentagem);
  Serial.println("%");

  // Exibe no LCD
  LCD.setCursor(0, 0);
  LCD.print("Umidade: ");
  LCD.print(porcentagem);
  LCD.print("%   ");

  // Verifica se o solo está seco (valor alto = seco)
  if (mediaUmidade > UmidadeLimite)
  {
    // Solo seco - Liga a irrigação
    digitalWrite(Rele, LOW);

    LCD.setCursor(0, 1);
    LCD.print(">> Irrigando  <<");

    Serial.println("*** BOMBA LIGADA ***");
  }
  else
  {
    // Solo úmido - Desliga a irrigação
    digitalWrite(Rele, HIGH);

    LCD.setCursor(0, 1);
    LCD.print("   Solo Umido   ");

    Serial.println("Bomba desligada");
  }

  // Aguarda 2 segundos para próxima leitura
  delay(2000);
}
