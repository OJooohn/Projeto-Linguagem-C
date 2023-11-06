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

  int soma = 0, num;
  for(i = 0; i < 9; i++){
    soma += CPF[i] * (10 - i);
  }

  if(11 - (soma % 11) > 9){
    num = 0;
  } else {
    num = 11 - soma % 11;
  }

  if(CPF[9] != num){
    printf("CPF invalido!\n");
    system("pause");
    return 2;
  }

  soma = 0;
  for(i = 0; i < 10; i++){
    soma += CPF[i] * (11 - i);
  }

  if(11 - (soma % 11) > 9){
    num = 0;
  } else {
    num = 11 - (soma % 11);
  }

  if(CPF[10] != num){
    printf("CPF invalido!\n");
    system("pause");
    return 2;
  }

  free(CPF);
  return 1;
  
}

int validarID(int n_pessoa, int id, Pessoa *p){

  int val = 0, retorno = 0;

  if(n_pessoa > 1){
      for(int i = 0; i < n_pessoa; i++){
        if(id == p[i].id_pessoa){
          val = 0;
          break;
        } else {
          val = 1;
        }
      }
    }

    if(val >= 1){
      retorno = 1;
    } else {
      retorno = 0;
    }

    return retorno;

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

void novoCadastro(int n, Pessoa *p, FILE *arquivo){

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

    val = validarID(n, p[n].id_pessoa, p);

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

  arquivo = fopen("funcionarios.txt", "r+");

  if(arquivo == NULL){
    printf("Erro ao abrir arquivo\n");
    system("exit");
  }

  fseek(arquivo, 0, SEEK_END);

  fprintf(arquivo, "\nid: %d\n", p[n].id_pessoa);
  fprintf(arquivo, "nome: %s\n", p[n].nome);
  fprintf(arquivo, "CPF: %s\n", p[n].CPF);
  fprintf(arquivo, "email: %s\n", p[n].email);
  fprintf(arquivo, "telefone: %s\n", p[n].telefone);
  fprintf(arquivo, "funcao: %s\n", p[n].funcao);
  fprintf(arquivo, "setor: %s\n", p[n].setor);

  if(fclose(arquivo) != 0) {
    printf("Erro ao fechar arquivo\n");
    system("exit");
  }
  
}

int excluirCadastro(Pessoa *p, FILE *arquivo, int n_pessoa){

  arquivo = fopen("funcionarios.txt", "r+");

  if(arquivo == NULL){
    printf("Erro ao abrir arquivo\n");
    system("exit");
  }

  int id, id_pessoa, linha_id = 1;

  int valID = 0, val = 0;

  while (valID == 0){
    printf("Informe o id do cadastro: ");
    scanf("%d", &id);

    val = validarID(n_pessoa, id, p);

    if(val >= 1){
      printf("Id de pessoa nao cadastrada!\n");
      system("pause");
      valID = 0;
    } else {
      valID = 1;
    }
  }

  if(valID >= 1){
    char nome[100];
    char CPF[15];
    char email[100];
    char telefone[15];
    char funcao[30];
    char setor[30];

    while(fgetc(arquivo) != EOF){
      
      fseek(arquivo, -1, SEEK_CUR);
      
      fscanf(arquivo, "id: %d\n", &id_pessoa);

      if(id_pessoa == id) {
        break;
      } else {
        fscanf(arquivo, "nome: %[^\n]\n", &nome);
        fscanf(arquivo, "CPF: %[^\n]\n", &CPF);
        fscanf(arquivo, "email: %[^\n]\n", &email);
        fscanf(arquivo, "telefone: %[^\n]\n", &telefone);
        fscanf(arquivo, "funcao: %[^\n]\n", &funcao);
        fscanf(arquivo, "setor: %[^\n]\n", &setor);
        linha_id += 8;
      }
      
    }

    int i, j, aux;

    for(int i = 0; i < n_pessoa; i++){
      if(id == p[i].id_pessoa){
        j = i;
        aux = j;
        p[j].id_pessoa = 0;
        break;
      }
    }

    for(j = aux; j < n_pessoa - 1; j++){
      p[j].id_pessoa = p[j + 1].id_pessoa;
      strncpy(p[j].nome, p[j + 1].nome, sizeof(p[j + 1].nome));
      strncpy(p[j].CPF, p[j + 1].CPF, sizeof(p[j + 1].CPF));
      strncpy(p[j].email, p[j + 1].email, sizeof(p[j + 1].email));
      strncpy(p[j].telefone, p[j + 1].telefone, sizeof(p[j + 1].telefone));
      strncpy(p[j].funcao, p[j + 1].funcao, sizeof(p[j + 1].funcao));
      strncpy(p[j].setor, p[j + 1].setor, sizeof(p[j + 1].setor));
    } 

  }

  printf("linha do id [%d] = %d\n", id, linha_id);
  system("pause");

  p = (Pessoa*) realloc(p, --n_pessoa * sizeof(Pessoa));
  
  return p;

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

int lerArquivo(FILE *arquivo, Pessoa *p, int n_pessoa){

  arquivo = fopen("funcionarios.txt", "r");

  if(arquivo == NULL){
    printf("Erro ao abrir arquivo\n");
    return;
  }

  while(fgetc(arquivo) != EOF){
    
    fseek(arquivo, -1, SEEK_CUR);
    
    p = (Pessoa*) realloc(p, ++n_pessoa * sizeof(Pessoa));
    fscanf(arquivo, "id: %d\n", &p[n_pessoa - 1].id_pessoa);
    fscanf(arquivo, "nome: %[^\n]\n", &p[n_pessoa - 1].nome);
    fscanf(arquivo, "CPF: %[^\n]\n", &p[n_pessoa - 1].CPF);
    fscanf(arquivo, "email: %[^\n]\n", &p[n_pessoa - 1].email);
    fscanf(arquivo, "telefone: %[^\n]\n", &p[n_pessoa - 1].telefone);
    fscanf(arquivo, "funcao: %[^\n]\n", &p[n_pessoa - 1].funcao);
    fscanf(arquivo, "setor: %[^\n]\n", &p[n_pessoa - 1].setor);
  }

  if(fclose(arquivo) != 0) {
    printf("Erro ao fechar arquivo\n");
    system("exit");
  }

  return p;
  
}

int main() {

  FILE *arquivo;

  Pessoa *pessoa;
  pessoa = (Pessoa*) malloc(0 * sizeof(Pessoa));

  
  if(pessoa == NULL){
    printf("Erro de alocacao de memoria!\n");
    return 1;
  }

  int menu = 1, n_pessoa = 0;

  pessoa = lerArquivo(arquivo, pessoa, n_pessoa);
  for(int i = 0; i < sizeof(pessoa) + 1; i++){
    n_pessoa++;
  }

  for(int i = 0; i < n_pessoa; i++){
    printf("ID: %d\n", pessoa[i].id_pessoa);
    printf("nome: %s\n", pessoa[i].nome);
    printf("CPF: %s\n", pessoa[i].CPF);
    printf("E-mail: %s\n", pessoa[i].email);
    printf("Telefone: %s\n", pessoa[i].telefone);
    printf("Funcao: %s\n", pessoa[i].funcao);
    printf("Setor: %s\n\n", pessoa[i].setor);
  }
  
  system("pause");

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
      novoCadastro(n_pessoa - 1, pessoa, arquivo);
      break;
      
      case 2: 
      pessoa = excluirCadastro(pessoa, arquivo, n_pessoa);
      n_pessoa--;
      for(int i = 0; i < n_pessoa; i++){
        printf("ID: %d\n", pessoa[i].id_pessoa);
        printf("nome: %s\n", pessoa[i].nome);
        printf("CPF: %s\n", pessoa[i].CPF);
        printf("E-mail: %s\n", pessoa[i].email);
        printf("Telefone: %s\n", pessoa[i].telefone);
        printf("Funcao: %s\n", pessoa[i].funcao);
        printf("Setor: %s\n\n", pessoa[i].setor);
      }

      system("pause");
      break;

      /*case 3: atualizarCadastro();
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