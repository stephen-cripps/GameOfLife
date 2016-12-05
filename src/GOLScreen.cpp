/*
 * GOLScreen.cpp
 *
 *  Created on: 15 Oct 2016
 *      Author: user
 */

#include "GOLScreen.h"
#include "GOLSwarm.h"
#include <iostream>
using namespace std;

GOLScreen::GOLScreen() :
	m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL),
			SCREEN_WIDTH(0), SCREEN_HEIGHT(0) {

}

bool GOLScreen::init(int W, int H, int C) {
	CELL_SIZE = C;
	SCREEN_WIDTH = W * C;
	SCREEN_HEIGHT = H * C;

	//Check, initialisation

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}

	//Create SDL window.
	m_window = SDL_CreateWindow("Game Of Life", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

	//Create renderer and texture
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (m_renderer == NULL) {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}
	if (m_texture == NULL) {
		SDL_DestroyTexture(m_texture);
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	//Create buffer array, allocating space for each pixel
	m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

	//set initial buffer value
	memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

	return true;

}

void GOLScreen::setPixel(int x, int y, Uint32 colour) {

	for (int i = y * CELL_SIZE; i < (y + 1) * CELL_SIZE; i++) {
		for (int j = x * CELL_SIZE; j < (x + 1) * CELL_SIZE; j++) { //for every pixel in cell
			m_buffer[(i * SCREEN_WIDTH) + j] = colour; //colour
		}
	}
}

void GOLScreen::update() {
	//update texture, clear and update renderer
	SDL_UpdateTexture(m_texture, NULL, m_buffer, sizeof(Uint32) * SCREEN_WIDTH);
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

int GOLScreen::processEvents() {
	SDL_Event event;
	int out = 0;
	//Check for events and execute
	while (SDL_PollEvent(&event)) {
		switch (event . type) {

		case SDL_QUIT: // if x is pressed
			out = 1;
			break;
		case SDL_KEYDOWN: // if space is pressed
			if (event.key.keysym.sym == SDLK_SPACE)
				out = 2;
			break;
		case SDL_MOUSEBUTTONDOWN: {
			Cx = event.button.x; //Set x and y coords to be accessed outside of this scope
			Cy = event.button.y;
			out = 3;
			break;
			case SDL_MOUSEMOTION:
			//if mose moves...
			if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) { //...while left button is held down
				Cx = event.button.x;
				Cy = event.button.y;
				out = 3;
				break;
			}
		}
		}
	}
	return out;
}

int GOLScreen::getX() {

	return Cx;
}
int GOLScreen::getY() {

	return Cy;
}

void GOLScreen::close() {
	delete[] &m_buffer;
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();

}

GOLScreen::~GOLScreen() {
	// TODO Auto-generated destructor stub
}
