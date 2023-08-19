#include <iostream>
#include <map>
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

void Warlock::learnSpell( ASpell* spell ) {
  if( spell != NULL ) {
    std::map<std::string, ASpell*>::iterator it;
    std::string                              spellName = spell->getName();

    it = _spells.find( spellName );
    if( it == _spells.end() ) {
      _spells[spellName] = spell;
    }
  }
}

void Warlock::forgetSpell( std::string spellName ) {
  std::map<std::string, ASpell*>::iterator it;

  it = _spells.find( spellName );
  if( it != _spells.end() ) {
    _spells.erase( it );
  }
}

void Warlock::launchSpell( std::string spellName, ATarget& target ) {
  std::map<std::string, ASpell*>::iterator it;

  it = _spells.find( spellName );
  if( it != _spells.end() ) {
    it->second->launch( target );
    delete it->second;
  }
}

/* Warlock& operator=( Warlock const& rhs ); */

/* Warlock( void ); */

/* Warlock( Warlock const& src ); */
