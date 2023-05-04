#include <iostream>
#include <string>

#include "Dummy.hpp"

/*  CANON
------------------------------------------------- */

Dummy::Dummy( void ) : ATarget( "Target Practice Dummy" ) {
  return;
}

Dummy::~Dummy( void ) {
  return;
}

/* ---------------------------------------------- */

Dummy* Dummy::clone( void ) const {
  return new Dummy();
}
