#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "BibliotecaArvore.h"
#define MAX_COD_UNI = 9999
#define MIN_COD_UNI = 1000
#define MAX_NUM_UNI = 99
#define MIN_NUM_UNI = 10
#define MAX_GRAVIDADE = 3
#define MIN_GRAVIDADE = 1

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
        printf("\n\n 1 - Cadastrar Equipamento"); //Colocar tabela Hash
        printf("\n 2 - Registrar Incidente");
        printf("\n 3 - Consultar Equipamento e incidente"); // falta função
        printf("\n 4 - Listar os incidentes"); // falta função
        printf("\n 5 - Excluir um incidente"); //falta função
        printf("\n 6 - Excluir um equipamento"); //falta função
        printf("\n 7 - Pesquisar Incidente"); //falta função
        printf("\n 8 - Sair");

        printf("\n\n==================-------====================");
        printf("\n\nEscolha: ");
        opcao = ler_int();

        switch(opcao)
        {
        case 1:
            Eqp novo;
            novo.codEqp = ler_intervalo("Código de Equipamento", MIN_COD_UNI, MAX_COD_UNI);

            short cont = 0;
            char name[11];
            limpar_buffer();

            do
            {
                cont = 1;
                printf("Nome do equipamento: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                limpar_buffer();
                if (strlen(name) >= 11)
                    {
                        printf("O código precisa ter no máximo 10 caracteres.\n");
                        cont = 0;
                    }
            } while (cont == 0);
                strcpy(novo.apelido, name);

            // ADICIONAR EQUIPAMENTO NA TABELA HASH
            break;
        case 2:
            Inc novo;

            novo.codUn = ler_intervalo("Código Único de Indentificação", MIN_NUM_UNI, MAX_NUM_UNI);

            do
            {
                int flag = 1;
                novo.codEqp = ler_intervalo("Código de Equipamento", MIN_COD_UNI, MAX_COD_UNI);

                /*if (codigo equip = Já existe)
                {
                    flag = 0;
                }*/
            } while (flag == 0);

            novo.gravidade = ler_intervalo("Gravidade do Incidente", MIN_GRAVIDADE, MAX_GRAVIDADE);

            //adicionar incidente na arvore
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (ArvVazia(RAIZ))
            {
                printf("\nNenhum incidente para remover.\n");
            }
            else
            {
                codEqp = ler_intervalo("\nCódigo do equipamento de 1000 até 9999: ", 1000, 9999);
                eq = BuscaEqp(TABELA, codEqp);
                if (eq == NULL)
                {
                    printf("\n Equipamento %d não encontrado. \n", codEqp);
                }
                else
                {
                    id = ler_intervalo("\nQual o ID do incidente de 10 a 99? ", 10, 99);




                    if (!buscarLista(eq->incidentes, id))




                    {
                        no = busca(RAIZ, id);
                        if (no == NULL)
                        {
                            printf("\n Incidente %d não encontrado. \n", id);
                        }
                        else
                        {
                            printf("\n O incidente %d pertence ao equipamento %d, não ao equipamento %d. \n", id, no->incidente.codEqp, codEqp);

                        }

                    }
                    else
                    {
                        no = busca(RAIZ, id);
                        imprimirIncidente(no->incidente);
                        imprimirEquipamento(eq->equipamento);
                        RemoverLista(eq->incidentes, id);
                        remover(RAIZ, id);
                        printf("\nIncidente %d excluído com sucesso!\n", id);
                    }
                }
            }
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            id = ler_intervalo("\n Qual o ID do incidente, de 10 a 99? ", 10, 99);
            no = busca(RAIZ, id);
            if (no == NULL)
            {
                printf("\nIncidente não encontrado!\n");
            }
            else
            {
                imprimirIncidente(no->incidente);
                eq = BuscaEqp(TABELA, no->incidente.codEqp);
                if (eq!=NULL)
                {
                    imprimirEquipamento(eq->equipamento);
                }
            }
            break;

        default:
            printf("\nOpção inválida.");


        }
    }while(opcao !=7 );
    liberararvore(RAIZ->raiz);
    free(RAIZ);
    RAIZ=NULL;

}
