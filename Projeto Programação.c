#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>


typedef struct
{
    char title [50];
    char autor[20];
    char genero[20];
    char num[5];
    char cpf_cli[11];// (se o livro estiver indisponível, o CPF do cliente que alugou)
    int estoque;

} Livro;


typedef struct
{

    char rua[40];
    char numero[5];
    char cep[8];
    char complemento[40];

} Endereco;


typedef struct  //sem senha ja que o foco do projeto é administração)(pode ser implementado login e senha para usuario)
{
    char nome[40];
    char cpf[15];
    Endereco end;
    int multa;
    int livro1;
    int livro2;
    char prazo[8];

} Usuario;

typedef struct
{
    Usuario u;
    Livro l;
    int estoque;
    char dataInicio[20];
    char dataEntrega[20];

} Reserva;


typedef struct
{
    char login[20];
    char senha[10];
} Admin;



void Pesquisar(int i, Usuario* c)
{
    if(i == 1)
    {
        int j;
        char nome[20];
        printf("Digite o nome do cliente: ");
        gets(nome);
        strupr(nome);
        int k = 0;
        for(j = 0; j < 50; j++)
        {
            if(strcmp(c[j].nome, nome) == 0)
            {
                k++;
            }
        }
        int v = 1;
        system("cls");
        printf("Foram encontrados %d clientes com o nome digitado: \n", k);
        for(j = 0; j < 50; j++)
        {
            if(strcmp(c[j].nome, nome) == 0)
            {
                printf("%d:\nNome: %s\n",v,c[j].nome);
                printf("CPF: %s\n", c[j].cpf);
                printf("Rua: %s, Numero: %s, Complemento: %s\n", c[j].end.rua, c[j].end.numero,c[j].end.complemento);
                printf("CEP: %s  ", c[j].end.cep);
                v++;
                printf("\n\n");
            }
        }
        system("pause");
        system("cls");
    }
    else if(i == 2)
    {
        char cpf[20];
        printf("Digite o CPF do cliente: ");
        gets(cpf);
        system("cls");
        int j, k = 0;
        for(j = 0; j < 50; j++)
        {
            if(strcmp(c[j].cpf, cpf) == 0)
            {
                printf("Nome: %s\n",c[j].nome);
                printf("CPF: %s\n", c[j].cpf);
                printf("Rua: %s, Numero: %s, Complemento: %s\n", c[j].end.rua, c[j].end.numero,c[j].end.complemento);
                printf("CEP: %s", c[j].end.cep);
                printf("\n\n");
            }
        }
        system("pause");
        system("cls");
    }
    else if(i == 3)
    {
        char rua[20];
        printf("Digite a rua do cliente: ");
        gets(rua);
        strupr(rua);
        int j, k = 0;
        for(j = 0; j < 50; j++)
        {
            if(strcmp(c[j].end.rua, rua) == 0)
            {
                k++;
            }
        }
        int v = 1;
        system("cls");
        printf("\nForam encontrados %d pessoas morando nesse endereco: \n", k);
        for(j = 0; j < 50; j++)
        {
            if(strcmp(c[j].end.rua, rua) == 0)
            {
                printf("%d:\nNome: %s\n",v,c[j].nome);
                printf("CPF: %s\n", c[j].cpf);
                printf("Rua: %s, Numero: %s, Complemento: %s\n", c[j].end.rua, c[j].end.numero,c[j].end.complemento);
                printf("CEP: %s", c[j].end.cep);
                v++;
                printf("\n\n");
            }
        }
        system("pause");
        system("cls");
    }
    else if(i==4)
    {

	}
    else
    {
        printf("Opção Inválida!");
        system("pause");
    }
    system("cls");
}

void add_cliente (Usuario* u, int i)
{
    fflush(stdin);
    printf("Digite o nome do novo cliente: \n");
    gets(u[i].nome);
    strupr(u[i].nome);
    printf("Digite o CPF do novo cliente: \n");
    gets((u[i]).cpf);
    printf("Digite o endereco (Rua) do novo cliente: \n");
    gets((u[i]).end.rua);
    strupr(u[i].end.rua);
    printf("Digite o numero da casa do novo cliente: \n");
    gets(u[i].end.numero);
    printf("Digite o CEP do novo cliente: \n");
    gets(u[i].end.cep);
    printf("Digite um complemento para o endereco do novo cliente: \n");
    gets(u[i].end.complemento);
    strupr(u[i].end.complemento);
    printf("Usuario cadastrado com sucesso!!!");
    system("pause");
    system("cls");
}

void Remover(Usuario* c)
{
    Usuario v;
    char cpf[11];
    int j;

    strcpy(v.cpf, "0");
    strcpy(v.nome, "0");

    do
    {

        printf("Digite o cpf do cliente que deseja remover(Para voltar digite sair.): \n");
        scanf("%s",cpf);
        fflush(stdin);
        strupr(cpf);

        for(j = 0; j < 50; j++)
        {
            if(strcmp(cpf,c[j].cpf)==0)
            {
                char x;
                system("cls");
                printf("Nome: %s\n",c[j].nome);
                printf("CPF: %s\n", c[j].cpf);
                printf("Rua: %s, numero: %s, complemento: %s\n", c[j].end.rua, c[j].end.numero,c[j].end.complemento);
                printf("CEP: %s", c[j].end.cep);
                printf("\n\n");
                printf("Tem certeza que deseja remover:(S ou N) ");
                scanf("%c",&x);
                fflush(stdin);


                if(x=='S' || x=='s')
                {
                    c[j]=v;
                    printf("Cliente Removido.\n");
                    system("pause");
                    break;
                }
                else if(x=='N' || x=='n')
                {
                    printf("Operacao cancelada.\n");
                    system("pause");
                    system("cls");
                    break;
                }

            }
            else if((strcmp(c[j].cpf, cpf)!=0) && (j==49) && strcmp("SAIR", cpf) != 0)
            {
                system("cls");
                printf("Cliente nao encontrado. Tente novamente...\n");
                system("pause");
            }
        }
        system("cls");
    }
    while(strcmp("SAIR", cpf) != 0);
}

void atualizar(Usuario* a)
{
    int escolha;
    system("cls");
    printf("Nome: %s\nCPF: %s",(*a).nome,(*a).cpf);
    printf("\n\n1. Editar nome\n2. Editar CPF\n3. Endereco\n4. Voltar\n");
    scanf("%d",&escolha);
    system("cls");
    switch(escolha)
    {
    case 1:
    {
        getchar();
        printf("Digite o novo nome: ");
        gets((*a).nome);
        strupr((*a).nome);
        printf("\n\nCliente atualizado com sucesso!\n");
        system("pause");
        break;
    }
    case 2:
    {
        getchar();
        printf("Digite o novo CPF: ");
        gets((*a).cpf);
        printf("\n\nCliente atualizado com sucesso!\n");
        system("pause");
        break;
    }
    case 3:
    {

        getchar();
        printf("Digite a rua: ");
        gets((*a).end.rua);
        strupr((*a).end.rua);
        printf("Digite o numero: ");
        gets((*a).end.numero);
        printf("Digite o CEP: ");
        gets((*a).end.cep);
        printf("Digite o complemento: ");
        gets((*a).end.complemento);
        strupr((*a).end.complemento);
        printf("\n\nCliente atualizado com sucesso!\n");
        system("pause");
    }
    case 4:
    	{
    		break;
		}
    }
}

void editarlivro(Livro* a)
{
    char escolha;
    system("cls");
    printf("%s\n%s",(*a).title,(*a).autor);
    printf("\n\nEditar livro escolhido? s/n");
    scanf("%c",&escolha);
    system("cls");

    if(escolha=='s' || escolha=='S')
    {
        fflush(stdin);
        printf("Nome: ");
        gets((*a).title);
        printf("Autor: ");
        gets((*a).autor);
        printf("Genero: ");
        gets((*a).genero);
    }
}

void Removerlivro(Livro* c)
{
    Livro v;
    char num1[5];
    int j;

    strcpy(v.num, "0");
    strcpy(v.title, " ");

    do
    {

        printf("Digite o codigo do livro que deseja remover(Para voltar digite sair.): \n");
        scanf("%s",num1);
        strupr(num1);
        fflush(stdin);

        for(j = 0; j < 50; j++)
        {
            if(strcmp(num1,c[j].num)==0)
            {
                int n;
                char x;
                system("cls");
                printf("Codigo: %s\nNome: %s\n",c[j].num,c[j].title);
                printf("Autor: %s\n", c[j].autor);
                printf("Genero: %s\n",c[j].genero);
                printf("Estoque: %d", c[j].estoque);
                printf("\n\n");
                printf("A quantidade de livros que deseja remover: ");
                scanf("%d",&n);
                fflush(stdin);
                printf("\n\nTem certeza que deseja remover:(S ou N) ");
                scanf("%c",&x);
                fflush(stdin);


                if(x=='S' || x=='s')
                {
                    c[j].estoque-=n;
                    if(n>=c[j].estoque)
                    {
                       c[j]=v;
                       printf("Livro removido do acervo.\n");
                       system("pause");
                       break;
                    }
                    else
                    {
                       printf("%d Livros foram removidos do acervo.\n",n);
                       system("pause");
                       break;
                    }
                }
                else if(x=='N' || x=='n')
                {
                    printf("Operacao cancelada.\n");
                    system("pause");
                    system("cls");
                    break;
                }

            }
            else if((strcmp(c[j].num, num1)!=0) && (j==49) && strcmp("SAIR", num1) != 0)
            {
                system("cls");
                printf("Livro nao encontrado. Tente novamente...\n");
                system("pause");
            }
        }
        system("cls");
    }
    while(strcmp("SAIR", num1) != 0);
}

int login()
{
    Admin a[10];
    char log[20], sen[10];
    int i;
    FILE* fusuarios;
    
    fusuarios = fopen("usuarios.bin", "rb");
            for(i=0;i<10;i++)
                {
                	 fread(&a[i], sizeof(Admin), 1, fusuarios);
				}
			fclose(fusuarios);
    

    printf("Digite o login: ");
    scanf("%s",log);
    printf("Digite a senha: ");
    scanf("%s",sen);
    for(i=0; i<10; i++)
    {

        if ((strcmp(a[i].login, log) || strcmp(a[i].senha,sen)) == 0)
        {
        	
            return 1;
        }

    }
    return 0;
}

main()
{
    Usuario clientes[50]; Livro livros[50];
    int i;
    
    printf("||||||Biblioteca||||||\n\n\n\n\n\ndeveloped by  DLRS\n\n\n\n\n");
    system("pause");
    system("cls");
    
    for(i=1;i<50;i++)
    {
    	
    	strcpy(clientes[i].cpf,"0");
	}

    while(1)
    {
        if (login() == 1)
        {
            system("cls");
            printf("Login efetuado\n");
            system("pause");
            system("cls");
            int escolha,escolha2,escolha3;
            FILE* fclientes;
			FILE* flivros;
            
			fclientes = fopen("clientes.bin", "rb");
            for(i=0;i<50;i++)
                {
                	 fread(&clientes[i], sizeof(Usuario), 1, fclientes);
				}
			fclose(fclientes);
			
			flivros = fopen("livros.bin", "rb");
            for(i=0;i<50;i++)
                {
                	 fread(&livros[i], sizeof(Livro), 1, flivros);
				}
			fclose(flivros);	
			
            do
            {
                printf("1. Cliente\n2. Livro\n3. Emprestimo\n4. Sair\n");
                scanf("%d",&escolha);
                system("cls");

                if(escolha==1)
                {
                    do
                    {
                    printf("Cliente\n\n");
                    printf("1. Pesquisar\n2. Adicionar\n3. Editar\n4. Voltar\n");
                    scanf("%d",&escolha2);
                    system("cls");
                    switch(escolha2)
                    {
                    case 1:
                    {
                        int op;
                        do
                        {

						printf("Pesquisar por:\n1.Nome\n2.CPF\n3.Endereco\n4.Voltar\nOpcao: ");
                        scanf("%d", &op);
                        getchar();
                        system("cls");
                        Pesquisar(op, clientes);
                        }while(op!=4);
                        break;
                    }
                    case 2:
                    {
                        int y;
                             for(y=0; y<50; y++)
    						{
        						if(strcmp(clientes[y].cpf,"0") == 0)
        						{
        						     add_cliente(clientes,y);
        							 break;
        						}

    						}

                            break;
                    }
                    case 3:
                    {
                        system("cls");
                        printf("1. Atualizar\n2. Remover\n");
                        scanf("%d",&escolha3);
                        if(escolha3==1)
                        {
                            system("cls");
                            char cpf[11];
                            escolha2=0;
                            int k=0;
                            do
                            {
                                int i;
                                printf("Atualizar\n\nCPF: ");
                                scanf("%s",&cpf);
                                for(i=0; i<50; i++)
                                {
                                    if(strcmp(clientes[i].cpf,cpf)==0)
                                    {
                                        atualizar(&clientes[i]);
                                        k++;
                                    }
                                }
                                if(k==0)
                                {
                                    printf("\nCPF nao encontrado!\n\n1. Tentar novamente\n2. Sair\n");
                                    scanf("%d",&escolha2);
                                }
                                else
                                {
                                    escolha2=2;
                                }
                                system("cls");

                            }
                            while(escolha2!=2);
                            break;
                            }
                            else if(escolha3==2)
                            {
                               system("cls");
                               Remover(clientes);
                               break;
                            }

                    }
                    case 4:
                    {
                        break;
                    }
                    }
                  }while(escolha2!=4);
                }
                else if(escolha==2)
                {
                    printf("Livro\n\n");
                    printf("1. Pesquisar\n2. Adicionar\n3. Editar\n4. Voltar\n");
                    scanf("%d",&escolha2);
                    system("cls");
                    switch(escolha2)
                    {
                    case 1:
                    {
                        break;
                    }
                    case 2:
                    {
                        break;
                    }
                    case 3:
                    {
                        printf("Editar\n\n1. Remover\n2. Alterar\n3. Voltar\n");
                        scanf("%d",&escolha3);
                        system("cls");
                        if(escolha3==1)
                        {
                              Removerlivro(livros);
                        }
                        else if(escolha3==2)
                        {
                            char codigolivro[5];
                            escolha3=0;
                            int k=0;
                            do
                            {
                                int i; fflush(stdin);
                                printf("Editar\n\nCodigo do livro: ");
                                gets(codigolivro);
                                system("cls");
                                for(i=0; i<50; i++)
                                {
                                    if(strcmp(livros[i].num,codigolivro)==0)
                                    {
                                        editarlivro(&livros[i]);
                                        k++;
                                    }
                                }
                                if(k==0)
                                {
                                    printf("\nLivro nao encontrado!\n\n1. Tentar novamente\n2. Sair\n");
                                    scanf("%d",&escolha2);
                                }
                                else
                                {
                                    escolha3=2;
                                }
                                system("cls");

                            }while(escolha3=!2);


                        }
                        else if(escolha3==3)
                        {
                            system("cls");
                            break;
                        }
                    }
                    case 4:
                    {
                        break;
                    }
                    }
                }
                else if(escolha==3)
                {
                    printf("Emprestimo\n\n1. Reserva\n2. Locacao\n3. Devolucao\n4. Voltar\n");
                    scanf("%d",&escolha2);
                    system("cls");
                    switch(escolha2)
                    {
                    case 1:
                    {
                        break;
                    }
                    case 2:
                    {
                        break;
                    }
                    case 3:
                    {
                        break;
                    }
                    case 4:
                    {
                        break;
                    }
                    }
                }
                
            }
            while(escolha!=4);
 
           
 fclientes = fopen("clientes.bin", "wb");
 fseek(fclientes, 0, SEEK_SET);            
for(i=0;i<50;i++)
    {
    	 fwrite(&clientes[i], sizeof(Usuario), 1, fclientes);
	}
fclose(fclientes);

 fseek(flivros, 0, SEEK_SET);
 flivros = fopen("livros.bin", "wb");
            for(i=0;i<50;i++)
                {
                	 fwrite(&livros[i], sizeof(Livro), 1, flivros);
				}
			fclose(flivros);

        }
        else
        {
            system("cls");
            printf("Login ou senha errados\n");
            system("pause");
            system("cls");
        }
    }
}

