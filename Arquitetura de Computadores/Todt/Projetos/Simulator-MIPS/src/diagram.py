import tkinter as tk
from tkinter import ttk
from parser import MipsInstruction
from typing import List, Dict


#=====================================================================================================


def create_diagram_legend(parent_frame: ttk.Frame, color_map: Dict[str, str], style: ttk.Style):
    """
    Cria e popula uma legenda de cores e estilos dentro de um frame fornecido.
    """

    # Adiciona um título para a legenda
    title_label = ttk.Label(parent_frame, text="Legenda:", font=("Arial", 10, "bold"))
    title_label.pack(pady=(5, 5), anchor="w")

    # Frame para conter os itens da legenda em uma grade ou linha
    items_frame = ttk.Frame(parent_frame)
    items_frame.pack(fill="x")

    # Mapeamento dos nomes dos estágios para descrições mais amigáveis
    legend_descriptions = {
        "IF": " IF - Busca de Instrução",
        "ID": "ID - Decodificação de Instrução",
        "EX": "EXE - Execução",
        "FW": "EXE_FW - Execução (com Forwarding)",
        "MEM": "MEM - Acesso à Memória",
        "WB": "WB - Escrita de Volta (Write Back)",
        "Stall": "Stall - Bolha",
    }
    
    # Ordem em que os itens aparecerão na legenda
    legend_order = ["IF", "ID", "EX", "FW", "MEM", "WB", "Stall"]
    
    col = 0
    for state in legend_order:
        description = legend_descriptions.get(state)
        if not description: continue
        
        # Frame para agrupar o quadrado de cor e o texto
        item_frame = ttk.Frame(items_frame)
        item_frame.grid(row=0, column=col, padx=10, pady=2, sticky="w")
        col += 1

        # Cria o quadrado de cor usando um Label
        # Determina o estilo correto (caso especial para Forwarding)
        style_key = "EX_FWD" if state == "FW" else state
        color_box = ttk.Label(item_frame, text="", style=f"{style_key}.TLabel", width=2)
        color_box.pack(side="left")

        # Cria o texto descritivo
        text_label = ttk.Label(item_frame, text=description)
        text_label.pack(side="left", padx=5)


#=====================================================================================================


def generate_diagram(instruction_list: List[MipsInstruction], history: List[Dict[int, Dict]], total_cycles: int):
    instrucoes = [instr.original_line.strip() for instr in instruction_list]
    
    if not instrucoes:
        print("Nenhuma instrução fornecida para gerar o diagrama.")
        return

    janela = tk.Tk()
    janela.title("Diagrama de Execução MIPS (Com Hazards e Forwarding)")
    janela.geometry("1000x500")

    container = ttk.Frame(janela)
    container.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)

    canvas = tk.Canvas(container, bg="white")
    v_scrollbar = ttk.Scrollbar(container, orient="vertical", command=canvas.yview)
    h_scrollbar = ttk.Scrollbar(container, orient="horizontal", command=canvas.xview)
    diagrama_frame = ttk.Frame(canvas, style="Diagram.TFrame")
    canvas.configure(yscrollcommand=v_scrollbar.set, xscrollcommand=h_scrollbar.set)
    canvas.grid(row=0, column=0, sticky="nsew")
    v_scrollbar.grid(row=0, column=1, sticky="ns")
    h_scrollbar.grid(row=1, column=0, sticky="ew")
    container.grid_rowconfigure(0, weight=1)
    container.grid_columnconfigure(0, weight=1)
    canvas.create_window((0, 0), window=diagrama_frame, anchor="nw")
    def configurar_scrollregion(event):
        canvas.configure(scrollregion=canvas.bbox("all"))
    diagrama_frame.bind("<Configure>", configurar_scrollregion)

    style = ttk.Style(janela)
    style.configure("Diagram.TFrame", background="white")
    style.configure("Header.TLabel", background="white", font=("Arial", 10, "bold"))
    style.configure("Inst.TLabel", background="white", font=("Arial", 10, "bold"))
    
    color_map = {
        "IF": "#87CEEB", "ID": "#90EE90", "EX": "#FFD700", "FW": "#FF2600",
        "MEM": "#FFA07A", "WB": "#DDA0DD", "Stall": "#FFB6C1",
    }
    
    # Estilo base para cada célula
    for state, color in color_map.items():
        style.configure(f"{state}.TLabel", background=color, foreground="black", anchor="center", 
                        relief="solid", borderwidth=1)
    
    # Estilo para célula com forwarding 
    style.configure("EX_FWD.TLabel", background=color_map["FW"], foreground="black", anchor="center",
                    relief="solid", borderwidth=1)

    style.configure("Empty.TLabel", background="white", relief="solid", borderwidth=1)

    # Cabeçalho dos Ciclos
    ttk.Label(diagrama_frame, text="", style="Header.TLabel").grid(row=0, column=0, padx=5, pady=5)
    for cycle in range(1, total_cycles + 1):
        ttk.Label(diagrama_frame, text=f"Ciclo {cycle}", style="Header.TLabel").grid(row=0, column=cycle, padx=10, pady=5, sticky="ew")

    # Corpo do Diagrama
    for i, instrucao in enumerate(instrucoes):
        ttk.Label(diagrama_frame, text=instrucao, style="Inst.TLabel").grid(row=i + 1, column=0, padx=5, pady=5, sticky="w")
        
        for cycle in range(1, total_cycles + 1):
            state_info = history[i].get(cycle)
            
            if state_info:
                stage = state_info.get('stage')
                style_key = stage
                
                # LÓGICA DE VISUALIZAÇÃO DO FORWARDING
                if stage == 'EX' and 'forward_info' in state_info:
                    style_key = "EX_FWD"
                    
                display_text = stage
                if stage.startswith("Stall"): 
                    display_text = "Stall"
                    style_key = "Stall"
                
                label = ttk.Label(diagrama_frame, text=display_text, style=f"{style_key}.TLabel", width=10)
                label.grid(row=i + 1, column=cycle, padx=2, pady=2, ipady=5)
            else:
                # Célula vazia
                ttk.Label(diagrama_frame, text="", style="Empty.TLabel", width=10).grid(row=i + 1, column=cycle, padx=2, pady=2, ipady=5)

    # Adiciona um separador visual entre o diagrama e a legenda 
    separator = ttk.Separator(janela, orient='horizontal')
    separator.pack(fill='x', padx=10, pady=5)

    # Cria um frame para a legenda na parte inferior da janela 
    legend_frame = ttk.Frame(janela)
    legend_frame.pack(fill='x', padx=10, pady=5)
    
    # Chama a função para criar e preencher a legenda 
    create_diagram_legend(legend_frame, color_map, style)
            
    janela.mainloop()


#=====================================================================================================