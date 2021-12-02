#include "MainHeader.hpp"

int main(const int argc, char* argv[]) {

    auto window  = make_unique<RenderWindow>(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "2048");
    auto game    = make_unique<Game>();

    //--------------------- GAME STUFF INIT --------------------//

    auto tile = make_unique<RectangleShape>();

    auto font = make_unique<Font>();
    font->loadFromFile("resources/fonts/ClearSans-Regular.ttf");

    auto text = make_unique<Text>("Test", *font);
    text->setStyle(Text::Bold);
    
    //--------------------- GAME LOOP --------------------//
    while (window->isOpen()) {
        Event e;
        while (window->pollEvent(e)) {
            if (e.type == Event::Closed) {
                window->close();
            }

            auto gameMove = std::make_unique<KeyboardGetMoveStrategy>(e)->GetMove();

            game->MakeMove(gameMove);
        }

        window->clear(Color(250, 248, 239));

        //--------------------- FIELD DRAW --------------------//

        tile->setSize(Vector2f(WINDOW_WIDTH, WINDOW_WIDTH));
        tile->setOrigin(0, 0);
        tile->setPosition(Vector2f(0, WINDOW_MARGIN));
        tile->setFillColor(Color(166, 148, 130));
        window->draw(*tile);

        tile->setSize(Vector2f(TILE_SIZE - 2 * TILE_PADDING, TILE_SIZE - 2 * TILE_PADDING));
        tile->setFillColor(Color(191, 177, 161));

        //--------------------- TILES DRAW --------------------//

        for (auto i = 0; i < FIELD_SIZE; ++i) {
            for (auto j = 0; j < FIELD_SIZE; ++j) {
                tile->setPosition(j * TILE_SIZE + TILE_PADDING, i * TILE_SIZE + TILE_PADDING + WINDOW_MARGIN);
                window->draw(*tile);
            }
        }

        //---------------- TILES-NUMBERS DRAW ----------------//

        for (auto i = 0; i < FIELD_SIZE; ++i) {
            for (auto j = 0; j < FIELD_SIZE; ++j) {
                const auto element = game->GetElement(i, j);

                if (element != 0) {
                    
                    //---------------- DRAW TILE SQUARE ----------------//
                    
                    tile->setSize(Vector2f(TILE_SIZE - 2 * TILE_PADDING, TILE_SIZE - 2 * TILE_PADDING));
                    tile->setOrigin(tile->getSize() / 2.0f);
                    tile->setPosition(Vector2f(j * TILE_SIZE + TILE_SIZE / 2.0f, i * TILE_SIZE + TILE_SIZE / 2.0f + WINDOW_MARGIN));
                    tile->setFillColor(GetTileColor(element));
                    window->draw(*tile);

                    //---------------- DRAW TILE FONT ----------------//

                    text->setPosition(tile->getPosition());
                    text->setOrigin(Vector2f(text->getLocalBounds().width / 2.0f + text->getLocalBounds().left,
                        text->getLocalBounds().height / 2.0f + text->getLocalBounds().top));
                    
                    if (element <= 4) {
                        text->setFillColor(Color(121, 112, 100));
                    }
                    else {
                        text->setFillColor(Color::White);
                    }
                    text->setString(fmt::format("{}", element));
                    window->draw(*text);


                }
            }
        }

        if (game->IsWin()) {
            tile->setOrigin(0, 0);
            tile->setSize(Vector2f(WINDOW_WIDTH, WINDOW_WIDTH));
            tile->setPosition(Vector2f(0, WINDOW_MARGIN));
            tile->setFillColor(Color(255, 255, 0, 100));
            window->draw(*tile);

            text->setOrigin(Vector2f(text->getLocalBounds().width / 2.0f + text->getLocalBounds().left,
                text->getLocalBounds().height / 2.0f + text->getLocalBounds().top));
            text->setPosition(Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_WIDTH / 2.0f + WINDOW_MARGIN));
            text->setFillColor(Color::White);
            text->setString("YOU WIN!!!");
            window->draw(*text);
        }
        else if (!game->IsPlaying()) {
            tile->setOrigin(0, 0);
            tile->setSize(Vector2f(WINDOW_WIDTH, WINDOW_WIDTH));
            tile->setPosition(Vector2f(0, WINDOW_MARGIN));
            tile->setFillColor(Color(255, 255, 255, 100));
            window->draw(*tile);

            text->setOrigin(Vector2f(text->getLocalBounds().width / 2.0f + text->getLocalBounds().left,
                text->getLocalBounds().height / 2.0f + text->getLocalBounds().top));
            text->setPosition(Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_WIDTH / 2.0f + WINDOW_MARGIN));
            text->setFillColor(Color(121, 112, 100));
            text->setString("Game over");
            window->draw(*text);
        }

        window->display();
    }

    return EXIT_SUCCESS;
}