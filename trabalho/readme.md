# 🗺️ Projeto de Roteiro de Viagem com Eventos

Este projeto é um sistema interativo em terminal, desenvolvido em **C** com a biblioteca **ncurses**, que permite simular uma árvore de cidades e eventos turísticos com funcionalidades de busca, ordenação e gerenciamento.

## 📋 Funcionalidades

- Visualizar cidades em diferentes percursos da árvore binária (Pré-Ordem, In-Ordem, Pós-Ordem)
- Exibir eventos disponíveis em cada cidade
- Buscar eventos por nome ou avaliação
- Criar roteiro de viagem com uma ou duas cidades
- Cancelar e reinserir eventos
- Ordenar eventos por avaliação usando diversos algoritmos clássicos:
  - Bubble Sort
  - Merge Sort
  - Quick Sort
  - Selection Sort
  - Insertion Sort
  - Heap Sort
  - Shell Sort
- Interface amigável no terminal com **navegação por setas**

## 🧱 Estruturas principais

- **Árvore binária de cidades**
- **Eventos associados a cada cidade**
- **Sistema de mensagens aleatórias**
- **Cancelamento e reinserção de eventos**

## 🧪 Requisitos

- Sistema com WSL (ou Linux nativo)
- Biblioteca `ncurses` instalada

Para instalar:
```bash
sudo apt update
sudo apt install libncurses5-dev libncursesw5-dev
```

## 🚀 Como compilar
```bash
gcc projetoreal.c -o projetoreal -lncurses -lm
```

## ▶️ Como executar
```bash
./projetoreal
```

## 🎨 Exemplo de uso

Ao iniciar o programa, use as **setas do teclado** para navegar pelo menu e pressione **Enter** para escolher a opção desejada. Todas as interações ocorrem em modo texto, com uma interface visual personalizada usando cores e bordas.

## 👩‍💻 Desenvolvedores

- Maria Eduarda Vieira Orsi  
- Camille Silva Oliveira  
- Mariana Rodrigues Martins  
- Iani Brenda Cavalcanti Quaresma