#include <string>
#include <iostream>

#include "ASpell.hpp"

#include "Fireball.hpp"

Fireball::Fireball( void ) :
  ASpell( "Fireball", "burnt to a crisp" ) {
  return;
}

Fireball::~Fireball( void ) {
  return;
}

Fireball* Fireball::clone( void ) const {
  return new Fireball();
}
