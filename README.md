# Trabalho de Sistemas Operacionais

##Pré-requisitos:
Compilador C

## Como compilar o programa:
  gcc -pthread main.c -o {output_name}

EX:
`gcc -pthread main.c -o main`

## Como executar o programa:
Existem 2 formas de executar o programa:
`./{output_name}`
Executara o programa utilizando valores padrões para suas variáveis

`./{output_name} {tempo_cpu} {tempo_disco} {instrução_disco} {lista_instruções}`
Permite que o usuário inicialize opções da simulação

EX: 
`./main 1 10 3 2 23 14 5 12 3 5 7 8`

OBS: {tempo_cpu} {tempo_disco} em segundos
