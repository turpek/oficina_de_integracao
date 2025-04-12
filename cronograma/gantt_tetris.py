import pandas as pd
import matplotlib.pyplot as plt
from datetime import datetime

# Dados fornecidos
dados = [
    ("Codificação para renderizar peças\nna matriz de led", "15/04/2025", "22/04/2025"),
    ("Teste de unidade das funções de\nrenderização", "15/04/2025", "22/04/2025"),
    ("Codificação para a movimentação\ndas peças  [Marco 1]", "22/04/2025", "06/05/2025"),
    ("Teste de unidade das funções de\n movimentação e pontuação", "22/04/2025", "06/05/2025"),
    ("Codigo do sistema de pontuação", "29/04/2025", "06/05/2025"),
    ("Teste na prática usando o arduino,\n matriz de led e os controles", "29/04/2025", "06/05/2025"),
    ("Desenvolvimento das funções de\n game over e pause", "06/05/2025", "13/05/2025"),
    ("Teste unitário das funções de\n game over/pause", "06/05/2025", "13/05/2025"),
    ("Códificação do sistema de soms", "13/05/2025", "20/05/2025"),
    ("Teste unitário do sistema de som", "13/05/2025", "20/05/2025"),
    ("Montagem dos componentes\nna estrutura", "20/05/2025", "27/05/2025"),
    ("Teste na prática de todas\nas funcionalidades", "20/05/2025", "27/05/2025"),
    ("Ajuste finais [Marco 2]", "27/05/2025", "03/06/2025"),
    ("Ajuste finais", "03/06/2025", "17/06/2025"),
    ("Produção do vídeo", "17/06/2025", "20/06/2025"),
    ("Confecção do relatório [Marco 3]", "17/06/2025", "24/06/2025"),
]


# Criando DataFrame
df = pd.DataFrame(dados, columns=["Tarefa", "Início", "Fim"])
df["Início"] = pd.to_datetime(df["Início"], dayfirst=True)
df["Fim"] = pd.to_datetime(df["Fim"], dayfirst=True)
df["Duração"] = (df["Fim"] - df["Início"]).dt.days

# Regerando o gráfico com as linhas horizontais da grade desativadas
fig, ax = plt.subplots(figsize=(12, 8))

# Plotando as barras
ax.barh(df.index, df["Duração"], left=df["Início"].map(datetime.toordinal), color='firebrick')

# Customizando os eixos
ax.set_yticks(df.index)
ax.set_yticklabels(df["Tarefa"], fontsize=12)
ax.set_xlabel("")
ax.set_title("Cronograma Geral", fontsize=18, color='black')
ax.invert_yaxis()  # tarefas do topo primeiro

# Eixo X no topo
ax.xaxis.set_label_position('top')
ax.xaxis.tick_top()

# Linha vertical para marcar os marcos
marcos = [(2025, 5, 6), (2025, 6, 3), (2025, 6, 24)]
marcos_label = ['Marco 1', 'Marco 2', 'Marco 3']
for date, label in zip(marcos, marcos_label):
    data_linha = datetime(*date).toordinal()
    ax.axvline(x=data_linha, color='black', linestyle='-', linewidth=2, label=label)

# Formatando datas no eixo X
ticks = pd.date_range(start=df["Início"].min(), end=df["Fim"].max(), freq="7D")
ax.set_xticks(ticks.map(datetime.toordinal))
ax.set_xticklabels(ticks.strftime("%d/%m"), rotation=45)
ax.tick_params(axis='x', labelsize=12)

# Apenas linhas verticais na grade
plt.grid(axis='x', linestyle='--', alpha=0.5)
ax.grid(visible=True, axis='y', linestyle='', linewidth=0)  # desativa grade horizontal

plt.tight_layout()
plt.grid(axis='x', linestyle='--', alpha=0.5)
plt.savefig("cronograma_geral.png", dpi=100)

