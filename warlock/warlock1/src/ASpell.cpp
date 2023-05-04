#include <iostream>
#include <string>

#include "ASpell.hpp"
#include "ATarget.hpp"

/*  CANON
------------------------------------------------- */

ASpell::ASpell( void ) {
  return;
}

ASpell::ASpell( std::string const& name, std::string const& effects )
  : _name( name ),
    _effects( effects ) {
  return;
}

ASpell::ASpell( ASpell const& src )
  : _name( src._name ),
    _effects( src._effects ) {
  return;
}

ASpell::~ASpell( void ) {
  return;
}

ASpell& ASpell::operator=( ASpell const& rhs ) {
  if( this == &rhs ) {
    return *this;
  }
  _name = rhs._name;
  _effects = rhs._effects;
  return *this;
}

void ASpell::print( std::ostream& o ) const {
  o << _name;
  return;
}

std::ostream& operator<<( std::ostream& o, ASpell const& i ) {
  i.print( o );
  return o;
}

/* ---------------------------------------------- */

void ASpell::launch( ATarget const& target ) const {
  target.getHitBySpell( *this );
  return;
}

/*  GETTER SETTER
------------------------------------------------- */

std::string const& ASpell::getName( void ) const {
  return _name;
}

std::string const& ASpell::getEffects( void ) const {
  return _effects;
}
