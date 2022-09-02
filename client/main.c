#include "../include/texto.h"
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
  //verificar se recebeu 5 argumentos
  if(argc != 5)
  {
    printf("Você não seguiu as regras de compilação do programa e passou ");
    if(argc < 5) { printf("menos"); }
    else { printf("mais"); }
    printf(" de 5 comandos\n"); 
    exit(1);
  }

  char op;
  int contexto = atoi(argv[3]);
  String *query = create_string(argv[4]);
  double time = 0.00;

  //Passo 1:
  //coloca o arquivo texto limpo em uma unica String
  String *string = leArqTexto(argv[2]);

  //Passo 2 :
  //Criar array de sufixos da string texto
  Suffix **sufixos = create_suf_array(string,string->len);
  //Para a opção r
  Suffix **sufixos1 = NULL;

  //para o caso s
  char *nova_query = (char*)malloc(1000*sizeof(char));
  
  //receber opções por linha de comando
  while( (op = getopt (argc , argv,"aorcs")) != -1 )
  {
    switch(op)
    {
      case 'a':
      //imprime o array de sufixos
      print_suf_array(sufixos,string->len);
      break;

      case 'o':
      // imprime o array de sufixos ordenado
      sort_suf_array_qsort(sufixos,string->len);
      print_suf_array(sufixos,string->len);
      break;

      case 'r':
      //imprime o tempo de ordenação para cada método
      sufixos1 = create_suf_array(string,string->len);
      //ordena por quickSort
      time = sort_suf_array_qsort(sufixos1,string->len);
      printf("System qsort          %.4f (s)\n",time);
      //print_suf_array(sufixos1,string->len);
      //libera 
      destroy_suf_array(sufixos1,string->len);

      //ordena por insertionSort
      time = sort_suf_array_insort(sufixos,string->len);
      printf("My_sort_insertion     %.4f (s)\n",time);
      //print_suf_array(sufixos,string->len);
      break;

      case 'c':
      printf("%s\n",argv[4]);
      sort_suf_array_qsort(sufixos,string->len);
      rank(sufixos,contexto,query);
      break;

      case 's':
      sort_suf_array_qsort(sufixos,string->len);
      printf("%s\n",argv[4]);
      //considerei também a query recebida por parâmetro
      rank(sufixos,contexto,query);      

      while(1)
      {
        //recebe uma query por linha
        fgets(nova_query,99,stdin);          
        //se string vazia, finaliza
        if((strcmp(nova_query,"\n")==0) || (strcmp(nova_query,"\0")==0 ))
        {
          break;
        }
        else
        {
          //tirar o \n que o fgets insere no final
          nova_query[strlen(nova_query)-1]='\0';
          //imprimir a query
          printf("\n%s\n",nova_query);
          //libera a antiga
          destroy_string(query);
          query = create_string(nova_query);      
          rank(sufixos,contexto,query);          
        }
      }      
    }
  }

  //libera memória
  destroy_suf_array(sufixos,string->len);
  destroy_string(string);
  destroy_string(query);
  free(nova_query);
  
 return 0;
}
