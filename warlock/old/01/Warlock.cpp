#include <iostream>

#include "Warlock.hpp"
#include "ASpell.hpp"
#include "ATarget.hpp"

Warlock::Warlock( std::string const& name, std::string const& title ) :
  _name( name ),
  _title( title ) {
    std::cout << _name << ": This look like another boring day.\n";
    return;
}

Warlock::~Warlock( void ) {
  std::map<std::string, ASpell*>::iterator it;

  for ( it = _spells.begin(); it != _spells.end(); it++ ) {
    delete it->second;
  }
  std::cout << _name << ": My job here is done!\n";
  return;
}

std::string const& Warlock::getName( void ) const {
  return _name;
}

std::string const& Warlock::getTitle( void ) const {
  return _title;
}

void Warlock::setTitle( std::string const& title ) {
  _title = title;
  return;
}

void Warlock::introduce( void ) const {
  std::cout << _name << ": I am " << _name << ", " << _title << "!\n";
  return;
}

void Warlock::learnSpell( ASpell *spell ) {
  _spells[spell->getName()] = spell->clone(); // TODO if exist ? leak ?
  return;
}

void Warlock::forgetSpell( std::string spellName ) {
  std::map<std::string, ASpell*>::iterator it;

  it = _spells.find( spellName );
  if ( it == _spells.end() ) {
    return;
  }
  delete it->second; // TODO
  _spells.erase( it ); // TODO why not it.erase() ?
  return;
}

void Warlock::launchSpell( std::string spellName, ATarget &target ) {
  std::map<std::string, ASpell*>::iterator it;

  it = _spells.find( spellName );
  if ( it == _spells.end() ) {
    return;
  }
  it->second->launch( target );
  return;
}
