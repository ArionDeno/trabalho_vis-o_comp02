#ifndef SPRITES_H
#define SPRITES_H

#include <stdio.h>
#include<stdlib.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

//velocidade de movimentação
#define VELO 2
//rotação
#define ROT  0.5f
#define SCALA_FAT  0.03f;

/*
 Definição de Sprite
 que será usado para carregar as imagens
*/
typedef struct
{
 SDL_Rect pos;
 SDL_Texture *textura;
 SDL_Point eixo;
 //----------
  double angulo;
  unsigned short int virar;
  float scala_x,scala_y;
  SDL_Color cor;
} Sprite;


/*constante para deteção
*  das teclas precionadas*/
const Uint8 *tecla;


/*
 *carrega a imagens que serão exibidas
*/
SDL_bool carrega_textura(const char *caminho,SDL_Renderer *re,Sprite *s);


/*
 função para incializar os dados da estrutura
*/
void init_sprite(Sprite *s,int x,int y);


/*
 controla a Sprite permite mover pelo teclado
*/
void controla_spr(Sprite *s);


/*
 * função para desenhar sprite
*/
 void desenha_sprite(SDL_Renderer *r,Sprite *s);


/*
 função libera os dados alocados dinamicamente da estrutura
*/
 void desinit_sprite(Sprite *s);


#endif // SPRITES_H
