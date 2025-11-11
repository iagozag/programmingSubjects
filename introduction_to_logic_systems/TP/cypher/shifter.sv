module shifter (
    input wire                    clk,       // Sinal de clock
    input wire                    reset,     // Sinal de reset
    input wire [7:0]              key,       // Chave de entrada de 8 bits
    output wire [`MSG_SIZE - 1:0] out        // Saída do deslocador
);

    reg [`MSG_SIZE - 1:0] shift_reg;  // Registrador de deslocamento

    always @(posedge clk or posedge reset)
        begin
            if (reset)
                shift_reg <= {`MSG_SIZE{key}};  // Inicializa o registrador com a chave ao ocorrer o reset
            else
                shift_reg <= {shift_reg[`MSG_SIZE - 9 : 8], shift_reg[`MSG_SIZE - 1 : 8]};  // Desloca o registrador em 1 byte
        end

    // Atribui a saída out ao registrador de deslocamento
    assign out = shift_reg;

endmodule
