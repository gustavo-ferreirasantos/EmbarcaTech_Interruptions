# EmbarcaTech_Interruptions

Este projeto consiste na implementação de um contador utilizando uma matriz de LEDs RGB controlada pelo Raspberry Pi Pico W. O valor do contador pode ser incrementado ou decrementado por meio de dois botões e é exibido na matriz de LEDs. Além disso, um LED pisca continuamente.

## Objetivos
- Compreender o funcionamento e a aplicação de interrupções em microcontroladores.
- Identificar e corrigir o fenômeno do bouncing em botões por meio de debouncing via software.
- Manipular e controlar LEDs comuns e LEDs endereçáveis WS2812.
- Fixar o estudo do uso de resistores de pull-up internos em botões de acionamento.
- Desenvolver um projeto funcional que combine hardware e software.

## Funcionalidades  

- Contador de 0 a 9 com exibição em matriz de LEDs.  
- Controle via botões:  
  - **Botão A (GPIO5)**: Incrementa o contador.  
  - **Botão B (GPIO6)**: Decrementa o contador.  
- O LED vermelho do LED RGB (GPIO13) pisca continuamente 5 vezes por segundo.

## Hardware Necessário:

- Placa BitDogLab
- Matriz 5x5 de LEDs (endereçáveis) WS2812, conectada à GPIO 7.
- LED RGB, com os pinos conectados às GPIOs (11, 12 e 13).
- Botão A conectado à GPIO 5.
- Botão B conectado à GPIO 6.


## Vídeo de demonstração: https://youtu.be/FE2Z7IdMPk0
