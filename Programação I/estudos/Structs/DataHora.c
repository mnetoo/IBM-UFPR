#include <stdio.h>
#include <string.h>

struct data_t
{
    short dia;
    short mes;
    short ano;
};

typedef struct data_t data_t;

struct hora_t
{
    short hora;
    short minuto;
    short segundo;
};

typedef struct hora_t hora_t;

struct datahora_t
{
    data_t data;
    hora_t hora;
};

typedef struct datahora_t datahora_t;

void lerData(data_t *data) // por referência 
{
    printf("\nDigite o dia: ");
    scanf("%hd", &data->dia); //(armazena no campo dia de data_t)
    printf("Digite o mês: ");
    scanf("%hd", &data->mes); //(armazena no campo mes de data_t)
    printf("Digite o ano: ");
    scanf("%hd", &data->ano); //(armazena no campo ano de data_t)
    printf("\n");
}

void lerHora(hora_t *hora) // por referência
{
    printf("Digite as horas: ");
    scanf("%hd", &hora->hora);  //(armazena no campo horas de hora_t)
    printf("Digite os minutos: ");
    scanf("%hd", &hora->minuto);  //(armazena no campo minutos de hora_t)
    printf("Digite os segundos: ");
    scanf("%hd", &hora->segundo);  //(armazena no campo segundos de hora_t)
    printf("\n");
}

void lerDataHora(datahora_t *datahora) // por referência
{
    printf("Digite a data");
    lerData(&datahora->data);  // chama a função lerData (armazena no campo data de datahora_t)
    printf("\n");
    printf("Digite a hora\n");
    lerHora(&datahora->hora);  // chama a função lerHora (armazena no campo hora de datahora_t)
    printf("\n");
}

void imprimeData(data_t data)
{
    printf("Data Atual: ");
    printf("%02hd/%02hd/%04hd\n", data.dia, data.mes, data.ano);  // Usa 4 dígitos para o ano
}

void imprimeHora(hora_t hora)
{
    printf("Hora Atual: ");
    printf("%02hd:%02hd:%02hd\n", hora.hora, hora.minuto, hora.segundo);
    printf("\n");
}

void imprimeDataHora(datahora_t datahora)
{
    printf("Data e hora atual: %02hd/%02hd/%04hd\n", datahora.data.dia, datahora.data.mes, datahora.data.ano);
    printf("Hora atual: %02hd:%02hd:%02hd\n", datahora.hora.hora, datahora.hora.minuto, datahora.hora.segundo);
    printf("\n");
}

int data_dias(data_t data) {
    int dias_totais = 0;
    int dias_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};  // Número de dias por mês

    // Soma os dias dos anos anteriores
    dias_totais += (data.ano - 1) * 365;

    // Soma os dias dos meses anteriores do ano atual
    for (int i = 0; i < data.mes - 1; i++) {
        dias_totais += dias_mes[i];
    }

    // Soma os dias do mês atual
    dias_totais += data.dia;

    return dias_totais;
}

// Função que retorna o número de segundos a partir do início do dia
int hora_segs(hora_t hora) {
    return hora.hora * 3600 + hora.minuto * 60 + hora.segundo;
}

int main()
{
    data_t datas;
    hora_t horas;
    datahora_t datahoras;

    lerData(&datas);
    lerHora(&horas);
    lerDataHora(&datahoras);

    imprimeData(datas);
    imprimeHora(horas);
    imprimeDataHora(datahoras);
    
    int total_dias = data_dias(datas);
    printf("\nNúmero total de dias desde 1/1/1: %d\n", total_dias);

    // Calcula o número de segundos a partir do início do dia
    int segundos = hora_segs(horas);
    printf("Número de segundos desde o início do dia: %d\n", segundos);

    return 0;
}