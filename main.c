#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <windows.h>
#include "list.h"

#define MenuInicio 1
#define MenuFin 5
#define LineaDeInicio 1

#define XSIZE 650
#define YSIZE 850

typedef struct{
    char user[4];
    int puntaje;
}Usuario;

void goy(int y);
void Ventana(int,char**);

typedef struct{
    int x1,y1;
    int x2,y2;
    int vx,vy;

}Misil;

typedef struct{
    int x1,y1;
    int x2,y2;
    int x3,y3;
    int vx,vy;
    Misil *misiles;

}Nave;

//FUNCION MENU PRINCIPAL
void Menu(int argc, char** argv){
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
        Ventana(argc,argv);
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

}

//FUNCION SDL PARA JUEGO
void Ventana(int argc, char** argv){
    //Crear puntero ventana ; declarar dimensiones de la ventana emergente
    SDL_Window *window = NULL;
    SDL_Surface *windowSurface = NULL;
    SDL_Renderer *renderer;
    SDL_Event event;

    Nave nave = {XSIZE/2, YSIZE/2, XSIZE/2-10, YSIZE/2+10, XSIZE/2+10, YSIZE/2+10, 5, 5,NULL};
    int ancho = 640;
    int largo = 480;

    //Crear ventana emergente
    if (SDL_Init(SDL_INIT_VIDEO) < 0){ //INICIAR SDL con video
        printf("[ERROR AL ABRIR SDL_Init Error: %s]\n",SDL_GetError());
        return EXIT_FAILURE;
    }

    else{

        window = SDL_CreateWindow("Ventana Emergente",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,ancho,largo,SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        windowSurface = SDL_GetWindowSurface(window);
        if (window == NULL){
            printf("[ERROR AL ABRIR VENTANA EMERGENTE SDL_Init Error: %s]\n",SDL_GetError());
            return EXIT_FAILURE;
        }

        bool running = true;
        SDL_Event ev;

        while (running){
            while (SDL_PollEvent(&ev) != 0){
                if (ev.type == SDL_QUIT){
                    running = false;
                }
            }
            //Menú
            SDL_UpdateWindowSurface(window);
            SDL_SetRenderDrawColor(renderer,0,0,0,0);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer,255,255,255,0);
            navePinta(&nave,renderer);
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void navePinta(Nave *nave, SDL_Renderer*renderer){
    SDL_Point points[4] = {
        {nave->x1,nave->y1},
        {nave->x2,nave->y2},
        {nave->x3,nave->y3},
    };
    points[3] = points[0];
    SDL_RenderDrawLines(renderer,points,4);
}

int main(int argc, char** argv)
{
    Menu(argc,argv);

    return EXIT_SUCCESS;
}

//Mostrar Rankings
void mostrarRankings(){


}

//GUARDAR DATOS EN CSV
void guardarDatosListaCSV(){


}

//FUNCION RANKINGS
void rankings(){

    List *listaRankings = createList();
    //Usuario *aux¨= user;

    //meter usuario en la lista
    //pushBack(listaRankings,aux);




}

void goy(int y){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = 0;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}
