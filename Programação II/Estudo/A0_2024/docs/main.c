#include <stdlib.h>
#include <stdio.h>





typedef struct teddy_machine 
{
    unsigned int id;
    unsigned int probability;

    struct teddy_machine *next;
    struct teddy_machine *previous;
} teddy_machine;





// Função para criar uma lista duplamente encadeada circular
teddy_machine* create_list(unsigned int machines) 
{
    // Se não tem máquinas, retorna NULL
    if (machines == 0) return NULL;

    // Passo 1: Criar o primeiro nó (cabeça da lista)
    teddy_machine *lista = (teddy_machine*) malloc(sizeof(teddy_machine));
    if (!lista) return NULL; // Verifica se a alocação foi bem-sucedida

    lista->id = machines;   // Define o ID como o número total de máquinas
    lista->probability = 5; // Define a probabilidade inicial
    lista->next = NULL;     
    lista->previous = NULL;

    teddy_machine *atual = lista; // Ponteiro auxiliar para percorrer a lista

    // Passo 2: Criar os demais nós e encadeá-los
    for (unsigned int i = machines - 1; i > 0; i--) 
    {
        // Aloca espaço para a nova máquina
        teddy_machine *novo_nodo = (teddy_machine*) malloc(sizeof(teddy_machine));

        // Se não conseguiu alocar, libera a lista e retorna NULL
        if (!novo_nodo) 
            return NULL;

        // Define os valores do novo nó
        novo_nodo->id = i;
        novo_nodo->probability = 5;
        novo_nodo->next = atual;  // O próximo do novo nó é o nó atual
        novo_nodo->previous = NULL; // O anterior ainda não está definido

        atual->previous = novo_nodo; // O nó atual aponta para o novo nó como anterior
        atual = novo_nodo; // Atualiza o ponteiro para o novo nó
    }

    // Passo 3: Fechar a lista em forma de círculo
    atual->previous = lista; // O primeiro nó criado aponta para a cabeça da lista
    lista->next = atual;     // A cabeça da lista aponta para o primeiro nó criado

    return atual; // Retorna o primeiro nó da lista
}





teddy_machine* select_machine(teddy_machine *list, unsigned int place) 
{
    if (!list) return NULL;
    
    teddy_machine *selection = list;
    for (unsigned int i = 0; i < place; i++) 
    {
        if (!selection->next) 
            return NULL;  // Evita acessar um ponteiro inválido
        selection = selection->next;
    }
    
    return selection;
}





teddy_machine* remove_machine(teddy_machine *list, teddy_machine *remove) 
{
    if (!list || !remove) return NULL;

    // Se for o único nó na lista
    if (remove == list && remove->next == list) 
    {
        free(remove);
        return NULL;
    }

    // Atualiza a lista se o nó removido for a cabeça
    if (remove == list) 
        list = remove->next;

    // Ajusta os ponteiros dos nós vizinhos
    remove->next->previous = remove->previous;
    remove->previous->next = remove->next;

    free(remove);
    return list;
}




void destroy_list (teddy_machine *list)
{
    while ((list = remove_machine(list, list)));
}





unsigned int get_place(unsigned int machines)
{
    return rand() % machines;
}

unsigned int get_attempt()
{
    return rand() % 100 + 1;
}

/* Printing functions */

void print_attempt(teddy_machine *machine, unsigned int attempt)
{

    if (attempt <= machine->probability) 
        printf("O URSO DA MAQUINA %u [FOI] OBTIDO!\n", machine->id);
    else 
        printf("O URSO DA MAQUINA %u [NAO FOI] OBTIDO!\n", machine->id);
}

void print_available_machines(teddy_machine *list)
{

    if (!list) 
        printf("NAO HA MAQUINAS DISPONIVEIS!\n");
    else
        {
        teddy_machine *i = list;
        do 
        {
            printf("PROBABILIDADE DA MAQUINA %u: %u\n", i->id, i->probability);
            i = (teddy_machine*) i->next;
        } while((i) && (i != list));
    }

}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("USO: main [NR. DE MAQUINAS] [NR. DE RODADAS] [SEMENTE DE RAND.]\n");
        return -1;
    }

    unsigned int machines = atoi(argv[1]);
    unsigned int rounds = atoi(argv[2]);
    unsigned int seed = atoi(argv[3]);

    if (!machines || !rounds || !seed) {
        printf("USO: main [NR. DE MAQUINAS] [NR. DE RODADAS] [SEMENTE DE RAND.]\n");
        return (!machines) ? -2 : (!rounds) ? -3 : -4;
    }

    teddy_machine *list = create_list(machines);
    printf("seed: %d\n", seed);
    srand(seed);

    for (unsigned int r = 0; r < rounds; r++) {
        unsigned int machine_place = get_place(machines); // Define a localização da máquina da rodada
        unsigned int machine_attempt = get_attempt(); // Define a tentativa da rodada

        teddy_machine *round_machine = select_machine(list, machine_place);
        if (!round_machine) break;

        printf("\n============================ ROUND %u ============================\n", r + 1);
        print_attempt(round_machine, machine_attempt);

        if (round_machine->probability > machine_attempt) {
            list = remove_machine(list, round_machine);
        } else {
            round_machine->probability += 2;
        }

        print_available_machines(list);
        printf("==================================================================\n");
    }

    destroy_list(list);
    return 0;
}