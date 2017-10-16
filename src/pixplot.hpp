#ifndef PIXEPLOT_HPP
#define PIXEPLOT_HPP

#define PIXEL_SIZE 30

#include <SFML/Graphics.hpp>

#include "types.hpp"

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
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
    }

    window->clear(sf::Color::Black);
    for (int i = 0; i < 256; i++) {
        sf::RectangleShape pix(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
        pix.setPosition(sf::Vector2f((i%16) * PIXEL_SIZE, ((int)i/16) * PIXEL_SIZE));
        pix.setFillColor(sf::Color((vram[i] << 8) + 0xff));
        window->draw(pix);
    }
    window->display();
}

#endif
