#pragma once

#include <string>

enum class Move : short {
    NO = 0, LEFT, UP, RIGHT, DOWN
};

static std::string MoveToString(Move move) {
	switch (move) {
		case Move::DOWN: {
			return "down";
		}
		case Move::LEFT: {
			return "left";
		}
		case Move::NO: {
			return "no";
		}
		case Move::RIGHT: {
			return "right";
		}
		case Move::UP: {
			return "up";
		}
		default: {
			return "";
		}
	}
}
