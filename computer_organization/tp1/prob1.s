.data

##### R1 START MODIFIQUE AQUI START #####
#
# Este espaço é para você definir as suas constantes e vetores auxiliares.
#

vetor: .word 1 2 3 4 5 6 7 8 9 10

##### R1 END MODIFIQUE AQUI END #####

.text
        add s0, zero, zero # Quantidade de testes em que seu programa passou
        la a0, vetor
        addi a1, zero, 10
        addi a2, zero, 2
        jal ra, multiplos
        addi t0, zero, 5
        bne a0,t0,teste2
        addi s0,s0,1
teste2: la a0, vetor
        addi a1, zero, 10
        addi a2, zero, 3
        jal ra, multiplos
        addi t0, zero, 3
        bne a0,t0, FIM
        addi s0,s0,1
        beq zero,zero,FIM

##### R2 START MODIFIQUE AQUI START #####

exit: 	jalr zero, 0(ra)

loop: 	beq t0, a1, exit    # se i = tamanho vetor, termina loop 
		slli t1, t0, 2
        addi t0, t0, 1      # i++
        add t2, a7, t1
        lw t3, 0(t2)        # t3 = elemento na posicao i
		rem t4, t3, a2      # t4 = t3 % a2
        bne t4, zero, loop  # se resto diferente de 0 continua loop
        addi a0, a0, 1      # se eh igual, incrementa resposta em 1
        j loop 
        
multiplos:
		addi sp, sp, -8
		addi t0, zero, 0    # i = 0
        add a7, zero, a0    # a7 = endereco do vetor
        addi a0, zero, 0    # resposta = 0
        sw ra, 0(sp)
        jal ra, loop        # chama loop
        lw ra, 0(sp)
        addi sp, sp, 8
		jalr zero, 0(ra)

##### R2 END MODIFIQUE AQUI END #####

FIM: addi t0, s0, 0
