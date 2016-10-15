/*
 * GOLScreen.cpp
 *
 *  Created on: 15 Oct 2016
 *      Author: user
 */

#include "GOLScreen.h"
#include <iostream>

using namespace std;

GOLScreen::GOLScreen() :
	m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL) {

}

bool GOLScreen::init(int SCREEN_WIDTH, int SCREEN_HEIGHT) {

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
	cout << "setpixelstart" << endl;
	m_buffer[(y * SCREEN_WIDTH) + x] = colour;
	cout << "setpixelend" << endl;
}

void GOLScreen::update() {
	//update texture, clear and update renderer
	SDL_UpdateTexture(m_texture, NULL, m_buffer, sizeof(Uint32) * SCREEN_WIDTH);
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

bool GOLScreen::processEvents() {
	SDL_Event event;

	//Check for events and execute
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		}
	}
	return true;
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
