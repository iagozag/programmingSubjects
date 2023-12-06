module cypher (
    input wire                      clk,              // Sinal de clock
    input wire [`MSG_SIZE - 1 : 0]  otp,              // Chave única (One-Time Pad)
    input wire [`MSG_SIZE - 1 : 0]  message,          // Mensagem de entrada
    output wire [`MSG_SIZE - 1 : 0] ciphertext        // Mensagem cifrada
);

    // Atribui a saída ciphertext através do operador XOR
    assign ciphertext = message ^ otp;

endmodule
