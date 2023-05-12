#include <string>
#include <iostream>

#include "ASpell.hpp"

#include "ATarget.hpp"

ATarget::ATarget( void ) {
  return;
}

ATarget::ATarget( std::string type ) :
  _type( type ) {
  return;
}

ATarget::ATarget( ATarget const& src ) :
  _type( src._type ) {
  return;
}

ATarget::~ATarget( void ) {
  return;
}

ATarget& ATarget::operator=( ATarget const& rhs ) {
  if ( this == &rhs ) {
    return *this;
  }
  _type = rhs._type;
  return *this;
}


std::string const& ATarget::getType( void ) const {
  return _type;
}

void ATarget::getHitBySpell( ASpell const& spell ) const {
  std::cout << _type << " has been " << spell.getEffects() << "!\n";
  return;
}
