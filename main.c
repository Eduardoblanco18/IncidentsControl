#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "BibliotecaArvore.h"

void limpar_buffer()
{

    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int ler_int()
{
    int num, flag;
    flag = 0;
    while (flag == 0)

    {
        if (scanf("%d", &num) == 1)
        {
            flag = 1;
        }
        else
        {
            printf("\nEntrada inválida, digite apenas números inteiros.\n");
        }
        limpar_buffer();

    }
    return num;
}

int ler_intervalo(char texto[], int min, int max)
{

    int num;
    printf("%s", texto);
    num = ler_int();
    while(num < min || num > max)
    {
        printf("\nEntrada inválida, digite apenas números entre %d (no minimo) ou %d(no máximo).\n");
        num = ler_int();
    }
    return num;
}

int main()
{
    setlocale(LC_ALL, "portuguese");
    int opcao, id, codEquip;
    Inc inc;
    NoArv *no;
    Arv *RAIZ = NULL;
    RAIZ = CriarArvore();
    //tabela hash aqui depois

    do
    {
        printf("\n\n=================== MENU ==================");
        printf("\n\n 1 - Cadastrar Equipamento");
        printf("\n 2 - Registrar Incidente");
        printf("\n 3 - Consultar Equipamento e incidente");
        printf("\n 4 - Listar os incidentes");
        printf("\n 5 - Excluir um incidente");
        printf("\n 6 - Excluir um equipamento");
        printf("\n 7 - Sair");
        printf("\n\n==================-------====================");
        printf("\n\nEscolha: ");
        opcao = ler_int();
        switch(opcao)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        default:
            printf("\nOpção inválida.");


        }
    }while(opcao !=7 );
    //liberararvore();
    free(RAIZ);
    RAIZ=NULL;

}
