#pragma once

#include <iostream>
//#include <format>

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

using namespace std;
using namespace sf;
