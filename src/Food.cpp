#include "Food.h"

Food::Food() : Entity(APPLE) {
	
}

const Entity& Food::getEntity() const {
	return *this;  
}