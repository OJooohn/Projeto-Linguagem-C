#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GRAY     "\e[0;37m"
#define ANSI_COLOR_GREEN    "\033[32m"

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
  borda(100); vazio(); seletoresInicio(39);
  printf("MENU PRINCIPAL                                           ██\n");
  vazio(); borda(100); vazio(); seletoresInicio(5);
  printf("0 - Sair programa                                                                          ██\n");
  seletoresInicio(5);
  printf("1 - Cadastrar novo funcionário                                                             ██\n");
  seletoresInicio(5);
  printf("2 - Excluir funcionário                                                                    ██\n");
  seletoresInicio(5);
  printf("3 - Atualizar cadastro                                                                     ██\n");
  seletoresInicio(5);
  printf("4 - Informação cadastro                                                                    ██\n");
  vazio(); borda(100);
  printf("\n        Digite a opção: ");
}

void printCadastro(){
  borda(100); vazio(); seletoresInicio(42);
  printf("CADASTRO                                              ██\n");
  vazio(); borda(100); vazio(); seletoresInicio(5);
  printf("0 - Menu principal                                                                         ██\n");
  seletoresInicio(5);
  printf("1 - Digitar ID                                                                             ██\n");
  vazio(); borda(100);
}

void printExcluir(){
  borda(100); vazio(); seletoresInicio(38);
  printf("EXCLUIR CADASTRO                                          ██\n");
  vazio(); borda(100); vazio(); seletoresInicio(5);
  printf("0 - Menu principal                                                                         ██\n");
  seletoresInicio(5);
  printf("1 - Digitar ID                                                                             ██\n");
  vazio(); borda(100);
}

void printAtualizar(){
  borda(100); vazio(); seletoresInicio(38);
  printf("ATUALIZAR CADASTRO                                        ██\n");
  vazio(); borda(100); vazio(); seletoresInicio(5);
  printf("0 - Menu principal                                                                         ██\n");
  seletoresInicio(5);
  printf("1 - Digitar ID                                                                             ██\n");
  vazio(); borda(100);
}

void printInformacao(){
  borda(100); vazio(); seletoresInicio(40);
  printf("INFORMAÇÃO                                              ██\n");
  vazio(); borda(100); vazio(); seletoresInicio(5);
  printf("0 - Menu principal                                                                         ██\n");
  seletoresInicio(5);
  printf("1 - Listar todos os cadastros                                                              ██\n");
  seletoresInicio(5);
  printf("2 - Listar somente [ID] cadastro                                                           ██\n");
  seletoresInicio(5);
  printf("3 - Listar [ID] cadastro por CPF                                                           ██\n");
  seletoresInicio(5);
  printf("4 - Listar intervalo de cadastros                                                          ██\n");
  vazio(); borda(100);
}

typedef struct {

  int id_pessoa;
  char nome[70];
  char CPF[15];
  char email[70];
  char telefone[15];
  char funcao[30];
  char setor[30];

} Pessoa;

int verificarCPF(char *CPF_digitado){

  int i, j, *CPF;
  CPF = (int*) malloc(11 * sizeof(int));
  
  for(i = 0, j = 0; i < strlen(CPF_digitado); i++){
    if(CPF_digitado[i] >= 48 && CPF_digitado[i] <= 57){
      CPF[j] = CPF_digitado[i] - 48;
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
    printf(ANSI_COLOR_RED "        CPF inválido (digitos iguais)\n\n" ANSI_COLOR_GRAY); system("pause");
    return 0;
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
    printf(ANSI_COLOR_RED "        CPF inválido!\n\n" ANSI_COLOR_GRAY); system("pause");
    return 0;
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
    printf(ANSI_COLOR_RED "        CPF inválido!\n\n" ANSI_COLOR_GRAY); system("pause");
    return 0;
  }

  char padrao[15];

  for(i = 0, j = 0; i < 15; i++){

    if(i == 3 || i == 7){
      padrao[i] = '.';
      i++; j++;
      padrao[i] = CPF[j - 1] + 48;
    } else {
      if(i == 11){
        padrao[i] = '-';
        i++; j++;
        padrao[i] = CPF[j - 1] + 48;
      } else {
        padrao[i] = CPF[j] + 48;
        j++;
      }
    }
  }

  padrao[14] = '\0';

  strncpy(CPF_digitado, padrao, sizeof(padrao));

  free(CPF);
  return 1;

}

int verificarID(Pessoa *pessoa, int id_digitado, int n_pessoa){

  int i;

  for(i = 0; i < n_pessoa; i++){
    if(id_digitado == pessoa[i].id_pessoa){
      return 0; break;
    }
  }

  return 1;

}

int ordenarCadastros(Pessoa *p, int n_fim, int n_inicio){

  typedef struct{
    int id_pessoa;
    char nome[70];
    char CPF[15];
    char email[70];
    char telefone[15];
    char funcao[30];
    char setor[30];
  } sTemp;
  
  sTemp *pessoa;
  int i, j, k, metTam;
  if(n_inicio == n_fim) return;
  metTam = (n_inicio + n_fim) / 2;

  ordenarCadastros(p, n_inicio, metTam);
  ordenarCadastros(p, metTam + 1, n_fim);
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

void imprimirOrdenacao(Pessoa *pessoa, FILE *arquivo, int n_pessoa){

  arquivo = fopen("funcionarios.txt", "w+");

  if(arquivo == NULL){
    printf(ANSI_COLOR_RED "Erro ao abrir arquivo\n" ANSI_COLOR_GRAY); return;
  }

  fseek(arquivo, 0, SEEK_SET);

  for(int i = 0; i < n_pessoa; i++){
    fprintf(arquivo, "ID: %d\n", pessoa[i].id_pessoa);
    fprintf(arquivo, "Nome: %s\n", pessoa[i].nome);
    fprintf(arquivo, "CPF: %s\n", pessoa[i].CPF);
    fprintf(arquivo, "E-mail: %s\n", pessoa[i].email);
    fprintf(arquivo, "Telefone: %s\n", pessoa[i].telefone);
    fprintf(arquivo, "Função: %s\n", pessoa[i].funcao);
    if(i != (n_pessoa - 1)){
      fprintf(arquivo, "Setor: %s\n\n", pessoa[i].setor);
    } else {
      fprintf(arquivo, "Setor: %s\n", pessoa[i].setor);
    }
  }

  if(fclose(arquivo) != 0) {
    printf(ANSI_COLOR_RED "Erro ao fechar arquivo\n" ANSI_COLOR_GRAY); return;
  }
  
}

int novoCadastro(Pessoa *pessoa, int n_pessoa, int *n_pessoa_fim){

  int menu = 1, valID = 0, valCPF = 0, id;
  
  while(menu != 0){

    menu1:

    system("cls"); printCadastro(); printf("\n        Digite a opção: ");
    scanf("%d", &menu);

    if(menu < 0 || menu > 1){
      printf(ANSI_COLOR_RED "\n        Opção inválida!\n\n" ANSI_COLOR_GRAY); system("cls");
      goto menu1;
    }

    switch(menu){

      case 0: goto exit;
      break;

      case 1: goto cadastro;
      break;

    }

  }

  cadastro:

  while(valID == 0){
    system("cls"); printCadastro();
    
    printf("\n        Digite o ID: ");
    scanf("%d", &id);

    if(id == 0)
      goto exit;

    valID = verificarID(pessoa, id, n_pessoa);

    if(valID == 0){
      printf(ANSI_COLOR_RED "        ID já cadastrado! Tente novamente...\n\n" ANSI_COLOR_GRAY); system("        pause");
    }
  }

  if(valID == 1){

    pessoa = (Pessoa*) realloc(pessoa, ++n_pessoa * sizeof(Pessoa));

    pessoa[n_pessoa - 1].id_pessoa = id;
    
    printf("        Digite o nome: ");
    scanf(" %[^\n]", &pessoa[n_pessoa - 1].nome);
    printf("        Digite o CPF: ");
    scanf(" %[^\n]", &pessoa[n_pessoa - 1].CPF);
    printf("        Digite o E-mail: ");
    scanf(" %[^\n]", &pessoa[n_pessoa - 1].email);
    printf("        Digite o Telefone: ");
    scanf(" %[^\n]", &pessoa[n_pessoa - 1].telefone);
    printf("        Digite o Função: ");
    scanf(" %[^\n]", &pessoa[n_pessoa - 1].funcao);
    printf("        Digite o Setor: ");
    scanf(" %[^\n]", &pessoa[n_pessoa - 1].setor); printf("\n");

    valCPF = verificarCPF(&pessoa[n_pessoa - 1].CPF);

    while(valCPF == 0){
      
      system("cls"); printCadastro();
      printf("\n        Digite o CPF: ");
      scanf(" %[^\n]", &pessoa[n_pessoa - 1].CPF);

      valCPF = verificarCPF(&pessoa[n_pessoa - 1].CPF);
    }

    goto exit;

  }

  exit:
  *n_pessoa_fim = n_pessoa;
  return pessoa;

}

int excluirCadastro(Pessoa *pessoa, int n_pessoa, int *n_pessoa_fim){

  int menu = 1, id, valID = 1;

  while(menu != 0){

    menu2:
    
    system("cls"); printExcluir(); printf("\n        Digite a opção: ");
    scanf("%d", &menu);

    if(menu < 0 || menu > 1){
      printf(ANSI_COLOR_RED "\n        Opção inválida!\n\n" ANSI_COLOR_GRAY); system("pause");
      goto menu2;
    }

    switch(menu){

      case 0: goto exit1;
      break;

      case 1: goto excluir;
      break;

    }

  }

  excluir:
  while(valID == 1){
    
    system("cls"); printExcluir();
    printf("\n        Informe o ID do cadastro: ");
    scanf("%d", &id);

    if(id == 0)
      goto exit1;

    valID = verificarID(pessoa, id, n_pessoa);

    if(valID == 1){
      printf(ANSI_COLOR_RED "\n        ID não cadastrado! Tente novamente...\n\n" ANSI_COLOR_GRAY); system("        pause");
    }

    valID = verificarID(pessoa, id, n_pessoa);

  }

  int i;

  for(i = 0; i < n_pessoa; i++){
    if(id == pessoa[i].id_pessoa){
      break;
    }
  }

  system("cls"); printExcluir(); printf("\n");
  printf("        Informações do cadastro:\n\n");
  printf("        ID: %d\n", pessoa[i].id_pessoa);
  printf("        Nome: %s\n", pessoa[i].nome);
  printf("        CPF: %s\n", pessoa[i].CPF);
  printf("        E-mail: %s\n", pessoa[i].email);
  printf("        Telefone: %s\n", pessoa[i].telefone);
  printf("        Função: %s\n", pessoa[i].funcao);
  printf("        Setor: %s\n\n", pessoa[i].setor);

  char caracterR;
 
  printf("        Deseja continuar com a exclusão do cadastro (S/N)? ");
  scanf(" %c", &caracterR); printf("\n");

  if(toupper(caracterR) == 'N'){
    system("cls"); printExcluir();
    printf(ANSI_COLOR_RED "\n        Excluir cadastro ID número [%d] cancelado\n\n"ANSI_COLOR_GRAY, id); system("pause");
    goto exit1;
  } else {

    for(i = i; i < n_pessoa - 1; i++){
      pessoa[i].id_pessoa = pessoa[i + 1].id_pessoa;
      strncpy(pessoa[i].nome, pessoa[i + 1].nome, sizeof(pessoa[i + 1].nome));
      strncpy(pessoa[i].CPF, pessoa[i + 1].CPF, sizeof(pessoa[i + 1].CPF));
      strncpy(pessoa[i].email, pessoa[i + 1].email, sizeof(pessoa[i + 1].email));
      strncpy(pessoa[i].telefone, pessoa[i + 1].telefone, sizeof(pessoa[i + 1].telefone));
      strncpy(pessoa[i].funcao, pessoa[i + 1].funcao, sizeof(pessoa[i + 1].funcao));
      strncpy(pessoa[i].setor, pessoa[i + 1].setor, sizeof(pessoa[i + 1].setor));
    }

    pessoa = (Pessoa*) realloc(pessoa, --n_pessoa * sizeof(Pessoa));
    *n_pessoa_fim = n_pessoa;

    system("cls"); printExcluir();
    printf(ANSI_COLOR_GREEN "\n        Cadastro ID número [%d] excluído com sucesso!\n\n" ANSI_COLOR_GRAY , id); system("pause");
 
    return pessoa;
    
  }
    
  exit1: return pessoa;

}

int atualizarCadastro(Pessoa *pessoa, int n_pessoa){

  int menu = 1, i, id, valID = 1, opcao;
  
  char email[70];
  char telefone[15];
  char funcao[30];
  char setor[30];

  while(menu != 0){

    menu3:
    
    system("cls"); printAtualizar(); printf("\n        Digite a opção: ");
    scanf("%d", &menu);

    if(menu < 0 || menu > 1){
      printf(ANSI_COLOR_RED "\n        Opção inválida!\n\n" ANSI_COLOR_GRAY); system("pause");
      goto menu3;
    }

    switch(menu){

      case 0: goto exit4;
      break;

      case 1: goto atualizar;
      break;

    }

  }

  atualizar:
  while(valID == 1){

    system("cls"); printAtualizar();
    printf("\n        Informe o ID do cadastro: ");
    scanf("%d", &id);

    if(id == 0)
      goto exit4;

    valID = verificarID(pessoa, id, n_pessoa);

    if(valID == 1){
      printf(ANSI_COLOR_RED "\n        ID não cadastrado! Tente novamente...\n\n" ANSI_COLOR_GRAY); system("pause");
    }

    valID = verificarID(pessoa, id, n_pessoa);

  }

  if(valID == 0){

    for(i = 0; i < n_pessoa; i++){
      if(id == pessoa[i].id_pessoa){
        break;
      }
    }

    system("cls");
    borda(100); vazio(); seletoresInicio(38);
    printf("ATUALIZAR CADASTRO                                        ██\n");
    vazio();borda(100); vazio(); seletoresInicio(5);
    printf("1 - Alterar E-mail                                                                         ██\n");
    seletoresInicio(5);
    printf("2 - Alterar Telefone                                                                       ██\n");
    seletoresInicio(5);
    printf("3 - Alterar Função                                                                         ██\n");
    seletoresInicio(5);
    printf("4 - Alterar Setor                                                                          ██\n");
    vazio(); borda(100);
    printf("\n        Digite a opção: ");
    scanf("%d", &opcao);

    system("cls");
    borda(100); vazio(); seletoresInicio(38);
    printf("ATUALIZAR CADASTRO                                        ██\n");
    vazio();borda(100); 

    switch(opcao){


      case 1:
      printf("\n        Digite o E-mail: ");
      scanf(" %[^\n]", &email);
      strncpy(pessoa[i].email, email, sizeof(email));
      break;

      case 2:
      printf("\n        Digite o Telefone: ");
      scanf(" %[^\n]", &telefone);
      strncpy(pessoa[i].telefone, telefone, sizeof(telefone));
      break;

      case 3:
      printf("\n        Digite o Função: ");
      scanf(" %[^\n]", &funcao);
      strncpy(pessoa[i].funcao, funcao, sizeof(funcao));
      break;

      case 4:
      printf("\n        Digite o Setor: ");
      scanf(" %[^\n]", &setor);
      strncpy(pessoa[i].setor, setor, sizeof(setor));
      break;
    
    }
    
    goto exit4;

  }

  exit4:
  return pessoa;

}

void informacaoCadastro(Pessoa *pessoa, int n_pessoa){

  int menu = 1, i, id, valID = 1, inicio, fim, valMin = 0, valMax = 0, valCPF = 0;
  char CPF[15];

  while(menu != 0){

    menu2:
    
    system("cls"); printInformacao(); printf("\n        Digite a opção: ");
    scanf("%d", &menu);

    if(menu < 0 || menu > 4){
      printf(ANSI_COLOR_RED  "\n        Opção inválida!\n\n" ANSI_COLOR_GRAY); system("pause");
      goto menu2;
    }

    switch(menu){

      case 0: goto exit3;
      break;

      case 1: goto todos;
      break;

      case 2: goto um;
      break;

      case 3: goto infoCPF;
      break;

      case 4: goto intervalo;
      break;

    }

  }

  borda(100); vazio(); seletoresInicio(40);
  printf("INFORMAÇÃO                                              ██\n");
  vazio(); borda(100);

  todos:
  printf("\n        Informações dos cadastros:\n\n");
  for(i = 0; i < n_pessoa; i++){
    printf("        ID: %d\n", pessoa[i].id_pessoa);
    printf("        Nome: %s\n", pessoa[i].nome);
    printf("        CPF: %s\n", pessoa[i].CPF);
    printf("        E-mail: %s\n", pessoa[i].email);
    printf("        Telefone: %s\n", pessoa[i].telefone);
    printf("        Função: %s\n", pessoa[i].funcao);
    printf("        Setor: %s\n\n", pessoa[i].setor); 
  }
  system("pause");
  goto exit3;

  um:
  while(valID == 1){

    printf("\n        Informe o ID do cadastro: ");
    scanf("%d", &id);

    if(id == 0)
      goto exit3;

    valID = verificarID(pessoa, id, n_pessoa);

    if(valID == 1){
      printf(ANSI_COLOR_RED  "\n\n        ID não cadastrado! Tente novamente...\n" ANSI_COLOR_GRAY); system("pause");
    }

    valID = verificarID(pessoa, id, n_pessoa);

  }

  if(valID == 0){
    for(i = 0; i < n_pessoa; i++){
      if(id == pessoa[i].id_pessoa){
        break;
      }
    }

    system("cls"); borda(100); vazio(); seletoresInicio(40);
    printf("INFORMAÇÃO                                              ██\n");
    vazio(); borda(100);

    printf("\n        Informações do cadastro:\n\n");
    printf("        ID: %d\n", pessoa[i].id_pessoa);
    printf("        Nome: %s\n", pessoa[i].nome);
    printf("        CPF: %s\n", pessoa[i].CPF);
    printf("        E-mail: %s\n", pessoa[i].email);
    printf("        Telefone: %s\n", pessoa[i].telefone);
    printf("        Função: %s\n", pessoa[i].funcao);
    printf("        Setor: %s\n\n", pessoa[i].setor);
    system("        pause");

    goto exit3;
    
  }

  infoCPF:
  printf("        Digite o CPF: ");
  scanf(" %[^\n]", &CPF);
  
  valCPF = verificarCPF(&CPF);

  while(valCPF == 0){
    
    system("cls"); printInformacao();
    printf("\n        Digite o CPF: ");
    scanf(" %[^\n]", &CPF);
  
    valCPF = verificarCPF(&CPF);
  }

  for(i = 0; i < n_pessoa; i++){
    if(strcmp(CPF, pessoa[i].CPF) == 0){
      break;
    }
  }

  system("cls"); borda(100); vazio(); seletoresInicio(40);
  printf("INFORMAÇÃO                                              ██\n");
  vazio(); borda(100);

  printf("\n        Informações do cadastro:\n\n");
  printf("        ID: %d\n", pessoa[i].id_pessoa);
  printf("        Nome: %s\n", pessoa[i].nome);
  printf("        CPF: %s\n", pessoa[i].CPF);
  printf("        E-mail: %s\n", pessoa[i].email);
  printf("        Telefone: %s\n", pessoa[i].telefone);
  printf("        Função: %s\n", pessoa[i].funcao);
  printf("        Setor: %s\n\n", pessoa[i].setor);
  system("        pause");

  goto exit3;

  intervalo:
  while(valMin == 0 && valMax == 0){

    inicio:
    system("cls"); borda(100); vazio(); seletoresInicio(40);
    printf("INFORMAÇÃO                                              ██\n");
    vazio(); borda(100);

    printf("\n        Total cadastros: [%d]\n", n_pessoa);
    printf("\n        Mínimo: [%d] | Máximo: [%d]\n", 1, n_pessoa);

    printf("        Informe o começo do intervalo: ");
    scanf("%d", &inicio);

    if(inicio - 1 < 1){
      printf("\n        O valor do início não pode ser menor que o mínimo!\n"); system("pause");
      goto inicio;
    }
    if(inicio > n_pessoa){
      printf("\n        O valor do início não pode ultrapassar do valor máximo!\n"); system("pause");
      goto inicio;
    }

    fim:
    system("cls"); borda(100); vazio(); seletoresInicio(40);
    printf("INFORMAÇÃO                                              ██\n");
    vazio(); borda(100);

    printf("\n        Total cadastros: [%d]\n", n_pessoa);
    printf("\n        Mínimo: [%d] | Máximo: [%d]\n", 1, n_pessoa);
    printf("        Valor mínimo digitado: [%d]\n", inicio);

    printf("\n        Informe o final do intervalo: ");
    scanf("%d", &fim);

    if(fim - 1 > n_pessoa - 1){
      printf("\n        O valor do final não pode ultrapassar o valor máximo!\n"); system("pause");
      goto fim;
    }
    if(fim < inicio){
      printf("\n        O valor do final não pode ser menor que o valor mínimo digitado!\n"); system("pause");
      goto fim;
    }

    valMin = 1; valMax = 1;

  }

  system("cls"); borda(100); vazio(); seletoresInicio(40);
  printf("INFORMAÇÃO                                              ██\n");
  vazio(); borda(100);

  if(valMin == 1 && valMax == 1){
    if(inicio == fim){
      printf("\n        Informações do cadastro:\n\n");
      printf("        ID: %d\n", pessoa[inicio - 1].id_pessoa);
      printf("        Nome: %s\n", pessoa[inicio - 1].nome);
      printf("        CPF: %s\n", pessoa[inicio - 1].CPF);
      printf("        E-mail: %s\n", pessoa[inicio - 1].email);
      printf("        Telefone: %s\n", pessoa[inicio - 1].telefone);
      printf("        Função: %s\n", pessoa[inicio - 1].funcao);
      printf("        Setor: %s\n\n", pessoa[inicio - 1].setor);
      system("pause");
      goto exit3;
    }

    printf("\n        Informações dos cadastros:\n\n");
    for(i = inicio - 1; i < fim; i++){
      printf("        ID: %d\n", pessoa[i].id_pessoa);
      printf("        Nome: %s\n", pessoa[i].nome);
      printf("        CPF: %s\n", pessoa[i].CPF);
      printf("        E-mail: %s\n", pessoa[i].email);
      printf("        Telefone: %s\n", pessoa[i].telefone);
      printf("        Função: %s\n", pessoa[i].funcao);
      printf("        Setor: %s\n\n", pessoa[i].setor);
    }
    system("pause");
    goto exit3;
  }

  exit3: return;

}

void main(){

  UINT CPAGE_UTF8 = 65001;
  UINT CPAGE_DEFAULT = GetConsoleOutputCP();

  SetConsoleOutputCP(CPAGE_UTF8);

  FILE *arquivo;

  Pessoa *pessoa;
  pessoa = (Pessoa*) malloc(0 * sizeof(Pessoa));

  if(pessoa == NULL){
    printf(ANSI_COLOR_RED "Erro de alocação de memória!\n" ANSI_COLOR_GRAY); return;
  }

  int menu = 1, n_pessoa = 0;
  char caracter;

  arquivo = fopen("funcionarios.txt", "a+");

  if(arquivo == NULL){
    printf(ANSI_COLOR_RED "Erro ao abrir aquivo!\n" ANSI_COLOR_GRAY); return;
  }

  if(fgets(&caracter, 0, arquivo) == NULL){

    int verificacao;

    fseek(arquivo, 0, SEEK_SET);
    fscanf(arquivo, "ID: %d", &verificacao);

    if(verificacao > 0)
      goto ler;

    n_pessoa = 0;

  } else {

    ler:

    fseek(arquivo, 0, SEEK_SET);

    while(fgetc(arquivo) != EOF){

      fseek(arquivo, -1, SEEK_CUR);

      pessoa = (Pessoa*) realloc(pessoa, ++n_pessoa * sizeof(Pessoa));

      fscanf(arquivo, "ID: %d\n", &pessoa[n_pessoa - 1].id_pessoa);
      fscanf(arquivo, "Nome: %[^\n]\n", &pessoa[n_pessoa - 1].nome);
      fscanf(arquivo, "CPF: %[^\n]\n", &pessoa[n_pessoa - 1].CPF);
      fscanf(arquivo, "E-mail: %[^\n]\n", &pessoa[n_pessoa - 1].email);
      fscanf(arquivo, "Telefone: %[^\n]\n", &pessoa[n_pessoa - 1].telefone);
      fscanf(arquivo, "Função: %[^\n]\n", &pessoa[n_pessoa - 1].funcao);
      fscanf(arquivo, "Setor: %[^\n]\n", &pessoa[n_pessoa - 1].setor);
      
    }

    if(fclose(arquivo) != 0){
      printf(ANSI_COLOR_RED "Erro ao fechar o arquivo!\n" ANSI_COLOR_GRAY);
      return;
    }

    if(n_pessoa > 1){
      pessoa = ordenarCadastros(pessoa, n_pessoa - 1, 0);
      imprimirOrdenacao(pessoa, arquivo, n_pessoa);
    }
    
  }

  while(menu != 0){

    menu:

    system("cls"); printMenu();
    scanf("%d", &menu);

    if(menu < 0 || menu > 4){
      printf(ANSI_COLOR_RED "\n        Opção inválida!\n" ANSI_COLOR_GRAY); system("pause" );
      goto menu;
    }

    switch(menu){

      case 1:
      pessoa = novoCadastro(pessoa, n_pessoa, &n_pessoa);
      if(n_pessoa > 1){
        pessoa = ordenarCadastros(pessoa, n_pessoa - 1, 0);
      }
      imprimirOrdenacao(pessoa, arquivo, n_pessoa);
      
      break;

      case 2:
      pessoa = excluirCadastro(pessoa, n_pessoa, &n_pessoa);
      imprimirOrdenacao(pessoa, arquivo, n_pessoa);
      break;

      case 3:
      pessoa = atualizarCadastro(pessoa, n_pessoa);
      imprimirOrdenacao(pessoa, arquivo, n_pessoa);
      break;

      case 4:
      informacaoCadastro(pessoa, n_pessoa);
      break;

    }

  }

  free(pessoa);
  return;
  
}