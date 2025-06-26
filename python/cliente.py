import random
import os

class Cliente:
    TAMANHO_REGISTRO = 90  # 5 + 50 + 15 + 10 + 10 = 90 caracteres

    def __init__(self, id_cliente, nome, cpf, data_nascimento, saldo):
        self.id_cliente = str(id_cliente)
        self.nome = nome
        self.cpf = cpf
        self.data_nascimento = data_nascimento
        self.saldo = saldo

    def para_string_registro(self):
        id_cliente_str = self.id_cliente.ljust(5)[:5]
        nome_str = str(self.nome).ljust(50)[:50]
        cpf_str = str(self.cpf).ljust(15)[:15]
        data_nasc_str = str(self.data_nascimento).ljust(10)[:10]
        saldo_str = f"{self.saldo:.2f}".rjust(10, '0')[:10]
        return f"{id_cliente_str}{nome_str}{cpf_str}{data_nasc_str}{saldo_str}"

    @staticmethod
    def salva_cliente(cliente_obj, arquivo_out):
        registro_str = cliente_obj.para_string_registro() + '\n'
        if len(registro_str) != Cliente.TAMANHO_REGISTRO + 1:
            print(f"Erro: Tamanho do registro ({len(registro_str)}) != esperado ({Cliente.TAMANHO_REGISTRO + 1})")
            return
        try:
            arquivo_out.write(registro_str)
        except Exception as e:
            print(f"Erro ao salvar cliente: {e}")

    @staticmethod
    def de_string_registro(registro_str):
        try:
            id_cliente = registro_str[0:5].strip()
            nome = registro_str[5:55].strip()
            cpf = registro_str[55:70].strip()
            data_nasc = registro_str[70:80].strip()
            saldo = float(registro_str[80:90].strip())
            return Cliente(id_cliente, nome, cpf, data_nasc, saldo)
        except Exception as e:
            print(f"Erro ao converter string para Cliente: {e}")
            return None

    @staticmethod
    def le_cliente(arquivo_in):
        tamanho_linha = Cliente.TAMANHO_REGISTRO + 1
        try:
            registro_str = arquivo_in.read(tamanho_linha)
            if not registro_str:
                return None
            registro_str = registro_str.strip()
            if len(registro_str) < Cliente.TAMANHO_REGISTRO:
                print(f"Aviso: Registro incompleto. Esperado: {Cliente.TAMANHO_REGISTRO}, lido: {len(registro_str)}")
                return None
            return Cliente.de_string_registro(registro_str)
        except Exception as e:
            print(f"Erro ao ler cliente: {e}")
            return None

    def exibir_info(self):
        return (f"ID: {self.id_cliente}\n"
                f"Nome: {self.nome}\n"
                f"CPF: {self.cpf}\n"
                f"Data de Nascimento: {self.data_nascimento}\n"
                f"Saldo: R${self.saldo:.2f}")

    @staticmethod
    def imprime_cliente(cliente_obj):
        if isinstance(cliente_obj, Cliente):
            print(cliente_obj.exibir_info())
        else:
            print("Erro: O objeto fornecido não é um Cliente válido.")

    @staticmethod
    def criar_base_dados(nome_arquivo, tamanho_base):
        ids = list(range(1, tamanho_base + 1))
        random.shuffle(ids)

        print(f"\nGerando a base de dados de clientes '{nome_arquivo}' com {tamanho_base} registros...")

        try:
            with open(nome_arquivo, 'w', encoding="utf-8") as f:
                for i, id_cliente in enumerate(ids):
                    nome = f"Cliente {id_cliente}".ljust(50)
                    
                    # Geração do CPF
                    cpf_numeros = ''.join([str(random.randint(0, 9)) for _ in range(11)])
                    cpf = (f"{cpf_numeros[0:3]}.{cpf_numeros[3:6]}."
                           f"{cpf_numeros[6:9]}-{cpf_numeros[9:11]}")
                    cpf = cpf.ljust(15)[:15]

                    # Geração da Data de Nascimento
                    ano_min = 1950 
                    ano_max = 2005
                    ano = random.randint(ano_min, ano_max)
                    mes = random.randint(1, 12)
                    
                    if mes in [4, 6, 9, 11]:
                        dia = random.randint(1, 30)
                    elif mes == 2:
                        if (ano % 4 == 0 and ano % 100 != 0) or (ano % 400 == 0):
                            dia = random.randint(1, 29)
                        else:
                            dia = random.randint(1, 28)
                    else:
                        dia = random.randint(1, 31)
                    
                    data_nascimento = f"{dia:02d}/{mes:02d}/{ano}".ljust(10)[:10]

                    # Saldo aleatório entre 100 e 10000
                    saldo = random.uniform(100.0, 10000.0)

                    cliente_gerado = Cliente(id_cliente, nome, cpf, data_nascimento, saldo)
                    
                    Cliente.salva_cliente(cliente_gerado, f)

                    if (i + 1) % (tamanho_base // 10 if tamanho_base >= 100 else 10) == 0 or (i + 1) == tamanho_base:
                         print(f"  {i + 1}/{tamanho_base} clientes gerados...", end='\r')
                print("\n")
            
            print(f"Base de dados de clientes gerada com sucesso em '{nome_arquivo}'.")

        except Exception as e:
            print(f"Ocorreu um erro ao criar a base de dados: {e}")

    @staticmethod
    def imprimir_base_dados(nome_arquivo):
        print(f"\nImprimindo a base de dados de clientes '{nome_arquivo}'...\n")

        try:
            with open(nome_arquivo, 'r', encoding="utf-8") as f:
                f.seek(0)
                while True:
                    cliente = Cliente.le_cliente(f)
                    if cliente is None:
                        break
                    Cliente.imprime_cliente(cliente)
                    print("-" * 30)
            
            print("Fim da impressão da base de dados.")

        except FileNotFoundError:
            print(f"Erro: Arquivo '{nome_arquivo}' não encontrado. Por favor, crie a base de dados primeiro.")
        except Exception as e:
            print(f"Ocorreu um erro ao imprimir a base de dados: {e}")

    @staticmethod
    def compara_cliente(c1, c2):
        if c1 is None:
            return c2 is None
        if c2 is None:
            return False
        if c1.id_cliente.strip() != c2.id_cliente.strip():
            return False
        if c1.nome.strip() != c2.nome.strip():
            return False
        return True

    @staticmethod
    def verificar_tamanho_registros(nome_arquivo):
        print(f"\n--- Verificando tamanho dos registros em '{nome_arquivo}' ---")
        try:
            with open(nome_arquivo, 'r', encoding="utf-8") as f:
                linha_num = 0
                while True:
                    registro_completo = f.read(Cliente.TAMANHO_REGISTRO + 1)
                    
                    if not registro_completo:
                        break
                    
                    linha_num += 1
                    tamanho_real = len(registro_completo)
                    tamanho_esperado = Cliente.TAMANHO_REGISTRO + 1

                    conteudo_registro = registro_completo.strip()

                    if tamanho_real == tamanho_esperado:
                        print(f"Linha {linha_num}: OK! Tamanho = {tamanho_real} bytes. Conteúdo (parcial): '{conteudo_registro[:20]}...'")
                    else:
                        print(f"Linha {linha_num}: ERRO! Tamanho esperado {tamanho_esperado}, mas lido {tamanho_real} bytes.")
                        print(f"  Conteúdo problemático: '{registro_completo.replace('\n', '\\n')}'")

            print("--- Verificação de tamanho concluída ---")
        except FileNotFoundError:
            print(f"Arquivo '{nome_arquivo}' não encontrado para verificação.")
        except Exception as e:
            print(f"Ocorreu um erro durante a verificação: {e}")

