#ifndef TEXTO_H
#define TEXTO_H

#include "suffix.h"

/*
  le o texto de entrada contido no arquivo e elimina
  espaços duplos e quebras de linha.
  Retorna o mesmo em uma única string
*/
String* leArqTexto(char *nomeArq);

#endif