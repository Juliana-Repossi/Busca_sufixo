#include "../include/texto.h"

String* leArqTexto(char *nomeArq)
{
  FILE *arq = fopen(nomeArq,"r");

  if(arq == NULL)
  {
    printf("Falha na abertura do arquivo %s\n",nomeArq);
    exit(2);
  }

  int qtd = 0;
  //lê a quantidade de caracteres do texto
  fscanf(arq,"%d\n",&qtd);

  //alocar uma string em c do 
  //tamanho do total de caracteres + 1 ('\0')
  char *string = (char*)malloc((qtd + 1)*sizeof(char));
  int cont = 0;

  char aux;
  int space = 0;

  while( qtd != 0 )
  {
    //lê um caracter do arquivo
    fscanf(arq,"%c",&aux); 
    qtd --;

    //verificar se é espaço repetido ou quebra de linha
    if(aux == '\n')
    {
      space ++;
      if(space == 1)
      {
        string[cont] = ' ';
        cont ++;
      }      
      continue;
    }
    else if (aux == ' ')
    {
      space ++;
      if( space != 1)
      {
        continue;
      }      
    }
    else
    {
      space = 0;
    }

    //coloca no vetor
    string[cont] = aux;
    cont ++;
  }

  //coloca '\0' na ultima posição
  string[cont] = '\0';

  //converter para o tipo String
  String* S = create_string(string);

  //fechar arquivo
  fclose(arq);
  //liberar string auxiliar
  free(string);

  return S;
}