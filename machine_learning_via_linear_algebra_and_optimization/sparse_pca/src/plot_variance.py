import os
import re
import matplotlib.pyplot as plt

def plot_variance_curves(filepath, ratios, filename):
    # Converte os ratios (0.71) para porcentagens (71.0)
    acc_var = [r * 100 for r in ratios]
    
    # Calcula a variância marginal (o atual menos o anterior)
    marg_var = [acc_var[0]] + [acc_var[i] - acc_var[i-1] for i in range(1, len(acc_var))]
    
    components = list(range(1, len(acc_var) + 1))

    fig, ax1 = plt.subplots(figsize=(8, 5))

    # Gráfico de Barras: Contribuição Marginal
    ax1.bar(components, marg_var, color='skyblue', edgecolor='black', alpha=0.7, label='Marginal (%)')
    ax1.set_xlabel('Índice do Componente')
    ax1.set_ylabel('Variância Marginal (%)', color='tab:blue', fontweight='bold')
    ax1.tick_params(axis='y', labelcolor='tab:blue')
    ax1.set_xticks(components)

    # Cria um segundo eixo Y que compartilha o mesmo eixo X
    ax2 = ax1.twinx()  
    
    # Gráfico de Linha: Variância Acumulada
    ax2.plot(components, acc_var, color='red', marker='o', linestyle='-', linewidth=2, label='Acumulada (%)')
    ax2.set_ylabel('Variância Acumulada (%)', color='red', fontweight='bold')
    ax2.tick_params(axis='y', labelcolor='red')

    # Ajusta os limites para o gráfico não cortar os dados
    ax1.set_ylim(0, max(marg_var) * 1.3 if marg_var else 100)
    ax2.set_ylim(0, max(100, max(acc_var) + 10))

    # Linha tracejada indicando o critério de parada dos 70%
    ax2.axhline(70, color='gray', linestyle='--', alpha=0.6, label='Meta de 70%')

    # Título com o nome do arquivo limpo (ex: spambase_5)
    clean_title = filename.replace('.data', '')
    plt.title(f'Curva de Variância Explicada - {clean_title}')
    
    # Salva a imagem na mesma pasta do .data
    save_path = filepath.replace('.data', '_variance_curve.png')
    plt.savefig(save_path, bbox_inches='tight', dpi=300)
    plt.close()
    
    return save_path

def main():
    print(">> Iniciando a extração das curvas de variância...")
    data_dir = "../data"
    
    if not os.path.exists(data_dir):
        print(f"Erro: O diretório '{data_dir}' não foi encontrado.")
        return

    # Regex para capturar o ratio bruto (ex: accumulated variance ratio: 0.1523)
    ratio_pattern = re.compile(r"accumulated variance ratio:\s*([\d.]+)", re.IGNORECASE)

    arquivos_processados = 0

    for root, _, files in os.walk(data_dir):
        for file in files:
            if file.endswith(".data"):
                filepath = os.path.join(root, file)
                
                ratios = []
                with open(filepath, 'r', encoding='utf-8') as f:
                    for line in f:
                        match = ratio_pattern.search(line)
                        if match:
                            ratios.append(float(match.group(1)))
                
                # Se encontrou históricos de variância, gera o gráfico
                if ratios:
                    save_path = plot_variance_curves(filepath, ratios, file)
                    print(f"[OK] Gráfico gerado: {save_path}")
                    arquivos_processados += 1

    print("-" * 50)
    print(f"Total de curvas geradas: {arquivos_processados}")

if __name__ == "__main__":
    main()