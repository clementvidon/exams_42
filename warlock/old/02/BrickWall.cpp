#include <iostream>
#include <string>

#include "ATarget.hpp"
#include "BrickWall.hpp"

BrickWall::BrickWall( void ) :
  ATarget ( "Inconspicuous Red-brick Wall" ) {
  return;
}

BrickWall::~BrickWall( void ) {
  return;
}

BrickWall* BrickWall::clone( void ) const {
  return new BrickWall();
}

