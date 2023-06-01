
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


/// DEFINEÇÃO DE DADOS

typedef struct {
 int identificador;
 int totalpts;
 int ultimafase;
 int vidas;
 char nomejogador[9];

}save_st;


/// FUNÇÕES
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

void menu_Inicial()     /// Função que chama o menu inicial do jogo
{
    system("cls"); //Limpa Tela

    mostra_logo();

    textcolor(CYAN);
    cprintf("\n\n\n\t     [N - Novo Jogo]");
    cprintf("\t\t [C - Carregar Jogo]");
    cprintf("\t\t [T - Tutorial]");
    cprintf("\t\t [M - Créditos]");
    cprintf("\t\t [S - Sair]\n\n");
}

char le_opcao()     /// Função para ler a opção escolhida do menu
{
    char op;

    op = getch();
    op = toupper(op);   // le um uma letra do teclado, convertendo-a para maiuscula

    if(!(op == 'N' || op == 'C' || op == 'M' || op == 'T' || op == 'S'))    // se o caracter for diferente dos especificados, chama a mesma função novamente
    {
        op = le_opcao();
    }

            switch (op)     // Senão, seleciona qual função sera chamada conforme o valor do caracter 'op'
            {
            case 'N': novo_jogo(); break;
            case 'C': carregar_jogo(); break;
            case 'T': sobre_jogo(); break;
            case 'M': creditos(); break;
            case 'S': exit(0); break;
        }
}

int mostra_lista_saves (int inic, int term)     /// Função que mostra uma lista crescente de todos os saves do arquivo 'Saves.bin' e retorna o save(slot) de um jogador
{
/// Variáveis:
    int i, tecla, retorno, j = 0, fim = 1;
    FILE *allsaves;
    save_st save;

    allsaves = fopen ("Saves/AllSaves.bin", "rb");  // abre o arquivo binário

    system("cls");

    textcolor(CYAN);
    cprintf("\n\n\n\t\t\t\t\t CARREGAR JOGO");
    textcolor(LIGHTGREEN);

    while (!feof(allsaves) && fim)      // enquanto o arquivo não chegar ao fim
    {
         if( (fread(&save, sizeof(save), 1, allsaves)) == 1)    // leitura da informação em save_st do arquivo binario e armazenada no buffer 'save'
            {
                j++;    // a cada struct, soma+1 em j
            }

        else    // se allsaves for 0, termina o loop
        {
            fim = 0;
        }
    }

    /// Organização da quantidade de saves que serão apresentados a cada página:
    if (term > j)   //impede paginas além do maior save
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
    /// Impressão de cada campo da struct de allsaves:
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

        fclose(allsaves);   // fechamento do arquivo binário
        fflush(stdin);

        textcolor(CYAN);
        cprintf("\n\n\t\t\t [A - Pagina anterior] \t\t [D - Pagina seguinte] \n\n\t\t\t [C - Carregar slot] \t\t [S - Sair] \n");

        /// Leitura da variavel tecla para a troca de pagina, carregar um save ou retornar ao menu inicial:
        tecla = getch();
        tecla = toupper(tecla);

        if(tecla == 'D')    // Avança uma pagina
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

        else    // Se o caracter escolhido não for dentro dos esperados, executa a lista novamente
        {
            mostra_lista_saves(inic, term);
        }
    }
}

void novo_jogo()    /// Função para salvar os dados de um novo jogador e iniciar o jogo
{
 /// Variáveis:
    FILE *savefile, *allsaves;
    save_st save;
    int j = 1, fim = 1;

    system("cls");
    fflush(stdin);

    textcolor(CYAN);
    cprintf("\n\n\n\n\n\n\n\t\t\t\t\tNOVO JOGO");

    allsaves = fopen ("Saves/AllSaves.bin", "ab+"); // abre o arquivo binário 'AllSaves' para escrever um novo dado ao final

    rewind(allsaves);


    while (!feof(allsaves) && fim)
    {
        if( (fread(&save, sizeof(save), 1, allsaves)) == 1){    // Enquanto não chega ao final do arquivo, soma a variavel j para saber em qual slot vago sera escrito as informações do novo jogador
            j++;

        /// Criando os dados do novo jogador:
        }else{
            textcolor(LIGHTGREEN);
            cprintf("\n\n\t\t\t   Jogador, digite o seu 'Nick': ");
            scanf(" %s", save.nomejogador);
            fflush(stdin);

            /// Dados pré-determinados para qualquer jogador que comece do inicio:
            save.identificador = j;
            save.totalpts = 0;
            save.ultimafase = 1;
            save.vidas = 5;

            fim=0;  //  término  da criação dos dados do novo jogador
        }
    }

    fwrite (&save, sizeof(save), 1, allsaves);  // Escreve os dados no arquivo binário
    fclose(allsaves);   // fechamento do arquivo


    system("cls");

    /// Interface com as informações do novo jogador:
    textcolor(CYAN);
    cprintf("\n\n\n\n\n\n\n\t\t\t\t\t NOVO JOGO");

    textcolor(LIGHTGREEN);
    printf ("\n\n\n\t\t\t\t\t Slot: %d \n\n\t\t\t\t\t Pontos: %d \n\n\t\t\t\t\t Fase: %d \n\n\t\t\t\t\t Vidas: %d \n\n\t\t\t\t\t Nickname: %s \n\n\n\n\n\n\t\t\t        ", save.identificador, save.totalpts, save.ultimafase, save.vidas, save.nomejogador);

    textcolor(CYAN);
    system("Pause");

    /// Chama a primeira fase para o novo jogador, ja registrado
    abre_fase(save);

}

void carregar_jogo()    /// Função para carregar os dados de um jogador e retornar ao jogo na ultima fase jogada
{
/// Variáveis
    FILE *allsaves;
    save_st save;
    int fim = 1, i=0, j=0, escolha, num = 0;

    allsaves = fopen ("Saves/AllSaves.bin", "rb");  // Abertura do arquivo binário 'AllSaves'

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

    fclose(allsaves);   // fechamento do arquivo binário

    system("cls");
    fflush(stdin);

    /// Seleção do identificador (slot) de um save para carregar o jogo desejado
    if (num < 3)
    {
        escolha = mostra_lista_saves(0, num);
    }

    else
    {
        escolha = mostra_lista_saves(0, 2);
    }

    /// Abre o arquivo binário, procura a struct que contem o identificador (slot) escolhido e abre a fase

    allsaves = fopen ("Saves/AllSaves.bin", "rb");
    rewind(allsaves);
    fseek(allsaves, escolha*sizeof(save_st), 1);

    if( (fread(&save, sizeof(save), 1, allsaves)) ==1)
        {
            abre_fase(save);
        }

    else    // Se o slot não existir, retorna ao menu inicial
    {
        menu_Inicial();
        le_opcao();
    }
}

void salva_jogo(save_st save)   /// Função para salvar o progresso do jogador ao fim de cada fase
{
/// Variáveis
    char tecla;
    FILE *allsaves;

    system("cls");

    /// Interface
    textcolor(LIGHTGREEN);
    cprintf("\n\n\n\n\n\n\n\t\t\t\t         Fase concluída!!");
    cprintf("\n\n\n\n\n\t\t\t\t    Deseja salvar o progresso?");
    cprintf("\n\n\n\n\n\t\t\t\t      [S - Sim]    [N - Nao] \n\n");

    /// Leitura da tecla
    tecla = getch();
    tecla = toupper(tecla);

    fflush(stdin);

    if ((tecla != 'S') && (tecla != 'N'))   // Se a tecla for diferente das opções esperadas, pergunta novamente
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

    }else   // Se o jogador não quiser salvar o progresso, segue para a proxima fase
    {
        abre_fase(save);
    }
}

void abre_fase(save_st save)    /// Função para ler cada uma das fases do jogo conforme a situação do jogador e carrega-las em uma matriz (buffer)
{
/// Variáveis:
    FILE *fases;
    char matriz_fase[14][13];
    int i, j, BX, BY;

    system("cls");

    /// Se o jogador não tiver mais vidas suficientes para continuar a jogar, encerra o jogo e retorna ao menu inicial
    if (save.vidas < 0)
    {
        system("cls");

        textcolor(RED);
        cprintf("\n\n\n\n\n\n\n\t\t\t\t\t GAME OVER");

        textcolor(CYAN);
        cprintf("\n\n\n\n\t\t   Você perdeu todas as vidas. Retornando para a tela inicial, onde ");
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
    case 16:    // Após a última fase do jogo (fase 15), ao invés de abrir o proximo arquivo texto, termina o jogo
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

        /// Identifica a posição do Baú na fase e armazena-a em BX e BY
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

    /// Assim que a fase esta pronta para ser carregada, chama a função mapa
    mapa(save, matriz_fase, 0, BX, BY);

}

int mapa(save_st save, char matriz_deslocada[14][13], int creditos, int BX, int BY)     /// Função para desenhar as fases do jogo, executar os comandos de movimento do jogador e dos inimigos e contabilizar os dados de jogo
{
/// Variáveis:

    int i, j;                           // contadores para a leitura das linhas e colunas da matriz que armazena a fase
    int x, y;                           // variáveis que armazenam a posição do Lolo (jogador)
    int tecla;                          // Recebe a direção em que o Lolo se movimentará a cada "casa" deslocada
    int buffer[14][13];                 // Buffer para armazenar as trocas de posições dos inimigos
    int inimigos = 0, randmov = 0;      // Variáveis para armazenar a quantidade de inimigos em cada fase e o valor que será utilizado para aleatorizar o seu movimento

    system("cls");

    /// Se o jogador não possuir créditos (corações) suficientes para derrotar um inimigo, perde 1 vida
    if (creditos < 0)
    {
        save.vidas--;
        abre_fase(save);
    }

    /// Interface com informações sobre o jogo e jogador
    textcolor(CYAN);
    cprintf("\n\n\n\n\n\t\t\t\t\t   FASE %d \n", save.ultimafase);

    textcolor(LIGHTGREEN);
    cprintf ("\n\t\t\t\t         pts:%d", save.totalpts);

    textcolor(CYAN);
    cprintf ("\t %cx%d", 2, save.vidas);

    textcolor(RED);
    cprintf ("\n\n\t\t\t\t\t     %cx%d \n\t\t\t\t\t", 3, creditos);

        /// Identifica em que posição inicial encontra-se Lolo e armazena-a em 'x' e 'y' / Identifica em que posições estão os inimigos e contabiliza a sua quantidade.
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

        /// Movimentação randomica de cada inimigo:
        for(i = 0; i < 14; i++)
        {
            for(j = 0; j < 13; j++)
            {
                if (matriz_deslocada[i][j] == 'E')
                {
                    randmov = (rand() % 4);    // randmov recebe valores entre 0 e 3, randomicamente através de rand()

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

        /// Identifica a posição do Baú na fase e, se ainda existirem inimigos na fase, cria uma mascara para não mostrar a posição do Baú para o jogador:
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

        /// Tira a máscara da posição do Baú quando a quantidade de inimigos for zero

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

        /// OBS.: Para cada direção que o jogador venha a se mover (para cima, para baixo, para direita ou para a esquerda), verifica que tipo de objeto há em seu caminho.
        /// Dependendo da situação, realiza uma atualização diferente e imprime o mapa novamente. Os casos:
        ///                                                                     Se for um espaço vazio, Lolo vai a ele naturalmente
        ///                                                                     Se for uma Parede (P), Lolo permanecerá na sua posição atual
        ///                                                                     Se for um Coração (C), Lolo vai a ele, substituindo-o por uma posição vazia e somando +1 em créditos
        ///                                                                     Se for um Inimigo (E), Lolo o derrota, substituindo-o por uma posição vazia, perde um crédito e ganha +1 ponto (outras verificações ocorrem no após o chamamento do mapa)
        ///                                                                     Se for um espaço com Água (A), Lolo se afogará, perdendo 1 vida e seus créditos
        ///                                                                     Se for um Baú (T), Lolo abre o baú, indo para a próxima fase e chamando a função de salvar jogo
        ///                                                                     Se for um Bloco Móvel (B), Lolo consegue empurra-lo para a direção em que esta andando.
        ///                                                                                 Se a posição a frente for um espaço vazio, ele avançará.
        ///                                                                                 Se for Água, ele fará uma ponte, transformando-se em um espaço vazio e não poderá ser mais empurrado.

        /// OBS.2: Após Lolo derrotar um inimigo, verifica se a sua pontuação é múltipla de 10; caso seja, o jogador ganha +1 vida.

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

void sobre_jogo()   /// Função para mostrar sobre o jogo, após ser escolhida no menu inicial
{
    system("cls");

    textcolor(CYAN);
    cprintf("\n\n\n\n\n\n\n\t\t\t\t\tSOBRE LOLO'S ADVENTURE");

    textcolor(LIGHTGREEN);
    cprintf("\n\n\t\t\t   Neste jogo, o jogador controla Lolo, que deve salvar Lala, presa ");
    cprintf("\n\t\t no topo de uma torre cercada por monstros. Em cada fase, Lolo deve derrotar ");
    cprintf("\n\t\t alguns destes inimigos e encontrar a chave que abre a porta para o próximo ");
    cprintf("\n\t\t estágio. Lolo vence a fase se conseguir eliminar todos os inimigos e abrir ");
    cprintf("\n\t\t o baú que contém a chave da saída. Para eliminar um inimigo, Lolo precisa ");
    cprintf("\n\t\t encostar em algum dos corações espalhados pela fase. \n\n\n\n\n\t\t\t\t");

    textcolor(CYAN);
    system("Pause");

    menu_Inicial();
    le_opcao();

}

void venceu_jogo()  /// Função chamada após completar a fase 15 para parabenizar o jogador por vencer Lolo's Adventure
{
    system("cls");

    mostra_logo();

    textcolor(YELLOW);
    cprintf("\n\n\n\n\t\t\t        Parabens! Voce completou todos os desafios e resgatou Lala da torre!! \n\n\n\t\t\t\t\t");

    system("Pause");

    creditos();

    main();
}

void creditos()     /// Função para mostrar os créditos do jogo
{
    system("cls");

    textcolor(CYAN);
    cprintf("\n\n\n\n\n\n\n\t\t\t\t\tCRÉDITOS: ");

    textcolor(LIGHTGREEN);
    cprintf("\n\n\t\t   Gabriel Alves Bohrer,         Cartao UFRGS numero 00318222");
    cprintf("\n\t\t   Pedro Afonso Tremea Serpa,    Cartão UFRGS numero 00275960  \n\n\n\n\n\t\t\t");

    textcolor(CYAN);
    system("Pause");

    menu_Inicial();
    le_opcao();

}

void desenha(char ch)   /// Função que recebe o caracter de determinada posição de uma matriz e imprimi o simbolo correspondente
{
    switch(ch)
    {
        case '\n': // QUEBRAR LINHA
            {
                cprintf("\n\t\t\t\t\t");
                break;
            }

        case ' ': // ESPAÇO VAZIO
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
        case 'A': // ÁGUA
            {
                textcolor(LIGHTCYAN);
                textbackground(LIGHTCYAN);
                cprintf("%c", ch);
                break;
            }
        case 'C': //CORAÇÃO
            {
                textcolor(RED);
                cprintf("%c", 003);
                break;
            }
        case 'B': //BLOCO MOVÍVEL
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
        case 'T': // BAÚ
            {
                textcolor(YELLOW);
                cprintf("%c", 15);
                break;
            }
    }

    textcolor(WHITE);
    textbackground(BLACK);
}

int main ()     /// Função principal do programa
{

    setlocale(LC_ALL, "");   // Função para usar acentos e caracteres do Português
    srand(time(NULL));       // Função para "gerar" números aleatórios

    system("cls");          // Função que limpa a tela

    textcolor(CYAN);
    cprintf("\n\n\n\n\n\n\n\t\t\t Por favor, antes de prosseguir, deixe a janela em tela  cheia \n\t\t e aumente o tamanho da tela com ctrl + mouse scroll até a tela ter o tamanho da seta.");
    cprintf ("\n\n<---------------------------------------------------------------------------------------------------------------------------------------------->\n\n\n\n\t\t\t\t");

    system("pause");        // Função "Pressione qualquer tecla para continuar..."


    menu_Inicial();                    // Chama a logo e menu de opções

    le_opcao();                        // Chama a função que valida opção

}
