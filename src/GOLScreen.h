/*
 * GOLScreen.h
 *
 *  Created on: 15 Oct 2016
 *      Author: user
 */

#ifndef GOLSCREEN_H_
#define GOLSCREEN_H_
#include <SDL.h>
#include <string.h>

class GOLScreen {
private:
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;
	Uint32 *m_buffer;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int CELL_SIZE;
	int Cx;
	int Cy;



public:
	GOLScreen();
	bool init(int SCREEN_WIDTH, int SCREEN_HEIGHT, int CELL_SIZE);
	void setPixel(int x, int y, Uint32 colour);
	void update();
	int processEvents();
	void close();
	int getX();
	int getY();

	virtual ~GOLScreen();
};

#endif /* GOLSCREEN_H_ */
