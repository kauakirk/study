#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
// Definições de constantes
#define TAM_NOME 50
#define TAM_EVENTOS 30
#define TAM_CIDADES 10

// Estrutura para representar um evento
typedef struct evento {
    char name[TAM_NOME];
    float avaliacao;
    char horario[6];
} TEvento;

// Estrutura para representar uma cidade
typedef struct cidade {
    int id;
    char name[TAM_NOME];
    TEvento eventos[TAM_EVENTOS];
    int num_eventos;
} TCidade;

// Nó da árvore binária
typedef struct celula {
    TCidade cidade;
    struct celula *pai;
    struct celula *esquerdo;
    struct celula *direito;
} TCelula;

// Estrutura da árvore binária
typedef struct arvoreBinaria {
    TCelula *raiz;
} TArvoreBinaria;

// Protótipo da função OrdenarEventosPorHorario
void OrdenarEventosPorHorario(TEvento eventos[], int n);

// Outros protótipos de funções
void GerarHorarioAleatorio(char *horario);
void InserirCidade(TCelula **celula, TCelula *pai, TCidade cidade);
void GerarEventos(TCidade *cidade);
void BubbleSort(TEvento eventos[], int n);
void MergeSort(TEvento eventos[], int l, int r);
void SelectionSort(TEvento eventos[], int n);
void QuickSort(TEvento eventos[], int low, int high);
void InsertionSort(TEvento eventos[], int n);
void ShellSort(TEvento eventos[], int n);
void Heapify(TEvento eventos[], int n, int i);
void HeapSort(TEvento eventos[], int n);
void TrocarCidades(TCidade *a, TCidade *b);
void EmbaralharCidades(TCidade cidades[], int n);
void PreOrdem(TCelula *x);
void InOrdem(TCelula *x);
void PosOrdem(TCelula *x);
TCelula* PesquisarCidade(TCelula *x, int id);
TCelula* PesquisarCidadeNome(TCelula *x, char *nome);
void BuscarEventos(TCidade *cidade, char *nome, float avaliacao);
void ExibirEventos(TCidade *cidade);
void RoteiroViagem(TCelula *raiz);
void CancelarEvento(TCidade *cidade, char *nomeEvento);
void ExibirMensagemEspecial();
void ReinserirEvento(TCelula *raiz);
void menu();
TCidade* EscolherCidade();
void EscolherMetodoOrdenacao(TEvento eventos[], int n);

// Função para gerar horário aleatório
void GerarHorarioAleatorio(char *horario) {
    int hora = 8 + rand() % 15; // Horário entre 08:00 e 22:00
    int minuto = (rand() % 4) * 15; // Minutos em 0, 15, 30, 45
    sprintf(horario, "%02d:%02d", hora, minuto);
}

// Estrutura para cancelamento de evento
typedef struct eventoCancelado {
    TEvento evento;
    int cidadeId;
    int posicao;
    int cancelado;
} TEventoCancelado;

TEventoCancelado eventoCancelado = {.cancelado = 0};

// Lista de eventos disponíveis
TEvento eventos[TAM_EVENTOS] = {
    {"Festival de Musica", 9.5},
    {"Feira de Artesanato", 8.7},
    {"Exposicao de Arte", 9.0},
    {"Festival de Cinema", 9.2},
    {"Conferencia de Tecnologia", 8.9},
    {"Festival Gastronomico", 9.3},
    {"Feira do Livro", 8.5},
    {"Show de Stand-up", 8.8},
    {"Campeonato de E-sports", 9.1},
    {"Seminario de Inovacao", 8.6},
    {"Mostra de Fotografia", 8.9},
    {"Feira de Ciencias", 9.0},
    {"Workshop de Danca", 8.4},
    {"Encontro de Carros Antigos", 9.2},
    {"Competicao de Robotica", 9.4},
    {"Festival de Jazz", 9.6},
    {"Semana de Sustentabilidade", 8.3},
    {"Feira de Design", 8.7},
    {"Exibicao de Curtas", 9.0},
    {"Congresso de Medicina", 8.9},
    {"Corrida de Rua", 8.8},
    {"Festival de Teatro", 9.1},
    {"Hackathon de Programacao", 9.3},
    {"Feira de Empregos", 8.5},
    {"Simposio de Astronomia", 8.9},
    {"Festival de Cervejas Artesanais", 9.2},
    {"Concurso de Fotografia", 8.7},
    {"Encontro de Vinil", 9.0},
    {"Feira de Saude e Bem-estar", 8.6},
    {"Competicao de Xadrez", 9.4}
};

// Lista de cidades disponíveis
TCidade cidades[TAM_CIDADES] = {
    {4, "Belo Horizonte", {}, 0},
    {3, "Sabara", {}, 0},
    {2, "Ouro Preto", {}, 0},
    {1, "Mariana", {}, 0},
    {5, "Congonhas", {}, 0},
    {9, "Sao Joao del-Rei", {}, 0},
    {6, "Lagoa Dourada", {}, 0},
    {8, "Barbacena", {}, 0},
    {10, "Lavras", {}, 0},
    {7, "Tiradentes", {}, 0}
};

// Função para criar um nó da árvore
TCelula* CriaNo(TCidade cidade) {
    TCelula *celula = (TCelula *) malloc(sizeof(TCelula));
    celula->cidade = cidade;
    celula->pai = NULL;
    celula->esquerdo = NULL;
    celula->direito = NULL;
    return celula;
}

// Função para inserir cidade na árvore
void InserirCidade(TCelula **celula, TCelula *pai, TCidade cidade) {
    if ((*celula) == NULL) {
        (*celula) = CriaNo(cidade);
        (*celula)->pai = pai;
        return;
    }
    if (cidade.id < (*celula)->cidade.id)
        InserirCidade(&(*celula)->esquerdo, *celula, cidade);
    else
        InserirCidade(&(*celula)->direito, *celula, cidade);
}

// Função para gerar eventos aleatórios para uma cidade
void GerarEventos(TCidade *cidade) {
    cidade->num_eventos = rand() % (TAM_EVENTOS / 2) + 1;
    for (int i = 0; i < cidade->num_eventos; i++) {
        cidade->eventos[i] = eventos[rand() % TAM_EVENTOS];
        GerarHorarioAleatorio(cidade->eventos[i].horario); // Define o horário do evento
    }
}

// Função Bubble Sort para ordenar eventos por avaliação
void BubbleSort(TEvento eventos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (eventos[j].avaliacao < eventos[j + 1].avaliacao) {
                TEvento temp = eventos[j];
                eventos[j] = eventos[j + 1];
                eventos[j + 1] = temp;
            }
        }
    }
}

// Função Merge para o Merge Sort
void Merge(TEvento eventos[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    TEvento L[n1], R[n2];
    for (i = 0; i < n1; i++) L[i] = eventos[l + i];
    for (j = 0; j < n2; j++) R[j] = eventos[m + 1 + j];
    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (L[i].avaliacao >= R[j].avaliacao) eventos[k++] = L[i++];
        else eventos[k++] = R[j++];
    }
    while (i < n1) eventos[k++] = L[i++];
    while (j < n2) eventos[k++] = R[j++];
}

// Função MergeSort para ordenar eventos por avaliação
void MergeSort(TEvento eventos[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        MergeSort(eventos, l, m);
        MergeSort(eventos, m + 1, r);
        Merge(eventos, l, m, r);
    }
}

// Função SelectionSort para ordenar eventos por avaliação
void SelectionSort(TEvento eventos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (eventos[j].avaliacao > eventos[maxIndex].avaliacao) {
                maxIndex = j;
            }
        }
        TEvento temp = eventos[i];
        eventos[i] = eventos[maxIndex];
        eventos[maxIndex] = temp;
    }
}

// Função QuickSort para ordenar eventos por avaliação
void QuickSort(TEvento eventos[], int low, int high) {
    if (low < high) {
        int pivot = eventos[high].avaliacao;
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (eventos[j].avaliacao >= pivot) {
                i++;
                TEvento temp = eventos[i];
                eventos[i] = eventos[j];
                eventos[j] = temp;
            }
        }
        TEvento temp = eventos[i + 1];
        eventos[i + 1] = eventos[high];
        eventos[high] = temp;
        QuickSort(eventos, low, i);
        QuickSort(eventos, i + 2, high);
    }
}

// Função InsertionSort para ordenar eventos por avaliação
void InsertionSort(TEvento eventos[], int n) {
    for (int i = 1; i < n; i++) {
        TEvento key = eventos[i];
        int j = i - 1;
        while (j >= 0 && eventos[j].avaliacao < key.avaliacao) {
            eventos[j + 1] = eventos[j];
            j--;
        }
        eventos[j + 1] = key;
    }
}

// Função ShellSort para ordenar eventos por avaliação
void ShellSort(TEvento eventos[], int n) {
    int h = 1;
    while (h < n / 3) {
        h = 3 * h + 1; // Define o intervalo inicial
    }

    while (h >= 1) {
        for (int i = h; i < n; i++) {
            TEvento temp = eventos[i];
            int j = i;
            while (j >= h && eventos[j - h].avaliacao < temp.avaliacao) {
                eventos[j] = eventos[j - h];
                j -= h;
            }
            eventos[j] = temp;
        }
        h /= 3; // Reduz o intervalo
    }
}

// Função Heapify para construir um heap máximo
void Heapify(TEvento eventos[], int n, int i) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < n && eventos[esquerda].avaliacao > eventos[maior].avaliacao)
        maior = esquerda;

    if (direita < n && eventos[direita].avaliacao > eventos[maior].avaliacao)
        maior = direita;

    if (maior != i) {
        TEvento temp = eventos[i];
        eventos[i] = eventos[maior];
        eventos[maior] = temp;
        Heapify(eventos, n, maior);
    }
}
// Função HeapSort para ordenar eventos por avaliação
void HeapSort(TEvento eventos[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(eventos, n, i);

    for (int i = n - 1; i > 0; i--) {
        TEvento temp = eventos[0];
        eventos[0] = eventos[i];
        eventos[i] = temp;
        Heapify(eventos, i, 0);
    }
}

// Função para trocar duas cidades de posição
void TrocarCidades(TCidade *a, TCidade *b) {
    TCidade temp = *a;
    *a = *b;
    *b = temp;
}

// Função para embaralhar a lista de cidades
void EmbaralharCidades(TCidade cidades[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        TrocarCidades(&cidades[i], &cidades[j]);
    }
}

// Funções para percorrer a árvore (adaptadas para ncurses)
void PreOrdem(TCelula *x) {
    if (x != NULL) {
        printw("(ID: %d) %s\n", x->cidade.id, x->cidade.name);
        PreOrdem(x->esquerdo);
        PreOrdem(x->direito);
    }
}

void InOrdem(TCelula *x) {
    if (x != NULL) {
        InOrdem(x->esquerdo);
        printw("(ID: %d) %s\n", x->cidade.id, x->cidade.name);
        InOrdem(x->direito);
    }
}

void PosOrdem(TCelula *x) {
    if (x != NULL) {
        PosOrdem(x->esquerdo);
        PosOrdem(x->direito);
        printw("(ID: %d) %s\n", x->cidade.id, x->cidade.name);
    }
}

// Função para buscar uma cidade na árvore
TCelula* PesquisarCidade(TCelula *x, int id) {
    if (x == NULL || x->cidade.id == id)
        return x;
    if (id < x->cidade.id)
        return PesquisarCidade(x->esquerdo, id);
    return PesquisarCidade(x->direito, id);
}

// Função para buscar uma cidade pelo nome na árvore
TCelula* PesquisarCidadeNome(TCelula *x, char *nome) {
    if ((x == NULL) || (strcmp(x->cidade.name, nome) == 0))
        return x;
    if (strcmp(nome, x->cidade.name) < 0)
        return PesquisarCidadeNome(x->esquerdo, nome);
    else
        return PesquisarCidadeNome(x->direito, nome);
}

// Função para buscar eventos por nome ou avaliação (adaptada para ncurses)
void BuscarEventos(TCidade *cidade, char *nome, float avaliacao) {
    TEvento eventoMaisProximo = {"", -1};
    float menorDiferenca = 10.0; // Diferença máxima possível

    for (int i = 0; i < cidade->num_eventos; i++) {
        if (strcmp(cidade->eventos[i].name, nome) == 0) {
            printw("Evento encontrado: %s (Avaliacao: %.1f)\n", cidade->eventos[i].name, cidade->eventos[i].avaliacao);
            return;
        }

        float diferenca = fabs(cidade->eventos[i].avaliacao - avaliacao);
        if (diferenca < menorDiferenca) {
            menorDiferenca = diferenca;
            eventoMaisProximo = cidade->eventos[i];
        }
    }

    if (eventoMaisProximo.avaliacao != -1) {
        printw("Evento nao encontrado. Evento com avaliacao mais proxima: %s (Avaliacao: %.1f)\n", eventoMaisProximo.name, eventoMaisProximo.avaliacao);
    } else {
        printw("Nenhum evento encontrado.\n");
    }
}

// Função para exibir eventos de uma cidade (adaptada para ncurses)
void ExibirEventos(TCidade *cidade) {
    clear(); // Limpa a tela
    printw("\nEventos em %s:\n", cidade->name);
    for (int i = 0; i < cidade->num_eventos; i++) {
        printw(" - %s | Avaliacao: %.1f | Horario: %s\n", cidade->eventos[i].name, cidade->eventos[i].avaliacao, cidade->eventos[i].horario);
    }
    printw("\nPressione qualquer tecla para continuar...");
    refresh();
    getch();
}

// Função para definir um roteiro de viagem entre cidades (adaptada para ncurses)
void RoteiroViagem(TCelula *raiz) {
    if (raiz != NULL) {
        RoteiroViagem(raiz->esquerdo);
        clear(); // Limpa a tela
        printw("\nCidade: %s\n", raiz->cidade.name);
        OrdenarEventosPorHorario(raiz->cidade.eventos, raiz->cidade.num_eventos);
        ExibirEventos(&raiz->cidade);
        refresh();
        getch();
        RoteiroViagem(raiz->direito);
    }
}

// Função para cancelar um evento de uma cidade (adaptada para ncurses)
void CancelarEvento(TCidade *cidade, char *nomeEvento) {
    for (int i = 0; i < cidade->num_eventos; i++) {
        if (strcmp(cidade->eventos[i].name, nomeEvento) == 0) {
            eventoCancelado.evento = cidade->eventos[i];
            eventoCancelado.cidadeId = cidade->id;
            eventoCancelado.posicao = i;
            eventoCancelado.cancelado = 1;

            for (int j = i; j < cidade->num_eventos - 1; j++) {
                cidade->eventos[j] = cidade->eventos[j + 1];
            }
            cidade->num_eventos--;

            printw("Evento '%s' cancelado em %s.\n", nomeEvento, cidade->name);
            refresh();
            getch();
            return;
        }
    }
    printw("Evento '%s' nao encontrado em %s.\n", nomeEvento, cidade->name);
    refresh();
    getch();
}

// Função para exibir mensagem especial (adaptada para ncurses)
void ExibirMensagemEspecial() {
    const char *mensagens[] = {
        "Evento Top: Festival de Musica Imperdivel!",
        "Dica: Priorize os eventos com avaliacoes acima de 9.0!",
        "Sorte sua! Encontramos um evento altamente avaliado.",
        "Experimente explorar novas cidades e eventos!",
        "Eventos com avaliacoes acima de 8.5 costumam ser incriveis!"
    };

    int indice = rand() % 5;  // Escolhe uma mensagem aleatória
    printw("\n*** %s ***\n", mensagens[indice]);
    refresh();
    getch();
}

// Função para reinserir o evento cancelado de volta na cidade (adaptada para ncurses)
void ReinserirEvento(TCelula *raiz) {
    if (!eventoCancelado.cancelado) {
        printw("Nenhum evento foi cancelado para reinserir.\n");
        refresh();
        getch();
        return;
    }

    // Buscar a cidade pelo ID
    TCelula *noCidade = PesquisarCidade(raiz, eventoCancelado.cidadeId);
    if (noCidade == NULL) {
        printw("Cidade nao encontrada para reinserir o evento.\n");
        refresh();
        getch();
        return;
    }

    // Reposicionar o evento no vetor de eventos da cidade
    if (noCidade->cidade.num_eventos < TAM_EVENTOS) {
        for (int i = noCidade->cidade.num_eventos; i > eventoCancelado.posicao; i--) {
            noCidade->cidade.eventos[i] = noCidade->cidade.eventos[i - 1];
        }
        noCidade->cidade.eventos[eventoCancelado.posicao] = eventoCancelado.evento;
        noCidade->cidade.num_eventos++;

        printw("Evento '%s' reinserido em %s.\n", eventoCancelado.evento.name, noCidade->cidade.name);
        eventoCancelado.cancelado = 0; // Resetando o status do evento cancelado
    } else {
        printw("Limite de eventos atingido. Nao foi possivel reinserir o evento.\n");
    }
    refresh();
    getch();
}

// Função para ordenar eventos por horário (não requer adaptação para ncurses)
void OrdenarEventosPorHorario(TEvento eventos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(eventos[j].horario, eventos[j + 1].horario) > 0) {
                TEvento temp = eventos[j];
                eventos[j] = eventos[j + 1];
                eventos[j + 1] = temp;
            }
        }
    }
}

// Função para exibir o menu principal (adaptada para ncurses)
void menu() {
    clear(); // Limpa a tela
    printw("\n============ Menu Principal ============="
           "\n1. Exibir cidades na arvore (Percursos)"
           "\n2. Exibir eventos de uma cidade"
           "\n3. Buscar evento em uma cidade"
           "\n4. Criar roteiro de viagem"
           "\n5. Cancelar evento"
           "\n6. Reinserir evento cancelado"
           "\n7. Escolher o algoritmo de ordenacao"
           "\n0. Sair"
           "\n========================================"
           "\nEscolha uma opcao: ");
    refresh();
}

// Função para escolher a cidade (adaptada para ncurses)
TCidade* EscolherCidade() {
    clear(); // Limpa a tela
    printw("\nEscolha uma cidade para visualizar os eventos:\n");
    for (int i = 0; i < TAM_CIDADES; i++) {
        printw("%d - %s\n", cidades[i].id, cidades[i].name);
    }

    int escolha;
    printw("Digite o ID da cidade: ");
    refresh();
    scanw("%d", &escolha);

    for (int i = 0; i < TAM_CIDADES; i++) {
        if (cidades[i].id == escolha) {
            return &cidades[i];
        }
    }
    printw("Cidade nao encontrada.\n");
    refresh();
    getch();
    return NULL;
}

// Função para escolher o algoritmo de ordenação (adaptada para ncurses)
void EscolherMetodoOrdenacao(TEvento eventos[], int n) {
    clear(); // Limpa a tela
    printw("\nEscolha um algoritmo de ordenacao:\n");
    printw("1 - Bubble Sort\n");
    printw("2 - Merge Sort\n");
    printw("3 - Quick Sort\n");
    printw("4 - Selection Sort\n");
    printw("5 - Insertion Sort\n");
    printw("6 - Heap Sort\n");
    printw("7 - Shell Sort\n");

    int escolha;
    printw("Digite o numero correspondente: ");
    refresh();
    scanw("%d", &escolha);

    switch (escolha) {
        case 1: BubbleSort(eventos, n); break;
        case 2: MergeSort(eventos, 0, n - 1); break;
        case 3: QuickSort(eventos, 0, n - 1); break;
        case 4: SelectionSort(eventos, n); break;
        case 5: InsertionSort(eventos, n); break;
        case 6: HeapSort(eventos, n); break;
        case 7: ShellSort(eventos, n); break;
        default: printw("Opcao invalida.\n"); refresh(); getch(); return;
    }

    printw("Eventos ordenados com sucesso!\n");
    refresh();
    getch();
}

// Definições de cores
#define COLOR_BORDER 1
#define COLOR_MENU 2
#define COLOR_SELECTED 3
#define COLOR_TITLE 4

// Função para inicializar cores
void iniciarCores() {
    start_color();
    init_pair(COLOR_BORDER, COLOR_WHITE, COLOR_BLUE);      // Borda branca com fundo azul
    init_pair(COLOR_MENU, COLOR_WHITE, COLOR_BLACK);       // Texto branco com fundo preto
    init_pair(COLOR_SELECTED, COLOR_BLACK, COLOR_WHITE);   // Texto preto com fundo branco (selecionado)
    init_pair(COLOR_TITLE, COLOR_YELLOW, COLOR_BLUE);      // Título amarelo com fundo azul
}

// Função para desenhar bordas
void desenharBordas() {
    attron(COLOR_PAIR(COLOR_BORDER));
    for (int i = 0; i < COLS; i++) {
        mvprintw(0, i, "=");  // Borda superior
        mvprintw(LINES - 1, i, "=");  // Borda inferior
    }
    for (int i = 0; i < LINES; i++) {
        mvprintw(i, 0, "|");  // Borda esquerda
        mvprintw(i, COLS - 1, "|");  // Borda direita
    }
    attroff(COLOR_PAIR(COLOR_BORDER));
}

// Função para exibir o menu com navegação por setas
int exibirMenu() {
    const char *opcoes[] = {
        "1. Exibir cidades na arvore (Percursos)",
        "2. Exibir eventos de uma cidade",
        "3. Buscar evento em uma cidade",
        "4. Criar roteiro de viagem",
        "5. Cancelar evento",
        "6. Reinserir evento cancelado",
        "7. Escolher o algoritmo de ordenacao",
        "0. Sair"
    };
    int numOpcoes = sizeof(opcoes) / sizeof(opcoes[0]);
    int selecionado = 0;

    while (1) {
        clear();
        desenharBordas();

        // Título do menu
        attron(COLOR_PAIR(COLOR_TITLE));
        mvprintw(2, (COLS - 20) / 2, "=== Menu Principal ===");
        attroff(COLOR_PAIR(COLOR_TITLE));

        // Exibir opções do menu
        for (int i = 0; i < numOpcoes; i++) {
            if (i == selecionado) {
                attron(COLOR_PAIR(COLOR_SELECTED));
                mvprintw(4 + i, 4, "%s", opcoes[i]);
                attroff(COLOR_PAIR(COLOR_SELECTED));
            } else {
                attron(COLOR_PAIR(COLOR_MENU));
                mvprintw(4 + i, 4, "%s", opcoes[i]);
                attroff(COLOR_PAIR(COLOR_MENU));
            }
        }

        refresh();

        int tecla = getch();
        switch (tecla) {
            case KEY_UP:
                if (selecionado > 0) selecionado--;
                break;
            case KEY_DOWN:
                if (selecionado < numOpcoes - 1) selecionado++;
                break;
            case 10: // Enter
                return selecionado + 1; // Retorna a opção selecionada (1 a 8)
            default:
                break;
        }
    }
}

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    // Inicializa ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    iniciarCores(); // Inicializa cores

    srand(time(NULL));
    TArvoreBinaria arvore;
    arvore.raiz = NULL;

    // Criando e inserindo cidades na árvore
    for (int i = 0; i < TAM_CIDADES; i++) {
        GerarEventos(&cidades[i]);
        InserirCidade(&arvore.raiz, NULL, cidades[i]);
    }

    int opcao, cidadeId;
    char nomeEvento[TAM_NOME];
    float avaliacao;
    TCelula *cidadeEncontrada;

    do {
        opcao = exibirMenu(); // Exibe o menu e obtém a opção selecionada

        switch (opcao) {
            case 1: // Exibir percursos
                clear();
                printw("\nPercurso In-Ordem:\n");
                InOrdem(arvore.raiz);
                printw("\nPercurso Pre-Ordem:\n");
                PreOrdem(arvore.raiz);
                printw("\nPercurso Pos-Ordem:\n");
                PosOrdem(arvore.raiz);
                printw("\nPressione qualquer tecla para continuar...");
                refresh();
                getch();
                break;

            case 2: // Exibir eventos de uma cidade
                clear();
                printw("\nCidades disponíveis:\n");
                InOrdem(arvore.raiz);
                printw("Digite o ID da cidade: ");
                refresh();
                scanw("%d", &cidadeId);
                cidadeEncontrada = PesquisarCidade(arvore.raiz, cidadeId);
                if (cidadeEncontrada) {
                    ExibirEventos(&cidadeEncontrada->cidade);
                    ExibirMensagemEspecial();
                } else {
                    printw("Cidade não encontrada.\n");
                }
                refresh();
                getch();
                break;

            case 3: // Buscar evento em uma cidade
                clear();
                printw("\nCidades disponíveis:\n");
                InOrdem(arvore.raiz);
                printw("Digite o ID da cidade: ");
                refresh();
                scanw("%d", &cidadeId);
                getchar();
                printw("Digite o nome do evento: ");
                refresh();
                getstr(nomeEvento);
                printw("Digite a avaliação do evento: ");
                refresh();
                scanw("%f", &avaliacao);
                cidadeEncontrada = PesquisarCidade(arvore.raiz, cidadeId);
                if (cidadeEncontrada) {
                    BuscarEventos(&cidadeEncontrada->cidade, nomeEvento, avaliacao);
                    ExibirMensagemEspecial();
                } else {
                    printw("Cidade não encontrada.\n");
                }
                refresh();
                getch();
                break;

            case 4: // Criar roteiro de viagem
                clear();
                printw("\nEscolha o número de cidades para o roteiro:\n");
                printw("1 - Roteiro com 1 cidade\n");
                printw("2 - Roteiro com 2 cidades\n");
                refresh();
                int numCidadesRoteiro;
                scanw("%d", &numCidadesRoteiro);

                if (numCidadesRoteiro == 1 || numCidadesRoteiro == 2) {
                    TCelula *cidadesRoteiro[2];
                    int idsCidades[2];

                    for (int i = 0; i < numCidadesRoteiro; i++) {
                        clear();
                        printw("\nEscolha a cidade %d:\n", i + 1);
                        InOrdem(arvore.raiz);
                        printw("Digite o ID da cidade: ");
                        refresh();
                        scanw("%d", &idsCidades[i]);
                        cidadesRoteiro[i] = PesquisarCidade(arvore.raiz, idsCidades[i]);
                        if (cidadesRoteiro[i] == NULL) {
                            printw("Cidade não encontrada. Tente novamente.\n");
                            i--;
                            refresh();
                            getch();
                        }
                    }

                    clear();
                    printw("\nEscolha o tipo de eventos:\n");
                    printw("1 - Todos os eventos\n");
                    printw("2 - Apenas eventos com nota >= 8\n");
                    refresh();
                    int opcaoEventos;
                    scanw("%d", &opcaoEventos);

                    for (int i = 0; i < numCidadesRoteiro; i++) {
                        if (cidadesRoteiro[i] != NULL) {
                            clear();
                            printw("\nCidade: %s\n", cidadesRoteiro[i]->cidade.name);
                            OrdenarEventosPorHorario(cidadesRoteiro[i]->cidade.eventos, cidadesRoteiro[i]->cidade.num_eventos);
                            for (int j = 0; j < cidadesRoteiro[i]->cidade.num_eventos; j++) {
                                if (opcaoEventos == 1 || cidadesRoteiro[i]->cidade.eventos[j].avaliacao >= 8.0) {
                                    printw(" - %s | Avaliacao: %.1f | Horario: %s\n",
                                        cidadesRoteiro[i]->cidade.eventos[j].name,
                                        cidadesRoteiro[i]->cidade.eventos[j].avaliacao,
                                        cidadesRoteiro[i]->cidade.eventos[j].horario);
                                }
                            }
                            refresh();
                            getch();
                        }
                    }
                } else {
                    printw("Opção inválida.\n");
                    refresh();
                    getch();
                }
                break;

            case 5: // Cancelar evento
                clear();
                printw("\nCidades disponíveis:\n");
                InOrdem(arvore.raiz);
                printw("Digite o ID da cidade: ");
                refresh();
                scanw("%d", &cidadeId);
                getchar();
                printw("Digite o nome do evento a cancelar: ");
                refresh();
                getstr(nomeEvento);
                cidadeEncontrada = PesquisarCidade(arvore.raiz, cidadeId);
                if (cidadeEncontrada) {
                    CancelarEvento(&cidadeEncontrada->cidade, nomeEvento);
                    ExibirMensagemEspecial();
                } else {
                    printw("Cidade não encontrada.\n");
                }
                refresh();
                getch();
                break;

            case 6: // Reinserir evento cancelado
                clear();
                ReinserirEvento(arvore.raiz);
                ExibirMensagemEspecial();
                refresh();
                getch();
                break;

            case 7: // Escolher método de ordenação
                clear();
                printw("\nCidades disponíveis:\n");
                InOrdem(arvore.raiz);
                printw("\nDigite o ID da cidade: ");
                refresh();
                scanw("%d", &cidadeId);
                cidadeEncontrada = PesquisarCidade(arvore.raiz, cidadeId);
                if (cidadeEncontrada) {
                    TEvento eventosCopia[TAM_EVENTOS];
                    int n = cidadeEncontrada->cidade.num_eventos;
                    for (int i = 0; i < n; i++) {
                        eventosCopia[i] = cidadeEncontrada->cidade.eventos[i];
                    }

                    EscolherMetodoOrdenacao(eventosCopia, n);

                    clear();
                    printw("\nEventos ordenados (sem alterar os originais):\n");
                    for (int i = 0; i < n; i++) {
                        printw(" - %s | Avaliacao: %.1f | Horario: %s\n", eventosCopia[i].name, eventosCopia[i].avaliacao, eventosCopia[i].horario);
                    }
                    ExibirMensagemEspecial();
                } else {
                    printw("Cidade não encontrada.\n");
                }
                refresh();
                getch();
                break;

            case 8: // Sair
                clear();
                printw("Encerrando programa...\n");
                refresh();
                break;

            default:
                clear();
                printw("Opção inválida!\n");
                refresh();
                getch();
                break;
        }
    } while (opcao != 8);

    // Finaliza ncurses
    endwin();
    return 0;
}
