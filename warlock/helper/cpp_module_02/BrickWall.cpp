#include "BrickWall.hpp"

BrickWall::BrickWall(void):
	ATarget("Inconspicuous Red-brick Wall")
{}

BrickWall::~BrickWall(void)
{}

BrickWall*	BrickWall::clone(void) const
{
	return (new BrickWall());
}