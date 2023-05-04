#include <iostream>
#include <string>

#include "ASpell.hpp"
#include "ATarget.hpp"

/*  CANON
------------------------------------------------- */

ATarget::ATarget( void ) {
  return;
}

ATarget::ATarget( std::string const& type ) : _type( type ) {
  return;
}

ATarget::ATarget( ATarget const& src ) : _type( src._type ) {
  return;
}

ATarget::~ATarget( void ) {
  return;
}

ATarget& ATarget::operator=( ATarget const& rhs ) {
  if( this == &rhs ) {
    return *this;
  }
  _type = rhs._type;
  return *this;
}

void ATarget::print( std::ostream& o ) const {
  o << _type;
  return;
}

std::ostream& operator<<( std::ostream& o, ATarget const& i ) {
  i.print( o );
  return o;
}

/* ---------------------------------------------- */

void ATarget::getHitBySpell( ASpell const& spell ) const {
  std::cout << _type << " has been " << spell.getEffects() << "!\n";
  return;
}

std::string const& ATarget::getType( void ) const {
  return _type;
}
