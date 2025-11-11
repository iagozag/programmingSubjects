module d_flip_flop (
    input wire clk,      // Sinal de clock de entrada
    input wire reset,    // Sinal de reset de entrada
    input wire d,        // Sinal de dado de entrada
    output reg q         // Saída Q (registrador de saída)
);

  // Sempre que houver uma borda de subida no sinal de clock ou uma borda de subida no sinal de reset
  always @(posedge clk or posedge reset) begin
      if (reset)            // Se o sinal de reset estiver ativo
            q <= 1'b0;      // Zera a saída Q
        else                // Caso contrário
            q <= d;         // Atribui o valor de D à saída Q no próximo ciclo de clock
    end

endmodule