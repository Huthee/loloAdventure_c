
/// Bibliotecas usadas:
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio2.h>
#include <locale.h>
#include <math.h>
#include <string.h>

/// Autores:
///   GABRIEL ALVES BOHRER
///   PEDRO AFONSO TREMEA SERPA


/// DEFINE��O DE DADOS

typedef struct {
 int identificador;
 int totalpts;
 int ultimafase;
 int vidas;
 char nomejogador[9];

}save_st;


/// FUN��ES
void mostra_logo()
{
    textcolor(CYAN);
    cprintf("\n                                                                                           @");
    cprintf("\n                                                                                            @@");
    cprintf("\n                                  @@@@           @@@@@@@@@@@@@  @@@@           @@@@@@@@@@@@@ @@  @@@@@@@@@@@@@");
    cprintf("\n                                  @@@@           @@@@@@@@@@@@@  @@@@           @@@@@@@@@@@@@  @  @@@@@@@@@@@@@");
    cprintf("\n                                  @@@@           @@@@     @@@@  @@@@           @@@@     @@@@  @  @@@@     ");
    cprintf("\n                                  @@@@           @@@@     @@@@  @@@@           @@@@     @@@@     @@@@ ");
    cprintf("\n                                  @@@@           @@@@     @@@@  @@@@           @@@@     @@@@     @@@@@@@@@@@@@");
    cprintf("\n                                  @@@@           @@@@     @@@@  @@@@           @@@@     @@@@     @@@@@@@@@@@@@");
    cprintf("\n                                  @@@@           @@@@     @@@@  @@@@           @@@@     @@@@              @@@@");
    cprintf("\n                                  @@@@           @@@@     @@@@  @@@@           @@@@     @@@@              @@@@");
    cprintf("\n                                  @@@@@@@@@@@@@  @@@@@@@@@@@@@  @@@@@@@@@@@@@  @@@@@@@@@@@@@     @@@@@@@@@@@@@");
    cprintf("\n                                  @@@@@@@@@@@@@  @@@@@@@@@@@@@  @@@@@@@@@@@@@  @@@@@@@@@@@@@     @@@@@@@@@@@@@\n\n\n");


    textcolor(LIGHTGREEN);
    cprintf("\n       @@@@@@@@@    @@@@@@@@@@@   @@@@        @@@@  @@@@@@@@@@@@@  @@@@     @@@@  @@@@@@@@@@@@@  @@@@     @@@@  @@@@@@@@@@     @@@@@@@@@@@@@ ");
    cprintf("\n     @@@@@@@@@@@@@  @@@@@@@@@@@@  @@@@        @@@@  @@@@@@@@@@@@@  @@@@@    @@@@  @@@@@@@@@@@@@  @@@@     @@@@  @@@@@@@@@@@    @@@@@@@@@@@@@ ");
    cprintf("\n     @@@@     @@@@  @@@@     @@@@ @@@@        @@@@  @@@@           @@@@@@   @@@@      @@@@@      @@@@     @@@@  @@@@     @@@   @@@@          ");
    cprintf("\n     @@@@     @@@@  @@@@     @@@@  @@@@      @@@@   @@@@           @@@@ @   @@@@      @@@@@      @@@@     @@@@  @@@@     @@@@  @@@@ ");
    cprintf("\n     @@@@     @@@@  @@@@     @@@@   @@@@    @@@@    @@@@@@@@@@@@@  @@@@ @@  @@@@      @@@@@      @@@@     @@@@  @@@@@@@@@@@@@  @@@@@@@@@@@@@ ");
    cprintf("\n     @@@@@@@@@@@@@  @@@@     @@@@    @@@@  @@@@     @@@@@@@@@@@@@  @@@@  @  @@@@      @@@@@      @@@@     @@@@  @@@@@@@@@@@@@  @@@@ ");
    cprintf("\n     @@@@@@@@@@@@@  @@@@     @@@@     @@@@@@@@      @@@@           @@@@  @@ @@@@      @@@@@      @@@@     @@@@  @@@@     @@@@  @@@@ ");
    cprintf("\n     @@@@     @@@@  @@@@@@@@@@@@       @@@@@@       @@@@@@@@@@@@@  @@@@   @@@@@@      @@@@@      @@@@@@@@@@@@@  @@@@     @@@@  @@@@@@@@@@@@@ ");
    cprintf("\n     @@@@     @@@@  @@@@@@@@@@@@        @@@@        @@@@@@@@@@@@@  @@@@   @@@@@@      @@@@@      @@@@@@@@@@@@@  @@@@     @@@@  @@@@@@@@@@@@@ ");
}

void menu_Inicial()     /// Fun��o que chama o menu inicial do jogo
{
    system("cls"); //Limpa Tela

    mostra_logo();

    textcolor(CYAN);
    cprintf("\n\n\n\t     [N - Novo Jogo]");
    cprintf("\t\t [C - Carregar Jogo]");
    cprintf("\t\t [T - Tutorial]");
    cprintf("\t\t [M - Cr�ditos]");
    cprintf("\t\t [S - Sair]\n\n");
}

char le_opcao()     /// Fun��o para ler a op��o escolhida do menu
{
    char op;

    op = getch();
    op = toupper(op);   // le um uma letra do teclado, convertendo-a para maiuscula

    if(!(op == 'N' || op == 'C' || op == 'M' || op == 'T' || op == 'S'))    // se o caracter for diferente dos especificados, chama a mesma fun��o novamente
    {
        op = le_opcao();
    }

            switch (op)     // Sen�o, seleciona qual fun��o sera chamada conforme o valor do caracter 'op'
            {
            case 'N': novo_jogo(); break;
            case 'C': carregar_jogo(); break;
            case 'T': sobre_jogo(); break;
            case 'M': creditos(); break;
            case 'S': exit(0); break;
        }
}

int mostra_lista_saves (int inic, int term)     /// Fun��o que mostra uma lista crescente de todos os saves do arquivo 'Saves.bin' e retorna o save(slot) de um jogador
{
/// Vari�veis:
    int i, tecla, retorno, j = 0, fim = 1;
    FILE *allsaves;
    save_st save;

    allsaves = fopen ("Saves/AllSaves.bin", "rb");  // abre o arquivo bin�rio

    system("cls");

    textcolor(CYAN);
    cprintf("\n\n\n\t\t\t\t\t CARREGAR JOGO");
    textcolor(LIGHTGREEN);

    while (!feof(allsaves) && fim)      // enquanto o arquivo n�o chegar ao fim
    {
         if( (fread(&save, sizeof(save), 1, allsaves)) == 1)    // leitura da informa��o em save_st do arquivo binario e armazenada no buffer 'save'
            {
                j++;    // a cada struct, soma+1 em j
            }

        else    // se allsaves for 0, termina o loop
        {
            fim = 0;
        }
    }

    /// Organiza��o da quantidade de saves que ser�o apresentados a cada p�gina:
    if (term > j)   //impede paginas al�m do maior save
    {
        mostra_lista_saves (j-3, j);
    }

    if( inic < 0)
    {
        if(j < 3)
        {
            mostra_lista_saves (0, j);
        }

        else
        {
            mostra_lista_saves (0,2);
        }


    }
    /// Impress�o de cada campo da struct de allsaves:
    else
    {
        for (i = inic; i<term+1; i++)
        {
            rewind(allsaves);
            fseek(allsaves, i*sizeof(save_st), 1);

        if( (fread(&save, sizeof(save), 1, allsaves)) ==1)
            {
                textcolor(LIGHTGREEN);
                cprintf ("\n\n\t\t\t\t\t Slot: %d", save.identificador);
                cprintf ("\n\t\t\t\t\t Pontos: %d", save.totalpts);
                cprintf ("\n\t\t\t\t\t Fase: %d", save.ultimafase);
                cprintf ("\n\t\t\t\t\t Vidas: %d", save.vidas);
                cprintf ("\n\t\t\t\t\t Nickname: %s \n",save.nomejogador);
            }
        }

        fclose(allsaves);   // fechamento do arquivo bin�rio
        fflush(stdin);

        textcolor(CYAN);
        cprintf("\n\n\t\t\t [A - Pagina anterior] \t\t [D - Pagina seguinte] \n\n\t\t\t [C - Carregar slot] \t\t [S - Sair] \n");

        /// Leitura da variavel tecla para a troca de pagina, carregar um save ou retornar ao menu inicial:
        tecla = getch();
        tecla = toupper(tecla);

        if(tecla == 'D')    // Avan�a uma pagina
        {
            mostra_lista_saves(inic+3, term+3);
        }

        else if(tecla == 'A')   // Volta uma pagina
        {
            mostra_lista_saves(inic-3, term-3);
        }
        else if(tecla == 'C')   // retorna o valor do 'save.identificador' para carregar o jogo salvo
        {
            cprintf ("\n\n\t\t\t\t\t\    slot: ");
            scanf ("%d", &retorno);
            return retorno-1;
        }

        else if(tecla == 'S')   // Saida para o menu Inicial novamente
        {
            menu_Inicial();
            le_opcao();
        }

        else    // Se o caracter escolhido n�o for dentro dos esperados, executa a lista novamente
        {
            mostra_lista_saves(inic, term);
        }
    }
}

void novo_jogo()    /// Fun��o para salvar os dados de um novo jogador e iniciar o jogo
{
 /// Vari�veis:
    FILE *savefile, *allsaves;
    save_st save;
    int j = 1, fim = 1;

    system("cls");
    fflush(stdin);

    textcolor(CYAN);
    cprintf("\n\n\n\n\n\n\n\t\t\t\t\tNOVO JOGO");

    allsaves = fopen ("Saves/AllSaves.bin", "ab+"); // abre o arquivo bin�rio 'AllSaves' para escrever um novo dado ao final

    rewind(allsaves);


    while (!feof(allsaves) && fim)
    {
        if( (fread(&save, sizeof(save), 1, allsaves)) == 1){    // Enquanto n�o chega ao final do arquivo, soma a variavel j para saber em qual slot vago sera escrito as informa��es do novo jogador
            j++;

        /// Criando os dados do novo jogador:
        }else{
            textcolor(LIGHTGREEN);
            cprintf("\n\n\t\t\t   Jogador, digite o seu 'Nick': ");
            scanf(" %s", save.nomejogador);
            fflush(stdin);

            /// Dados pr�-determinados para qualquer jogador que comece do inicio:
            save.identificador = j;
            save.totalpts = 0;
            save.ultimafase = 1;
            save.vidas = 5;

            fim=0;  //  t�rmino  da cria��o dos dados do novo jogador
        }
    }

    fwrite (&save, sizeof(save), 1, allsaves);  // Escreve os dados no arquivo bin�rio
    fclose(allsaves);   // fechamento do arquivo


    system("cls");

    /// Interface com as informa��es do novo jogador:
    textcolor(CYAN);
    cprintf("\n\n\n\n\n\n\n\t\t\t\t\t NOVO JOGO");

    textcolor(LIGHTGREEN);
    printf ("\n\n\n\t\t\t\t\t Slot: %d \n\n\t\t\t\t\t Pontos: %d \n\n\t\t\t\t\t Fase: %d \n\n\t\t\t\t\t Vidas: %d \n\n\t\t\t\t\t Nickname: %s \n\n\n\n\n\n\t\t\t        ", save.identificador, save.totalpts, save.ultimafase, save.vidas, save.nomejogador);

    textcolor(CYAN);
    system("Pause");

    /// Chama a primeira fase para o novo jogador, ja registrado
    abre_fase(save);

}

void carregar_jogo()    /// Fun��o para carregar os dados de um jogador e retornar ao jogo na ultima fase jogada
{
/// Vari�veis
    FILE *allsaves;
    save_st save;
    int fim = 1, i=0, j=0, escolha, num = 0;

    allsaves = fopen ("Saves/AllSaves.bin", "rb");  // Abertura do arquivo bin�rio 'AllSaves'

    if (allsaves == NULL)   // Se tentar carregar um jogo mas nenhum save existir, cria um novo
    {
        novo_jogo();
    }

    /// Contabiliza o numero de saves existentes (slots ja ocupados):
    while (!feof(allsaves) && fim)
    {
        if( (fread(&save, sizeof(save), 1, allsaves)) == 1)
            {
                num++;
            }
        else
        {
            fim = 0;
        }
    }

    fclose(allsaves);   // fechamento do arquivo bin�rio

    system("cls");
    fflush(stdin);

    /// Sele��o do identificador (slot) de um save para carregar o jogo desejado
    if (num < 3)
    {
        escolha = mostra_lista_saves(0, num);
    }

    else
    {
        escolha = mostra_lista_saves(0, 2);
    }

    /// Abre o arquivo bin�rio, procura a struct que contem o identificador (slot) escolhido e abre a fase

    allsaves = fopen ("Saves/AllSaves.bin", "rb");
    rewind(allsaves);
    fseek(allsaves, escolha*sizeof(save_st), 1);

    if( (fread(&save, sizeof(save), 1, allsaves)) ==1)
        {
            abre_fase(save);
        }

    else    // Se o slot n�o existir, retorna ao menu inicial
    {
        menu_Inicial();
        le_opcao();
    }
}

void salva_jogo(save_st save)   /// Fun��o para salvar o progresso do jogador ao fim de cada fase
{
/// Vari�veis
    char tecla;
    FILE *allsaves;

    system("cls");

    /// Interface
    textcolor(LIGHTGREEN);
    cprintf("\n\n\n\n\n\n\n\t\t\t\t         Fase conclu�da!!");
    cprintf("\n\n\n\n\n\t\t\t\t    Deseja salvar o progresso?");
    cprintf("\n\n\n\n\n\t\t\t\t      [S - Sim]    [N - Nao] \n\n");

    /// Leitura da tecla
    tecla = getch();
    tecla = toupper(tecla);

    fflush(stdin);

    if ((tecla != 'S') && (tecla != 'N'))   // Se a tecla for diferente das op��es esperadas, pergunta novamente
    {
        salva_jogo(save);
    }

    else if(tecla == 'S')   // Se o jogador quiser salvar, abre o arquivo binario e salva os novos dados obtidos no slot correto, fechando o arquivo ao final
    {
        allsaves = fopen ("Saves/AllSaves.bin", "rb+");
        rewind(allsaves);

        fseek(allsaves, (save.identificador-1)*sizeof(save_st), 1);

        fwrite (&save, sizeof(save), 1, allsaves);

        fclose(allsaves);

    }else   // Se o jogador n�o quiser salvar o progresso, segue para a proxima fase
    {
        abre_fase(save);
    }
}

void abre_fase(save_st save)    /// Fun��o para ler cada uma das fases do jogo conforme a situa��o do jogador e carrega-las em uma matriz (buffer)
{
/// Vari�veis:
    FILE *fases;
    char matriz_fase[14][13];
    int i, j, BX, BY;

    system("cls");

    /// Se o jogador n�o tiver mais vidas suficientes para continuar a jogar, encerra o jogo e retorna ao menu inicial
    if (save.vidas < 0)
    {
        system("cls");

        textcolor(RED);
        cprintf("\n\n\n\n\n\n\n\t\t\t\t\t GAME OVER");

        textcolor(CYAN);
        cprintf("\n\n\n\n\t\t   Voc� perdeu todas as vidas. Retornando para a tela inicial, onde ");
        cprintf("\n\t\t\t    voce podera tentar mais uma vez!!\n\n\n\n\n\n\n\n\n\t\t\t    ");

        textcolor(RED);
        system("Pause");

        menu_Inicial();
        le_opcao();

    }

    /// Caso o jogador ainda possua vidas, seleciona qual fase ele esta conforme o dado de sua struct, abrindo o arquivo texto da fase correspondente
    switch(save.ultimafase)
    {
      case 1:
        {
            fases = fopen ("Fases/fase1.txt", "r");
            break;
        }
     case 2:
        {
            fases = fopen ("Fases/fase2.txt", "r");
            break;
        }
     case 3:
        {
            fases = fopen ("Fases/fase3.txt", "r");
            break;
        }
    case 4:
        {
            fases = fopen ("Fases/fase4.txt", "r");
            break;
        }
    case 5:
        {
            fases = fopen ("Fases/fase5.txt", "r");
            break;
        }
    case 6:
        {
            fases = fopen ("Fases/fase6.txt", "r");
            break;
        }
    case 7:
        {
            fases = fopen ("Fases/fase7.txt", "r");
            break;
        }
    case 8:
        {
            fases = fopen ("Fases/fase8.txt", "r");
            break;
        }
    case 9:
        {
            fases = fopen ("Fases/fase9.txt", "r");
            break;
        }
    case 10:
        {
            fases = fopen ("Fases/fase10.txt", "r");
            break;
        }
    case 11:
        {
            fases = fopen ("Fases/fase11.txt", "r");
            break;
        }
    case 12:
        {
            fases = fopen ("Fases/fase12.txt", "r");
            break;
        }
    case 13:
        {
            fases = fopen ("Fases/fase13.txt", "r");
            break;
        }
    case 14:
        {
            fases = fopen ("Fases/fase14.txt", "r");
            break;
        }
    case 15:
        {
            fases = fopen ("Fases/fase15.txt", "r");
            break;
        }
    case 16:    // Ap�s a �ltima fase do jogo (fase 15), ao inv�s de abrir o proximo arquivo texto, termina o jogo
        {
            venceu_jogo(save);
            break;
        }
    }

    /// Leitura do arquivo texto, passando os dados para a matriz_fase
    if((fread(&matriz_fase, sizeof(matriz_fase), 1, fases)) ==1)
        {
            for(i = 0; i < 14; i++)
            {
                for(j = 0; j < 13; j++)
                {
                    fscanf(fases, "%c", &matriz_fase[i][j]);
                }
            }
        }

        /// Identifica a posi��o do Ba� na fase e armazena-a em BX e BY
        for (i = 0; i < 14; i++)
        {
            for (j = 0; j < 13; j++)
            {
                if (matriz_fase[i][j] == 'T')
                    {
                        BX = i;
                        BY = j;
                    }
            }
        }

    fclose(fases);  // fechamento do arquivo texto

    system("cls");

    /// Assim que a fase esta pronta para ser carregada, chama a fun��o mapa
    mapa(save, matriz_fase, 0, BX, BY);

}

int mapa(save_st save, char matriz_deslocada[14][13], int creditos, int BX, int BY)     /// Fun��o para desenhar as fases do jogo, executar os comandos de movimento do jogador e dos inimigos e contabilizar os dados de jogo
{
/// Vari�veis:

    int i, j;                           // contadores para a leitura das linhas e colunas da matriz que armazena a fase
    int x, y;                           // vari�veis que armazenam a posi��o do Lolo (jogador)
    int tecla;                          // Recebe a dire��o em que o Lolo se movimentar� a cada "casa" deslocada
    int buffer[14][13];                 // Buffer para armazenar as trocas de posi��es dos inimigos
    int inimigos = 0, randmov = 0;      // Vari�veis para armazenar a quantidade de inimigos em cada fase e o valor que ser� utilizado para aleatorizar o seu movimento

    system("cls");

    /// Se o jogador n�o possuir cr�ditos (cora��es) suficientes para derrotar um inimigo, perde 1 vida
    if (creditos < 0)
    {
        save.vidas--;
        abre_fase(save);
    }

    /// Interface com informa��es sobre o jogo e jogador
    textcolor(CYAN);
    cprintf("\n\n\n\n\n\t\t\t\t\t   FASE %d \n", save.ultimafase);

    textcolor(LIGHTGREEN);
    cprintf ("\n\t\t\t\t         pts:%d", save.totalpts);

    textcolor(CYAN);
    cprintf ("\t %cx%d", 2, save.vidas);

    textcolor(RED);
    cprintf ("\n\n\t\t\t\t\t     %cx%d \n\t\t\t\t\t", 3, creditos);

        /// Identifica em que posi��o inicial encontra-se Lolo e armazena-a em 'x' e 'y' / Identifica em que posi��es est�o os inimigos e contabiliza a sua quantidade.
        for(i = 0; i < 14; i++)
        {
            for(j = 0; j < 13; j++)
            {
                buffer[i][j] = matriz_deslocada[i][j];

                if (matriz_deslocada[i][j] == '@')
                {
                    x = i;
                    y = j;
                }

                else if (matriz_deslocada[i][j] == 'E')
                {
                    inimigos++;
                }
            }
        }

        /// Movimenta��o randomica de cada inimigo:
        for(i = 0; i < 14; i++)
        {
            for(j = 0; j < 13; j++)
            {
                if (matriz_deslocada[i][j] == 'E')
                {
                    randmov = (rand() % 4);    // randmov recebe valores entre 0 e 3, randomicamente atrav�s de rand()

                    switch(randmov)
                    {

                    case 0:   // move pra cima
                        {
                            if (matriz_deslocada[i-1][j-1] == ' ')
                            {
                                buffer[i][j] = ' ';
                                buffer[i-1][j-1] = 'E';
                            }
                            break;
                        }

                    case 1:  // move pra baixo
                        {
                            if (matriz_deslocada[i+1][j+1] == ' ')
                            {
                                buffer[i][j] = ' ';
                                buffer[i+1][j+1] = 'E';
                            }
                            break;
                        }

                    case 2:  // move pra esquerda
                        {
                            if(matriz_deslocada[i][j-1] == ' ')
                            {
                                buffer[i][j] = ' ';
                                buffer[i][j-1] = 'E';
                            }
                            break;
                        }

                    case 3:  ///move pra direita
                        {
                            if(matriz_deslocada[i][j+1] == ' ')
                            {
                                buffer[i][j] = ' ';
                                buffer[i][j+1] = 'E';
                            }
                            break;
                        }

                    }
                }
            }
        }

        /// Identifica a posi��o do Ba� na fase e, se ainda existirem inimigos na fase, cria uma mascara para n�o mostrar a posi��o do Ba� para o jogador:
        for(i = 0; i < 14; i++)
        {
            for(j = 0; j < 13; j++)
            {
                matriz_deslocada[i][j] = buffer[i][j];

                if (matriz_deslocada[i][j] == 'T')
                {
                    if (inimigos != 0)
                    {
                        desenha (' ');
                    }

                    else
                    {
                        desenha(matriz_deslocada[i][j]);
                    }
                }

                else
                {
                    desenha(matriz_deslocada[i][j]);
                }
            }
        }

        /// Interface de Legenda

        textcolor(LIGHTGREEN);
        cprintf("\n\n\t\t\t\t    [Movimente com as setas]");
        cprintf("\n\t\t\t\t    [Esc para voltar ao menu]\n");

        textcolor(CYAN);
        cprintf("\n\t\t\t\t\t %c LoLo \n\t\t\t\t\t ",2);

        textcolor(BROWN);
        textbackground(BROWN);
        cprintf(" ");

        textcolor(BROWN);
        textbackground(BLACK);
        cprintf("Parede \n\t\t\t\t\t ");

        textcolor(LIGHTCYAN);
        textbackground(LIGHTCYAN);
        cprintf(" ");

        textcolor(LIGHTCYAN);
        textbackground(BLACK);
        cprintf("Agua");

        textcolor(RED);
        cprintf("\n\t\t\t\t\t %c Coracao \n\t\t\t\t\t ", 003);

        textcolor(BLUE);
        textbackground(GREEN);
        cprintf("%c", 29);
        textbackground(BLACK);
        cprintf("Bloco movivel");

        textcolor(LIGHTMAGENTA);
        cprintf("\n\t\t\t\t\t %c Inimigo", 31);

        /// Tira a m�scara da posi��o do Ba� quando a quantidade de inimigos for zero

        if (matriz_deslocada[BX][BY] != 'T' && inimigos == 0)
        {
            matriz_deslocada[BX][BY] = 'T';
        }

        cprintf("\n");
        fflush(stdin);

        /// Leitura da tecla para realizar o movimento de Lolo
        tecla = getch();
        tecla = toupper(tecla);

        fflush(stdin);

        /// OBS.: Para cada dire��o que o jogador venha a se mover (para cima, para baixo, para direita ou para a esquerda), verifica que tipo de objeto h� em seu caminho.
        /// Dependendo da situa��o, realiza uma atualiza��o diferente e imprime o mapa novamente. Os casos:
        ///                                                                     Se for um espa�o vazio, Lolo vai a ele naturalmente
        ///                                                                     Se for uma Parede (P), Lolo permanecer� na sua posi��o atual
        ///                                                                     Se for um Cora��o (C), Lolo vai a ele, substituindo-o por uma posi��o vazia e somando +1 em cr�ditos
        ///                                                                     Se for um Inimigo (E), Lolo o derrota, substituindo-o por uma posi��o vazia, perde um cr�dito e ganha +1 ponto (outras verifica��es ocorrem no ap�s o chamamento do mapa)
        ///                                                                     Se for um espa�o com �gua (A), Lolo se afogar�, perdendo 1 vida e seus cr�ditos
        ///                                                                     Se for um Ba� (T), Lolo abre o ba�, indo para a pr�xima fase e chamando a fun��o de salvar jogo
        ///                                                                     Se for um Bloco M�vel (B), Lolo consegue empurra-lo para a dire��o em que esta andando.
        ///                                                                                 Se a posi��o a frente for um espa�o vazio, ele avan�ar�.
        ///                                                                                 Se for �gua, ele far� uma ponte, transformando-se em um espa�o vazio e n�o poder� ser mais empurrado.

        /// OBS.2: Ap�s Lolo derrotar um inimigo, verifica se a sua pontua��o � m�ltipla de 10; caso seja, o jogador ganha +1 vida.

        switch (tecla)
        {
            case (27):  // Tecla ESC = Sair do jogo
            {
                menu_Inicial();
                le_opcao();
            }

            case (72): ///cima
            {
                if(matriz_deslocada[x-1][y-1] == ' ')
                {
                    matriz_deslocada[x-1][y-1] = '@';
                    matriz_deslocada[x][y] = ' ';
                    mapa (save, matriz_deslocada, creditos, BX, BY);
                }

                else if(matriz_deslocada[x-1][y-1] == 'P')
                {
                    mapa (save, matriz_deslocada, creditos, BX, BY);
                }

                else if(matriz_deslocada[x-1][y-1] == 'C')
                {
                    matriz_deslocada[x-1][y-1] = '@';
                    matriz_deslocada[x][y] = ' ';
                    creditos++;
                    mapa (save, matriz_deslocada, creditos, BX, BY);
                }

                else if(matriz_deslocada[x-1][y-1] == 'E')
                {
                    matriz_deslocada[x-1][y-1] = '@';
                    matriz_deslocada[x][y] = ' ';
                    creditos--;
                    save.totalpts++;

                    if ((save.totalpts % 10 == 0) && (save.totalpts != 0))
                    {
                        save.vidas++;
                    }

                    mapa (save, matriz_deslocada, creditos, BX, BY);
                }

                else if(matriz_deslocada[x-1][y-1] == 'A')
                {
                    save.vidas--;
                    abre_fase(save);
                }

                else if(matriz_deslocada[x-1][y-1] == 'T')
                {
                    if (inimigos==0)
                    {
                        save.ultimafase++;
                        //abre_fase(save);
                        salva_jogo(save);
                    }
                    else
                    {
                        matriz_deslocada[x-1][y-1] = '@';
                        matriz_deslocada[x][y] = ' ';
                        mapa (save, matriz_deslocada, creditos, BX, BY);
                    }
                }

                else if(matriz_deslocada[x-1][y-1] == 'B')
                {
                    if(matriz_deslocada[x-2][y-2] == ' ')
                    {
                        matriz_deslocada[x-2][y-2] = 'B';
                        matriz_deslocada[x-1][y-1] = '@';
                        matriz_deslocada[x][y] = ' ';
                        mapa (save, matriz_deslocada, creditos, BX, BY);
                    }

                    else if(matriz_deslocada[x-2][y-2] == 'A')
                    {
                        matriz_deslocada[x-2][y-2] = ' ';
                        matriz_deslocada[x-1][y-1] = '@';
                        matriz_deslocada[x][y] = ' ';
                        mapa (save, matriz_deslocada, creditos, BX, BY);
                    }

                    else
                    {
                        mapa (save, matriz_deslocada, creditos, BX, BY);
                    }

                }
            }

            case (80): ///baixo
            {
                if(matriz_deslocada[x+1][y+1] == ' ')
                {
                    matriz_deslocada[x+1][y+1] = '@';
                    matriz_deslocada[x][y] = ' ';
                    mapa (save, matriz_deslocada, creditos, BX, BY);
                }

                else if(matriz_deslocada[x+1][y+1] == 'P')
                {
                    mapa (save, matriz_deslocada, creditos, BX, BY);
                }

                else if(matriz_deslocada[x+1][y+1] == 'C')
                {
                    matriz_deslocada[x+1][y+1] = '@';
                    matriz_deslocada[x][y] = ' ';
                    creditos++;
                    mapa (save, matriz_deslocada, creditos, BX, BY);
                }

                else if(matriz_deslocada[x+1][y+1] == 'E')
                {
                    matriz_deslocada[x+1][y+1] = '@';
                    matriz_deslocada[x][y] = ' ';
                    creditos--;
                    save.totalpts++;

                    if ((save.totalpts % 10 == 0) && (save.totalpts != 0))
                    {
                        save.vidas++;
                    }

                   mapa (save, matriz_deslocada, creditos, BX, BY);
                }

                else if(matriz_deslocada[x+1][y+1] == 'A')
                {
                    save.vidas--;
                    abre_fase(save);
                }

                else if(matriz_deslocada[x+1][y+1] == 'T')
                {
                    if (inimigos==0)
                    {
                        save.ultimafase++;
                        //abre_fase(save);
                        salva_jogo(save);
                    }

                    else
                    {
                        matriz_deslocada[x+1][y+1] = '@';
                        matriz_deslocada[x][y] = ' ';
                        mapa (save, matriz_deslocada, creditos, BX, BY);
                    }

                }

                else if(matriz_deslocada[x+1][y+1] == 'B')
                {
                    if(matriz_deslocada[x+2][y+2] == ' ')
                    {
                        matriz_deslocada[x+2][y+2] = 'B';
                        matriz_deslocada[x+1][y+1] = '@';
                        matriz_deslocada[x][y] = ' ';
                        mapa (save, matriz_deslocada, creditos, BX, BY);
                    }

                    else if(matriz_deslocada[x+2][y+2] == 'A')
                    {
                        matriz_deslocada[x+2][y+2] = ' ';
                        matriz_deslocada[x+1][y+1] = '@';
                        matriz_deslocada[x][y] = ' ';
                        mapa (save, matriz_deslocada, creditos, BX, BY);
                    }

                    else
                    {
                        mapa (save, matriz_deslocada, creditos, BX, BY);
                    }

                }
            }

            case (75): ///esquerda
            {
                if(matriz_deslocada[x][y-1] == ' ')
                {
                    matriz_deslocada[x][y-1] = '@';
                    matriz_deslocada[x][y] = ' ';
                    mapa (save, matriz_deslocada, creditos, BX, BY);
                }

                else if(matriz_deslocada[x][y-1] == 'P')
                {
                    mapa (save, matriz_deslocada, creditos, BX, BY);
                }

                else if(matriz_deslocada[x][y-1] == 'C')
                {
                    matriz_deslocada[x][y-1] = '@';
                    matriz_deslocada[x][y] = ' ';
                    creditos++;
                    mapa (save, matriz_deslocada, creditos, BX, BY);
                }

                else if(matriz_deslocada[x][y-1] == 'E')
                {
                    matriz_deslocada[x][y-1] = '@';
                    matriz_deslocada[x][y] = ' ';
                    creditos--;
                    save.totalpts++;

                    if ((save.totalpts % 10 == 0) && (save.totalpts != 0))
                    {
                        save.vidas++;
                    }

                    mapa (save, matriz_deslocada, creditos, BX, BY);
                }

                else if(matriz_deslocada[x][y-1] == 'A')
                {
                    save.vidas--;
                    abre_fase(save);
                }

                else if(matriz_deslocada[x][y-1] == 'T')
                {
                    if (inimigos==0)
                    {
                        save.ultimafase++;
                        //abre_fase(save);
                        salva_jogo(save);
                    }

                    else
                    {
                        matriz_deslocada[x][y-1] = '@';
                        matriz_deslocada[x][y] = ' ';
                        mapa (save, matriz_deslocada, creditos, BX, BY);
                    }

                }

                else if(matriz_deslocada[x][y-1] == 'B')
                {
                    if(matriz_deslocada[x][y-2] == ' ')
                    {
                        matriz_deslocada[x][y-2] = 'B';
                        matriz_deslocada[x][y-1] = '@';
                        matriz_deslocada[x][y] = ' ';
                        mapa (save, matriz_deslocada, creditos, BX, BY);
                    }

                    else if(matriz_deslocada[x][y-2] == 'A')
                    {
                        matriz_deslocada[x][y-2] = ' ';
                        matriz_deslocada[x][y-1] = '@';
                        matriz_deslocada[x][y] = ' ';
                        mapa (save, matriz_deslocada, creditos, BX, BY);
                    }

                    else
                    {
                       mapa (save, matriz_deslocada, creditos, BX, BY);
                    }
                }
            }

            case (77): ///direita
            {
                if(matriz_deslocada[x][y+1] == ' ')
                {
                    matriz_deslocada[x][y+1] = '@';
                    matriz_deslocada[x][y] = ' ';
                    mapa (save, matriz_deslocada, creditos, BX, BY);
                }

                else if(matriz_deslocada[x][y+1] == 'P')
                {
                    mapa (save, matriz_deslocada, creditos, BX, BY);
                }

                else if(matriz_deslocada[x][y+1] == 'C')
                {
                    matriz_deslocada[x][y+1] = '@';
                    matriz_deslocada[x][y] = ' ';
                    creditos++;
                    mapa (save, matriz_deslocada, creditos, BX, BY);
                }

                 else if(matriz_deslocada[x][y+1] == 'E')
                 {
                    matriz_deslocada[x][y+1] = '@';
                    matriz_deslocada[x][y] = ' ';
                    creditos--;
                    save.totalpts++;

                    if ((save.totalpts % 10 == 0) && (save.totalpts != 0))
                    {
                        save.vidas++;
                    }

                    mapa (save, matriz_deslocada, creditos, BX, BY);
                 }

                 else if(matriz_deslocada[x][y+1] == 'A')
                 {
                    save.vidas--;
                    abre_fase(save);
                 }

                 else if(matriz_deslocada[x][y+1] == 'T')
                 {
                    if (inimigos==0)
                    {
                        save.ultimafase++;
                       //abre_fase(save);
                        salva_jogo(save);
                    }

                    else
                    {
                        matriz_deslocada[x][y+1] = '@';
                        matriz_deslocada[x][y] = ' ';
                        mapa (save, matriz_deslocada, creditos, BX, BY);
                    }
                 }

                 else if(matriz_deslocada[x][y+1] == 'B')
                 {
                     if(matriz_deslocada[x][y+2] == ' ')
                    {
                        matriz_deslocada[x][y+2] = 'B';
                        matriz_deslocada[x][y+1] = '@';
                        matriz_deslocada[x][y] = ' ';
                        mapa (save, matriz_deslocada, creditos, BX, BY);
                    }

                    else if(matriz_deslocada[x][y+2] == 'A')
                    {
                        matriz_deslocada[x][y+2] = ' ';
                        matriz_deslocada[x][y+1] = '@';
                        matriz_deslocada[x][y] = ' ';
                        mapa (save, matriz_deslocada, creditos, BX, BY);
                    }

                    else
                    {
                        mapa (save, matriz_deslocada, creditos, BX, BY);
                    }

                 }
            }
        }

        /// Se a tecla precionada for diferente das sugeridas, chama o mapa novamente
        if ( (tecla != 27) && (tecla != 72) && (tecla != 80) && (tecla != 75) && (tecla != 77) )
        {
             mapa(save, matriz_deslocada, creditos, BX, BY);
        }

}

void sobre_jogo()   /// Fun��o para mostrar sobre o jogo, ap�s ser escolhida no menu inicial
{
    system("cls");

    textcolor(CYAN);
    cprintf("\n\n\n\n\n\n\n\t\t\t\t\tSOBRE LOLO'S ADVENTURE");

    textcolor(LIGHTGREEN);
    cprintf("\n\n\t\t\t   Neste jogo, o jogador controla Lolo, que deve salvar Lala, presa ");
    cprintf("\n\t\t no topo de uma torre cercada por monstros. Em cada fase, Lolo deve derrotar ");
    cprintf("\n\t\t alguns destes inimigos e encontrar a chave que abre a porta para o pr�ximo ");
    cprintf("\n\t\t est�gio. Lolo vence a fase se conseguir eliminar todos os inimigos e abrir ");
    cprintf("\n\t\t o ba� que cont�m a chave da sa�da. Para eliminar um inimigo, Lolo precisa ");
    cprintf("\n\t\t encostar em algum dos cora��es espalhados pela fase. \n\n\n\n\n\t\t\t\t");

    textcolor(CYAN);
    system("Pause");

    menu_Inicial();
    le_opcao();

}

void venceu_jogo()  /// Fun��o chamada ap�s completar a fase 15 para parabenizar o jogador por vencer Lolo's Adventure
{
    system("cls");

    mostra_logo();

    textcolor(YELLOW);
    cprintf("\n\n\n\n\t\t\t        Parabens! Voce completou todos os desafios e resgatou Lala da torre!! \n\n\n\t\t\t\t\t");

    system("Pause");

    creditos();

    main();
}

void creditos()     /// Fun��o para mostrar os cr�ditos do jogo
{
    system("cls");

    textcolor(CYAN);
    cprintf("\n\n\n\n\n\n\n\t\t\t\t\tCR�DITOS: ");

    textcolor(LIGHTGREEN);
    cprintf("\n\n\t\t   Gabriel Alves Bohrer,         Cartao UFRGS numero 00318222");
    cprintf("\n\t\t   Pedro Afonso Tremea Serpa,    Cart�o UFRGS numero 00275960  \n\n\n\n\n\t\t\t");

    textcolor(CYAN);
    system("Pause");

    menu_Inicial();
    le_opcao();

}

void desenha(char ch)   /// Fun��o que recebe o caracter de determinada posi��o de uma matriz e imprimi o simbolo correspondente
{
    switch(ch)
    {
        case '\n': // QUEBRAR LINHA
            {
                cprintf("\n\t\t\t\t\t");
                break;
            }

        case ' ': // ESPA�O VAZIO
            {
                textcolor(BLACK);
                textbackground(BLACK);
                cprintf(" ");
                break;
            }

        case '@': // LOLO
            {
                textcolor(CYAN);
                cprintf("%c", 2);

                break;
            }
        case 'P': // PEDRA
            {
                textcolor(BROWN);
                textbackground(BROWN);
                cprintf("%c", ch);
                break;
            }
        case 'A': // �GUA
            {
                textcolor(LIGHTCYAN);
                textbackground(LIGHTCYAN);
                cprintf("%c", ch);
                break;
            }
        case 'C': //CORA��O
            {
                textcolor(RED);
                cprintf("%c", 003);
                break;
            }
        case 'B': //BLOCO MOV�VEL
            {
                textcolor(BLUE);
                textbackground(GREEN);
                cprintf("%c", 29);
                break;
            }
        case 'E': // INIMIGO
            {
                textcolor(LIGHTMAGENTA);
                cprintf("%c", 31);
                break;
            }
        case 'T': // BA�
            {
                textcolor(YELLOW);
                cprintf("%c", 15);
                break;
            }
    }

    textcolor(WHITE);
    textbackground(BLACK);
}

int main ()     /// Fun��o principal do programa
{

    setlocale(LC_ALL, "");   // Fun��o para usar acentos e caracteres do Portugu�s
    srand(time(NULL));       // Fun��o para "gerar" n�meros aleat�rios

    system("cls");          // Fun��o que limpa a tela

    textcolor(CYAN);
    cprintf("\n\n\n\n\n\n\n\t\t\t Por favor, antes de prosseguir, deixe a janela em tela  cheia \n\t\t e aumente o tamanho da tela com ctrl + mouse scroll at� a tela ter o tamanho da seta.");
    cprintf ("\n\n<---------------------------------------------------------------------------------------------------------------------------------------------->\n\n\n\n\t\t\t\t");

    system("pause");        // Fun��o "Pressione qualquer tecla para continuar..."


    menu_Inicial();                    // Chama a logo e menu de op��es

    le_opcao();                        // Chama a fun��o que valida op��o

}
