#include <iostream>
#include <string>

#include "ASpell.hpp"
#include "Fwoosh.hpp"

Fwoosh::Fwoosh( void ) :
  ASpell ( "Fwoosh", "fwosshed" ) {
  return;
}

Fwoosh::~Fwoosh( void ) {
  return;
}

Fwoosh* Fwoosh::clone( void ) const {
  return new Fwoosh();
}

