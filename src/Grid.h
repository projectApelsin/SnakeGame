#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include <iostream>
#include "src/Entity.h"

class Grid {
private:
	std::vector<std::shared_ptr<Entity>> grid;
public:
	Grid() {

	}
};