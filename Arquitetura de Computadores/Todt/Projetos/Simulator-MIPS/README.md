# Trabalho Final Arquitetura de Computadores - 2025/2

Tema: Simulador MIPS Pipeline

Descrição: O simulador tem como objetivo ler um conjunto de instruções e gerar o respectivo diagrama de execução, mostrando visualmente como funciona o processador MIPS Pipeline, igualmente é ensinado em sala pelo Professor Eduardo Todt.

Alunos: Marcus S. A. R. Neto, Henrique Vilella e Alexandre Sbrissia



## Estrutura do Projeto

src/
│
├── diagrama.py: Lê as instruções/metadados para gerar o diagrama.
├── parser.py: Lê um arquivo de entrada (.asm) e identificar as instruções.
└── hazard_detect.py: Responsável por detectar bolhas/stalls e dependências.