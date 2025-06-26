from funcionario import Funcionario
from cliente import Cliente
from livro import Livro


def main():
    arquivo_func = "funcionario.dat"
    arquivo_cliente = "cliente.dat"
    arquivo_livro = "livro.dat"
    log_file = "log.txt"

    # Abrir/registrar log
    try:
        with open(log_file, "a+", encoding="utf-8") as log:
            log.write("Iniciando execução do programa.\n")
    except Exception as e:
        print("Erro ao abrir arquivo de log.")
        exit(1)
    try:
        Funcionario.criar_base_dados(arquivo_func, 10)
        Cliente.criar_base_dados(arquivo_cliente, 10)
        Livro.criar_base_dados(arquivo_livro, 10)
    except Exception as e:
        print(f"Erro ao criar base: {e}")
        exit(1)
    
    
    #Funcionario.imprimir_base_dados(arquivo_func)
    #Funcionario.verificar_tamanho_registros_funcionario(arquivo_func)
    #Cliente.verificar_tamanho_registros("clientes.dat")
    #Cliente.imprimir_base_dados(arquivo_cliente)
    Livro.verificar_tamanho_registros(arquivo_livro)
    Livro.imprimir_base_dados(arquivo_livro)
    


    # (Descomente para imprimir a base completa — cuidado com o tamanho!)
    # Funcionario.imprimir_base_dados(nome_arquivo)

if __name__ == "__main__":
    main()
