# Sistema de Irrigação Automática com Arduino

## 📋 Resumo do Projeto

Este projeto consiste em um **sistema de irrigação automática** desenvolvido com Arduino, capaz de monitorar a umidade do solo e acionar automaticamente uma bomba d'água quando o solo estiver seco. O sistema utiliza sensores de umidade capacitivos ou resistivos, um módulo relé para controle da bomba, e um display LCD 16x2 para exibição das informações em tempo real.

### Objetivo Geral
Automatizar o processo de irrigação de plantas, garantindo que o solo mantenha níveis adequados de umidade sem a necessidade de intervenção manual constante.

### Objetivos Específicos
- Monitorar continuamente a umidade do solo
- Acionar a irrigação automaticamente quando a umidade estiver abaixo do limite estabelecido
- Exibir informações de status no display LCD
- Otimizar o consumo de água

---

## 🔧 Componentes Utilizados

| Componente | Quantidade | Descrição |
|------------|------------|-----------|
| Arduino UNO/Nano | 1 | Microcontrolador principal |
| Sensor de Umidade do Solo | 1 (atual) / 3 (futuro) | Leitura analógica da umidade |
| Módulo Relé 5V | 1 | Controle da bomba d'água |
| Display LCD 16x2 | 1 | Interface visual |
| Bomba d'água | 1 | Irrigação do canteiro |
| Fonte de alimentação | 1 | Alimentação do sistema |
| Jumpers e cabos | Diversos | Conexões do circuito |

---

## 📐 Esquema de Conexões

### Pinagem Atual

| Componente | Pino Arduino |
|------------|--------------|
| LCD RS | 7 |
| LCD E (Enable) | 6 |
| LCD D4 | 5 |
| LCD D5 | 4 |
| LCD D6 | 3 |
| LCD D7 | 2 |
| Sensor Umidade 1 | A0 |
| Módulo Relé | 8 |

### Pinagem Futura (Expansão)

| Componente | Pino Arduino |
|------------|--------------|
| Sensor Umidade 2 | A1 |
| Sensor Umidade 3 | A2 |

---

## 💻 Funcionamento do Sistema

### Fluxo de Operação

```
┌─────────────────┐
│  Inicialização  │
│    do Sistema   │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│  Leitura dos    │
│  Sensores       │◄──────────────┐
└────────┬────────┘               │
         │                        │
         ▼                        │
┌─────────────────┐               │
│ Cálculo da Média│               │
│   de Umidade    │               │
└────────┬────────┘               │
         │                        │
         ▼                        │
┌─────────────────┐               │
│ Umidade > Limite│               │
│   (Solo Seco?)  │               │
└────────┬────────┘               │
    Sim  │   Não                  │
    ┌────┴────┐                   │
    ▼         ▼                   │
┌───────┐ ┌───────┐               │
│ Liga  │ │Desliga│               │
│ Bomba │ │ Bomba │               │
└───┬───┘ └───┬───┘               │
    │         │                   │
    └────┬────┘                   │
         │                        │
         ▼                        │
┌─────────────────┐               │
│  Atualiza LCD   │               │
└────────┬────────┘               │
         │                        │
         ▼                        │
┌─────────────────┐               │
│  Aguarda 2s     │───────────────┘
└─────────────────┘
```

### Parâmetros de Configuração

- **Limite de Umidade**: 500 (valores acima indicam solo seco)
- **Intervalo de Leitura**: 2 segundos
- **Tipo de Leitura**: Analógica (0-1023)

---

## 📊 Etapa Atual do Projeto

### Trabalho Realizado

1. **Levantamento Bibliográfico**
   - Pesquisa sobre sistemas de irrigação automatizados
   - Estudo dos componentes eletrônicos utilizados
   - Análise de projetos similares para referência

2. **Manutenção do Circuito**
   - Revisão e correção de soldas
   - Verificação e melhoria das conexões
   - Testes de continuidade elétrica

3. **Análise do Código Existente**
   - Identificação de erros de sintaxe
   - Documentação das funções utilizadas

### Correções Necessárias no Código

O código atual apresenta alguns erros que precisam ser corrigidos:

| Linha | Erro | Correção |
|-------|------|----------|
| 22 | `Serial.Begin(9600)` | `Serial.begin(9600)` |
| 27 | `HIGHT` | `HIGH` |
| 49 | `LCD.setCursor("0,1")` | `LCD.setCursor(0,1)` |
| 58 | `digitalWrite(rele,LOW)` | `digitalWrite(Rele,LOW)` |
| 66 | `HIGHT` | `HIGH` |

---

## 🚀 Projeções Futuras

### Fase 1: Expansão dos Sensores (Em Andamento)
- [ ] Adicionar 2 sensores de umidade adicionais (A1 e A2)
- [ ] Implementar cálculo de média aritmética das leituras
- [ ] Adaptar o código para leitura de múltiplos sensores

### Fase 2: Melhorias no Software
- [ ] Implementar calibração automática dos sensores
- [ ] Adicionar diferentes modos de operação por tipo de planta
- [ ] Criar sistema de logs via Serial Monitor
- [ ] Implementar alarmes visuais/sonoros para manutenção

### Fase 3: Interface e Conectividade
- [ ] Adicionar módulo WiFi (ESP8266/ESP32) para monitoramento remoto
- [ ] Desenvolver aplicativo mobile ou dashboard web
- [ ] Implementar notificações push para alertas

### Fase 4: Otimizações
- [ ] Adicionar sensor de nível de água no reservatório
- [ ] Implementar economia de energia (modo sleep)
- [ ] Criar perfis de irrigação por horário
- [ ] Integrar sensor de temperatura e luminosidade

---

## 📁 Estrutura do Projeto

```
ROBÓTICA/
├── README.md                    # Este arquivo
├── RELATORIO_FINAL.pdf          # Relatório acadêmico do projeto
├── code/
│   └── code.ino                 # Código fonte do Arduino
└── Imagens/
    └── (esquemas e fotos)       # Documentação visual
```

---

## 📚 Referências Técnicas

### Bibliotecas Utilizadas
- **LiquidCrystal.h**: Biblioteca padrão do Arduino para controle de displays LCD

### Funções Arduino Utilizadas

| Função | Descrição |
|--------|-----------|
| `pinMode()` | Define o modo do pino (entrada/saída) |
| `digitalWrite()` | Escreve valor digital no pino |
| `analogRead()` | Lê valor analógico do pino (0-1023) |
| `delay()` | Pausa a execução por milissegundos |
| `Serial.begin()` | Inicializa comunicação serial |

### Funções LCD Utilizadas

| Função | Descrição |
|--------|-----------|
| `LCD.begin(cols, rows)` | Inicializa o LCD com dimensões |
| `LCD.setCursor(col, row)` | Posiciona o cursor |
| `LCD.print()` | Imprime texto no display |
| `LCD.clear()` | Limpa o display |

---

## 👥 Equipe

- **Autora Original**: Sophia Di Consulin
- **Manutenção e Aprimoramento**: [Seu Nome]

---

## 📅 Histórico de Versões

| Versão | Data | Descrição |
|--------|------|-----------|
| 1.0 | - | Versão inicial com 1 sensor |
| 1.1 | Fev/2026 | Manutenção do circuito e correção de soldas |
| 2.0 | (Planejado) | Expansão para 3 sensores com média aritmética |

---

## 📝 Licença

Este projeto foi desenvolvido para fins educacionais.

---

## ⚠️ Observações

- Sempre verifique a polaridade das conexões antes de energizar o circuito
- Utilize fonte de alimentação adequada para a bomba d'água
- Mantenha os componentes eletrônicos protegidos da umidade
- Realize manutenção preventiva periodicamente

