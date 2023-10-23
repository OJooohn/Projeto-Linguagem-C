#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cadastro{
  int id_pessoa;
  char nome[100];
  char CPF[15];
  char email[100];
  char telefone[15];
  char funcao[30];
  char setor[30];
} Pessoa;

int verificadorCPF(){

}


void printMenu(){
  printf("**************************************************\n");
  printf("*                                                *\n");
  printf("*                 Menu Principal                 *\n");
  printf("*                                                *\n");
  printf("**************************************************\n");
  printf("*                                                *\n");
  printf("*     0 - Sair do programa                       *\n");
  printf("*     1 - Cadastrar novo funcionario             *\n");
  printf("*     2 - Excluir funcionario                    *\n");
  printf("*     3 - Atualizar cadastro                     *\n");
  printf("*     4 - Recrutamento e selecao                 *\n");
  printf("*     5 - Controle de ponto                      *\n");
  printf("*                                                *\n");
  printf("**************************************************\n");
  printf("Digite a opcao: ");
}

Pessoa novoCadastro(int n){

  Pessoa p;
  
  printf("Digite o id: ");
  scanf(" %d", &p.id_pessoa);
  printf("Digite o nome: ");
  scanf(" %[^\n]", p.nome);
  printf("Digite seu CPF: ");
  scanf(" %[^\n]", p.CPF);
  printf("Digite seu e-mail: ");
  scanf(" %[^\n]", p.email);
  printf("Digite seu telfone: ");
  scanf(" %[^\n]", p.telefone);
  printf("Digite a funcao: ");
  scanf(" %[^\n]", p.funcao);
  printf("Digite o setor: ");
  scanf(" %[^\n]", p.setor);
  return p;
}

int main() {

  Pessoa *pessoa;
  pessoa = (Pessoa*) malloc(0 * sizeof(Pessoa));
  int menu, n_pessoa = 0;

  system("cls");
  printMenu();
  scanf("%d", &menu);

  while (menu != 0){
    system("cls");
    printMenu();
    scanf("%d", &menu);

    if(menu < 0 || menu > 5){
      system("cls");
      printf("Opcao invalida!\n");
      system("pause");
    }

    switch (menu){
      case 1:
      pessoa = (Pessoa*) realloc(pessoa, ++n_pessoa * sizeof(Pessoa));
      novoCadastro(n_pessoa - 1);
      break;
      
      /*case 2: excluirCadastro();
      break;

      case 3: atualizarCadastro();
      break;

      case 4: recrutamentoSelecao();
      break;

      case 5: pontoControle();
      break;*/
    }
  }
  
  free(pessoa);
  printf("n_pessoa: [%d]", n_pessoa);
  return 0;
}