#include "Monster.h"
#include "MemoryManager.h"


Monster::Monster()
{	

}

void Monster::Move(Point2D* toGo) {
	*position = *position + *toGo;
	lifeTime--;
}

