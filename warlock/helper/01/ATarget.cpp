#include "ATarget.hpp"

#include <iostream>

using namespace std;

ATarget::ATarget( void ) {
}

ATarget::~ATarget( void ) {
}

ATarget::ATarget( const ATarget& from ) : type( from.type ) {
}

ATarget& ATarget::operator=( const ATarget& from ) {
  if( this == &from )
    return ( *this );
  this->type = from.type;
  return ( *this );
}

const string& ATarget::getType( void ) const {
  return ( this->type );
}

ATarget::ATarget( string type ) : type( type ) {
}

void ATarget::getHitBySpell( const ASpell& spell ) const {
  cout << this->type << " has been " << spell.getEffects() << "!\n";
}
