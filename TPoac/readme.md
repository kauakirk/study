# Documentação do Montador

## 1. Requisitos

* **Python 3.8 ou superior**: O montador foi desenvolvido em Python e requer essa linguagem instalada no sistema.
* Sistema operacional: Windows ou Linux.

---

## 2. Instalação do Python

### **Linux**

1. Atualize os repositórios:

   ```bash
   sudo apt update
   ```
2. Instale o Python:

   ```bash
   sudo apt install python3 python3-pip -y
   ```
3. Verifique a instalação:

   ```bash
   python3 --version
   ```

### **Windows**

1. Acesse o site oficial do Python: [https://www.python.org/downloads/](https://www.python.org/downloads/).
2. Faça o download da versão mais recente.
3. Durante a instalação, **marque a opção "Add Python to PATH"**.
4. Verifique a instalação no terminal ou PowerShell:

   ```bash
   python --version
   ```

---

## 3. Como executar o montador

### **Comando básico**

O script aceita como entrada um arquivo `.asm` e pode gerar a saída em binário ou hexadecimal.

#### **Sintaxe**

```bash
python montador.py <arquivo_entrada> -o <arquivo_saida> [--hex]
```

#### **Exemplo 1 (Saída em binário)**

```bash
python montador.py entrada.asm -o saida.txt
```

#### **Exemplo 2 (Saída em hexadecimal)**

```bash
python montador.py entrada.asm -o saida.txt --hex
```

#### **Exemplo sem arquivo de saída**

Se o parâmetro `-o` for omitido, o resultado será exibido diretamente no terminal:

```bash
python montador.py entrada.asm
```

---

## 4. Explicação do código

### **Função `traduzir_linha(linha)`**

Essa função realiza a tradução de uma linha do código assembly para o formato binário. Ela é essencial para interpretar as instruções do arquivo `.asm`.

* **Entrada:** Uma linha de texto do arquivo assembly.
* **Saída:** Uma string representando a instrução em binário.

### **Trecho que processa a entrada**

```python
with open(entrada, 'r') as f:
    linhas = f.readlines()
```

Esse bloco abre o arquivo especificado na linha de comando e lê todas as linhas, armazenando-as em uma lista.

### **Conversão para hexadecimal**

No código, a conversão de binário para hexadecimal ocorre com o seguinte comando:

```python
hex(int(binario, 2))[2:]
```

* `int(binario, 2)`: Converte a string binária para um número inteiro.
* `hex(...)`: Converte o número inteiro para hexadecimal.
* `[2:]`: Remove o prefixo "0x" da string hexadecimal.

### **Bloco `try-except`**

O código utiliza estruturas `try-except` para capturar erros:

1. **Ao traduzir linhas inválidas:**

   ```python
   try:
       binario = traduzir_linha(linha)
       binarios.append(binario)
   except Exception as e:
       print(f"Erro na linha: {linha}")
       sys.exit(1)
   ```

   Caso uma linha não possa ser traduzida, o programa exibe a linha problemática e encerra a execução.

2. **Arquivo não encontrado:**

   ```python
   except FileNotFoundError:
       print(f"Arquivo não encontrado: {entrada}")
       sys.exit(1)
   ```

   Se o arquivo de entrada especificado não existir, o programa informará o erro e encerrará.

### **Execução condicional para hexadecimal**

A geração da saída em hexadecimal depende de uma flag passada na linha de comando:

```python
if hexadecimal:
    f.write(f"{hex(int(b, 2))[2:]}
")
else:
    f.write(b + '\n')
```

* Se `--hex` for especificado, a saída será convertida para hexadecimal.
* Caso contrário, a saída será mantida no formato binário.

---

## 5. Capturas de tela

1. **Exemplo de execução com saída em binário:**

   ![image](https://github.com/user-attachments/assets/99ecb9c7-2297-4fa5-999a-d4caa0da43d1)


2. **Exemplo de execução com saída em hexadecimal:**

   ![image](https://github.com/user-attachments/assets/a3bf25ec-2e6a-473f-bfc2-0d928598030f)


---

## 6. Considerações finais e overleaf

Este montador é uma ferramenta simples e eficiente para traduzir códigos assembly para binário ou hexadecimal. Para melhorar o uso, recomenda-se utilizar arquivos `.asm` bem formatados e seguir as instruções de execução à risca.
link overleaf: https://www.overleaf.com/project/6841e749c41fe46ba3c89520
