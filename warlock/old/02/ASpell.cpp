#include <iostream>

#include "ATarget.hpp"
#include "ASpell.hpp"

ASpell::ASpell( std::string name, std::string effects ) :
  _name( name ),
  _effects( effects ) {
  return;
}

ASpell::ASpell( ASpell const& src ) :
 _name( src._name ),
 _effects( src._effects ) {
  return;
}

ASpell::~ASpell( void ) {
  return;
}

ASpell& ASpell::operator=( ASpell const& rhs ) {
  if ( this == &rhs ) {
    return ( *this );
  }
  _name = rhs._name;
  _effects = rhs._effects;
  return ( *this );
}

std::string ASpell::getName( void ) const {
  return _name;
}

std::string ASpell::getEffects( void ) const {
  return _effects;
}

void ASpell::launch( ATarget const& target ) const {
  target.getHitBySpell( *this );
  return;
}
