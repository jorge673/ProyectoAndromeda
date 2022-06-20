#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <windows.h>
#include <SDL2/SDL_image.h>

#define MenuInicio 1
#define MenuFin 5
#define LineaDeInicio 1

typedef struct Nave Nave;
typedef struct Misil Misil;
typedef struct Punto Punto;
void navePintar(Nave*,SDL_Renderer*);
void naveIzquierdaDerecha(Nave*);
void naveDispara(Nave*);
void misilAvanza(Misil *);
void borrarMisiles(Misil *);
void dibujarlineaInferior(Punto *,SDL_Renderer *);
void goy(int);

struct Misil{
    int x1,y1;
    int x2,y2;
    int velocidad_x,velocidad_y;
    Misil *siguiente;
};

struct Nave{
    int x1,y1;
    int x2,y2;
    int x3,y3;
    int x4,y4;
    int x5,y5;
    int x6,y6;
    int x7,y7;
    int velocidad_x, velocidad_y;
    Misil *misiles;
};

struct Punto{
    int x1,y1;
    int x2,y2;
};

int SDL(){
    SDL_Window *window = NULL;
    //SDL_Surface *windowSurface = NULL;
    SDL_Renderer *renderer = NULL;

    int largo = 480;
    int ancho = 640;
    int size_x = 650;
    int size_y = 850;

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("ERROR\n");
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("Ventana",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,ancho,largo,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    //windowSurface = SDL_GetWindowSurface(window);

    //TTF_Font*sans = TTF_OpenFont("sans.ttf",24);

    //Punto linea = {size_x/2+330,size_y/2+20,size_x/2-330,size_y/2+20};

    SDL_Event event;
    bool running = true;
    const unsigned char *keys = SDL_GetKeyboardState(NULL);
    int typeEvent;

    //imagenes

    Nave nave = {size_x/2,size_y/2,
                size_x/2+5,size_y/2+10,
                size_x/2+20,size_y/2+10,
                size_x/2+20,size_y/2+20,
                size_x/2-20,size_y/2+20,
                size_x/2-20,size_y/2+10,
                size_x/2-5,size_y/2+10,5,5,NULL};

    if (window == NULL){
        printf("ERROR");
        return EXIT_FAILURE;
    }

    while (running){
        while (SDL_PollEvent(&event)){
                if (event.type == SDL_QUIT){
                    running = false;
                }
                else if(typeEvent == SDL_SCANCODE_SPACE){
                    if (GetAsyncKeyState(VK_SPACE)){
                        naveDispara(&nave);
                    }
                }
                else if (keys[SDL_SCANCODE_LEFT]){
                    nave.velocidad_x = -abs(nave.velocidad_x);
                    naveIzquierdaDerecha(&nave);
                }
                else if(keys[SDL_SCANCODE_RIGHT]){
                    nave.velocidad_x = +abs(nave.velocidad_x);
                    naveIzquierdaDerecha(&nave);
                }
                else if (keys[SDL_SCANCODE_SPACE]){
                    naveDispara(&nave);
                }
            }


            borrarMisiles(nave.misiles);

            SDL_UpdateWindowSurface(window);
            SDL_SetRenderDrawColor(renderer,0,0,0,0);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer,0,255,12,0);
            navePintar(&nave,renderer);

            SDL_RenderDrawPoint(renderer,100,100);

            //dibujarlineaInferior(&linea,renderer);

            SDL_RenderPresent(renderer);
            SDL_Delay(10);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void navePintar(Nave *nave,SDL_Renderer *renderer){
    SDL_Point points[8] = {
        {nave->x1,nave->y1},
        {nave->x2,nave->y2},
        {nave->x3,nave->y3},
        {nave->x4,nave->y4},
        {nave->x5,nave->y5},
        {nave->x6,nave->y6},
        {nave->x7,nave->y7},
    };
    points[7] = points[0];
    SDL_RenderDrawLines(renderer,points,8);

    //Pintar misiles
    Misil *auxMisil = nave->misiles;
    while (auxMisil != NULL){
        misilAvanza(auxMisil);
        SDL_RenderDrawLine(renderer,auxMisil->x1,auxMisil->y1,auxMisil->x2,auxMisil->y2);
        auxMisil = auxMisil->siguiente;
    }
}

void naveIzquierdaDerecha(Nave *nave){
    nave->x1 += nave->velocidad_x;
    nave->x2 += nave->velocidad_x;
    nave->x3 += nave->velocidad_x;
    nave->x4 += nave->velocidad_x;
    nave->x5 += nave->velocidad_x;
    nave->x6 += nave->velocidad_x;
    nave->x7 += nave->velocidad_x;

}

void naveDispara(Nave *nave){
    if (nave->misiles == NULL){
        nave->misiles = (Misil*)SDL_malloc(sizeof(Misil));
        nave->misiles->x1 = nave->x1;
        nave->misiles->y1 = nave->y1;
        nave->misiles->x2 = nave->x1;
        nave->misiles->y2 = nave->y1 - 5;
        nave->misiles->velocidad_x = 0;
        nave->misiles->velocidad_y = -5;
        nave->misiles->siguiente = NULL;
    }
    else{
        Misil *auxMisil = nave->misiles;
        while (auxMisil->siguiente != NULL){
            auxMisil = auxMisil->siguiente;
        }
        auxMisil->siguiente = (Misil*)SDL_malloc(sizeof(Misil));
        auxMisil = auxMisil->siguiente;
        auxMisil->x1 = nave->x1;
        auxMisil->y1 = nave->y1;
        auxMisil->x2 = nave->x1;
        auxMisil->y2 = auxMisil->y1 - 5;
        auxMisil->velocidad_x = 0;
        auxMisil->velocidad_y = -5;
        auxMisil->siguiente = NULL;
    }
}

void misilAvanza(Misil *misil){
    misil->x1 += misil->velocidad_x;
    misil->y1 += misil->velocidad_y;
    misil->x2 += misil->velocidad_x;
    misil->y2 += misil->velocidad_y;
}

void borrarMisiles(Misil *misiles){
    Misil *auxMisil = misiles;
    Misil *auxiliar_misiles;

    if (auxMisil == NULL){
        return;
    }
    while (auxMisil->siguiente != NULL){
        if (auxMisil->siguiente->y1 < 0){
            auxiliar_misiles = auxMisil->siguiente->siguiente;
            SDL_free(auxMisil->siguiente);
            auxMisil->siguiente = auxiliar_misiles;
        }else{
                auxMisil = auxMisil->siguiente;
            }
        }
}

void dibujarlineaInferior(Punto *punto,SDL_Renderer *renderer){
    SDL_Point points[3] = {
        {punto->x1,punto->y1},
        {punto->x2,punto->y2},
    };
    points[2] = points[0];
    SDL_RenderDrawLines(renderer,points,3);
}

//FUNCION MENU PRINCIPAL
void Menu(){
    system("COLOR 9");
    int menu;
    printf("--------PROTOTIPO MENU BASICO--------v1.0\n");
    goy(LineaDeInicio);
    printf("\t[1]Jugar\n");
    printf("\t[2]Dificultad\n");
    printf("\t[3]Tutorial\n");
    printf("\t[4]Rankings\n");
    printf("\t[5]Salir\n");
    menu = 1;
    goy(LineaDeInicio);
    printf("---->");

    while (1){
        Sleep(200);
        if(GetAsyncKeyState(VK_UP)){
            menu == MenuInicio ? MenuFin: --menu;
            printf("\r     ");
            goy(LineaDeInicio + menu-1);
            printf("---->");
        }
        else{
            if (GetAsyncKeyState(VK_DOWN)){
                menu == MenuFin ? MenuInicio: ++menu;
                printf("\r     ");
                goy(LineaDeInicio + menu-1);
                printf("---->");
            }
            else{
                if (GetAsyncKeyState(VK_RETURN)){break;}
            }
        }
    }
    printf("\n\n\n\n");
    if (menu == 1){
        SDL();
    }
    if (menu == 2){
        system("pause");

        printf("[FUNCION DIFICULTAD]");
    }
    if (menu == 3){
        system("pause");
        printf("[FUNCION DIFICULTAD]");
    }
    if (menu == 4){
        system("pause");
        printf("[FUNCION MOSTRAR RANKINGS]");
    }
    if (menu == 5){
        printf("Opcion 5");
    }

    //CAMBIAR MENU A UNO MAS BONITO
    /*
    switch (menu){
    case 1:
        Ventana(argc,argv);
    case 2:
    */
}
void goy(int y){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = 0;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}

int main(int argc, char **argv){
    Menu();
    return EXIT_SUCCESS;
}
