#include "MainHeader.hpp"

int main(const int argc, char* argv[]) {
    auto window = make_unique<RenderWindow>(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "2048");

    while (window->isOpen()) {
        Event e;
        while (window->pollEvent(e)) {
            if (e.type == Event::Closed) {
                window->close();
            }
        }

        window->clear(Color(250, 248, 239));
        window->display();
    }

    return EXIT_SUCCESS;
}