import re
from dataclasses import dataclass
from typing import Optional


#=====================================================================================================


# Estrutura de dados
@dataclass
class MipsInstruction:
    "Armazena uma instrução do MIPS decodificada"
    original_line: str 
    mnemonic: str
    type: str
    
    rs: Optional[str] = None
    rt: Optional[str] = None
    rd: Optional[str] = None
    imm: Optional[int] = None 

    def __str__(self):
        line = self.original_line.strip()
        return (
            f"MipsInstruction(line='{line}', op='{self.mnemonic}', type='{self.type}', "
            f"rd={self.rd}, rs={self.rs}, rt={self.rt}, imm={self.imm})"
        )

INSTRUCTION_MAP = {
    # Tipo R: mnemonic rd, rs, rt
    'add': {'type': 'R'},
    'sub': {'type': 'R'},
    'and': {'type': 'R'},
    'or':  {'type': 'R'},
    
    # Tipo I (Memória): mnemonic rt, imm(rs) 
    'lw': {'type': 'I_MEM'},
    'sw': {'type': 'I_MEM'},
    
    # Tipo I (Aritmética): mnemonic rt, rs, imm
    'addi': {'type': 'I_ARITH'},
    
    # Tipo I (Branch): mnemonic rs, rt, label
    'beq': {'type': 'I_BRANCH'},
    'blt': {'type': 'I_BRANCH'},
    
    # Tipo J: mnemonic label
    'j': {'type': 'J'}
}


#=====================================================================================================


# Classe Parser
class MipsParser:
    def __init__(self, instruction_map):
        self.instruction_map = instruction_map

    def parse(self, filepath: str) -> list[MipsInstruction]:
        instruction_memory: list[MipsInstruction] = []
    
        try:
            with open(filepath, 'r') as f:
                for line_number, line in enumerate(f, 1):
                    original_line = line
                    line = line.split('#')[0].strip()
                    if not line: continue
                    try:
                        instruction_obj = self._parse_line(line, original_line)
                        instruction_memory.append(instruction_obj)
                    except Exception as e:
                        print(f"[Erro de Parsing na Linha {line_number}]: {e}")
                        
            return instruction_memory
            
        except FileNotFoundError:
            print(f"[Erro]: Arquivo não encontrado em '{filepath}'")
            return []
        
    def _parse_line(self, line: str, original_line: str) -> MipsInstruction:
        tokens = list(filter(None, re.split(r'[ \t,()]+', line)))

        if not tokens:
            raise ValueError("Linha não contém tokens")
        
        # Pega o mnemônico e o tipo
        mnemonic = tokens[0].lower()
        info = self.instruction_map.get(mnemonic)

        if not info:
            raise ValueError(f"Instrução desconhecida: '{mnemonic}'")
        
        inst_type = info['type']

        parsed_data = {
            'original_line': original_line,
            'mnemonic': mnemonic,
            'type': inst_type
        }

        try:
            if inst_type == 'R':
                # tokens: ['add', '$rd', '$rs', '$rt']
                parsed_data['rd'] = tokens[1]
                parsed_data['rs'] = tokens[2]
                parsed_data['rt'] = tokens[3]
                
            elif inst_type == 'I_MEM':
                # tokens: ['lw', '$rt', 'imm', '$rs']
                parsed_data['rt'] = tokens[1]
                parsed_data['imm'] = int(tokens[2])
                parsed_data['rs'] = tokens[3]

            elif inst_type == 'I_ARITH':
                # tokens: ['addi', '$rt', '$rs', 'imm']
                parsed_data['rt'] = tokens[1]
                parsed_data['rs'] = tokens[2]
                parsed_data['imm'] = int(tokens[3])

            elif inst_type == 'I_BRANCH':
                # tokens: ['beq', '$rs', '$rt', 'label']
                parsed_data['rs'] = tokens[1]
                parsed_data['rt'] = tokens[2]
                parsed_data['imm'] = int(tokens[3]) # label é um endereço numérico

            elif inst_type == 'J':
                # tokens: ['j', 'label']
                parsed_data['imm'] = int(tokens[1]) 

            else:
                raise ValueError(f"Tipo de instrução não suportado: {inst_type}")

        except (IndexError, ValueError) as e:
            raise ValueError(
                f"Número/formato de argumentos inválido para '{mnemonic}'. "
                f"Esperado formato para {inst_type}. Tokens: {tokens}"
            )

        # Retorna o objeto final
        return MipsInstruction(**parsed_data)
    

#=====================================================================================================