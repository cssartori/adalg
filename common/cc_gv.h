/*
  gv.h

  Funções públicas do módulo graphviz.

*/
#ifndef __GV_H__
#define __GV_H__

#include <stdio.h>
#include <stdlib.h>

static FILE *fp = NULL;


static inline void __gv_test_valid_fp (const char *function_name)
{
  if (!fp){
    fprintf (stderr, "%s foi chamada, mas gv_init não foi chamada antes, abort()\n", function_name);
    abort();
  }
}

/**
 * gv_init
 *
 * Esta função deve ser chamada para inicializar o arquivo onde o
 * grafo será registrado. Um nome de arquivo, opcional, pode ser
 * passado como argumento para esta função. Caso o parâmetro com o
 * nome do arquivo seja NULL, a saída será impressa na saída de erro.
 */
void gv_init (const char *filename)
{
  //verificar se gv_init já foi chamada
  if (fp){
    fprintf (stderr, "%s:%d já foi chamada, abort()\n", __FUNCTION__, __LINE__);
    abort();

  }

  //se o nome do arquivo for válido, abre arquivo com esse nome para escrita
  if (filename){
    fp = fopen (filename, "w");
    if (!fp){
      fprintf (stderr, "%s:%d não conseguiu abrir o arquivo %s para escrita\n", __FUNCTION__, __LINE__, filename);
      abort();
    }
  }else{
    fp = stderr;
  }
  fprintf (fp, "digraph G {\n");
}

/**
 * gv_close
 *
 * Esta função deve ser chamada para fechar o arquivo com o grafo
 * registrado. Ela deve ser chamada no final do compilador.
 */
void gv_close (void)
{
  __gv_test_valid_fp (__FUNCTION__);
  fprintf (fp, "}\n");
  fclose(fp);
  fp = NULL;
}


/**
 * gv_declare
    Recebe o tipo de nó (0 - Depósito | 1 - Cliente) e o número do nó (que o identificará graficamente)

 */
void gv_declare (const unsigned int num_node)
{
  __gv_test_valid_fp (__FUNCTION__);

  char description[20];
  sprintf(description, "%u", num_node);

  fprintf (fp, "node_%i [label=\"%s\", shape=circle]\n", num_node, description);
}


/**
 * gv_connect
    Conecta dois nós no grafo.
 */
void gv_connect (const int node1, const int node2, const double weight)
{
  __gv_test_valid_fp (__FUNCTION__);

  fprintf(fp, "node_%i -> node_%i [label=%.2lf]\n", node1, node2, weight);
}

void gv_connect (const int node1, const int node2, const unsigned int weight)
{
  __gv_test_valid_fp (__FUNCTION__);

  fprintf(fp, "node_%i -> node_%i [label=%u]\n", node1, node2, weight);
}

#endif
