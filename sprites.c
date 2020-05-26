#include"sprites.h"



void init_sprite(Sprite *s,int x,int y)
{
 s->pos.x = x;
 s->pos.y = y;
 s->pos.h = 0;
 s->pos.w = 0;
 s->textura = NULL;
 s->angulo = 0;
 s->virar = SDL_FLIP_NONE;
 s->scala_x = 1.0f;
 s->scala_y = 1.0f;
 s->cor.a =255;
 s->cor.r =255;
 s->cor.g =255;
 s->cor.b =255;
 s->virar = 0;
 fprintf(stdout,"inicializa sprite\n\n");
}


/*
 * carrega a imagen e tranforma em textura
*/
SDL_bool carrega_textura(const char *caminho,SDL_Renderer *re,Sprite *s)
{
// imagen que será retornada
 SDL_Surface  *img_temp =NULL;
 SDL_Texture *tex=NULL;

 img_temp = IMG_Load(caminho);
 // erro ao carregar img
 if(img_temp == NULL)
 {
  fprintf(stderr,"erro ao carregar Img %s\n\n",
          SDL_GetError());
  return SDL_TRUE;
 }
// converte a SDL_Surface em textura
 tex = SDL_CreateTextureFromSurface(re,img_temp);
 if(tex == NULL)
 {
  fprintf(stderr,"Erro cirar textura da img \n%s \n%s\n"
          ,caminho,SDL_GetError());
  return SDL_TRUE;
 }

// libera memoria da img
 SDL_FreeSurface(img_temp);

 //salva textura;
 s->textura = tex;
 fprintf(stdout,"imagem carrega:%s\n",caminho);
 return  SDL_FALSE;
}

/*
função para controlar a imagen do braço.
de acordo com cada teclad do teclado.
*/

void controla_spr(Sprite *s)
{

/*pega dados do teclado*/
tecla = SDL_GetKeyboardState(NULL);

//tecla cima
if(tecla[SDL_SCANCODE_UP])
{ s->pos.y-= VELO; }

//tecla baixo
else if (tecla[SDL_SCANCODE_DOWN])
{ s->pos.y+= VELO; }

//tecla esquerda
else if (tecla[SDL_SCANCODE_LEFT])
{ s->pos.x-= VELO; }

//tecla direita
else if (tecla[SDL_SCANCODE_RIGHT])
{ s->pos.x+= VELO; }

// rotação horaria
else if (tecla[SDL_SCANCODE_R])
{ s->angulo+= ROT; }

// rotação anti-horaria
else if (tecla[SDL_SCANCODE_E])
{ s->angulo-= ROT; }

// escala aumenta
else if (tecla[SDL_SCANCODE_H])
{
 s->scala_x+= SCALA_FAT;
 s->scala_y+= SCALA_FAT;
}

// escala diminui
else if (tecla[SDL_SCANCODE_G])
{
 s->scala_x-= SCALA_FAT;
 s->scala_y-= SCALA_FAT;
}

//flip -virar imagen H/V
else if (tecla[SDL_SCANCODE_F])
{
  s->virar++;
  if(s->virar > 4)
  {s->virar =0;}
}

}


/*
 * função para desenhar sprite
*/
 void desenha_sprite(SDL_Renderer *r,Sprite *s)
{
  SDL_SetTextureColorMod(s->textura,s->cor.r,s->cor.g,s->cor.b);
  SDL_RenderCopyEx(r,s->textura,NULL,&s->pos,s->angulo,&s->eixo,s->virar);
  SDL_RenderSetScale(r,s->scala_x,s->scala_y);
}



 /*
  função libera os dados alocados dinamicamente da estrutura
 */
  void desinit_sprite(Sprite *s)
 {
   SDL_DestroyTexture(s->textura);
   s->textura = NULL;
   fprintf(stdout," memoria sprite liberada \n\n");
 }

