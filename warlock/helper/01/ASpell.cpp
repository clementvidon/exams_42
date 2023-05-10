#include "ASpell.hpp"

ASpell::ASpell( void ) {
}

ASpell::~ASpell( void ) {
}

ASpell::ASpell( const ASpell& from )
  : name( from.name ),
    effects( from.effects ) {
}

ASpell& ASpell::operator=( const ASpell& from ) {
  if( this == &from )
    return ( *this );
  this->name = from.name;
  this->effects = from.effects;
  return ( *this );
}

string ASpell::getName( void ) const {
  return ( this->name );
}

string ASpell::getEffects( void ) const {
  return ( this->effects );
}

ASpell::ASpell( string name, string effects )
  : name( name ),
    effects( effects ) {
}

void ASpell::launch( const ATarget& target ) const {
  target.getHitBySpell( *this );
}
