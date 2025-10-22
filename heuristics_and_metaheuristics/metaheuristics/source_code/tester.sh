EXECUTAVEL="./main"
INPUT_DIR="examples"
TARGET_FILE="data/brkga.txt"

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
        $EXECUTAVEL "$FILE_NAME"
        echo "--------------------------------------"
    fi
done

echo "Processo concluído."
