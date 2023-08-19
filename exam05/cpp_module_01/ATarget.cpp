#include <iostream>
#include <string>

#include "ASpell.hpp"
#include "ATarget.hpp"

ATarget::ATarget( void ) {}

ATarget::ATarget( std::string type ) : _type( type ) {}

ATarget::ATarget( ATarget const& src ) : _type( src._type ) {}

ATarget::~ATarget( void ) {}

ATarget& ATarget::operator=( ATarget const& rhs ) {
  if( this != &rhs ) {
    _type = rhs._type;
  }
  return *this;
}

std::string ATarget::getType( void ) const { return _type; }

void ATarget::getHitBySpell( ASpell const& spell ) const {
  std::cout << _type << " has been " << spell.getEffects() << "!\n";
}
