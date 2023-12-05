## Especificação Descritiva:
O módulo "d_flip_flop" é um flip-flop D síncrono que opera conforme as seguintes especificações de entradas e saída:
#### Entradas:
- "clk" (wire): Sinal de clock utilizado para sincronizar as operações do flip-flop.
- "reset" (wire): Sinal de reset que redefine o estado interno do flip-flop.
- "d" (wire): Entrada de dados que será armazenada no flip-flop.
#### Saída:
- "q" (reg): Saída de dados do flip-flop.

## Especificação Comportamental:
O comportamento do módulo "d_flip_flop" pode ser descrito da seguinte maneira:
Sempre que ocorrer uma transição de subida no sinal de clock "clk", os seguintes passos serão executados:
- Verifica se o sinal de reset "reset" está ativo.
  - Se estiver ativo, a saída "q" é definida como "0".
- Caso contrário, o fluxo de execução continua para o próximo passo.
  - Define a saída "q" como o valor presente na entrada "d".
- Caso contrário, mantém o valor atual da saída "q".

Dessa forma, o flip-flop D síncrono armazena o valor de entrada "d" na saída "q" em cada transição de subida do sinal de clock "clk". Contudo, se o sinal de reset estiver ativo, a saída "q" é redefinida para o valor lógico "0".

