#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int id_pessoa;
  char nome[100];
  char CPF[15];
  char email[100];
  char telefone[15];
  char funcao[30];
  char setor[30];
} Pessoa;

/*int verificadorCPF(){

}*/


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
  printf("*     4 - Informacao cadastro                    *\n");
  printf("*     5 - Recrutamento e selecao                 *\n");
  printf("*     6 - Controle de ponto                      *\n");
  printf("*                                                *\n");
  printf("**************************************************\n");
  printf("Digite a opcao: ");
}

void novoCadastro(int n, Pessoa *p){

  int valID = 0, val = 0;

  system("cls");
  printf("**************************************************\n");
  printf("*                                                *\n");
  printf("*                   Cadastro                     *\n");
  printf("*                                                *\n");
  printf("**************************************************\n");

  while (valID == 0){
    printf("Digite o id: ");
    scanf("%d", &p[n].id_pessoa);

    if(n > 1){
      for(int i = 0; i < n; i++){
        if(p[i].id_pessoa == p[i - 1].id_pessoa){
          val = 1;
        }
      }
    } else {
      if(p[0].id_pessoa == p[1].id_pessoa)
        val = 0;
      else
        val = 1;
    }

    if(val >= 1){
      valID = 1;
    } else {
      printf("Id de pessoa ja cadastrada!\n");
      system("pause");
      valID = 0;
    }
  }
  
  printf("Digite o nome: ");
  scanf(" %[^\n]", &p[n].nome);
  printf("Digite seu CPF: ");
  scanf(" %[^\n]", &p[n].CPF);
  printf("Digite seu e-mail: ");
  scanf(" %[^\n]", &p[n].email);
  printf("Digite seu telfone: ");
  scanf(" %[^\n]", &p[n].telefone);
  printf("Digite a funcao: ");
  scanf(" %[^\n]", &p[n].funcao);
  printf("Digite o setor: ");
  scanf(" %[^\n]", &p[n].setor);
  
}

void cadastroInformacao(Pessoa *p, int n){
  
  int id;

  printf("Digite o id da pessoa: ");
  scanf("%d", &id);

  for(int i = 0; i < n; i++){
    if(id == p[i].id_pessoa) {
      printf("ID: %d\n", p[i].id_pessoa);
      printf("nome: %s\n", p[i].nome);
      printf("CPF: %s\n", p[i].CPF);
      printf("E-mail: %s\n", p[i].email);
      printf("Telfone: %s\n", p[i].telefone);
      printf("Funcao: %s\n", p[i].funcao);
      printf("Setor: %s\n", p[i].setor);
    }
  }

  system("pause");

}

int main() {

  Pessoa *pessoa;
  pessoa = (Pessoa*) malloc(0 * sizeof(Pessoa));
  
  if(pessoa == NULL){
    printf("Erro de alocacao de memoria!\n");
    return 1;
  }

  int menu = 1, n_pessoa = 0;

  while (menu != 0){
    system("cls");
    printMenu();
    scanf("%d", &menu);

    if(menu < 0 || menu > 6){
      system("cls");
      printf("Opcao invalida!\n");
      system("pause");
    }

    switch (menu){
      case 1:
      pessoa = (Pessoa*) realloc(pessoa, ++n_pessoa * sizeof(Pessoa));
      novoCadastro(n_pessoa - 1, pessoa);
      break;
      
      /*case 2: excluirCadastro();
      break;

      case 3: atualizarCadastro();
      break;*/

      case 4: cadastroInformacao(pessoa, n_pessoa);
      break;

      /*case 5: recrutamentoSelecao();
      break;

      case 5: pontoControle();
      break;*/
    }
  }
  
  free(pessoa);
  printf("n_pessoa: [%d]", n_pessoa);
  return 0;
}