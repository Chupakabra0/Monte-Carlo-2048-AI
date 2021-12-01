#pragma once

#include <iostream>
//#include <format>

#if defined(_WIN32)
    #define NOMINMAX
    #include <Windows.h>
#endif

#include <argparse/argparse.hpp>

#include <SFML/Graphics.hpp>

#include "const/Const.hpp"
#include "Game/Game.hpp"

using namespace std;
using namespace sf;
