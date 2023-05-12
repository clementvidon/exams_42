#include <string>
#include <iostream>

#include "ASpell.hpp"

#include "Fwoosh.hpp"

Fwoosh::Fwoosh( void ) :
  ASpell( "Fwoosh", "fwooshed" ) {
  return;
}

Fwoosh::~Fwoosh( void ) {
  return;
}

Fwoosh* Fwoosh::clone( void ) const {
  return new Fwoosh();
}
