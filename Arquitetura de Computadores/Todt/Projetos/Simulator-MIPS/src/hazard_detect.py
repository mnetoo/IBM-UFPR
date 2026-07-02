from parser import MipsInstruction
from typing import List, Dict, Optional, Tuple

class PipelineSimulator:

    # Declarações iniciais, seta registradores em 0 
    def __init__(self, instructions: List[MipsInstruction]):
        self.instructions = instructions
        self.pc = 0
        self.cycle = 0
        # [IF, ID, EX, MEM, WB]
        self.pipeline_stages: List[Optional[int]] = [None] * 5 
        self.history: List[Dict[int, Dict]] = [{} for _ in self.instructions]

        # Precisamos dos registradores para o loop funcionar ($t0 diminuir)
        self.registers = {f"${i}": 0 for i in range(32)}
        self.registers['$zero'] = 0

    # Retorna a lista de instruções que leem dados dos registradores
    def _get_read_registers(self, instruction: Optional[MipsInstruction]) -> List[str]:
        if not instruction: return []
        read_regs = []
        if instruction.rs: read_regs.append(instruction.rs)
        if instruction.type in ['R', 'I_BRANCH'] or (instruction.type == 'I_MEM' and instruction.mnemonic == 'sw'):
            if instruction.rt: read_regs.append(instruction.rt)
        return read_regs

    # Retorna a lista de instruções que escrevem dados nos registradores
    def _get_written_register(self, instruction: Optional[MipsInstruction]) -> Optional[str]:
        if not instruction: return None
        if instruction.type == 'R': return instruction.rd
        if instruction.type in ['I_ARITH', 'I_MEM'] and instruction.mnemonic != 'sw':
            return instruction.rt
        return None

    # Checa se a próxima instrução é um hazard de dados, e caso seja possível faz o foward
    def _check_hazards(self) -> Tuple[bool, Optional[Dict]]:
        """Verifica Hazards de DADOS (Stall e Forwarding)"""
        idx_id = self.pipeline_stages[1]
        if idx_id is None: return False, None

        inst_id = self.instructions[idx_id]
        read_regs = self._get_read_registers(inst_id)
        
        # Checa EX
        idx_ex = self.pipeline_stages[2]
        if idx_ex is not None:
            inst_ex = self.instructions[idx_ex]
            dest_ex = self._get_written_register(inst_ex)
            if dest_ex and dest_ex in read_regs:
                if inst_ex.mnemonic == 'lw': return True, None # Stall Load-Use
                return False, {'source_stage': 'EX', 'reg': dest_ex} # Forwarding

        # Checa MEM
        idx_mem = self.pipeline_stages[3]
        if idx_mem is not None:
            inst_mem = self.instructions[idx_mem]
            dest_mem = self._get_written_register(inst_mem)
            if dest_mem and dest_mem in read_regs:
                return False, {'source_stage': 'MEM', 'reg': dest_mem} # Forwarding
        
        return False, None

    def run(self):
        print(f"Iniciando simulação Simplificada (Always Not Taken)...")
        
        while True:
            # Condição de parada
            if self.pc >= len(self.instructions) and all(s is None for s in self.pipeline_stages):
                break
                
            self.cycle += 1
            flush_pipeline = False

            # Faz o IF
            if self.pipeline_stages[0] is None and self.pc < len(self.instructions):
                self.pipeline_stages[0] = self.pc
                self.pc += 1

            # Faz o WB 
            # checa se a instrução tem resultado, caso tenha escreve
            idx_wb = self.pipeline_stages[4]
            if idx_wb is not None:
                inst = self.instructions[idx_wb]
                if hasattr(inst, 'result'): 
                    dest = self._get_written_register(inst)
                    if dest and dest != '$zero':
                        self.registers[dest] = inst.result

            # Faz o EX, simulando uma ULA
            idx_ex = self.pipeline_stages[2]
            if idx_ex is not None:
                inst = self.instructions[idx_ex]
                
                # FUNÇÃO DE FORWARDING 
                # Essa função procura o valor mais recente do registrador
                def get_forwarded_value(reg_name):
                    if not reg_name or reg_name == '$zero': return 0
                    
                    # Checa MEM 
                    if self.pipeline_stages[3] is not None:
                        inst_mem = self.instructions[self.pipeline_stages[3]]
                        if hasattr(inst_mem, 'result'): # Se ela calculou algo
                            dest = self._get_written_register(inst_mem)
                            if dest == reg_name:
                                return inst_mem.result # Pegamos o dado 

                    # Checa WB
                    if self.pipeline_stages[4] is not None:
                        inst_wb = self.instructions[self.pipeline_stages[4]]
                        if hasattr(inst_wb, 'result'):
                            dest = self._get_written_register(inst_wb)
                            if dest == reg_name:
                                return inst_wb.result

                    # Se ninguém tem, pega do banco normal
                    return self.registers.get(reg_name, 0)

                # --- AGORA USAMOS A FUNÇÃO PARA LER OS VALORES ---
                val_rs = get_forwarded_value(inst.rs)
                val_rt = get_forwarded_value(inst.rt)
                imm = inst.imm if inst.imm is not None else 0

                # Lógica para o loop funcionar
                inst.result = 0 # aloca campo temporário para o resultado da ULA
                if inst.mnemonic == 'add': inst.result = val_rs + val_rt
                elif inst.mnemonic == 'sub': inst.result = val_rs - val_rt
                elif inst.mnemonic == 'addi': inst.result = val_rs + imm
                
                # --- LÓGICA JUMP E BRANCH ---
                
                if inst.mnemonic == 'j':
                    print(f"[Ciclo {self.cycle}] JUMP detectado para linha {imm}. FLUSH!")
                    self.pc = imm    # endereço absoluto 
                    flush_pipeline = True 
                
                elif inst.mnemonic == 'beq':
                    if val_rs == val_rt:
                        print(f"[Ciclo {self.cycle}] BRANCH TAKEN (Previsão errou). FLUSH!")
                        self.pc = idx_ex + 1 + imm  #endereço relativo
                        flush_pipeline = True 

                elif inst.mnemonic == 'blt':
                    if val_rs  < val_rt:
                        print(f"[Ciclo {self.cycle}] BRANCH TAKEN (Previsão errou). FLUSH!")
                        self.pc = idx_ex + 1 + imm #endereço relativo
                        flush_pipeline = True 


            # MOVIMENTAÇÃO DO PIPELINE
            
            # Checa Stall
            needs_stall, forward_info = self._check_hazards()

            # Registra Histórico, para visualização e atualiza o estágio 
            if self.pipeline_stages[4] is not None: self.history[self.pipeline_stages[4]][self.cycle] = {'stage': 'WB'}
            self.pipeline_stages[4] = self.pipeline_stages[3] # MEM <- EX
            if self.pipeline_stages[4] is not None: self.history[self.pipeline_stages[4]][self.cycle] = {'stage': 'MEM'}
            
            self.pipeline_stages[3] = self.pipeline_stages[2] # EX <- ID
            if self.pipeline_stages[3] is not None:
                info = {'stage': 'EX'}
                if forward_info: info['forward_info'] = forward_info
                self.history[self.pipeline_stages[3]][self.cycle] = info

            # Lida com FLUSH ou STALL ou NORMAL
            if flush_pipeline:
                # da flush 
                if self.pipeline_stages[1] is not None:
                    self.history[self.pipeline_stages[1]][self.cycle] = {'stage': 'FLUSH'}
                if self.pipeline_stages[0] is not None:
                    self.history[self.pipeline_stages[0]][self.cycle] = {'stage': 'FLUSH'}
                
                self.pipeline_stages[2] = None # EX recebe bolha
                self.pipeline_stages[1] = None 
                self.pipeline_stages[0] = None 
            
            elif needs_stall:
                # Trava ID e IF
                if self.pipeline_stages[1] is not None:
                    self.history[self.pipeline_stages[1]][self.cycle] = {'stage': 'Stall'}
                self.pipeline_stages[2] = None # EX recebe bolha
            
            else:
                # Avança Normal
                self.pipeline_stages[2] = self.pipeline_stages[1] # EX <- ID
                if self.pipeline_stages[2] is not None:
                    self.history[self.pipeline_stages[2]][self.cycle] = {'stage': 'ID'}
                
                self.pipeline_stages[1] = self.pipeline_stages[0] # ID <- IF
                if self.pipeline_stages[1] is not None:
                    self.history[self.pipeline_stages[1]][self.cycle] = {'stage': 'IF'}
                
                self.pipeline_stages[0] = None

        return self.history, self.cycle