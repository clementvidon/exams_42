#include <iostream>
#include <map>
#include <string>

#include "Warlock.hpp"

/*  CANON
------------------------------------------------- */

Warlock::Warlock( std::string const& name, std::string const& title )
  : _name( name ),
    _title( title ) {
  std::cout << _name << ": This looks like another boring day.\n";
  return;
}

Warlock::~Warlock( void ) {
  std::map<std::string, ASpell*>::iterator it;

  for( it = _spells.begin(); it != _spells.end(); ++it ) {
    delete it->second;
  }
  std::cout << _name << ": My job here is done!\n";
  return;
}

/* ---------------------------------------------- */

void Warlock::introduce( void ) const {
  std::cout << _name;
  std::cout << ": I am ";
  std::cout << _name;
  std::cout << ", ";
  std::cout << _title;
  std::cout << "!" << std::endl;
  return;
}

void Warlock::learnSpell( ASpell* spell ) {
  _spells[spell->getName()] = spell->clone();
  return;
}

void Warlock::forgetSpell( std::string name ) {
  std::map<std::string, ASpell*>::iterator it;

  it = _spells.find( name );
  if( it == _spells.end() ) {
    return;
  }
  delete it->second;
  _spells.erase( it );
  return;
}

void Warlock::launchSpell( std::string name, ATarget& target ) {
  std::map<std::string, ASpell*>::iterator it;

  it = this->_spells.find( name );
  if( it == _spells.end() ) {
    return;
  }
  it->second->launch( target );
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
