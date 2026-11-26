#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include "BibliotecaArvore.h"
#define MAX_COD_UNI 9999
#define MIN_COD_UNI 1000
#define MAX_NUM_UNI 99
#define MIN_NUM_UNI 10
#define MAX_GRAVIDADE 3
#define MIN_GRAVIDADE 1

void limpar_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limpa_tela()
{
    printf("\n\n\n");
    system("Pause");
    system("cls");
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
        printf("\nEntrada inválida, digite apenas números entre %d (no minimo) ou %d(no máximo).\n", min, max);
        printf("%s", texto);
        num = ler_int();
    }
    return num;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    setlocale(LC_ALL, ".UTF-8");

    NoEqp *Hash[TAM] = {NULL};

    int opcao, id, codEquip;
    Inc novoInc;
    Eqp novoEqp;
    int flag, auxPos;
    short cont;
    char name[11];
    NoArv *no;
    Arv *RAIZ = NULL;
    RAIZ = CriarArvore();

    do
    {
        printf("\n\n=================== MENU ==================");
        printf("\n\n 1 - Cadastrar Equipamento");
        printf("\n 2 - Registrar Incidente");
        printf("\n 3 - Consultar Equipamento e incidente");
        printf("\n 4 - Listar os incidentes");
        printf("\n 5 - Excluir um incidente");
        printf("\n 6 - Excluir um equipamento");
        printf("\n 7 - Pesquisar Incidente");
        printf("\n 8 - Sair");

        printf("\n\n==================-------====================");
        printf("\n\nEscolha: ");
        opcao = ler_int();

        switch(opcao)
        {
        case 1:
            do
            {
                flag = 1;
                novoEqp.codEqp = ler_intervalo("Código de Equipamento: ", MIN_COD_UNI, MAX_COD_UNI);
                if(BuscaEqp(Hash, novoEqp.codEqp) != NULL)
                {
                    printf("\nEquipamento já registrado. Tente outro.\n");
                    system("pause");
                    flag = 0;
                }
            }while(flag == 0);

            limpar_buffer();

            do
            {
                flag = 1;
                printf("Nome do equipamento: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                limpar_buffer();
                if (strlen(name) >= 11)
                    {
                        printf("\nO código precisa ter no máximo 10 caracteres.\n");
                        flag = 0;
                    }
            } while (flag == 0);
            strcpy(novoEqp.apelido, name);
            novoEqp.incidentes = CriaLista();

            adicionarEqpNaHash(Hash, novoEqp);

            limpa_tela();
            break;
        case 2:

            novoInc.codEqp = ler_intervalo("Código de Equipamento: ", MIN_COD_UNI, MAX_COD_UNI);

            if(BuscaEqp(Hash, novoInc.codEqp) == NULL)
            {
                printf("\nCadastre o equipamento respectivo antes de cadastrar um incidente.");
                limpa_tela();
                break;
            }

            do
            {
                flag = 1;
                novoInc.codUn = ler_intervalo("Código Único de Indentificação: ", MIN_NUM_UNI, MAX_NUM_UNI);

                if (busca(RAIZ, novoInc.codUn) != NULL)
                {
                    flag = 0;
                    printf("\nCódigo de incidente já existe. Tente outro.\n");
                    system("pause");
                }
            } while (flag == 0);

            novoInc.gravidade = ler_intervalo("Gravidade do Incidente: ", MIN_GRAVIDADE, MAX_GRAVIDADE);

            if(!insere(RAIZ, novoInc))
            {
                printf("\nNão foi possível Adicionar\n");
            }

            adicionarIncNaHash(Hash, novoInc);

            limpa_tela();
            break;
        case 3:
            codEquip = ler_intervalo("\nQual é o código do Equipamento: ", MIN_COD_UNI, MAX_COD_UNI);
            if(BuscaEqp(Hash, codEquip) != NULL)
            {
                Eqp *EqpProcura = BuscaEqp(Hash, codEquip);
                imprimirEquipamento(EqpProcura);
                printf("\nIncidentes relacionados:\n");
                if(!ListaVazia(EqpProcura->incidentes))
                {
                    imprimirLista(EqpProcura->incidentes);
                }
                else
                {
                    printf("\nNenhum incidente relacionado");
                }
            }
            else
            {
                printf("\nEquipamento inexistente!");
            }
            limpa_tela();
            break;
        case 4:
            if(!ArvVazia(RAIZ))
            {
                imprimirOrdemArv(RAIZ->raiz);
            }
            else
            {
                printf("\nNenhum Incidente cadastrado.");
            }
            limpa_tela();
            break;
        case 5:
            if (ArvVazia(RAIZ))
            {
                printf("\nNenhum incidente para remover.\n");
            }
            else
            {
                id = ler_intervalo("\nQual é o código do incidente?", MIN_NUM_UNI, MAX_NUM_UNI);
                NoArv *aux = busca(RAIZ, id);
                if (aux != NULL)
                {
                    Inc auxInc = aux->incidente;
                    int auxPos = funcaoHash(auxInc.codEqp);
                    remover(RAIZ, auxInc.codUn);
                    NoEqp *auxEqp = Hash[auxPos];
                    while(auxEqp->equipamento.codEqp != auxInc.codEqp)
                    {
                        auxEqp = auxEqp->prox;
                    }
                    RemoverLista(auxEqp->equipamento.incidentes, auxInc.codUn);
                    printf("\nIncidente apagado com sucesso.");
                }
                else
                {
                    printf("\nIncidente inexistente.");
                }
            }
            limpa_tela();
            break;
        case 6:
            codEquip = ler_intervalo("\nQual é o código do Equipamento", MIN_COD_UNI, MAX_COD_UNI);
            if(BuscaEqp(Hash, codEquip) != NULL)
            {
                removerEqpDaHash(Hash, codEquip, RAIZ);
            }
            printf("\nEquipamento e incidentes apagados com sucesso!\n");
            limpa_tela();
            break;
        case 7:
            id = ler_intervalo("\n Qual o ID do incidente, de 10 a 99? ", MIN_NUM_UNI, MAX_NUM_UNI);
            no = busca(RAIZ, id);
            if (no == NULL)
            {
                printf("\nIncidente não encontrado!\n");
            }
            else
            {
                imprimirIncidente(no->incidente);
                Eqp *eq = BuscaEqp(Hash, no->incidente.codEqp);
                printf("Equipamento relacionado:");
                imprimirEquipamento(eq);
            }
            limpa_tela();
            break;
        case 8:
            printf("\nSaindo\n");
            system("pause");
            break;

        default:
            printf("\nOpção inválida.\n");
            system("pause");
            system("cls");
        }
    }while(opcao !=8 );
    liberarArv(RAIZ->raiz);
    liberarHash(Hash);
    free(RAIZ);
}
