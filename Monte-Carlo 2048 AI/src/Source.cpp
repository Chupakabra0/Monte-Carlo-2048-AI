#include "MainHeader.hpp"

int main(const int argc, char* argv[]) {

    // TODO: argparse factory method
    auto argparser = make_unique<ArgumentParser>();
    argparser->add_argument("-s", "--simulations")
        .help("determines the number of games' simulations for each possible move")
        .default_value(DEFAULT_SIMULATIONS_COUNT);
    argparser->add_argument("-l", "--length")
        .help("determines the maximum number of moves made during the simulation")
        .default_value(DEFAULT_MAX_LENGTH_GAME);

    argparser->parse_args(argc, argv);

    const auto simulations = strtol(argparser->get<std::string>("-s").c_str(), nullptr, 10);
    const auto length      = strtol(argparser->get<std::string>("-l").c_str(), nullptr, 10);

    auto window    = make_unique<RenderWindow>(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "2048");
    auto game      = make_unique<Game>();

    //--------------------- GAME STUFF INIT --------------------//

    auto tile = make_unique<RectangleShape>();

    auto font = make_unique<Font>();
    font->loadFromFile("resources/fonts/ClearSans-Regular.ttf");
    
    //--------------------- GAME LOOP --------------------//
    while (window->isOpen()) {
        Event e;
        while (window->pollEvent(e)) {
            if (e.type == Event::Closed) {
                window->close();
            }

            //auto gameMove = std::make_unique<KeyboardGetMoveStrategy>(e)->GetMove(*game);
        }

        if (game->IsPlaying()) {
            const auto gameMove = std::make_unique<AIGetMoveStrategy>(
                std::make_shared<MonteCarloAI>(simulations, length)
            )->GetMove(*game);

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
                    tile->setOrigin(tile->getSize() / 2.f);
                    tile->setPosition(Vector2f(j * TILE_SIZE + TILE_SIZE / 2.f, i * TILE_SIZE + TILE_SIZE / 2.f + WINDOW_MARGIN));
                    tile->setFillColor(GetTileColor(element));
                    window->draw(*tile);

                    //---------------- DRAW TILE FONT ----------------//

                    auto text = make_unique<Text>(fmt::format("{}", element), *font);
                    text->setStyle(Text::Bold);
                    text->setPosition(tile->getPosition());
                    text->setOrigin(Vector2f(text->getLocalBounds().width / 2.f + text->getLocalBounds().left,
                        text->getLocalBounds().height / 2.f + text->getLocalBounds().top));
                    
                    if (element <= 4) {
                        text->setFillColor(Color(121, 112, 100));
                    }
                    else {
                        text->setFillColor(Color::White);
                    }
                    window->draw(*text);


                }
            }
        }

        //---------------- DRAW SCORE TEXT ----------------//

        auto scoreText = make_unique<Text>(fmt::format("SCORE: {}", game->GetScore()), *font);
        scoreText->setStyle(Text::Bold);
        scoreText->setOrigin(Vector2f(scoreText->getLocalBounds().width / 2.f + scoreText->getLocalBounds().left,
            scoreText->getLocalBounds().height / 2.f + scoreText->getLocalBounds().top));
        scoreText->setPosition(Vector2f(WINDOW_WIDTH / 2.f, WINDOW_WIDTH / 6.f));
        scoreText->setFillColor(Color(121, 112, 100));
        window->draw(*scoreText);

        //---------------- DRAW LOSE TEXT ----------------//

        if (!game->IsPlaying()) {
            tile->setOrigin(0, 0);
            tile->setSize(Vector2f(WINDOW_WIDTH, WINDOW_WIDTH));
            tile->setPosition(Vector2f(0, WINDOW_MARGIN));
            tile->setFillColor(Color(255, 255, 255, 100));
            window->draw(*tile);

            auto loseText = make_unique<Text>("Game over", *font);
            loseText->setStyle(Text::Bold);
            loseText->setOrigin(Vector2f(loseText->getLocalBounds().width / 2.f + loseText->getLocalBounds().left,
                loseText->getLocalBounds().height / 2.f + loseText->getLocalBounds().top));
            loseText->setPosition(Vector2f(WINDOW_WIDTH / 2.f, WINDOW_WIDTH / 2.f + WINDOW_MARGIN));
            loseText->setFillColor(Color(121, 112, 100));
            window->draw(*loseText);
        }

        window->display();
    }

    return EXIT_SUCCESS;
}