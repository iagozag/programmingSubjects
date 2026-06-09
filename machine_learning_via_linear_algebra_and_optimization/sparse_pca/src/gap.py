import os
import re

def main():
    # Caminho para a pasta de dados (assumindo que rodará de dentro da pasta src/)
    data_dir = "../data"
    
    if not os.path.exists(data_dir):
        print(f"Erro: O diretório '{data_dir}' não foi encontrado.")
        return

    # Regex para capturar os números depois da palavra "Gap: " 
    # (Funciona para "Gap: 1.0000%" ou "Optimality Gap: 1.0000%")
    gap_pattern = re.compile(r"Gap:\s*([\d.]+)")

    results = []

    # Percorre recursivamente todas as pastas e arquivos dentro de ../data/
    for root, _, files in os.walk(data_dir):
        for file in files:
            if file.endswith(".data"):
                filepath = os.path.join(root, file)
                dataset_name = os.path.basename(root)
                
                gaps = []
                with open(filepath, 'r', encoding='utf-8') as f:
                    for line in f:
                        match = gap_pattern.search(line)
                        if match:
                            gaps.append(float(match.group(1)))
                
                # Se achou valores de gap no arquivo, calcula a média
                if gaps:
                    avg_gap = sum(gaps) / len(gaps)
                    results.append((dataset_name, file, avg_gap))
                else:
                    results.append((dataset_name, file, None))

    # Ordena os resultados pelo nome do Dataset e depois pelo nome do arquivo
    # Isso vai agrupar bonitinho o colon com colon, spambase com spambase, etc.
    results.sort(key=lambda x: (x[0], x[1]))

    # Imprime a tabela formatada no terminal
    print(f"\n{'Dataset':<15} | {'Arquivo (Instância)':<30} | {'Gap Médio (%)':<15}")
    print("-" * 65)
    
    for dataset, file, avg_gap in results:
        if avg_gap is not None:
            # Formata para 2 casas decimais para ficar perfeito para o LaTeX
            print(f"{dataset:<15} | {file:<30} | {avg_gap:.2f}")
        else:
            print(f"{dataset:<15} | {file:<30} | N/A")
            
    print("-" * 65)
    print("Pronto! Agora é só copiar os valores para a última coluna das tabelas no LaTeX.")

if __name__ == "__main__":
    main()