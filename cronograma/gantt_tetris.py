import pandas as pd
import matplotlib.pyplot as plt
from datetime import datetime

# Dados fornecidos
dados = [
    ("Codificação para renderizar peças na matriz de LED", "15/04/2025", "29/04/2025"),
    ("Codificação para a movimentação das peças", "22/04/2025", "06/05/2025"),
    ("Teste unitário das funções de\nrenderização e movimentação [Marco 1]", "15/04/2025", "06/05/2025"),
    ("Teste de integridade da fita de LED,\n botões e joystick", "06/05/2025", "13/05/2025"),
    ("Código do sistema de pontuação", "06/05/2025", "20/05/2025"),
    ("Teste de integração do software com o hardware", "13/05/2025", "20/05/2025"),
    ("Codificação do game over e pause", "20/05/2025", "03/06/2025"),
    ("Teste unitário das funções de pontuação,\ngame over e pause [Marco 2]", "06/05/2025", "03/06/2025"),
    ("Codificação do sistema de som", "03/06/2025", "10/06/2025"),
    ("Teste unitário do sistema de som", "03/06/2025", "10/06/2025"),
    ("Desenvolvimento do gabinete para a impressão 3D","03/06/2025", "17/06/2025"),
    ("Montagem dos componentes no gabinete", "17/06/2025", "24/06/2025"),
    ("Teste de jogabilidade [Marco 3]", "17/06/2025", "24/06/2025"),
    ("Ajuste finais", "24/06/2025", "01/07/2025"),
    ("Confecção do relatório", "24/06/2025", "08/07/2025"),
    ("Produção do vídeo", "01/07/2025", "05/07/2025")
]


# Criando DataFrame
df = pd.DataFrame(dados, columns=["Tarefa", "Início", "Fim"])
df["Início"] = pd.to_datetime(df["Início"], dayfirst=True)
df["Fim"] = pd.to_datetime(df["Fim"], dayfirst=True)
df["Duração"] = (df["Fim"] - df["Início"]).dt.days

# Regerando o gráfico com as linhas horizontais da grade desativadas
fig, ax = plt.subplots(figsize=(18, 12))

# Plotando as barras
ax.barh(df.index, df["Duração"], left=df["Início"].map(datetime.toordinal), height=0.5, color='firebrick')

# Customizando os eixos
ax.set_yticks(df.index)
ax.set_yticklabels(df["Tarefa"], fontsize=13.5)
ax.set_xlabel("")
ax.set_title("Cronograma Geral\n", fontsize=28, color='black')
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
print(df["Fim"].max())
ticks = pd.date_range(start=df["Início"].min(), end=df["Fim"].max(), freq="7D")
ax.set_xticks(ticks.map(datetime.toordinal))
ax.set_xticklabels(ticks.strftime("%d/%m"), rotation=45)
ax.tick_params(axis='x', labelsize=14)

# Apenas linhas verticais na grade
plt.grid(axis='x', linestyle='--', alpha=0.5)
ax.grid(visible=True, axis='y', linestyle='', linewidth=0)  # desativa grade horizontal


plt.tight_layout()
plt.grid(axis='x', linestyle='--', alpha=0.5)
plt.savefig("cronograma_geral.png", dpi=1000)

