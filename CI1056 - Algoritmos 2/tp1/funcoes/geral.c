int contagemTrocas = 0;      // Variável global para contar trocas
int contagemComparacoes = 0; // Variável global para contar comparações



/*===========================================================================================================*/

// Inicializa a semente com o tempo atual
void inicializaAleatorio() {
    srand(time(NULL));
}


/*===========================================================================================================*/


// Preenche um vetor de inteiros com valores aleatórios entre 0 e 2048
void geraVetor(int vetor[]) 
{
    for (int i = 0; i < TAM; i++) {
        vetor[i] = rand() % (MAX_VAL + 1); // Gera números aleatórios entre 0 e 2048
    }
}


/*===========================================================================================================*/



// Função para imprimir uma linha de separação
void linhaSeparacao() {
    printf("\n");
    printf("______________________________________________________________________________________");
    printf("\n");
    printf("\n");
}



/*===========================================================================================================*/




// Imprime um vetor de inteiros
void imprimeVetor(int vetor[], int n) 
{
    if (n > TAM)
        n = TAM;  // Limita a impressão ao tamanho máximo do vetor

    for (int i = 0; i < n; i++)
        printf("%d ", vetor[i]);

    printf("\n");
}


/*===========================================================================================================*/


//                                              MENU INTERATIVO


void menu (int v[], int opcao, char []) 
{
    int subOpcao;
    char resposta[1];

    printf("\n");
    printf("Bem vindo ao Trabalho Prático da disciplina de Algoritmos II!\n");
    printf("Aqui você verá a implementação de algoritmos de ordenação e busca.\n");
    printf("\n");
    printf("Logo abaixo, selecione a operação desejada:\n");
    printf("\n");

    printf("0. Sair\n");
    printf("1. Ordenação\n");
    printf("2. Busca\n");
    printf("\n");

    scanf("%d", &opcao);

    while (opcao != 0)
    {
        if (opcao == 1)
        {
            printf("Você escolheu a opção de ordenação.\n");
            printf("Aqui você poderá escolher entre os algoritmos de ordenação disponíveis:\n");
            printf("\n");
            printf("1. QuickSort - Pivô Último Elemento\n");
            printf("2. QuickSort - Pivô Mediana de Três\n");
            printf("3. Shell Sort - Espaçamento com Sequência de Hibbard\n");
            printf("4. Shell Sort - Espaçamento com Sequência de Knuth\n");
            printf("5. Selection Sort\n");
            printf("6. Voltar\n");
            scanf("%d", &subOpcao);

            if (subOpcao == 1)
            {
                printf("Você escolheu o QuickSort com o último elemento como pivô.\n");
                printf("Deseja gerar um vetor? (s/n) \n");
                printf("\n");
                scanf("%1s", resposta);
                if (strcmp(resposta, "s") == 0)
                {
                    int v[TAM];
                    geraVetor(v);
                    printf("Vetor gerado com sucesso!\n");
                    printf("Digite o tamanho do vetor que deseja visualizar: ");
                    scanf("%d", &subOpcao);
                    imprimeVetor(v, subOpcao);
                    printf("\n");

                    printf("Selecione a opção desejada:\n");
                    printf("1. Ordenar o vetor 1 vez.\n");
                    printf("2. Ordenar o vetor 1000 vezes.\n");
                    printf("3. Ordenar o vetor N vezes.\n");
                    printf("4. Voltar\n");

                    scanf("%d", &subOpcao);

                    if(subOpcao == 1)
                    {
                        printf("Ordenando o vetor 1 vez...\n");
                        printf("Vetor após a ordenação com último elemento como pivô\n");
                        printf("Digite o tamanho do vetor que deseja visualizar: ");
                        scanf("%d", &subOpcao);
                        imprimeVetor(v, subOpcao);
                    }

                    else if(subOpcao == 2)
                    {
                        printf("Ordenando o vetor 1000 vezes...\n");

                        while (subOpcao < 1000)
                        {
                            //quickSortUltimo();
                            subOpcao++;
                        }
                        printf("Vetor após a ordenação com último elemento como pivô\n");
                        printf("Digite o tamanho do vetor que deseja visualizar: ");
                        scanf("%d", &subOpcao);
                        imprimeVetor(v, subOpcao);
                    }

                    else if(subOpcao == 3)
                    {
                        int i = 0;
                        printf("Digite o número de vezes que deseja ordenar o vetor: ");
                        scanf("%d", &subOpcao);
                        printf("Ordenando o vetor %d vezes...\n", subOpcao);

                        while (i < subOpcao)
                        {
                            //quickSortUltimo();
                            i++;
                        }
                        printf("Vetor após a ordenação com último elemento como pivô\n");
                        printf("Digite o tamanho do vetor que deseja visualizar: ");
                        scanf("%d", &subOpcao);
                        imprimeVetor(v, subOpcao);
                    }

                    else if(subOpcao == 4)
                    {
                        printf("Voltando...\n");
                    }

                    else
                    {
                        printf("Opção inválida!\n");
                    }

                    printf("Ordenando o vetor...\n");
                    printf("Vetor após a ordenação com último elemento como pivô\n");
                    printf("Digite o tamanho do vetor que deseja visualizar: ");
                    scanf("%d", &subOpcao);
                    imprimeVetor(v, subOpcao);
                    
                }
            }
            
            else if(subOpcao == 2)
            {
                printf("Você escolheu o QuickSort com a mediana de três como pivô.\n");
                printf("Deseja gerar um vetor? (s/n) \n");
                printf("\n");
                scanf("%1s", resposta);
                if (strcmp(resposta, "s") == 0)
                {
                    int v[TAM];
                    geraVetor(v);
                    printf("Vetor gerado com sucesso!\n");
                    printf("Digite o tamanho do vetor que deseja visualizar: ");
                    scanf("%d", &subOpcao);
                    imprimeVetor(v, subOpcao);
                    printf("\n");

                    printf("Selecione a opção desejada:\n");
                    printf("1. Ordenar o vetor 1 vez.\n");
                    printf("2. Ordenar o vetor 1000 vezes.\n");
                    printf("3. Ordenar o vetor N vezes.\n");
                    printf("4. Voltar\n");

                    scanf("%d", &subOpcao);

                    if(subOpcao == 1)
                    {
                        printf("Ordenando o vetor 1 vez...\n");
                        printf("Vetor após a ordenação com mediana de três\n");
                        printf("Digite o tamanho do vetor que deseja visualizar: ");
                        scanf("%d", &subOpcao);
                        imprimeVetor(v, subOpcao);
                    }

                    else if(subOpcao == 2)
                    {
                        printf("Ordenando o vetor 1000 vezes...\n");

                        while (subOpcao < 1000)
                        {
                            //quickSortMediana();
                            subOpcao++;
                        }
                        printf("Vetor após a ordenação com mediana de três\n");
                        printf("Digite o tamanho do vetor que deseja visualizar: ");
                        scanf("%d", &subOpcao);
                        imprimeVetor(v, subOpcao);
                    }

                    else if(subOpcao == 3)
                    {
                        int i = 0;
                        printf("Digite o número de vezes que deseja ordenar o vetor: ");
                        scanf("%d", &subOpcao);
                        printf("Ordenando o vetor %d vezes...\n", subOpcao);

                        while (i < subOpcao)
                        {
                            //quickSortMediana();
                            i++;
                        }
                        printf("Vetor após a ordenação com mediana de três\n");
                        printf("Digite o tamanho do vetor que deseja visualizar: ");
                        scanf("%d", &subOpcao);
                        imprimeVetor(v, subOpcao);
                    }

                    else if(subOpcao == 4)
                    {
                        printf("Voltando...\n");
                    }

                    else
                    {
                        printf("Opção inválida!\n");
                    }
                }
            }

            else if(subOpcao == 3)
            {
                printf("Você escolheu o Shell Sort com a sequência de Hibbard.\n");
                printf("Deseja gerar um vetor? (s/n) \n");
                printf("\n");
                scanf("%1s", resposta);
                if (strcmp(resposta, "s") == 0)
                {
                    int v[TAM];
                    geraVetor(v);
                    printf("Vetor gerado com sucesso!\n");
                    printf("Digite o tamanho do vetor que deseja visualizar: ");
                    scanf("%d", &subOpcao);
                    imprimeVetor(v, subOpcao);
                    printf("\n");

                    printf("Selecione a opção desejada:\n");
                    printf("1. Ordenar o vetor 1 vez.\n");
                    printf("2. Ordenar o vetor 1000 vezes.\n");
                    printf("3. Ordenar o vetor N vezes.\n");
                    printf("4. Voltar\n");

                    scanf("%d", &subOpcao);

                    if(subOpcao == 1)
                    {
                        printf("Ordenando o vetor 1 vez...\n");
                        printf("Vetor após a ordenação com sequência de Hibbard\n");
                        printf("Digite o tamanho do vetor que deseja visualizar: ");
                        scanf("%d", &subOpcao);
                        imprimeVetor(v, subOpcao);
                    }

                    else if(subOpcao == 2)
                    {
                        printf("Ordenando o vetor 1000 vezes...\n");

                        while (subOpcao < 1000)
                        {
                            //shellSortHibbard();
                            subOpcao++;
                        }
                        printf("Vetor após a ordenação com sequência de Hibbard\n");
                        printf("Digite o tamanho do vetor que deseja visualizar: ");
                        scanf("%d", &subOpcao);
                        imprimeVetor(v, subOpcao);
                    }

                    else if(subOpcao == 3)
                    {
                        int i = 0;
                        printf("Digite o número de vezes que deseja ordenar o vetor: ");
                        scanf("%d", &subOpcao);
                        printf("Ordenando o vetor %d vezes...\n", subOpcao);

                        while (i < subOpcao)
                        {
                            //shellSortHibbard();
                            i++;
                        }
                        printf("Vetor após a ordenação com sequência de Hibbard\n");
                        printf("Digite o tamanho do vetor que deseja visualizar: ");
                        scanf("%d", &subOpcao);
                        imprimeVetor(v, subOpcao);
                    }

                    else if(subOpcao == 4)
                    {
                        printf("Voltando...\n");
                    }

                    else
                    {
                        printf("Opção inválida!\n");
                    }
                    
                }
            }

            else if(subOpcao == 4)
            {
                printf("Você escolheu o Shell Sort com a sequência de Knuth.\n");
                printf("Deseja gerar um vetor? (s/n) \n");
                printf("\n");
                scanf("%1s", resposta);
                if (strcmp(resposta, "s") == 0)
                {
                    int v[TAM];
                    geraVetor(v);
                    printf("Vetor gerado com sucesso!\n");
                    printf("Digite o tamanho do vetor que deseja visualizar: ");
                    scanf("%d", &subOpcao);
                    imprimeVetor(v, subOpcao);
                    printf("\n");

                    printf("Selecione a opção desejada:\n");
                    printf("1. Ordenar o vetor 1 vez.\n");
                    printf("2. Ordenar o vetor 1000 vezes.\n");
                    printf("3. Ordenar o vetor N vezes.\n");
                    printf("4. Voltar\n");

                    scanf("%d", &subOpcao);

                    if(subOpcao == 1)
                    {
                        printf("Ordenando o vetor 1 vez...\n");
                        printf("Vetor após a ordenação com sequência de Knuth\n");
                        printf("Digite o tamanho do vetor que deseja visualizar: ");
                        scanf("%d", &subOpcao);
                        imprimeVetor(v, subOpcao);
                    }

                    else if(subOpcao == 2)
                    {
                        printf("Ordenando o vetor 1000 vezes...\n");

                        while (subOpcao < 1000)
                        {
                            //shellSortKnuth();
                            subOpcao++;
                        }
                        printf("Vetor após a ordenação com sequência de Knuth\n");
                        printf("Digite o tamanho do vetor que deseja visualizar: ");
                        scanf("%d", &subOpcao);
                        imprimeVetor(v, subOpcao);
                    }

                    else if(subOpcao == 3)
                    {
                        int i = 0;
                        printf("Digite o número de vezes que deseja ordenar o vetor: ");
                        scanf("%d", &subOpcao);
                        printf("Ordenando o vetor %d vezes...\n", subOpcao);

                        while (i < subOpcao)
                        {
                            //shellSortKnuth();
                            i++;
                        }
                        printf("Vetor após a ordenação com sequência de Knuth\n");
                        printf("Digite o tamanho do vetor que deseja visualizar: ");
                        scanf("%d", &subOpcao);
                        imprimeVetor(v, subOpcao);
                    }

                    else if(subOpcao == 4)
                    {
                        printf("Voltando...\n");
                    }

                    else
                    {
                        printf("Opção inválida!\n");
                    }
                    
                }
            }

            else if(subOpcao == 5)
            {
                printf("Você escolheu o Selection Sort.\n");
                printf("Deseja gerar um vetor? (s/n) \n");
                printf("\n");
                scanf("%1s", resposta);
                if (strcmp(resposta, "s") == 0)
                {
                    int v[TAM];
                    geraVetor(v);
                    printf("Vetor gerado com sucesso!\n");
                    printf("Digite o tamanho do vetor que deseja visualizar: ");
                    scanf("%d", &subOpcao);
                    imprimeVetor(v, subOpcao);
                    printf("\n");

                    printf("Selecione a opção desejada:\n");
                    printf("1. Ordenar o vetor 1 vez.\n");
                    printf("2. Ordenar o vetor 1000 vezes.\n");
                    printf("3. Ordenar o vetor N vezes.\n");
                    printf("4. Voltar\n");

                    scanf("%d", &subOpcao);

                    if(subOpcao == 1)
                    {
                        printf("Ordenando o vetor 1 vez...\n");
                        printf("Vetor após a ordenação com selection sort\n");
                        printf("Digite o tamanho do vetor que deseja visualizar: ");
                        scanf("%d", &subOpcao);
                        imprimeVetor(v, subOpcao);
                    }

                    else if(subOpcao == 2)
                    {
                        printf("Ordenando o vetor 1000 vezes...\n");

                        while (subOpcao < 1000)
                        {
                            //selectionSort();
                            subOpcao++;
                        }
                        printf("Vetor após a ordenação com selection sort\n");
                        printf("Digite o tamanho do vetor que deseja visualizar: ");
                        scanf("%d", &subOpcao);
                        imprimeVetor(v, subOpcao);
                    }

                    else if(subOpcao == 3)
                    {
                        int i = 0;
                        printf("Digite o número de vezes que deseja ordenar o vetor: ");
                        scanf("%d", &subOpcao);
                        printf("Ordenando o vetor %d vezes...\n", subOpcao);

                        while (i < subOpcao)
                        {
                            //selectionSort();
                            i++;
                        }
                        printf("Vetor após a ordenação com selection sort\n");
                        printf("Digite o tamanho do vetor que deseja visualizar: ");
                        scanf("%d", &subOpcao);
                        imprimeVetor(v, subOpcao);
                    }

                    else if(subOpcao == 4)
                    {
                        printf("Voltando...\n");
                    }

                    else
                    {
                        printf("Opção inválida!\n");
                    }
                    
                }
            }

            else if(subOpcao == 6)
            {
                printf("Voltando ao menu principal...\n");
            }

            else
            {
                printf("Opção inválida!\n");
            }
        }


        else if(opcao == 2)
        {
            printf("Você escolheu a opção de busca.\n");
            printf("Aqui você poderá escolher entre os algoritmos de busca disponíveis:\n");
            printf("\n");
            printf("1. Busca Sequencial\n");
            printf("2. Busca Binária\n");
            printf("3. Voltar\n");

            scanf("%d", &subOpcao);

            if(subOpcao == 1)
            {
                printf("Você escolheu a busca sequencial.\n");
                printf("Deseja gerar um vetor? (s/n) \n");
                printf("\n");
                scanf("%1s", resposta);
                if (strcmp(resposta, "s") == 0)
                {
                    int v[TAM];
                    geraVetor(v);
                    printf("Vetor gerado com sucesso!\n");
                    printf("Digite o tamanho do vetor que deseja visualizar: ");
                    scanf("%d", &subOpcao);
                    imprimeVetor(v, subOpcao);
                    printf("\n");

                    printf("Selecione a opção desejada:\n");
                    printf("1. Digitar um número para busca\n");
                    printf("2. Gerar um número aleatório para busca\n");

                    scanf("%d", &subOpcao);

                    if(subOpcao == 1)
                    {
                        printf("Selecione a opção desejada:\n");
                        printf("1. Buscar pelo número 1 vez.\n");
                        printf("2. Buscar pelo número 1000 vezes.\n");
                        printf("3. Buscar pelo número N vezes.\n");
                        printf("4. Voltar\n");

                        scanf("%d", &subOpcao);

                        if(subOpcao == 1)
                        {
                            printf("Digite o número que deseja buscar: ");
                            scanf("%d", &subOpcao);
                            printf("Realizando a busca sequencial...\n");
                            printf("Elemento encontrado na posição: %d\n", subOpcao);
                        }

                        else if(subOpcao == 2)
                        {
                            printf("Buscando pelo número 1000 vezes...\n");
                            printf("Digite o número que deseja buscar: ");
                            scanf("%d", &subOpcao);
                            printf("Realizando a busca sequencial...\n");

                            while (subOpcao < 1000)
                            {
                                //buscaSequencial();
                                printf("Elemento encontrado na posição: %d\n", subOpcao);
                                subOpcao++;
                            }
                        }

                        else if(subOpcao == 3)
                        {
                            int i = 0;
                            printf("Digite o número de vezes que deseja buscar pelo número: ");
                            scanf("%d", &subOpcao);
                            printf("Buscando pelo número %d vezes...\n", subOpcao);

                            while (i < subOpcao)
                            {
                                //buscaSequencial();
                                printf("Elemento encontrado na posição: %d\n", subOpcao);
                                i++;
                            }
                        }

                        else if(subOpcao == 4)
                        {
                            printf("Voltando...\n");
                        }
                        
                        else
                        {
                            printf("Opção inválida!\n");
                        }
                    }

                    else if(subOpcao == 2)
                    {
                        printf("Selecione a opção desejada:\n");
                        printf("1. Buscar pelo número 1 vez.\n");
                        printf("2. Buscar pelo número 1000 vezes.\n");
                        printf("3. Buscar pelo número N vezes.\n");
                        printf("4. Voltar\n");

                        scanf("%d", &subOpcao);

                        if(subOpcao == 1)
                        {
                            subOpcao = geraAleatorio();
                            printf("Número gerado aleatoriamente para busca: %d\n", subOpcao);
                            printf("Realizando a busca sequencial 1 vez...\n");
                            printf("Elemento encontrado na posição: %d\n", subOpcao);
                        }

                        else if(subOpcao == 2)
                        {
                            printf("Buscando pelo número 1000 vezes...\n");
                            subOpcao = geraAleatorio();
                            printf("Número gerado aleatoriamente para busca: %d\n", subOpcao);
                            printf("Realizando a busca sequencial...\n");

                            while (subOpcao < 1000)
                            {
                                //buscaSequencial();
                                printf("Elemento encontrado na posição: %d\n", subOpcao);
                                subOpcao++;
                            }
                        }

                        else if(subOpcao == 3)
                        {
                            int i = 0;
                            subOpcao = geraAleatorio();
                            printf("Número gerado aleatoriamente para busca: %d\n", subOpcao);
                            printf("Buscando pelo número %d vezes...\n", subOpcao);

                            while (i < subOpcao)
                            {
                                //buscaSequencial();
                                printf("Elemento encontrado na posição: %d\n", subOpcao);
                                i++;
                            }
                        }

                        else if(subOpcao == 4)
                        {
                            printf("Voltando...\n");
                        }
                        
                        else
                        {
                            printf("Opção inválida!\n");
                        }
                    }

                    else
                    {
                        printf("Opção inválida!\n");
                    }
                }
            }

            else if(subOpcao == 2)
            {
                printf("Você escolheu a busca binária.\n");
                printf("Deseja gerar um vetor? (s/n) \n");
                printf("\n");
                scanf("%1s", resposta);
                if (strcmp(resposta, "s") == 0)
                {
                    int v[TAM];
                    geraVetor(v);
                    printf("Vetor gerado com sucesso!\n");
                    printf("Digite o tamanho do vetor que deseja visualizar: ");
                    scanf("%d", &subOpcao);
                    imprimeVetor(v, subOpcao);
                    printf("\n");

                    printf("Selecione a opção desejada:\n");
                    printf("1. Digitar um número para busca\n");
                    printf("2. Gerar um número aleatório para busca\n");

                    scanf("%d", &subOpcao);

                    if(subOpcao == 1)
                    {
                        printf("Selecione a opção desejada:\n");
                        printf("1. Buscar pelo número 1 vez.\n");
                        printf("2. Buscar pelo número 1000 vezes.\n");
                        printf("3. Buscar pelo número N vezes.\n");
                        printf("4. Voltar\n");

                        scanf("%d", &subOpcao);

                        if(subOpcao == 1)
                        {
                            printf("Digite o número que deseja buscar: ");
                            scanf("%d", &subOpcao);
                            printf("Realizando a busca binária...\n");
                            printf("Elemento encontrado na posição: %d\n", subOpcao);
                        }

                        else if(subOpcao == 2)
                        {
                            printf("Buscando pelo número 1000 vezes...\n");
                            printf("Digite o número que deseja buscar: ");
                            scanf("%d", &subOpcao);
                            printf("Realizando a busca binária...\n");

                            while (subOpcao < 1000)
                            {
                                //buscaBinaria();
                                printf("Elemento encontrado na posição: %d\n", subOpcao);
                                subOpcao++;
                            }
                        }

                        else if(subOpcao == 3)
                        {
                            int i = 0;
                            printf("Digite o número de vezes que deseja buscar pelo número: ");
                            scanf("%d", &subOpcao);
                            printf("Buscando pelo número %d vezes...\n", subOpcao);

                            while (i < subOpcao)
                            {
                                //buscaBinaria();
                                printf("Elemento encontrado na posição: %d\n", subOpcao);
                                i++;
                            }
                        }

                        else if(subOpcao == 4)
                        {
                            printf("Voltando...\n");
                        }
                        
                        else
                        {
                            printf("Opção inválida!\n");
                        }
                    }

                    else if(subOpcao == 2)
                    {
                        printf("Selecione a opção desejada:\n");
                        printf("1. Buscar pelo número 1 vez.\n");
                        printf("2. Buscar pelo número 1000 vezes.\n");
                        printf("3. Buscar pelo número N vezes.\n");
                        printf("4. Voltar\n");

                        scanf("%d", &subOpcao);

                        if(subOpcao == 1)
                        {
                            subOpcao = geraAleatorio();
                            printf("Número gerado aleatoriamente para busca: %d\n", subOpcao);
                            printf("Realizando a busca binária 1 vez...\n");
                            printf("Elemento encontrado na posição: %d\n", subOpcao);
                        }

                        else if(subOpcao == 2)
                        {
                            printf("Buscando pelo número 1000 vezes...\n");
                            subOpcao = geraAleatorio();
                            printf("Número gerado aleatoriamente para busca: %d\n", subOpcao);
                            printf("Realizando a busca binária...\n");

                            while (subOpcao < 1000)
                            {
                                //buscaBinaria();
                                printf("Elemento encontrado na posição: %d\n", subOpcao);
                                subOpcao++;
                            }
                        }

                        else if(subOpcao == 3)
                        {
                            int i = 0;
                            subOpcao = geraAleatorio();
                            printf("Número gerado aleatoriamente para busca: %d\n", subOpcao);
                            printf("Buscando pelo número %d vezes...\n", subOpcao);

                            while (i < subOpcao)
                            {
                                //buscaBinaria();
                                printf("Elemento encontrado na posição: %d\n", subOpcao);
                                i++;
                            }
                        }

                        else if(subOpcao == 4)
                        {
                            printf("Voltando...\n");
                        }
                        
                        else
                        {
                            printf("Opção inválida!\n");
                        }
                    }

                    else if(subOpcao == 3)
                    {
                        printf("Voltando ao menu principal...\n");
                    }

                    else
                    {
                        printf("Opção inválida!\n");
                    }
                }
            }
        }


        else
        {
            printf("Opção inválida!\n");
        }

        printf("\n");
        printf("Selecione alguma opção:\n");
        printf("0. Sair\n");
        printf("1. Ordenação\n");
        printf("2. Busca\n");
        scanf("%d", &opcao);
    }
}


/*===========================================================================================================*/


// Troca o conteúdo de duas variáveis
void trocar(int *a, int *b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
    contagemTrocas++;
}


/*==========================================================================================================================*/


void exibirContagens(char *metodo) {
    printf("\n[%s] Contagem de trocas: %d\n", metodo, contagemTrocas);
    printf("[%s] Contagem de comparações: %d\n", metodo, contagemComparacoes);
}