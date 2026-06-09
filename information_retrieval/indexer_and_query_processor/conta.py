import json

with open('index/doc_stats.json', 'r') as f:
    indice_docs = json.load(f)

total_tokens = sum(indice_docs["lengths"].values())

print(f"Total de tokens na coleção: {total_tokens}")
