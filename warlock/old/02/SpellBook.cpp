#include <iostream>

#include "ASpell.hpp"

#include "SpellBook.hpp"

SpellBook::SpellBook( void ) {
  return;
}

SpellBook::~SpellBook( void ) {
  std::map<std::string, ASpell*>::iterator it;

  for ( it = _spells.begin(); it != _spells.end(); ++it ) {
    delete it->second;
  }
  return;
}

void SpellBook::learnSpell( ASpell* spell ) {
  _spells[spell->getName()] = spell->clone(); // TODO if exist ? leak ?
  return;
}

void SpellBook::forgetSpell( std::string const& spellName ) {
  std::map<std::string, ASpell*>::iterator it;

  it = _spells.find( spellName );
  if ( it == _spells.end() ) {
    return;
  }
  delete it->second; // TODO
  _spells.erase( it ); // TODO why not it.erase() ?
  return;
}

ASpell* SpellBook::createSpell( std::string const& spellName ) {
  std::map<std::string, ASpell*>::iterator it;

  it = _spells.find( spellName );
  if ( it == _spells.end() ) {
    return NULL;
  }
  return it->second->clone();
}
