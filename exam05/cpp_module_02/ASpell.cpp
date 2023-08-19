#include <string>

#include "ASpell.hpp"
#include "ATarget.hpp"

ASpell::ASpell( void ) {}

ASpell::ASpell( std::string name, std::string effects )
  : _name( name ),
    _effects( effects ) {}

ASpell::ASpell( ASpell const& src )
  : _name( src._name ),
    _effects( src._effects ) {}

ASpell::~ASpell( void ) {}

ASpell& ASpell::operator=( ASpell const& rhs ) {
  if( this != &rhs ) {
    _name = rhs._name;
    _effects = rhs._effects;
  }
  return *this;
}

std::string ASpell::getName( void ) const { return _name; }

std::string ASpell::getEffects( void ) const { return _effects; }

void ASpell::launch( ATarget const& target ) const {
  target.getHitBySpell( *this );
}
