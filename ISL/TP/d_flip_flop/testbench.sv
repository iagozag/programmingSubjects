module tb_d_flip_flop;
   // Declaracao de variáveis
   reg clk, reset, d;
   wire q;

   // Instância do flip-flop tipo D
   d_flip_flop ff_d_inst (.clk(clk), .reset(reset), .d(d), .q(q));

   always #2 clk = ~clk;  // O sinal de clock muda a cada 2 unidades de tempo
   always #4 d = ~d;      // O sinal de dados (d) muda a cada 4 unidades de tempo

   initial begin
      // Inicialização das variáveis no início da simulação
      clk = 0;
      d = 0;
      reset = 0;
      
	  #16 reset = 1; // Após 16 unidades de tempo, o sinal de reset é ativado (1)
      #4 reset = 0;  // Após mais 4 unidades de tempo, o sinal de reset é desativado (0) novamente
      #20 $finish;   // Encerra a simulação após mais 20 unidades de tempo
   end

   // Sempre que há uma borda de subida no clock ou uma borda de subida no reset, exibe a saída do flip-flop naquele momento
   always @(posedge clk or posedge reset) begin
      $display("Tempo %t, d = %b, q = %b", $time, d, q);
   end

   // Escolhe arquivo para salvar o gráfico de ondas
   initial begin
      $dumpfile("waveform.vcd");
      $dumpvars();
   end

endmodule
