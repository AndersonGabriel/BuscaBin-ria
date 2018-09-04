#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int main(void)
{
	FILE *arquivo;
	Endereco e;
	int tentativas;
	char chave_de_busca[8];
	int pos_inicial;
	int pos_meio;
	int pos_final;
	int posicao;
    printf("Entre com o CEP:"); 
    scanf("%s", chave_de_busca);
	arquivo = fopen("cep_ordenado.dat","r");  // abertura do arquivo
	fseek(arquivo,0,SEEK_END);  //fui para o final do arquivo
	posicao = ftell(arquivo);  //guarda posição do final do arquvo
	rewind(arquivo);  // volta para o inicio do arquivo
	pos_inicial = 0;
	pos_final = (posicao/sizeof(Endereco))-1;
	tentativas = 0;
    while(pos_inicial <= pos_final)
    {
        tentativas++;
        pos_meio = (pos_inicial+pos_final)/2;
		fseek(arquivo, pos_meio * sizeof(Endereco), SEEK_SET);  //indo para o meio
		fread(&e,sizeof(Endereco),1,arquivo);
        if(strncmp(chave_de_busca, e.cep,8)==0)
        {
           printf("Logradouro: %.72s\nBairro:     %.72s\nCidade:     %.72s\n",e.logradouro,e.bairro,e.cidade);
           printf("UF:         %.72s\nSigla:      %.2s\nCEP:        %.8s\n",e.uf,e.sigla,e.cep);
		   break; 
        }
        int valor1 = atoi(chave_de_busca);
        int valor2 = atoi(e.cep);
        if(valor1 < valor2)
		{
			pos_final = pos_meio - 1;
		
		}
		if(valor1 > valor2)
		{
			pos_inicial = pos_meio + 1;
		}

    }
printf("Total de Tentativas: %d\n", tentativas);
fclose(arquivo);
printf("Pressione ENTER para sair \n");
}

