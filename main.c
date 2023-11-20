#include "funcionalidades.c"

void programa(Filial *filiais)
{
	sleep(3);
	system("clear");
	int escolha;

	imprimeMenuPrincipal();

	printf("Digite a opcao desejada: ");
	scanf("%d", &escolha);

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
		inserirFilial(&filiais, novaFilial);
	}
	else if (escolha == 4)
	{
		printf("Informe o ID da filial a ser excluida: ");
		int idOrigem, idDestino;
		scanf("%d", &idOrigem);
		printf("Informe o ID da filial que receberá os dados da antiga: ");
		scanf("%d", &idDestino);
		excluirFilial(filiais, idOrigem, idDestino); // transferir base de dados para outra filial
	}
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
		programa(filiais);
	}

	programa(filiais);
}

int main()
{
	Filial *filiais = NULL;
	programa(filiais);

	return 0;
}