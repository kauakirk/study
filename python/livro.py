import random
import os

class Livro:
    TAMANHO_REGISTRO = 125  # 5 + 50 + 50 + 10 + 10 = 125 caracteres

    def __init__(self, id_livro, titulo, autor, genero, preco):
        self.id_livro = str(id_livro)
        self.titulo = titulo
        self.autor = autor
        self.genero = genero
        self.preco = preco

    def para_string_registro(self):
        id_livro_str = self.id_livro.ljust(5)[:5]
        titulo_str = str(self.titulo).ljust(50)[:50]
        autor_str = str(self.autor).ljust(50)[:50]
        genero_str = str(self.genero).ljust(10)[:10]
        preco_str = f"{self.preco:.2f}".rjust(10, '0')[:10]
        return f"{id_livro_str}{titulo_str}{autor_str}{genero_str}{preco_str}"

    @staticmethod
    def salva_livro(livro_obj, arquivo_out):
        registro_str = livro_obj.para_string_registro() + '\n'
        if len(registro_str) != Livro.TAMANHO_REGISTRO + 1:
            print(f"Erro: Tamanho do registro ({len(registro_str)}) != esperado ({Livro.TAMANHO_REGISTRO + 1})")
            return
        try:
            arquivo_out.write(registro_str)
        except Exception as e:
            print(f"Erro ao salvar livro: {e}")

    @staticmethod
    def de_string_registro(registro_str):
        try:
            id_livro = registro_str[0:5].strip()
            titulo = registro_str[5:55].strip()
            autor = registro_str[55:105].strip()
            genero = registro_str[105:115].strip()
            preco = float(registro_str[115:125].strip())
            return Livro(id_livro, titulo, autor, genero, preco)
        except Exception as e:
            print(f"Erro ao converter string para Livro: {e}")
            return None

    @staticmethod
    def le_livro(arquivo_in):
        tamanho_linha = Livro.TAMANHO_REGISTRO + 1
        try:
            registro_str = arquivo_in.read(tamanho_linha)
            if not registro_str:
                return None
            registro_str = registro_str.strip()
            if len(registro_str) < Livro.TAMANHO_REGISTRO:
                print(f"Aviso: Registro incompleto. Esperado: {Livro.TAMANHO_REGISTRO}, lido: {len(registro_str)}")
                return None
            return Livro.de_string_registro(registro_str)
        except Exception as e:
            print(f"Erro ao ler livro: {e}")
            return None

    def exibir_info(self):
        return (f"ID: {self.id_livro}\n"
                f"Título: {self.titulo}\n"
                f"Autor: {self.autor}\n"
                f"Gênero: {self.genero}\n"
                f"Preço: R${self.preco:.2f}")

    @staticmethod
    def imprime_livro(livro_obj):
        if isinstance(livro_obj, Livro):
            print(livro_obj.exibir_info())
        else:
            print("Erro: O objeto fornecido não é um Livro válido.")

    @staticmethod
    def criar_base_dados(nome_arquivo, tamanho_base):
        ids = list(range(1, tamanho_base + 1))
        random.shuffle(ids)

        print(f"\nGerando a base de dados de livros '{nome_arquivo}' com {tamanho_base} registros...")

        # Listas para geração de dados aleatórios
        generos = ["Romance", "Ficção", "Aventura", "Terror", "Biografia", "História", "Infantil", "Poesia", "Autoajuda", "Negócios"]
        autores = ["Machado de Assis", "Clarice Lispector", "Jorge Amado", "Carlos Drummond", "Monteiro Lobato", 
                  "Stephen King", "J.K. Rowling", "George Orwell", "Agatha Christie", "Tolkien"]
        palavras_titulo = ["Amor", "Guerra", "Segredos", "Perdido", "Escuro", "Luz", "Vida", "Morte", "Esperança", "Tempo"]

        try:
            with open(nome_arquivo, 'w', encoding="utf-8") as f:
                for i, id_livro in enumerate(ids):
                    # Gera título aleatório
                    palavra1 = random.choice(palavras_titulo)
                    palavra2 = random.choice(palavras_titulo)
                    titulo = f"{palavra1} de {palavra2}".ljust(50)[:50]
                    
                    # Seleciona autor e gênero aleatórios
                    autor = random.choice(autores).ljust(50)[:50]
                    genero = random.choice(generos).ljust(10)[:10]
                    
                    # Gera preço aleatório entre 20 e 200
                    preco = random.uniform(20.0, 200.0)

                    livro_gerado = Livro(id_livro, titulo, autor, genero, preco)
                    
                    Livro.salva_livro(livro_gerado, f)

                    if (i + 1) % (tamanho_base // 10 if tamanho_base >= 100 else 10) == 0 or (i + 1) == tamanho_base:
                         print(f"  {i + 1}/{tamanho_base} livros gerados...", end='\r')
                print("\n")
            
            print(f"Base de dados de livros gerada com sucesso em '{nome_arquivo}'.")

        except Exception as e:
            print(f"Ocorreu um erro ao criar a base de dados: {e}")

    @staticmethod
    def imprimir_base_dados(nome_arquivo):
        print(f"\nImprimindo a base de dados de livros '{nome_arquivo}'...\n")

        try:
            with open(nome_arquivo, 'r', encoding="utf-8") as f:
                f.seek(0)
                while True:
                    livro = Livro.le_livro(f)
                    if livro is None:
                        break
                    Livro.imprime_livro(livro)
                    print("-" * 30)
            
            print("Fim da impressão da base de dados.")

        except FileNotFoundError:
            print(f"Erro: Arquivo '{nome_arquivo}' não encontrado. Por favor, crie a base de dados primeiro.")
        except Exception as e:
            print(f"Ocorreu um erro ao imprimir a base de dados: {e}")

    @staticmethod
    def compara_livro(l1, l2):
        if l1 is None:
            return l2 is None
        if l2 is None:
            return False
        if l1.id_livro.strip() != l2.id_livro.strip():
            return False
        if l1.titulo.strip() != l2.titulo.strip():
            return False
        return True

    @staticmethod
    def verificar_tamanho_registros(nome_arquivo):
        print(f"\n--- Verificando tamanho dos registros em '{nome_arquivo}' ---")
        try:
            with open(nome_arquivo, 'r', encoding="utf-8") as f:
                linha_num = 0
                while True:
                    registro_completo = f.read(Livro.TAMANHO_REGISTRO + 1)
                    
                    if not registro_completo:
                        break
                    
                    linha_num += 1
                    tamanho_real = len(registro_completo)
                    tamanho_esperado = Livro.TAMANHO_REGISTRO + 1

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
