#include <iostream>
#include <string>

#include "Fwoosh.hpp"

/*  CANON
------------------------------------------------- */

Fwoosh::Fwoosh( void ) : ASpell( "Fwoosh", "fwooshed" ) {
  return;
}

Fwoosh::~Fwoosh( void ) {
  return;
}

/* ---------------------------------------------- */

Fwoosh* Fwoosh::clone( void ) const {
  return new Fwoosh();
}
