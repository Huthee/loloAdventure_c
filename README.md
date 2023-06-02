# Lolo's Adventure
Olá! Bem vindo ao trabalho final da faculdade sobre Algoritmos e Programação.

![Screenshot_1](https://github.com/Huthee/loloAdventure_c/assets/89394453/61a8258d-51f6-4d1a-9eca-2aef942b6001)

Finalizado em Dezembro de 2020, este projeto teve como intuito praticar lógica de programação na Linguagem C, desde definição de variáveis até manipulação de arquivos e funções recursivas. Como proposta de trabalho, deveríamos desenvolver uma versão simplificada em ASCII do jogo de NES "Lolo's Adventure".

![image](https://github.com/Huthee/loloAdventure_c/assets/89394453/c2fdab89-ef12-4c56-ba99-c915de4a2e69)

O jogo tem como objetivo resgatar a namorada de Lolo. Através de 10 fases, Lolo precisa coletar todos os corações espalhados pelo cenário sem ser pego por inimigos e, se preciso, empurrar blocos para alcançar novas áreas do cenário. Se Lolo for atingido por um inimigo, ele perde um ponto de vida; caso seus pontos cheguem em zero, o jogo termina. A cada coração coletado, o jogador ganha 1 ponto; a pontuação, assim como a fase, é um modo de manter o progresso do jogador durante o jogo. Também, o jogo conta com um sistema de "saves", ou arquivos, que cria e carrega últimos estados de jogo. Portanto, ao término de cada fase, o jogador pode salvar seu progresso, podendo carregará-lo e continuar a aventura de onde parou!

# Ferramentas Utilizadas:

* CodeBlocks (IDE)
* Linguagem C/C++
* Biblioteca conio2.h

# Demonstração:

https://github.com/Huthee/loloAdventure_c/assets/89394453/5069f733-9cbf-4e4b-ae7e-46a412bc1622

# Observações:

* Graças à biblioteca conio2.h, foi possível uma pequena customização nos "sprites" em ASCII utilizados.
* Como segue no repositório, os "saves" do jogador são arquivos binários e as fases arquivos txt.
* As fases foram desenhadas em txt. Um caracter específico representa que tipo de objeto será feito durante a execução delas.
* É importante ajustar o Zoom ao abrir o programa (Crtl + roda mouse).

# Dificuldades:

* O sistema de arquivos não está completo; não foi implementado a exclusão de "saves", assim como há um limite em que podem ser utilizados.
* Como maior dificuldade (à época!), os inimigos não se movimentam em trajetórias determinadas/aleatoriamente SEM QUE o jogador se mova. Ou seja, os inimigos pré dispostos nas fases apenas execução um movimento em conjunto com a do jogador.
* Sendo código legado e a biblioteca conio2.h não ser facilmente instalada, é provável que o jogo esteja quebrado.


## Feito Por:
###      Gabriel Alves Bohrer
###      Pedro Afonso Tremea Serpa (https://github.com/pedro-7123)
