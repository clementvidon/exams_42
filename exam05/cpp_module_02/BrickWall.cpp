#include "ATarget.hpp"
#include "BrickWall.hpp"

BrickWall::BrickWall( void ) : ATarget( "Inconspicuous Red-brick Wall" ) {}

BrickWall* BrickWall::clone( void ) const { return new BrickWall(); }
