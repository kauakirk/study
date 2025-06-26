# funcionario.py

import random
import os
from datetime import datetime

class Funcionario:
    TAMANHO_REGISTRO = 90

    def __init__(self, id_funcionario, nome, cpf, data_nascimento, salario):
        self.id_funcionario = str(id_funcionario)
        self.nome = nome
        self.cpf = cpf
        self.data_nascimento = data_nascimento
        self.salario = salario

    def para_string_registro(self):
        id_func_str = self.id_funcionario.ljust(5)[:5]
        nome_str = str(self.nome).ljust(50)[:50]
        cpf_str = str(self.cpf).ljust(15)[:15] 
        data_nasc_str = str(self.data_nascimento).ljust(10)[:10] # Garante 10 caracteres
        salario_str = f"{self.salario:.2f}".rjust(10, '0')[:10]
        return f"{id_func_str}{nome_str}{cpf_str}{data_nasc_str}{salario_str}"

    @staticmethod
    def salva_funcionario(funcionario_obj, arquivo_out):
        registro_str = funcionario_obj.para_string_registro() + '\n'
        if len(registro_str) != Funcionario.TAMANHO_REGISTRO + 1:
            print(f"Erro: Tamanho do registro ({len(registro_str)}) != esperado ({Funcionario.TAMANHO_REGISTRO + 1})")
            return
        try:
            arquivo_out.write(registro_str)
        except Exception as e:
            print(f"Erro ao salvar: {e}")

    @staticmethod
    def de_string_registro(registro_str):
        try:
            id_func = registro_str[0:5].strip()
            nome = registro_str[5:55].strip()
            cpf = registro_str[55:70].strip()
            data_nasc = registro_str[70:80].strip() # Importante manter o .strip() na leitura
            salario = float(registro_str[80:90].strip())
            return Funcionario(id_func, nome, cpf, data_nasc, salario)
        except Exception as e:
            print(f"Erro ao converter string para Funcionario: {e}")
            return None

    @staticmethod
    def le_funcionario(arquivo_in):
        tamanho_linha = Funcionario.TAMANHO_REGISTRO + 1
        try:
            registro_str = arquivo_in.read(tamanho_linha)
            if not registro_str:
                return None
            registro_str = registro_str.strip()
            if len(registro_str) < Funcionario.TAMANHO_REGISTRO:
                print(f"Aviso: Registro incompleto. Esperado: {Funcionario.TAMANHO_REGISTRO}, lido: {len(registro_str)}")
                return None
            return Funcionario.de_string_registro(registro_str)
        except Exception as e:
            print(f"Erro ao ler funcionário: {e}")
            return None

    def exibir_info(self):
        return (f"ID: {self.id_funcionario}\n"
                f"Nome: {self.nome}\n"
                f"CPF: {self.cpf}\n"
                f"Data de Nascimento: {self.data_nascimento}\n"
                f"Salário: R${self.salario:.2f}")

    @staticmethod
    def imprime_funcionario(funcionario_obj):
        if isinstance(funcionario_obj, Funcionario):
            print(funcionario_obj.exibir_info())
        else:
            print("Erro: O objeto fornecido não é um Funcionario válido.")

    @staticmethod
    def criar_base_dados(nome_arquivo, tamanho_base):
        ids = list(range(1, tamanho_base + 1))
        random.shuffle(ids)

        print(f"\nGerando a base de dados '{nome_arquivo}' com {tamanho_base} funcionários...")

        try:
            with open(nome_arquivo, 'w', encoding="utf-8") as f:
                for i, id_func in enumerate(ids):
                    nome = f"Funcionario {id_func}".ljust(50)
                    
                    # --- Geração do CPF (como na última correção) ---
                    cpf_numeros = ''.join([str(random.randint(0, 9)) for _ in range(11)])
                    cpf = (f"{cpf_numeros[0:3]}.{cpf_numeros[3:6]}."
                           f"{cpf_numeros[6:9]}-{cpf_numeros[9:11]}")
                    cpf = cpf.ljust(15)[:15] 

                    # --- CORREÇÃO AQUI: Geração da Data de Nascimento Aleatória ---
                    # Definir um intervalo de anos (ex: funcionários de 18 a 65 anos)
                    ano_min = 1950 
                    ano_max = 2005 # Ajuste este valor conforme a idade desejada para os funcionários
                    
                    ano = random.randint(ano_min, ano_max)
                    mes = random.randint(1, 12)
                    
                    # Para o dia, precisamos considerar o número de dias no mês e anos bissextos
                    # Usamos uma lógica simples para evitar importações complexas de data
                    if mes in [4, 6, 9, 11]: # Meses com 30 dias
                        dia = random.randint(1, 30)
                    elif mes == 2: # Fevereiro
                        if (ano % 4 == 0 and ano % 100 != 0) or (ano % 400 == 0): # Ano bissexto
                            dia = random.randint(1, 29)
                        else:
                            dia = random.randint(1, 28)
                    else: # Meses com 31 dias
                        dia = random.randint(1, 31)
                    
                    # Formatar para DD/MM/AAAA e garantir 10 caracteres
                    data_nascimento = f"{dia:02d}/{mes:02d}/{ano}".ljust(10)[:10]

                    salario = 3000.00 + (id_func * 10.50)

                    funcionario_gerado = Funcionario(id_func, nome, cpf, data_nascimento, salario)
                    
                    Funcionario.salva_funcionario(funcionario_gerado, f)

                    if (i + 1) % (tamanho_base // 10 if tamanho_base >= 100 else 10) == 0 or (i + 1) == tamanho_base:
                         print(f"  {i + 1}/{tamanho_base} funcionários gerados...", end='\r')
                print("\n")
            
            print(f"Base de dados de funcionários gerada com sucesso em '{nome_arquivo}'.")

        except Exception as e:
            print(f"Ocorreu um erro ao criar a base de dados: {e}")

    @staticmethod
    def imprimir_base_dados(nome_arquivo):
        # ... (código existente de imprimir_base_dados) ...
        print(f"\nImprimindo a base de dados '{nome_arquivo}'...\n")

        try:
            with open(nome_arquivo, 'r', encoding="utf-8") as f:
                f.seek(0)
                while True:
                    funcionario = Funcionario.le_funcionario(f)
                    if funcionario is None:
                        break
                    Funcionario.imprime_funcionario(funcionario)
                    print("-" * 30)
            
            print("Fim da impressão da base de dados.")

        except FileNotFoundError:
            print(f"Erro: Arquivo '{nome_arquivo}' não encontrado. Por favor, crie a base de dados primeiro.")
        except Exception as e:
            print(f"Ocorreu um erro ao imprimir a base de dados: {e}")

    def compara_funcionario(f1, f2):
        # ... (código existente de compara_funcionario) ...
        if f1 is None:
            return f2 is None
        if f2 is None:
            return False
        if f1.id_funcionario.strip() != f2.id_funcionario.strip():
            return False
        if f1.nome.strip() != f2.nome.strip():
            return False
        return True
    @staticmethod
    def verificar_tamanho_registros_funcionario(nome_arquivo):
        print(f"\n--- Verificando tamanho dos registros em '{nome_arquivo}' ---")
        try:
            with open(nome_arquivo, 'r', encoding="utf-8") as f:
                linha_num = 0
                while True:
                    # Lê exatamente o tamanho que um registro MAIS a quebra de linha deve ter
                    registro_completo = f.read(Funcionario.TAMANHO_REGISTRO + 1)
                    
                    if not registro_completo: # Fim do arquivo
                        break
                    
                    linha_num += 1
                    tamanho_real = len(registro_completo)
                    tamanho_esperado = Funcionario.TAMANHO_REGISTRO + 1

                    # O strip() aqui é importante para remover o \n ao imprimir o conteúdo,
                    # mas o tamanho_real já inclui o \n se ele estiver lá.
                    conteudo_registro = registro_completo.strip() 

                    if tamanho_real == tamanho_esperado:
                        print(f"Linha {linha_num}: OK! Tamanho = {tamanho_real} bytes. Conteúdo (parcial): '{conteudo_registro[:20]}...'")
                    else:
                        print(f"Linha {linha_num}: ERRO! Tamanho esperado {tamanho_esperado}, mas lido {tamanho_real} bytes.")
                        print(f"  Conteúdo problemático: '{registro_completo.replace('\n', '\\n')}'")
                        # Se houver um problema aqui, pode indicar que um registro não foi escrito corretamente.

            print("--- Verificação de tamanho concluída ---")
        except FileNotFoundError:
            print(f"Arquivo '{nome_arquivo}' não encontrado para verificação.")
        except Exception as e:
            print(f"Ocorreu um erro durante a verificação: {e}")