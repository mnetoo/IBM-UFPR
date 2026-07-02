#include <stdio.h>
#include <string.h>

#define TAM 5

//declarei o novo tipo aluno_t
struct aluno_t
{
    char nome[100];
    short idade;
    short GRR;
    char curso[100];
};

//refefine o nome da struct
typedef struct aluno_t aluno_t;


// declarei vetor alunos do tipo struct (aluno_t)
aluno_t alunos[TAM] ;

//carrega vetor com as informaçoes
void leVetorAlunos(aluno_t alunos[]) 
{
    for (int i = 0; i < TAM; i++) 
    {
        printf("Nome: ");
        fgets(alunos[i].nome, sizeof(alunos[i].nome), stdin);
        alunos[i].nome[strcspn(alunos[i].nome, "\n")] = '\0';

        printf("Idade: ");
        scanf("%hd", &alunos[i].idade);
        getchar(); // Consome o '\n' após o scanf

        printf("GRR: ");
        scanf("%hd", &alunos[i].GRR);
        getchar(); // Consome o '\n' após o scanf

        printf("Curso: ");
        fgets(alunos[i].curso, sizeof(alunos[i].curso), stdin);
        alunos[i].curso[strcspn(alunos[i].curso, "\n")] = '\0';
        printf("------------------------------\n");
    }
}

//imprime todo os alunos
void imprimeVetorAlunos (aluno_t alunos[])
{
    printf("\n");
    printf("\n");
    printf("Alunos:\n");
    printf("\n");
    for(int i = 0; i < TAM; i++)
    {
        printf("Nome: %s\n", alunos[i].nome);
        printf("Idade: %hd\n", alunos[i].idade);
        printf("GRR: %hd\n", alunos[i].GRR);
        printf("Curso: %s\n", alunos[i].curso);
        printf("------------------------------\n");
    }
}

//imprime todos os alunos em forma de relacao
void imprimeRelacaoAlunos (aluno_t alunos[])
{
    printf("\n");
    printf("\n");
    printf("Relação de Alunos:\n");
    printf("\n");
    for(int i = 0; i < TAM; i++)
    {
        printf("Aluno %d: Nome: %s\n", i + 1, alunos[i].nome);
        printf("         Idade: %hd  \n", alunos[i].idade);
        printf("         GRR: %hd  \n", alunos[i].GRR);
        printf("         Curso: %s\n", alunos[i].curso);
        printf("------------------------------------------------\n");
    }
}

//imprime os alunos maios que 22 anos
void imprimeAlunosMaior (aluno_t alunos[])
{
    printf("\n");
    printf("\n");
    printf("Alunos com idade acima de 22 anos:\n");
    printf("\n");
    for(int i = 0; i < TAM; i++)
    {
        if(alunos[i]. idade > 22)
        {
            printf("Nome: %s\n", alunos[i].nome);
            printf("Idade: %hd\n", alunos[i].idade);
            printf("GRR: %hd\n", alunos[i].GRR);
            printf("Curso: %s\n", alunos[i].curso);
            printf("------------------------------\n");
        }
    }
}

void ordenaAlunosIdade(aluno_t alunos[])
{
    aluno_t auxiliar;

    for(int j = 0; j < TAM - 1; j++)
    {
        for(int h = 0; h < TAM - j - 1; h++)
        {
                if (alunos[h].idade > alunos[h + 1].idade)
                {
                        auxiliar = alunos[h];
                        alunos[h] = alunos[h + 1];
                        alunos[h + 1] = auxiliar;
                }
        }
    }
}

void imprimeVetor_OrdenadoIdade (aluno_t alunos[])
{
    printf("\n");
    printf("\n");
    printf("Alunos ordenados por idade:\n");
    printf("\n");
    for(int i = 0; i < TAM; i++)
    {
        printf("Nome: %s\n", alunos[i].nome);
        printf("Idade: %hd\n", alunos[i].idade);
        printf("GRR: %hd\n", alunos[i].GRR);
        printf("Curso: %s\n", alunos[i].curso);
        printf("------------------------------\n");
    }
}

int comparaNomes(const char *nome1, const char *nome2)
{
    return strcmp(nome1, nome2);
}

void ordenaAlunosPorNome(aluno_t alunos[]) 
{
    aluno_t auxiliar;
    for(int j = 0; j < TAM - 1; j++) 
    {
        for(int h = 0; h < TAM - j - 1; h++) 
        {
            if (comparaNomes(alunos[h].nome, alunos[h + 1].nome) > 0) 
            {
                auxiliar = alunos[h];
                alunos[h] = alunos[h + 1];
                alunos[h + 1] = auxiliar;
            }
        }
    }
}

void imprimeVetor_OrdenadoNome (aluno_t alunos[])
{
    printf("\n");
    printf("\n");
    printf("Alunos ordenados por ordem alfabética:\n");
    printf("\n");
    for(int i = 0; i < TAM; i++)
    {
        printf("Nome: %s\n", alunos[i].nome);
        printf("Idade: %hd\n", alunos[i].idade);
        printf("GRR: %hd\n", alunos[i].GRR);
        printf("Curso: %s\n", alunos[i].curso);
        printf("------------------------------\n");
    }
}

void program (aluno_t alunos[])
{
    leVetorAlunos(alunos);
    imprimeVetorAlunos(alunos);
    imprimeRelacaoAlunos(alunos);
    imprimeAlunosMaior(alunos);
    ordenaAlunosIdade(alunos);
    imprimeVetor_OrdenadoIdade(alunos);
    ordenaAlunosPorNome(alunos);
    imprimeVetor_OrdenadoNome(alunos);
}

int main ()
{
    program(alunos);
    return 0;
}