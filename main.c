#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

typedef struct{
  int id_pessoa;
  char nome[100];
  char CPF[15];
  char email[100];
  char telefone[15];
  char funcao[30];
  char setor[30];
} Pessoa;

void borda(int n){
  for(int i = 0; i < n + 1; i++){
    printf("█");
  }
  printf("\n");
}

void seletoresInicio(int n){
  printf("██");
  for(int i = 0; i < n + 1; i++){
    printf(" ");
  }
}

void vazio(){
  printf("██");
  for(int i = 0; i < 97; i++){
    printf(" ");
  }
  printf("██\n");
}

void printMenu(){
  borda(100);
  vazio();
  seletoresInicio(40);
//printf("MENU PRINCIPAL                                          ██\n");
  printf("MENU PRINCIPAL                                          ██\n");
  borda(100);
  vazio();
  seletoresInicio(35);
  printf("0 - Sair programa                                            ██\n");
  seletoresInicio(35);
  printf("1 - Cadastrar novo funcionário                               ██\n");
  seletoresInicio(35);
  printf("2 - Excluir funcionário                                      ██\n");
  seletoresInicio(35);
  printf("3 - Atualizar cadastro                                       ██\n");
  seletoresInicio(35);
  printf("4 - Informação cadastro                                      ██\n");
  seletoresInicio(35);
  printf("5 - Recrutamento e seleção                                   ██\n");
  seletoresInicio(35);
  printf("6 - Controle de ponto                                        ██\n");
  vazio();
  borda(100);
  printf("                                           Digite a opção: ");
}

void printCadastro(){
  borda(100);
  vazio();
  seletoresInicio(43);
//printf("MENU PRINCIPAL                                ██\n");
  printf("CADASTRO                                             ██\n");
  vazio();
  borda(100);
  vazio();
  seletoresInicio(40);
  printf("0 - Sair programa                                       ██\n");
  seletoresInicio(40);
  printf("Ou digite o ID                                          ██\n");
  vazio();
  borda(100);
  printf("                                            Digite o id: ");
}

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
    printf("CPF inválido (digitos iguais)\n");
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
    printf("CPF inválido!\n");
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
    printf("CPF inválido!\n");
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

void novoCadastro(int n, Pessoa *p, FILE *arquivo){

  int valID = 0, val = 0;

  system("cls");
  printCadastro();

  while (valID == 0){
    scanf("%d", &p[n].id_pessoa);

    val = validarID(n, p[n].id_pessoa, p);

    if(val >= 1){
      valID = 1;
    } else {
      printf("Id de pessoa já cadastrada!\n");
      system("pause");
      valID = 0;
    }
  }
  
  printf("                                    Digite o nome: ");
  scanf(" %[^\n]", &p[n].nome);
  printf("                                    Digite seu CPF: ");
  scanf(" %[^\n]", &p[n].CPF);
  printf("                                    Digite seu e-mail: ");
  scanf(" %[^\n]", &p[n].email);
  printf("                                    Digite seu telfone: ");
  scanf(" %[^\n]", &p[n].telefone);
  printf("                                    Digite a função: ");
  scanf(" %[^\n]", &p[n].funcao);
  printf("                                    Digite o setor: ");
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

  ordenarCadastro(p, n, n - 1, arquivo);
  
}

int excluirCadastro(Pessoa *p, FILE *arquivo, int n_pessoa, int *n){

  arquivo = fopen("funcionarios.txt", "r+");

  if(arquivo == NULL){
    printf("Erro ao abrir arquivo\n");
    system("exit");
  }

  int id, valID = 0, val = 0;

  while (valID == 0){
    printf("Informe o id do cadastro: ");
    scanf("%d", &id);

    val = validarID(n_pessoa, id, p);

    if(val >= 1){
      printf("Id de pessoa não cadastrada!\n");
      system("pause");
      valID = 0;
    } else {
      valID = 1;
    }
  }

  if(valID >= 1){

    int i, j;

    for(int i = 0; i < n_pessoa; i++){
      if(id == p[i].id_pessoa){
        j = i;
        break;
      }
    }

    char caracter;

    printf("Informações do cadastro:\n");
    printf("ID: %d\n", p[j].id_pessoa);
    printf("Nome: %s\n", p[j].nome);
    printf("CPF: %s\n", p[j].CPF);
    printf("E-mail: %s\n", p[j].email);
    printf("Telefone: %s\n", p[j].telefone);
    printf("Função: %s\n", p[j].funcao);
    printf("Setor: %s\n", p[j].setor);
    printf("Deseja mesmo excluir este cadastro? (S/N): ");
    scanf(" %c", &caracter);

    if(tolower(caracter) == 's') {
      for(j = j; j < n_pessoa - 1; j++){
        p[j].id_pessoa = p[j + 1].id_pessoa;
        strncpy(p[j].nome, p[j + 1].nome, sizeof(p[j + 1].nome));
        strncpy(p[j].CPF, p[j + 1].CPF, sizeof(p[j + 1].CPF));
        strncpy(p[j].email, p[j + 1].email, sizeof(p[j + 1].email));
        strncpy(p[j].telefone, p[j + 1].telefone, sizeof(p[j + 1].telefone));
        strncpy(p[j].funcao, p[j + 1].funcao, sizeof(p[j + 1].funcao));
        strncpy(p[j].setor, p[j + 1].setor, sizeof(p[j + 1].setor));
      } 


      p = (Pessoa*) realloc(p, --n_pessoa * sizeof(Pessoa));
      *n = n_pessoa;
      
      return p;

    } else {
      p = (Pessoa*) realloc(p, n_pessoa * sizeof(Pessoa));
      *n = n_pessoa++;
      return p;
    }

  }

}

void cadastroInformacao(Pessoa *p, int n){

  int menu, i, id;

  while (menu != 0){
    system("cls");
    printf("**************************************************\n");
    printf("*                                                *\n");
    printf("*                 Informação                     *\n");
    printf("*                                                *\n");
    printf("**************************************************\n");
    printf("*                                                *\n");
    printf("*     0 - Menu principal                         *\n");
    printf("*     1 - Listar todos os cadastros              *\n");
    printf("*     2 - Listar apenas um                       *\n");
    printf("*                                                *\n");
    printf("**************************************************\n");
    printf("Digite a opcao: ");
    scanf("%d", &menu);

    if(menu < 0 || menu > 2){
      system("cls");
      printf("Opção inválida!\n");
      system("pause");
    }

    switch (menu){
      case 0:
        return;
        break;

      case 1:
        system("cls");
        printf("**************************************************\n");
        printf("*                                                *\n");
        printf("*                 Informação                     *\n");
        printf("*                                                *\n");
        printf("**************************************************\n");
        for(i = 0; i < n; i++){
          printf("ID: %d\n", p[i].id_pessoa);
          printf("Nome: %s\n", p[i].nome);
          printf("CPF: %s\n", p[i].CPF);
          printf("E-mail: %s\n", p[i].email);
          printf("Telefone: %s\n", p[i].telefone);
          printf("Função: %s\n", p[i].funcao);
          printf("Setor: %s\n\n", p[i].setor);
        }
        system("pause");
        break;

      case 2:
        printf("Digite o id da pessoa: ");
        scanf("%d", &id);

        system("cls");
        printf("**************************************************\n");
        printf("*                                                *\n");
        printf("*                 Informação                     *\n");
        printf("*                                                *\n");
        printf("**************************************************\n");

        for(int i = 0; i < n; i++){
          if(id == p[i].id_pessoa) {
            printf("ID: %d\n", p[i].id_pessoa);
            printf("Nome: %s\n", p[i].nome);
            printf("CPF: %s\n", p[i].CPF);
            printf("E-mail: %s\n", p[i].email);
            printf("Telefone: %s\n", p[i].telefone);
            printf("Função: %s\n", p[i].funcao);
            printf("Setor: %s\n", p[i].setor);
          }
        }

        system("pause");
        break;
    }

  }

}

int ordenarCadastro(Pessoa *p, int n_fim, int n_inicio, FILE *arquivo){

  typedef struct{
    int id_pessoa;
    char nome[100];
    char CPF[15];
    char email[100];
    char telefone[15];
    char funcao[30];
    char setor[30];
  } sTemp;
  
  sTemp *pessoa;
  int i, j, k, metTam;
  if(n_inicio == n_fim) return;
  metTam = (n_inicio + n_fim) / 2;

  ordenarCadastro(p, n_inicio, metTam, arquivo);
  ordenarCadastro(p, metTam + 1, n_fim, arquivo);
  i = n_inicio;
  j = metTam + 1;
  k = 0;

  pessoa = (sTemp*) malloc((n_fim - n_inicio + 1) * sizeof(sTemp));

  while(i < metTam + 1 || j < n_fim + 1){
    if(i == metTam + 1){
      pessoa[k].id_pessoa = p[j].id_pessoa;
      strncpy(pessoa[k].nome, p[j].nome, sizeof(p[j].nome));
      strncpy(pessoa[k].CPF, p[j].CPF, sizeof(p[j].CPF));
      strncpy(pessoa[k].email, p[j].email, sizeof(p[j].email));
      strncpy(pessoa[k].telefone, p[j].telefone, sizeof(p[j].telefone));
      strncpy(pessoa[k].funcao, p[j].funcao, sizeof(p[j].funcao));
      strncpy(pessoa[k].setor, p[j].setor, sizeof(p[j].setor));
      j++;
      k++;
    }
    else if(j == n_fim + 1){
      pessoa[k].id_pessoa = p[i].id_pessoa;
      strncpy(pessoa[k].nome, p[i].nome, sizeof(p[i].nome));
      strncpy(pessoa[k].CPF, p[i].CPF, sizeof(p[i].CPF));
      strncpy(pessoa[k].email, p[i].email, sizeof(p[i].email));
      strncpy(pessoa[k].telefone, p[i].telefone, sizeof(p[i].telefone));
      strncpy(pessoa[k].funcao, p[i].funcao, sizeof(p[i].funcao));
      strncpy(pessoa[k].setor, p[i].setor, sizeof(p[i].setor));
      k++;
      i++;
    }
    else if(p[i].id_pessoa < p[j].id_pessoa){
      pessoa[k].id_pessoa = p[i].id_pessoa;
      strncpy(pessoa[k].nome, p[i].nome, sizeof(p[i].nome));
      strncpy(pessoa[k].CPF, p[i].CPF, sizeof(p[i].CPF));
      strncpy(pessoa[k].email, p[i].email, sizeof(p[i].email));
      strncpy(pessoa[k].telefone, p[i].telefone, sizeof(p[i].telefone));
      strncpy(pessoa[k].funcao, p[i].funcao, sizeof(p[i].funcao));
      strncpy(pessoa[k].setor, p[i].setor, sizeof(p[i].setor));
      k++;
      i++;
    }
    else {
      pessoa[k].id_pessoa = p[j].id_pessoa;
      strncpy(pessoa[k].nome, p[j].nome, sizeof(p[j].nome));
      strncpy(pessoa[k].CPF, p[j].CPF, sizeof(p[j].CPF));
      strncpy(pessoa[k].email, p[j].email, sizeof(p[j].email));
      strncpy(pessoa[k].telefone, p[j].telefone, sizeof(p[j].telefone));
      strncpy(pessoa[k].funcao, p[j].funcao, sizeof(p[j].funcao));
      strncpy(pessoa[k].setor, p[j].setor, sizeof(p[j].setor));
      j++;
      k++;
    }
  }

  for(i = n_inicio; i <= n_fim; i++){
    p[i].id_pessoa = pessoa[i - n_inicio].id_pessoa;
    strncpy(p[i].nome, pessoa[i - n_inicio].nome, sizeof(pessoa[i - n_inicio].nome));
    strncpy(p[i].CPF, pessoa[i - n_inicio].CPF, sizeof(pessoa[i - n_inicio].CPF));
    strncpy(p[i].email, pessoa[i - n_inicio].email, sizeof(pessoa[i - n_inicio].email));
    strncpy(p[i].telefone, pessoa[i - n_inicio].telefone, sizeof(pessoa[i - n_inicio].telefone));
    strncpy(p[i].funcao, pessoa[i - n_inicio].funcao, sizeof(pessoa[i - n_inicio].funcao));
    strncpy(p[i].setor, pessoa[i - n_inicio].setor, sizeof(pessoa[i - n_inicio].setor));
  }

  free(pessoa);

  return p;

}

void imprimirOrdenacao(Pessoa *p, FILE *arquivo, int n_pessoa){

  arquivo = fopen("funcionarios.txt", "w+");

  if(arquivo == NULL){
    printf("Erro ao abrir arquivo\n");
    system("exit");
  }

  fseek(arquivo, 0, SEEK_END);

  for(int i = 0; i < n_pessoa; i++){
    fprintf(arquivo, "id: %d\n", p[i].id_pessoa);
    fprintf(arquivo, "nome: %s\n", p[i].nome);
    fprintf(arquivo, "CPF: %s\n", p[i].CPF);
    fprintf(arquivo, "email: %s\n", p[i].email);
    fprintf(arquivo, "telefone: %s\n", p[i].telefone);
    fprintf(arquivo, "funcao: %s\n", p[i].funcao);
    if(i != (n_pessoa - 1)){
      fprintf(arquivo, "setor: %s\n\n", p[i].setor);
    } else {
      fprintf(arquivo, "setor: %s\n", p[i].setor);
    }
  }

  if(fclose(arquivo) != 0) {
    printf("Erro ao fechar arquivo\n");
    system("exit");
  }

}

int lerArquivo(FILE *arquivo, Pessoa *p, int n_pessoa, int *n){

  arquivo = fopen("funcionarios.txt", "r");

  if(arquivo == NULL){
    printf("Erro ao abrir arquivo\n");
    return;
  }

  char caracter;
  fscanf(arquivo, "%c", &caracter);
  fseek(arquivo, -1, SEEK_CUR);

  if(caracter == NULL){
    *n = 0;
    return p;
  } else {
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

      p = ordenarCadastro(p, n_pessoa - 1, 0, arquivo);
      *n = n_pessoa;

      return p;
  }
  
}

int main() {

  UINT CPAGE_UTF8 = 65001;
  UINT CPAGE_DEFAULT = GetConsoleOutputCP();

  SetConsoleOutputCP(CPAGE_UTF8);

  FILE *arquivo;
 
  Pessoa *pessoa;
  pessoa = (Pessoa*) malloc(0 * sizeof(Pessoa));

  if(pessoa == NULL){
    printf("Erro de alocação de memória!\n");
    return 1;
  }

  int menu = 1, n_pessoa = 0, aux;

  pessoa = lerArquivo(arquivo, pessoa, n_pessoa, &n_pessoa);
  if(n_pessoa != 0)
    n_pessoa = sizeof(pessoa) + 1;

  while (menu != 0){
    system("cls");
    printMenu();
    scanf("%d", &menu);

    if(menu < 0 || menu > 6){
      system("cls");
      printf("Opção inválida!\n");
      system("pause");
    }

    switch (menu){
      case 1:
      pessoa = (Pessoa*) realloc(pessoa, ++n_pessoa * sizeof(Pessoa));
      novoCadastro(n_pessoa - 1, pessoa, arquivo);
      imprimirOrdenacao(pessoa, arquivo, n_pessoa);
      break;
      
      case 2:
      if(n_pessoa > 0){
        aux = n_pessoa;
        pessoa = excluirCadastro(pessoa, arquivo, n_pessoa, &n_pessoa);
        n_pessoa--;
        if(aux > n_pessoa)
          n_pessoa++;
        imprimirOrdenacao(pessoa, arquivo, n_pessoa);
      } else {
        printf("Nenhum cadastro no banco de dados!\n");
        printf("Faça um cadastro antes usando a opção 1\n");
        system("pause");
        break;
      }

      /*case 3: atualizarCadastro();
      break;*/

      case 4:
      if(n_pessoa > 0) {
        cadastroInformacao(pessoa, n_pessoa);
      } else {
        printf("Nenhum cadastro no banco de dados!\n");
        printf("Faça um cadastro antes usando a opção 1\n");
        system("pause");
        break;
      }

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