#ifndef PIXEPLOT_HPP
#define PIXEPLOT_HPP

#define PIXEL_SIZE 15

#include <SFML/Graphics.hpp>
#include <map>

#include "types.hpp"

extern unsigned int palette[16];

class Display {
private:
    sf::RenderWindow *window;
    word_t *vram; // pointer to the start of the vram
public:
    Display(sf::RenderWindow *window, word_t *vram) : window(window), vram(vram) {}
    void draw();
    bool windowopen() {return window->isOpen();}
};

void Display::draw() {
    sf::RectangleShape border(sf::Vector2f(PIXEL_SIZE*64, PIXEL_SIZE*64));
    border.setPosition(sf::Vector2f(400, 0));
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color::White);
    border.setOutlineThickness(2);
    window->draw(border);
    for (int i = 0; i < 0xfff; i++) {
        sf::RectangleShape pix(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
        pix.setPosition(sf::Vector2f(((i%64) * PIXEL_SIZE) + 400, ((int)i/64) * PIXEL_SIZE));
        pix.setFillColor(sf::Color(palette[vram[i]]));
        window->draw(pix);
    }
}

#endif
