import sys

# Mapas de opcode, funct3 e funct7 para as instruções
opcodes = {
    'lb':  '0000011',
    'sb':  '0100011',
    'add': '0110011',
    'sub': '0110011',
    'and': '0110011',
    'sll': '0110011',
    'xor': '0110011',
    'srl': '0110011',
    'ori': '0010011',
    'bne': '1100011',
}

funct3 = {
    'lb':  '000',
    'sb':  '000',
    'add': '000',
    'sub': '000',
    'and': '111',
    'sll': '001',
    'xor': '100',
    'srl': '101',
    'ori': '110',
    'bne': '001',
}

funct7 = {
    'add': '0000000',
    'sub': '0100000',
    'and': '0000000',
    'sll': '0000000',
    'xor': '0000000',
    'srl': '0000000',
}

# Converte registrador xN para binário de 5 bits
def reg_bin(reg):
    try:
        return format(int(reg[1:]), '05b')
    except:
        raise ValueError(f'Registrador inválido: {reg}')

# Converte imediato para binário com sinal, com 'bits' largura
def imm_bin(val, bits):
    val = int(val)
    if val < 0:
        val = (1 << bits) + val
    return format(val, f'0{bits}b')[-bits:]

# Montagem tipo R (ex: add, sub, xor, srl, and, sll)
def montar_tipo_R(instr, rd, rs1, rs2):
    if instr not in funct7:
        raise ValueError(f'funct7 não definido para a instrução: {instr}')
    return (
        funct7[instr] +
        reg_bin(rs2) +
        reg_bin(rs1) +
        funct3[instr] +
        reg_bin(rd) +
        opcodes[instr]
    )

# Montagem tipo I (ex: ori, lb)
def montar_tipo_I(instr, rd, rs1, imm):
    return (
        imm_bin(imm, 12) +
        reg_bin(rs1) +
        funct3[instr] +
        reg_bin(rd) +
        opcodes[instr]
    )

# Montagem tipo S (ex: sb)
def montar_tipo_S(instr, rs2, offset, base):
    imm = imm_bin(offset, 12)
    return (
        imm[:7] +
        reg_bin(rs2) +
        reg_bin(base) +
        funct3[instr] +
        imm[7:] +
        opcodes[instr]
    )

# Montagem tipo B (ex: bne)
def montar_tipo_B(instr, rs1, rs2, imm):
    imm = imm_bin(imm, 13)  # 13 bits para branch (12 + sinal)
    return (
        imm[0] +       # bit 12
        imm[2:8] +     # bits 10:5
        reg_bin(rs2) +
        reg_bin(rs1) +
        funct3[instr] +
        imm[8:12] +    # bits 4:1
        imm[1] +       # bit 11
        opcodes[instr]
    )

# Traduz uma linha assembly para código binário
def traduzir_linha(linha):
    if '#' in linha:
        linha = linha.split('#')[0]
    tokens = linha.replace(',', ' ').replace('(', ' ').replace(')', ' ').split()
    if not tokens:
        return None

    instr = tokens[0]

    if instr not in opcodes:
        raise ValueError(f'Instrução não suportada: {instr}')

    # Instruções tipo R
    if instr in ['add', 'sub', 'and', 'sll', 'xor', 'srl']:
        if len(tokens) != 4:
            raise ValueError(f'Número inválido de operandos para {instr}')
        return montar_tipo_R(instr, tokens[1], tokens[2], tokens[3])

    # Tipo I
    elif instr == 'ori':
        if len(tokens) != 4:
            raise ValueError(f'Número inválido de operandos para {instr}')
        return montar_tipo_I(instr, tokens[1], tokens[2], tokens[3])

    elif instr == 'lb':
        # formato: lb rd, offset(base)
        if len(tokens) != 4:
            raise ValueError(f'Número inválido de operandos para {instr}')
        return montar_tipo_I(instr, tokens[1], tokens[3], tokens[2])

    # Tipo S
    elif instr == 'sb':
        # formato: sb rs2, offset(base)
        if len(tokens) != 4:
            raise ValueError(f'Número inválido de operandos para {instr}')
        return montar_tipo_S(instr, tokens[1], tokens[2], tokens[3])

    # Tipo B
    elif instr == 'bne':
        if len(tokens) != 4:
            raise ValueError(f'Número inválido de operandos para {instr}')
        return montar_tipo_B(instr, tokens[1], tokens[2], tokens[3])

    else:
        raise ValueError(f'Instrução não implementada: {instr}')

# Função principal do programa
def main():
    entrada = None
    saida = None
    hexadecimal = False

    idx = 1
    while idx < len(sys.argv):
        arg = sys.argv[idx]
        if arg == "-o" and idx + 1 < len(sys.argv):
            saida = sys.argv[idx + 1]
            idx += 2
        elif arg in ("--hex", "-x"):
            hexadecimal = True
            idx += 1
        elif not entrada:
            entrada = arg
            idx += 1
        else:
            idx += 1

    try:
        with open(entrada, 'r') as f:
            linhas = f.readlines()

        binarios = []
        for linha in linhas:
            linha = linha.strip()
            if not linha:
                continue
            try:
                binario = traduzir_linha(linha)
                if binario:
                    binarios.append(binario)
            except Exception as e:
                print(f"Erro na linha: {linha}")
                print(e)
                sys.exit(1)

        if saida:
            with open(saida, 'w') as f:
                for b in binarios:
                    if hexadecimal:
                        f.write(f"{hex(int(b, 2))[2:]}\n")  # converte binário -> int -> hex
                    else:
                        f.write(b + '\n')
            print(f"Montagem concluída! Arquivo salvo em: {saida}")
        else:
            for b in binarios:
                print(hex(int(b, 2))[2:] if hexadecimal else b)

    except FileNotFoundError:
        print(f"Arquivo não encontrado: {entrada}")
        sys.exit(1)
        
if __name__ == '__main__':
    main()
