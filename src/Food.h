#pragma once
#include "Entity.h"

class Food : public Entity{
private:

public:
	Food();

	const Entity& getEntity() const;
};