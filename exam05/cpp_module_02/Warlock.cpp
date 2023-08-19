#include <iostream>
#include <string>

#include "ASpell.hpp"
#include "ATarget.hpp"
#include "Warlock.hpp"

Warlock::Warlock( std::string name, std::string title )
  : _name( name ),
    _title( title ) {
  std::cout << _name << ": This looks like another boring day.\n";
}

Warlock::~Warlock( void ) { std::cout << _name << ": My job here is done!\n"; }

std::string const& Warlock::getName( void ) const { return _name; }

std::string const& Warlock::getTitle( void ) const { return _title; }

void Warlock::setTitle( std::string const& title ) { _title = title; }

void Warlock::introduce( void ) const {
  std::cout << _name << ": I am " << _name << ", " << _title << "!\n";
}

void Warlock::learnSpell( ASpell* spell ) { _spellbook.learnSpell( spell ); }

void Warlock::forgetSpell( std::string spellName ) {
  _spellbook.forgetSpell( spellName );
}

void Warlock::launchSpell( std::string spellName, ATarget& target ) {
  ASpell* spell = _spellbook.createSpell( spellName );

  if( spell != NULL ) {
    spell->launch( target );
    delete spell;
  }
}

/* Warlock( void ); */

/* Warlock( Warlock const& src ); */

/* Warlock& operator=( Warlock const& rhs ); */
