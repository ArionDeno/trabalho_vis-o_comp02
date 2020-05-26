/*
* Universiade Tuiuti do Paraná
* trabalho de visão computacional 02
* -------------------------------
* alinar o relogioa a mão, mesmo, aplicando
* rotação, translação, e escalonamento.
* ______________________
* Aluno: Arion Denovaro  - RA: 082246
* Professor: Sergio Marquees
* -------------------
* Inicio 14/05/2020
* Fim:   23/05/2020
*/
#include <stdio.h>
#include<stdlib.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "sprites.h"


#define LAR 640
#define ALT 480
#define FPS 60
#define UM_SEG 1000
#define TITULO "trabalho visao comp02"
#define CAMINHO_BRACO  "braco.png"
#define CAMINHO_RELOGIO "relogio.png"
#define DIST_REL_X   30
#define DIST_REL_Y   280


int main(int argc, char **arv)
{
  SDL_Window * janela = NULL;
  SDL_Renderer *render =NULL;
  SDL_Event  evt;
  SDL_bool gameloop = SDL_TRUE;
  Uint32 tempo_ini = 0, deltam =0, um_seg=0;
  short int fps =0, retorno_img=0;
/*------------------------------------*/
  //estruturas para manipulação dos dados
  Sprite spr_relogio,spr_braco;

  init_sprite(&spr_braco,120,50);
  init_sprite(&spr_relogio,100,322);


/*-----------------------------------*/
// incializa a SDL2
   if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS|SDL_INIT_TIMER) <0)
   {
     printf("Erro ao inciar SDL2\n%s\n",SDL_GetError());
     return(EXIT_FAILURE);
   }

// cria a janela
 janela = SDL_CreateWindow(TITULO,
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             LAR,ALT,SDL_WINDOW_SHOWN);
   if(janela == NULL)
   {
     printf("Erro ao inciar janela SDL2\n%s\n",SDL_GetError());
     SDL_Quit();
     return(EXIT_FAILURE);
   }

// influencia a escala
SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

//cria o render com aceleração e vsync
render = SDL_CreateRenderer(janela,-1,
            SDL_RENDERER_ACCELERATED|
            SDL_RENDERER_TARGETTEXTURE|
            SDL_RENDERER_PRESENTVSYNC);
//------------------INIT-----------------------------------------

/*===========================*/
/*inicializa a SDL2_Image para carregar png*/
   retorno_img = IMG_Init(IMG_INIT_PNG);

/*verificando erro da inicialização SDL_image*/
   if((IMG_INIT_PNG & retorno_img) != IMG_INIT_PNG)
   {
     fprintf(stderr,"Erro ao inicializar a SDL2_Image ->PNG\n");
     fprintf(stderr,"IMG_Init: %s",SDL_GetError());
     SDL_DestroyRenderer(render);
     SDL_DestroyWindow(janela);
     SDL_Quit();
     return EXIT_FAILURE;
   }
//----------------------
// carrega as imgs

//verifica se foi possivel carregas as imagens
 if( (carrega_textura(CAMINHO_BRACO,render,&spr_braco) ==SDL_TRUE) ||
   (carrega_textura(CAMINHO_RELOGIO,render,&spr_relogio) ==SDL_TRUE) )
 {
   fprintf(stderr,"Erro ao tentar carregar as imagens\n%s\n%s\n"
         ,CAMINHO_BRACO,CAMINHO_RELOGIO);
   fprintf(stderr,"IMG_Init: %s",SDL_GetError());
   SDL_DestroyRenderer(render);
   SDL_DestroyWindow(janela);
   SDL_Quit();
   return EXIT_FAILURE;
 }

/*encerra SDL_Image*/
 IMG_Quit();
/*===================================*/
//calcula os eixos de rotação
 // braco
 // pega altura e largura da textura
 SDL_QueryTexture(spr_braco.textura,
                  NULL,NULL,&spr_braco.pos.w,&spr_braco.pos.h);
//calcula o eixo no meio
spr_braco.eixo.x = 120;
spr_braco.eixo.y = 322;


// relogio
// pega altura e largura da textura
SDL_QueryTexture(spr_relogio.textura,
                 NULL,NULL,&spr_relogio.pos.w,&spr_relogio.pos.h);
//calcula o eixo no meio
spr_relogio.eixo.x = spr_relogio.pos.w /2;
spr_relogio.eixo.y= spr_relogio.pos.h /2;


 //------------------INIT-----------------------------------------
   while(gameloop != SDL_FALSE)
   {
     tempo_ini = SDL_GetTicks();
  //---INPUT--------------------------------------------------------
     if(SDL_PollEvent(&evt))
     {
        if(evt.type == SDL_QUIT ||
          evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        { gameloop = SDL_FALSE; }
     }
  //----------INPUT-------------------------

  //-------UPDATE----------------------------
    controla_spr(&spr_braco);
  /* atribui as posições
   * para que todas as ações
   * sem refletidas no relogio
  */
  spr_relogio.virar   = spr_braco.virar;
  spr_relogio.angulo  = spr_braco.angulo;
  spr_relogio.scala_x = spr_braco.scala_x;
  spr_relogio.scala_y = spr_braco.scala_y;
/* faz o relogio ficar no pulso mesmo com as tranformações
 acresenta-se a distancia relativa da imagem
*/
  spr_relogio.pos.x   =  DIST_REL_X + spr_braco.pos.x;
  spr_relogio.pos.y   =  DIST_REL_Y + spr_braco.pos.y;

  //-------UPDATE----------------------------

  //--------DRAW------------------------------
  SDL_SetRenderDrawColor(render,0,0,0,255);
  SDL_RenderClear(render);
    //....................

    desenha_sprite(render,&spr_braco);
    desenha_sprite(render,&spr_relogio);

    //....................
  SDL_RenderPresent(render);
  //--------DRAW---------------------------------------------------

  //----------FPS-------------------------------------------------
// calcula quando se passou 1 seg
    ++fps;
    deltam = SDL_GetTicks() - tempo_ini;
    um_seg += SDL_GetTicks();

// calcula FPS
    if(um_seg >= UM_SEG)
    {
    printf("FPS %d\n", FPS - fps );
    fps =0;  um_seg =0;
    }
// regula o FPS
    if(deltam > FPS)
    {
       SDL_Delay(deltam - FPS);
       printf("atraso %d\n",deltam - FPS );
    }
  //----------FPS-------------------------------------------------
}
//----------DESINIT-----------------------------
   desinit_sprite(&spr_braco);
   desinit_sprite(&spr_relogio);

//----------DESINIT-----------------------------

  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(janela);

  SDL_QuitSubSystem(SDL_INIT_VIDEO);
 /* finaliza os sub sistemas da SDL*/
  SDL_QuitSubSystem(SDL_INIT_AUDIO|
             SDL_INIT_EVENTS|
             SDL_INIT_TIMER);
  SDL_Quit();
//----------DESINIT-----------------------------

  return EXIT_SUCCESS;
}
