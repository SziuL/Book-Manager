#include "funcionalidades.c"

void programa(Filial *filiais)
{
	int escolha;

	printf("1 - Listar os dados de todas as filiais.\n"
		   "2 - Listar os dados de uma filial\n"
		   "3 - Criar nova filial\n"
		   "4 - Encerrar atividades de uma filial\n"
		   "5 - Realizar operacoes no estoque de uma filial\n"
		   "6 - Sair\n\n");

	printf("Digite a opcao desejada: ");
	scanf("%d", &escolha);
	int a = 0;
	while (escolha != 6)
	{
		if (escolha == 1)
			listarTodasFiliais(filiais);
		else if (escolha == 2)
		{
			printf("Informe o ID da filial desejada: ");
			int id;
			scanf("%d", &id);
			listarFilial(filiais, id);
		}
		else if (escolha == 3)
		{
			Filial *novaFilial = coletaDadosFilial(); // para criar uma nova filial
			inserirFilial(filiais, novaFilial);
		}
		else if (escolha == 4)
			excluirFilial(); // transferir base de dados para outra filial
		else if (escolha == 5)
		{
			printf("Informe o ID da filial desejada: ");
			int id;
			scanf("%d", &id);
			selecionaFilial(filiais, id); // opções de ações para se realizar dentro de uma filial
		}
		else if (escolha == 6)
			exit(1);
		else
		{
			printf("Escolha invalida.\n"
				   "Por favor, digite um numero valido.\n");
			system("cls");
		}
	}
}

int main()
{
	Filial *filiais = NULL;
	programa(filiais);

	return 0;
}