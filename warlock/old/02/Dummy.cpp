#include <iostream>
#include <string>

#include "ATarget.hpp"
#include "Dummy.hpp"

Dummy::Dummy( void ) :
  ATarget ( "Target Practice Dummy" ) {
  return;
}

Dummy::~Dummy( void ) {
  return;
}

Dummy* Dummy::clone( void ) const {
  return new Dummy();
}

