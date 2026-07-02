from parser import MipsParser, INSTRUCTION_MAP
from diagram import generate_diagram
from hazard_detect import PipelineSimulator

filepath = "../Arquivos_Testes/input.asm"
filepath4 = "../Arquivos_Testes/input2.asm"
filepath5 = "../Arquivos_Testes/input3.asm"
filepath6 = "../Arquivos_Testes/input4.asm"

#==========================================================================

def main():
    """
    Função principal que coordena a análise das instruções
    e a geração do diagrama.
    """

    # Inicializa o parser com o mapa de instruções
    parser = MipsParser(INSTRUCTION_MAP)
    
    # Faz o parsing do arquivo para obter a lista de instruções
    print(f"Analisando conjunto de instruções...")

    # Mudei para o arquivo teste com desvios sinalizados   
    instruction_list = parser.parse(filepath6)
    
    if instruction_list:
        print(f"{len(instruction_list)} instruções analisadas com sucesso.")

        # Roda o simulador
        print("Iniciando simulação do pipeline com detecção de hazards...")
        simulator = PipelineSimulator(instruction_list)
        final_history, total_cycles = simulator.run()
        print("Simulação concluída.")
        
        # Passa o resultado para o diagrama
        print("Gerando o diagrama de execução...")
        generate_diagram(instruction_list, final_history, total_cycles)

    else:
        print("Nenhuma instrução foi analisada. O diagrama não será gerado.")

if __name__ == "__main__":
    main()
