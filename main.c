#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
  int id_pessoa;
  char nome[100];
  char CPF[15];
  char email[100];
  char telefone[15];
  char funcao[30];
  char setor[30];
} Pessoa;

int verificadorCPF(char *cCPF){
  int i, j, *CPF;
  CPF = (int*) malloc(11 * sizeof(int));
  
  for(i = 0, j = 0; i < strlen(cCPF); i++){
    if(cCPF[i] >= 48 && cCPF[i] <= 57){
      CPF[j] = cCPF[i] - 48;
      j++;
    }
  }

  bool iguais = false;

  for(i = 1; i < 11; i++){
    if(CPF[i] != CPF[0]){
      iguais = true;
    }
  }

  if(iguais == false){
    printf("CPF invalido (digitos iguais)\n");
    system("pause");
    return 2;
  }

  int soma = 0, num1, num2;
  for(i = 0; i < 9; i++){
    soma += CPF[i] * (10 - i);
  }

  if(11 - (soma % 11) > 9){
    num1 = 0;
  } else {
    num1 = 11 - soma % 11;
  }

  if(CPF[9] != num1){
    printf("CPF invalido!\n");
    system("pause");
    return 2;
  }

  soma = 0;
  for(i = 0; i < 10; i++){
    soma += CPF[i] * (11 - i);
  }

  if(11 - (soma % 11) > 9){
    num1 = 0;
  } else {
    num1 = 11 - (soma % 11);
  }

  if(CPF[10] != num1){
    printf("CPF invalido!\n");
    system("pause");
    return 2;
  }

  free(CPF);
  return 1;
  
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

  int valCPF = verificadorCPF(&p[n].CPF);

  while(valCPF == 2){
    printf("Digite seu CPF: ");
    scanf(" %[^\n]", &p[n].CPF);
    valCPF = verificadorCPF(&p[n].CPF);
    if(valCPF == 1){
      valCPF = 1;
    } else {
      valCPF = 2;
    }
  }
  
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
      printf("Telefone: %s\n", p[i].telefone);
      printf("Funcao: %s\n", p[i].funcao);
      printf("Setor: %s\n", p[i].setor);
    }
  }

  system("pause");

}

int lerArquivo(FILE *arquivo, Pessoa *p) {

  int n = 0;
  char caracter;
  arquivo = fopen("funcionarios.txt", "r");

  if(arquivo == NULL){
    printf("Erro ao abrir arquivo\n");
    return 404;
  }

  rewind(arquivo);

  while(! feof(arquivo)){
    
    p = (Pessoa*) realloc(p, ++n * sizeof(Pessoa));
    fscanf(arquivo, "id: %d\n", &p[n - 1].id_pessoa);
    fscanf(arquivo, "nome: %s\n", &p[n - 1].nome);
    fscanf(arquivo, "CPF: %s\n", &p[n - 1].CPF);
    fscanf(arquivo, "email: %s\n", &p[n - 1].email);
    fscanf(arquivo, "telefone: %s\n", &p[n - 1].telefone);
    fscanf(arquivo, "funcao: %s\n", &p[n - 1].funcao);
    fscanf(arquivo, "setor: %s\n", &p[n - 1].setor);
  }

  printf("n_pessoa: [%d]\n", n);
  system("pause");

  if(fclose(arquivo) == 0){
    for(int i = 0; i < n; i++){
      printf("id: %d\n", p[i].id_pessoa);
      printf("nome: %s\n", p[i].nome);
      printf("CPF: %s\n", p[i].CPF);
      printf("email: %s\n", p[i].email);
      printf("telefone: %s\n", p[i].telefone);
      printf("funcao: %s\n", p[i].funcao);
      printf("setor: %s\n\n", p[i].setor);
    }

    system("pause");

  }


}

int main() {

  FILE *arquivo;

  Pessoa *pessoa;
  pessoa = (Pessoa*) malloc(0 * sizeof(Pessoa));

  lerArquivo(arquivo, pessoa);
  
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