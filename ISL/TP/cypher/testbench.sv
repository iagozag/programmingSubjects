module cypher_tb;
   reg clk;
   reg reset;
   reg [7:0] key;
   reg [`MSG_SIZE - 1 : 0] message;
   wire [`MSG_SIZE - 1 : 0] ciphertext;
   wire [`MSG_SIZE - 1 : 0] decrypted_text;
   wire [`MSG_SIZE - 1 : 0] otp_out;

   // Instanciação do shifter e cypher
   shifter sh (.clk(clk), .reset(reset), .key(key), .out(otp_out));
   cypher ci (.clk(clk), .otp(otp_out), .message(message), .ciphertext(ciphertext));

   always
     begin
        #10 clk = !clk; // Inverte o sinal de clock a cada 10 unidades de tempo
     end 

   // Bloco inicial
   initial
     begin
        clk = 0;
        reset = 1;
        key = 8'b10101010;
        message = `MSG;

        #2 reset = 0;

        // Finaliza a simulação após 10 unidades de tempo
        #10 $finish;
     end

   // Bloco ativado na borda de subida do clock
   always @(posedge clk)
     begin
       $display("message    : %b", message);
       $display("key        : %b", key);
       $display("ciphertext : %b", ciphertext);
       $display("decrypted  : %b", ciphertext ^ otp_out);
     end

endmodule

