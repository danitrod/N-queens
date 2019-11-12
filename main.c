#include <stdio.h>
#include <stdlib.h>

#define False   0
#define True    1

// 
// Problema das n-rainhas, por Daniel T. Rodrigues
// 

void printTabuleiro(int n, int tab[n][n]) {
  // Mostrar o tabuleiro na tela.
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j != n-1) {
        if (tab[i][j] == 1) {
          printf("(%d, %d) | ",i,j);
        } else {
          printf("(-, -) | ");
        }
      } else {
        if (tab[i][j] == 1) {
          printf("(%d, %d)\n",i,j);
        } else {
          printf("(-, -)\n");
        }
      }
    }
    for (int k = 0; k < n; k++) {
      printf("--------");
    }
    printf("\n");
  }
}

int celulaLivre(int n, int tab[n][n], int lin, int col) {
  // Retorna se a célula parâmetro está livre ou não.

  // Coluna
  for (int i = 0; i < n; i++) {
    if (tab[i][col] == 1) {
      return False;
    }
  }

  // Diagonal Principal
  int posAcima[2] = {lin, col};
  int posAbaixo[2] = {lin, col};
  while (True) {
    posAcima[0] -= 1;
    posAcima[1] -= 1;
    if (posAcima[0] < 0 || posAcima[1] < 0) {
      break;
    }
    if (tab[posAcima[0]][posAcima[1]] == 1) {
      return False;
    }
  }
  while (True) {
    posAbaixo[0] += 1;
    posAbaixo[1] += 1;
    if (posAbaixo[0] >= n || posAbaixo[1] >= n) {
      break;
    }
    if (tab[posAbaixo[0]][posAbaixo[1]] == 1) {
            return False;
    }
  }

  // Diagonal Secundária
  posAcima[0] = lin;
  posAcima[1] = col;
  posAbaixo[0] = lin;
  posAbaixo[1] = col;
  while (True) {
    posAcima[0] -= 1;
    posAcima[1] += 1;
    if (posAcima[0] < 0 || posAcima[1] >= n) {
      break;
    }
    if (tab[posAcima[0]][posAcima[1]] == 1) {
      return False;
    }
  }
  while (True) {
    posAbaixo[0] += 1;
    posAbaixo[1] -= 1;
    if (posAbaixo[0] >= n || posAbaixo[1] < 0) {
      break;
    }
    if (tab[posAbaixo[0]][posAbaixo[1]] == 1) {
      return False;
    }
  }

  return True;
}

int inserirRainha(int n, int tab[n][n], int linha) {
  // Insere uma rainha em uma linha no tabuleiro. Retorna 1 se inserir com sucesso e 0 se não conseguir inserir.
  for (int i = 0; i < n; i++) {
    if (celulaLivre(n, tab, linha, i)) {
      if (tab[linha][i] == -1) {
        tab[linha][i] = 1;
        return True;
      }
    }
  }
  return False;
}

int main(void)
{
  int n;
  printf("n << ");
  scanf("%d",&n);
  int tabuleiro[n][n];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      tabuleiro[i][j] = -1;
    }
  }
  int completo = False, iteracoes = 0, linha = 0;
  while (completo != True) {
    iteracoes += 1;
    if (inserirRainha(n, tabuleiro, linha)) {
      // Rainha inserida com sucesso, ir para próxima linha.
      linha += 1;
    } else {
      // Não foi possível inserir rainha, aplicar backtracking (voltar uma linha e trocar rainha de posição).
      linha -= 1;
      for (int j = 0; j < n; j++) {
        // Marcar posição como inválida (0).
        if (tabuleiro[linha][j] == 1) {
          tabuleiro[linha][j] = 0;
          break;
        }
      }
      for (int i = linha+1; i < n; i++) {
        for (int j = 0; j < n; j++) {
          // Resetar possíveis posições marcadas como inválidas em linhas posteriores.
          if (tabuleiro[i][j] == 0) {
            tabuleiro[i][j] = -1;
          }
        }
      }
    }
    if (linha == n) {
      completo = True;
    }
    if (linha < 0) {
      printf("\nERRO: não foi possível obter uma solução.\n");
      exit(1);
    }
  }
  // Imprimir solução
  int solucao[n], contador = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (tabuleiro[i][j] == 1) {
        solucao[contador++] = j;
      }
    }
  }
  printTabuleiro(n, tabuleiro);
  printf("Solução encontrada com %d iterações.\n",iteracoes);
  printf("Solução: [");
  for (int i = 0; i < n; i++) {
    if (i == n-1) {
      printf("%d]\n",solucao[i]);
    } else {
      printf("%d, ",solucao[i]);
    }
  }
  return 0;
}
