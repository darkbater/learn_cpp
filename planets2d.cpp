#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
// Фция рисования окружности
void SDL_RenderDrawCircle(SDL_Renderer * renderer, int centreX, int centreY, int radius) {
	int X; int Y; int F;
	for (int F = 0; F < 360; ++F) SDL_RenderDrawPoint(renderer, centreX + radius * cos(F), centreY - radius * sin(F));
	}
int main() {
	// Не только не писал, но и не читал =+)
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { return 1;}
	SDL_Window *window = SDL_CreateWindow("+", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_SHOWN);
	if (window == NULL) { SDL_Quit(); return 2; }
	SDL_Renderer *s = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	// Конец копипаста =+)

	// Флаг выхода
	bool quit = false;
	// Радиусы планет
	int Rm[] {4,9,11,7,40,30,18,20};
	// Радиусы орбит
	int Rx[] {90,120,150,180,210,240,270,300};
	// Уголвые скорости планет
	float S[] {0.1,1.2,0.6,0.3,0.7,1.2,0.1,0.4};
	// Цвета планет RGB
	float Color[8][3] {{255,0,0},{200,0,200},{0,200,0},{100,0,0},
		{0,100,0},{200,200,0},{255,255,255},{225,155,155}};
	// Фаза развития системы
	float Fase = 0;
	// int X;
	// int Y;
	SDL_Event evt;
	// Основной цикл
	while (!quit) {
		// Обработка закрытия окна
		while (SDL_PollEvent(&evt)) {
			switch (evt.type) {
				case SDL_QUIT: SDL_Log("sQUIrT"); quit = true; break;
				default:;
				}
			} // обработка закрытия
		// Сдвигаем фазу
		Fase+=0.05;
		// Чистим экран, задаём белый цвет, рисуем солнце
		SDL_RenderClear(s);
		SDL_SetRenderDrawColor(s, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderDrawCircle(s, 512, 384, 60);

		// Перебираем планеты
		for (int i = 0; i <= 8; ++i){
			// Их цвета
			SDL_SetRenderDrawColor(s, Color[i][1], Color[i][2], Color[i][3], 0xFF);
			// Рассчет их координат угловое смещение (фаза*угловая скорость)
			SDL_RenderDrawCircle(s, 
				512 + cos((float)Fase * S[i]) * Rx[i], 
				384 - sin((float)Fase * S[i]) * Rx[i],
				// Упс, радиусы оказались диаметрами. =+)
				Rm[i]/2);
			// SDL_Log(i);
			} //Планеты
		// А экран-то чёрный!
		SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderPresent(s);
		} // Главный цыкил
	// Пака!!
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(s);
	SDL_Quit();
	}
