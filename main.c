#include <stdio.h>
#include <string.h>
#include<stdlib.h>

struct notaFiscal{

int codigo, quantidade;
char produto[100];
double preco, valorTotal;
};

void carregarNotas(int* contador, struct notaFiscal notas[100]){
FILE *arquivo;
arquivo = fopen("notas.dat", "rb");

 if(arquivo == NULL){
    printf("Erro ao abrir arquivo!");
    return;
 }


 while(*contador < 100 && fread(&notas[*contador],sizeof(struct notaFiscal),1,arquivo) == 1){
      (*contador)++;
 }
    fclose(arquivo);
}

void limparBuffe(){
int c;
while((c = getchar()) != '\n' && c != EOF);

}

double calculoTotal (double preco,int quant){

return preco * quant;

}

void menu(){

printf("\n ------------------------");
printf("\n|1 - Cadastrar produto    |");
printf("\n|2 - Buscar produto      |");
printf("\n|3 - Gerar notas fiscais |");
printf("\n|0 - Sair do sistema     |");
printf("\n ------------------------");
printf("\n Opcao: ");
}

void cadastro(int* contador, int* proximoCodigo, struct notaFiscal notas[100]){

if(*contador >= 100){
  printf("Limite maximo atingido!");
  return;
}

limparBuffe();
printf("\n=== CADASTRO DOS PRODUTOS ===\n");
printf("\nNome do produto: ");

fgets(notas[*contador].produto , sizeof(notas[*contador].produto),stdin );
notas[*contador].produto[strcspn(notas[*contador].produto, "\n")] = '\0';

printf("\nPreco unitario do produto: ");
scanf("%lf", &notas[*contador].preco);

printf("\nQuantidade comprada: ");
scanf("%d", &notas[*contador].quantidade);
limparBuffe();

notas[*contador].valorTotal = calculoTotal(notas[*contador].preco, notas[*contador].quantidade);

//vetor do elemento codigo recebe valor 1000 na 1° posicao do vetor, depois acrescentar mais um a cada vez.
notas[*contador].codigo = *proximoCodigo;

FILE *arquivo;
arquivo = fopen("notas.dat", "ab");
fwrite(&notas[*contador], sizeof(struct notaFiscal), 1, arquivo);
fclose(arquivo);

system("cls");
printf("\nCadastro feito com sucesso!");
printf("\nCodigo gerado: %d\n", notas[*contador].codigo);

(*proximoCodigo)++;
(*contador)++;


}

void buscarProduto(int* contador, struct notaFiscal notas[100]){
int n;
if(*contador == 0){
    printf("Nenhum produto cadastrado!");
    limparBuffe();
    getchar();//retorna e nao exucuta o resto da funcao.
    return;
}
    printf(" Digite o codigo: ");
    scanf("%d", &n);
    getchar();

     system("cls");

     for(int i = 0; i < *contador; i++){
     if(n == notas[i].codigo){
       printf("\n PRODUTO ENCONTRADO | ");
       printf("codigo %d\n", notas[i].codigo);

       printf("\n---------------------------------------------");
       printf("\n| Nome do produto: %s                        ", notas[i].produto);
       printf("\n| Preco unitario: %.2lf$                    ", notas[i].preco);
       printf("\n| Quantidade adquirida: %d                   ", notas[i].quantidade);
       printf("\n| Valor pago: %.2lf$                 ",notas[i].valorTotal);
       printf("\n-------------------------------------------\n");
       printf("\nPressione ENTER para voltar...");
       getchar();
       return;
     }
}
    printf("\nProduto com o codigo %d nao foi encontrado.\n", n);
    getchar();
}

void gerarNotasFiscais (int* contador, struct notaFiscal notas[100]){

if(*contador == 0){
   printf("Nenhuma nota fiscal encontrada!");
   limparBuffe();
   return;
}

int n;
printf("\nQuantidade de notas fiscais %d\n",*contador);
printf("Digite quantas deseja gerar: ");
scanf("%d", &n);

 if(n <= 0 || n > *contador){
    printf("ERRO!");
    limparBuffe();
    return;
    }

for(int i = 0; i < n; i++){
  printf("\n---------------------------------------------");
  printf("\n| Codigo do produto: %d", notas[i].codigo);
  printf("\n| Nome do produto: %s                        ", notas[i].produto);
  printf("\n| Preco unitario: %.2lf$                    ", notas[i].preco);
  printf("\n| Quantidade adquirida: %d                   ", notas[i].quantidade);
  printf("\n| Valor pago: %.2lf$                 ",notas[i].valorTotal);
  printf("\n-------------------------------------------\n");

}
  printf("\nPressione ENTER para voltar...");
  getchar();
  return;
}

int main(){

struct notaFiscal notas[100];

int contador = 0;
int proximoCodigo = 1000;
int opcao;

 carregarNotas(&contador, notas);
 if(contador > 0){
 proximoCodigo = notas[contador -1].codigo + 1;
 }

do{
    system("cls");
    menu();
    scanf("%d", &opcao);
    system("cls");

 switch(opcao){
    case 1:
    cadastro(&contador, &proximoCodigo, notas);
    getchar();
    break;

    case 2:
    buscarProduto(&contador, notas);
    break;

    case 3:
    gerarNotasFiscais(&contador, notas);
    getchar();
    break;

    case 0:
    printf("\nSistema encerrado!\n");
    break;

    default:
        printf("\nOpcao invalida");
        limparBuffe();
        getchar();
    break;
 }
}while(opcao !=0);
 return 0;
}
