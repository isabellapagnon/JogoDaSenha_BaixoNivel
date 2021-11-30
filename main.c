#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>

int numerosDisponiveis[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int senhaOficial[4];
int senhaTentativa[4];
int posicaoCorreta[];
int posicaoIncorreta[];
int acertou = 0;

int random_number()
{
  int result = 0;
  srand(time(NULL));
  result = (rand() % 9);
  return result;
}

void sorteio()
{
  int numeroEscolhido;
  int i = 0;
  while (i < 4)
  {
    numeroEscolhido = random_number(0, 9);
    if (verificar(senhaOficial, numeroEscolhido) == 0)
    {
      senhaOficial[i] = numeroEscolhido;
      i++;
    }
  }
}

void printSenhaOficial()
{
  hd44780_puts("Você perdeu");
  hd44780_gotoxy(4, 1);
  printf("\nVocê perdeu!");
  printf("\nSenha a ser advinhada = ");

  for (int i = 0; i < 4; i++)
  {
    printf("%d", senhaOficial[i]);
  }
}

int verificar(int senhaOficial[], int numero)
{
  for (int i = 0; i < 4; i++)
  {
    if (senhaOficial[i] == numero)
    {
      return 1;
    }
  }
  return 0;
}

void transformarSenha(int senha)
{
  senhaTentativa[0] = senha / 1000;
  senha = senha - ((senhaTentativa[0]) * 1000);

  senhaTentativa[1] = senha / 100;
  senha = senha - ((senhaTentativa[1]) * 100);

  senhaTentativa[2] = senha / 10;
  senha = senha - ((senhaTentativa[2]) * 10);

  senhaTentativa[3] = senha / 1;
}

void printSenha(int array[4])
{
  for (int i = 0; i < 4; i++)
  {
    printf("%d", array[i]);
  }
}

void comparaSenhas(int senhaTentativa[4], int senhaOficial[4])
{
  int indexPosicaoCorreta = 0;
  int indexPosicaoIncorreta = 0;
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      if (senhaOficial[j] == senhaTentativa[i])
      {
        if (senhaOficial[j] == senhaTentativa[j])
        {
          posicaoCorreta[indexPosicaoCorreta] = senhaOficial[j];
          indexPosicaoCorreta++;
        }
        else
        {
          posicaoIncorreta[indexPosicaoIncorreta] = senhaOficial[j];
          indexPosicaoIncorreta++;
        }
      }
    }
  }
  printf("Estão na posição correta: ");
  for (int i = 0; i < indexPosicaoCorreta; i++)
  {
    printf("%d,", posicaoCorreta[i]);
    ;
  }

  printf("\n");

  if (indexPosicaoCorreta == 4)
  {
    hd44780_puts("Você ganhou");
    hd44780_gotoxy(4, 1);
    printf("Você ganhou!");
    acertou = 1;
  }
  else
  {
    printf("Estão na posição incorreta:");
    for (int i = 0; i < indexPosicaoIncorreta; i++)
    {
      printf("%d,", posicaoIncorreta[i]);
    }
  }
}

int main()
{
  int tentativas = 0;
  int senha;
  sorteio();
  struct tm *data_hora_atual;
  time_t segundos;
  while ((tentativas < 10) && (acertou == 0))
  {
    hd44780_init();
    hd44780_puts("Jogo da senha!");
    hd44780_gotoxy(4, 1);
    printf("\nDigite os 4 numeros da senha:"); //Programa aceita apenas numeros positivos
    scanf("%d", &senha);

    transformarSenha(senha);
    comparaSenhas(senhaTentativa, senhaOficial);
    tentativas++;

    if (tentativas == 10 && acertou == 0)
    {
      printSenhaOficial();
    }
  }
}