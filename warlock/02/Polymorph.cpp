#include <string>
#include <iostream>

#include "ASpell.hpp"

#include "Polymorph.hpp"

Polymorph::Polymorph( void ) :
  ASpell( "Polymorph", "turned into a critter" ) {
  return;
}

Polymorph::~Polymorph( void ) {
  return;
}

Polymorph* Polymorph::clone( void ) const {
  return new Polymorph();
}
