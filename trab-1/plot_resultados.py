import pandas as pd
import matplotlib.pyplot as plt

# Lê o arquivo CSV
df = pd.read_csv("resultadosV3.csv")

# Garante que os casos estão no formato correto no eixo X
df["Caso"] = df["Caso"].astype(int)

# Cria o gráfico
plt.figure(figsize=(10, 5))
plt.plot(df["Caso"], df["Operacoes"], marker='o', linestyle='-', color='blue')

# Títulos e rótulos
plt.title("Número de Operações por Caso / Terceira Versão")
plt.xlabel("Caso")
plt.ylabel("Operações")
plt.xticks(df["Caso"])  # Força o matplotlib a usar exatamente os valores dos casos no eixo X

plt.grid(True)
plt.tight_layout()
plt.show()
