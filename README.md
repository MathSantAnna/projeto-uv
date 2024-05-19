# Monitoramento de Radiação UV com NodeMCU e LEDs Indicadores

Este repositório contém o código-fonte e a documentação do projeto de monitoramento de radiação ultravioleta (UV) utilizando o módulo NodeMCU e LEDs indicadores de 5mm. O objetivo deste projeto é promover a saúde e o bem-estar, alinhando-se ao Objetivo de Desenvolvimento Sustentável 3 das Nações Unidas, que visa garantir uma vida saudável e promover o bem-estar para todos.

## Sobre o Projeto

O projeto foi desenvolvido como parte da disciplina de Objetos Inteligentes Conectados da turma 5B na Universidade Presbiteriana Mackenzie.

### Componentes Utilizados

- **NodeMCU**: Microcontrolador utilizado para coletar dados do sensor UV e enviar as informações para a plataforma MQTT.
- **Sensor UVM-30A**: Sensor utilizado para medir a intensidade da radiação UV.
- **LEDs Difusos de 5mm**: Utilizados para indicar visualmente os níveis de radiação UV.
  - LED Verde: Baixa exposição UV
  - LED Amarelo: Exposição UV moderada
  - LED Vermelho: Alta exposição UV
- **Mosquitto MQTT**: Protocolo utilizado para a comunicação entre o NodeMCU e a plataforma de visualização.
- **Node-RED**: Plataforma utilizada para desenvolver uma dashboard interativa para visualização dos dados em tempo real.

### Resultados

- **Medição Precisa**: O sensor UVM-30A demonstrou alta precisão na detecção de radiação UV.
- **Indicação Eficiente**: Os LEDs forneceram uma indicação visual clara dos níveis de radiação UV.
- **Desafios**: Durante a gravação noturna, utilizamos luz ultravioleta artificial para simular diferentes níveis de radiação UV.
- **Melhorias Futuras**: Implementação de uma fonte de alimentação externa para aumentar a portabilidade do dispositivo.

## Instalação

1. Clone o repositório para sua máquina local:
   git clone https://github.com/MathSantAnna/projeto-uv.git
   
2. Instale as bibliotecas necessárias:
ESP8266WiFi
PubSubClient
3. Carregue o código no NodeMCU utilizando o Arduino IDE.
4. Configure o servidor Mosquitto MQTT e a dashboard no Node-RED.
