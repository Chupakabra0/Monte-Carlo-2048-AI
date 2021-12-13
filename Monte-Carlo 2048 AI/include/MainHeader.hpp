#pragma once

#include <iostream>

#if defined(_WIN32)
    #define NOMINMAX
    #include <Windows.h>
#endif

#include <argparse/argparse.hpp>
#include <SFML/Graphics.hpp>
#include <fmt/format.h>

#include "const/Const.hpp"
#include "Game/Game.hpp"
#include "utils/Utils.hpp"
#include "GetMoveStrategy/KeyboardGetMoveStrategy.hpp"
#include "GetMoveStrategy/AIGetMoveStrategy.hpp"

using namespace std;
using namespace sf;
using namespace argparse;
