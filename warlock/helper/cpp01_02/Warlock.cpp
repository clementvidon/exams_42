#include "Warlock.hpp"

#include <iostream>

using namespace std;

Warlock::~Warlock( void ) {
  map<string, ASpell*>::iterator it;
  for( it = this->spells.begin(); it != this->spells.end(); it++ )
    delete it->second;
  cout << this->name << ": My job here is done!\n";
}

const string& Warlock::getName( void ) const {
  return ( this->name );
}

const string& Warlock::getTitle( void ) const {
  return ( this->title );
}

void Warlock::setTitle( const string& title ) {
  this->title = title;
}

Warlock::Warlock( string name, string title ) : name( name ), title( title ) {
  cout << this->name << ": This looks like another boring day.\n";
}

void Warlock::introduce( void ) const {
  cout << this->name << ": I am " << this->name << ", " << this->title << "!\n";
}

void Warlock::learnSpell( ASpell* spell ) {
  this->spells[spell->getName()] = spell->clone();
}

void Warlock::forgetSpell( string name ) {
  map<string, ASpell*>::iterator position = this->spells.find( name );
  if( position == this->spells.end() )
    return;
  delete position->second;
  this->spells.erase( position );
}

void Warlock::launchSpell( string name, ATarget& target ) {
  map<string, ASpell*>::iterator position = this->spells.find( name );
  if( position == this->spells.end() )
    return;
  position->second->launch( target );
}
