EXECUTAVEL="./main"
INPUT_DIR="examples"

# Verifica se o programa existe
if [[ ! -f $EXECUTAVEL ]]; then
    echo "Erro: o executável '$EXECUTAVEL' não foi encontrado."
    exit 1
fi

# Verifica se a pasta de entrada existe
if [[ ! -d $INPUT_DIR ]]; then
    echo "Erro: a pasta '$INPUT_DIR' não foi encontrada."
    exit 1
fi

# Verifica se um argumento foi fornecido
if [[ $# -lt 1 ]]; then
    echo "Uso: $0 [opcao]"
    echo "Opções:"
    echo "  1 - Limpa o arquivo data/tatt.txt"
    echo "  2 - Limpa o arquivo data/christofides.txt"
    exit 1
fi

# Escolhe a ação com base no parâmetro
case $1 in
    1)
        TARGET_FILE="data/tatt.txt"
        ;;
    2)
        TARGET_FILE="data/christofides.txt"
        ;;
    *)
        echo "Erro: opção inválida '$1'"
        echo "Opções válidas: 1, 2"
        exit 1
        ;;
esac

# Verifica se o arquivo a ser limpo existe antes de limpar
if [[ ! -f "$TARGET_FILE" ]]; then
    echo "Erro: o arquivo '$TARGET_FILE' não foi encontrado na pasta '$INPUT_DIR'."
    exit 1
fi

# Limpa o arquivo
echo "Limpando o arquivo: $TARGET_FILE"
> "$TARGET_FILE"

# Itera sobre os arquivos na pasta de entrada
echo "Executando o programa para todos os arquivos em $INPUT_DIR com o parâmetro: $1"
for FILE in "$INPUT_DIR"/*; do
    if [[ -f $FILE && $(basename "$FILE") != "$TARGET_FILE" ]]; then
        # Extrai apenas o nome do arquivo
        FILE_NAME=$(basename "$FILE")
        
        echo "Executando o programa para o arquivo: $FILE_NAME"
        $EXECUTAVEL "$FILE_NAME" "$1"
        echo "--------------------------------------"
    fi
done

echo "Processo concluído."
