.data

##### R1 START MODIFIQUE AQUI START #####

#
# Este espaço é para você definir as suas constantes e vetores auxiliares.
#

vetor1: .word 1 2 3 4 # Primeiro vetor
vetor2: .word 1 1 1 1 # Segundo vetor

##### R1 END MODIFIQUE AQUI END #####
      
.text    

        add s0, zero, zero
        la a0, vetor1
        addi a1, zero, 4
        jal ra, media
        addi t0, zero, 2
        bne a0,t0,teste2
        addi s0,s0,1
teste2: la a0, vetor2
        addi a1, zero, 4
        jal ra, media
        addi t0, zero, 1
        bne a0,t0, FIM
        addi s0,s0,1
        beq zero,zero, FIM

##### R2 START MODIFIQUE AQUI START #####

# Esse espaço é para você escrever o código dos procedimentos. 
# Por enquanto eles estão vazios

exit: 	jalr zero, 0(ra)

loop_m: beq t0, a1, exit    # se i = tamanho_vetor, sai do loop
		slli t1, t0, 2
        addi t0, t0, 1      # i++
        add t2, t5, t1      
        lw t3, 0(t2)        # t3 = elemento_vetor
		add a0, a0, t3      # soma += elemento
        j loop_m            # continua loop

media: 	addi sp, sp, -8
		addi t0, zero, 0    # i = 0
        add t5, zero, a0    # t5 = endereco vetor
        addi a0, zero, 0    # resposta = 0
        sw ra, 0(sp)
        jal ra, loop_m      # chama loop
        lw ra, 0(sp)
        div a0, a0, a1      # resposta = soma / tamanho_vetor
        addi sp, sp, 8
		jalr zero, 0(ra)

loop_v: beq t0, a2, exit    # se i = tamanho_vetor, sai do loop
		slli t1, t0, 2
        addi t0, t0, 1      # i++
        add t2, a6, t1
        add t3, a7, t1
        lw t4, 0(t2)        # t4 = v1[i]
        lw t5, 0(t3)        # t5 = v2[i]
		sub t4, t4, a3      # t4 = t4 - media_v1
        sub t5, t5, a4      # t5 = t5 - media_v2
        mul t5, t5, t4      # t5 = t4*t5
        add a0, a0, t5      # resposta += t5  
        j loop_v

variancia:
		addi sp, sp, -8
		addi a6, a0, 0      # a6 = endereco vetor 1
        addi a7, a1, 0      # a7 = endereco vetor 2
        addi a1, a2, 0      # a1 = tamanho_vetores
        sw ra, 0(sp)
        jal ra, media       # calcula media v1
        addi a3, a0, 0      # a3 = media
        addi a0, a7, 0
        jal ra, media       # calcula media v2 
        addi a4, a0, 0      # a4 = media
        addi t0, zero, 0    # i = 0
        addi a0, zero, 0    # resposta = 0
        jal ra, loop_v      # chama loop
        lw ra, 0(sp)
        addi a2, a2, -1     # tamanho = tamanho - 1
        div a0, a0, a2      # a0 = soma / tamanho
        addi sp, sp, 8
		jalr zero, 0(ra)


##### R2 END MODIFIQUE AQUI END #####

FIM: add t0, zero, s0
