#include "../include/suffix.h"

Suffix* create_suffix(String *s, int index)
{
  Suffix *sf = (Suffix*)malloc(sizeof(Suffix));

  sf->index = index;
  sf->s = s;

  return sf;  
}

void destroy_suffix(Suffix *suf)
{
  if (suf != NULL)
  {
    free(suf);
  }
}

void print_suffix(Suffix *suf)
{
  print_substring(suf->s,suf->index,suf->s->len);
}

Suffix** create_suf_array(String *text, int N)
{
  //aloca array de sufixos
  Suffix **suf = (Suffix**)malloc(N * sizeof(Suffix*));

  //alocando e inicializando array de sufixos
  for(int i=0; i < N; i++)
  {
    suf[i] = create_suffix(text,i);
  }
  return suf;
}

void destroy_suf_array(Suffix **a, int N)
{
  if(a!= NULL)
  {
    for(int i=0; i < N; i++)
    {
      if(a[i] != NULL)
      {
        destroy_suffix(a[i]);
      }
    }
  }
  free(a); 
}

void print_suf_array(Suffix **a, int N)
{
  if(a == NULL)
  {
    return;
  }
  for(int i=0; i < N; i++)
  {
    print_suffix(a[i]);
    printf("\n");
  }
}

static int compara_char (char l1 , char l2)
{
  //verificar se é letra maiuscula
  if(l1 > 64 && l1 < 91)
  {
    //verificar se é letra minuscula
    if(l2 > 96 && l2< 123)
    {
      if(l1 > (l2-32)) {return 1;} 
      if(l1 < (l2-32)) {return -1;} 
    }
  }
  //verificar se é letra maiuscula
  else if (l2 > 64 && l2 < 91)
  {
    //verificar se é letra minuscula
    if( l1 > 96 && l1 < 123)
    {
      if((l1-32) > l2) {return 1;} 
      if((l1-32) < l2) {return -1;} 
    }
  }
    
  if(l1 > l2) {return 1;} 
  if(l1 < l2) {return -1;}  

  return 0;
}

int compare_suffixos(const void *s1, const void *s2)
{

  //sufixos
  char *s3 = (*(Suffix**)s1)->s->c;
  char *s4 = (*(Suffix**)s2)->s->c;  

  //index de cada um
  int ini3 = (*(Suffix**)s1)->index;
  int ini4 = (*(Suffix**)s2)->index;

  //tamanho total da String
  int tam = (*(Suffix**)s1)->s->len;

  int max = 0;

  int compara = 0;

  //max de comparações
  if(ini3 > ini4){ max = tam - ini3; }
    else { max = tam - ini4; }
   
  //comparar caracter por caracter
  for(int i = 0; i < max; i ++)
  {
    compara = compara_char (s3[ini3 + i], s4[ini4 + i]);    

    if(compara != 0)
    {
      return compara;
    }
  }

  return (tam - ini3) - (tam - ini4);
}

double sort_suf_array_qsort(Suffix **a, int N)
{
  struct timespec beginCPU, endCPU; 
  double seconds, nanoseconds, elapsed;

  // Começa a medir o tempo
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &beginCPU);

  //ordena
  qsort(a, N, sizeof(Suffix*),compare_suffixos);

  // Termina de medir o tempo
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endCPU);

  // calcula o tempo de CPU
  seconds = endCPU.tv_sec - beginCPU.tv_sec;
  nanoseconds = endCPU.tv_nsec - beginCPU.tv_nsec;
  elapsed = seconds + nanoseconds*1e-9;             
  
  return elapsed;
}

double sort_suf_array_insort(Suffix **a, int N)
{
  struct timespec beginCPU, endCPU; 
  double seconds, nanoseconds, elapsed;

  // Começa a medir o tempo
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &beginCPU);

  int i, j, aux;

  for (i = 1; i < N; i++) 
  {    
    j = i - 1;          
      
    while (j >= 0 && compare_suffixos(&a[j],&a[j+1])>0)
    {
      //troca
      aux = a[j]->index;
      a[j]->index = a[j+1]->index;
      a[j+1]->index = aux;     

      j = j - 1;      
    }
  }

  // Termina de medir o tempo
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endCPU);

  // calcula o tempo de CPU
  seconds = endCPU.tv_sec - beginCPU.tv_sec;
  nanoseconds = endCPU.tv_nsec - beginCPU.tv_nsec;
  elapsed = seconds + nanoseconds*1e-9;        
  
  return elapsed;
}

void rank(Suffix **a, int N, String *query)
{
  int tam = a[0]->s->len;
  int fim =0;
  int ini =0;

  for(int i = 0; i < tam; i++)
  {
    //comparar o primeiro caracter
    if( a[i]->s->c[a[i]->index] == query->c[0])
    {
      //primeira letra igual
      //verifica o resto
      if (equals_substring(a[i]->s, a[i]->index, tam - 1, query)  == 1)
      {
        //evitar acesso indevido de memória no final
        if((a[i]->index + query->len + N) > tam)
        {
          fim = tam;
        }
        else
        {
          fim = (a[i]->index + query->len + N);
        }

        //evitar acesso indevido de memória no inicio
        if((a[i]->index - N) < 0)
        {
          ini = 0;
        }
        else
        {
          ini = (a[i]->index - N);
        }
        
        print_substring(a[i]->s, ini,fim);   
        printf("\n");  
      }
    }
    //ver se já não passou do local que ele deveria estar na ordem
    else if ( compara_char (a[i]->s->c[a[i]->index], query->c[0])>0)
    {
      //printf("%c",a[i]->s->c[a[i]->index]);
      //ja possou de onde poderia ser encontrado
      break;
    }   
  }
}

