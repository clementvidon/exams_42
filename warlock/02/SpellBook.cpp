#include <string>
#include <iostream>

#include "ASpell.hpp"
#include "ATarget.hpp"

#include "SpellBook.hpp"

/* SpellBook( void ) { */
/*   return; */
/* } */

SpellBook::SpellBook( void ) {
    return;
}

/* SpellBook( SpellBook const& src ) { */
/*   return; */
/* } */

SpellBook::~SpellBook( void ) {
  std::map<std::string, ASpell*>::iterator it;

  for ( it = _spells.begin(); it != _spells.end(); ++it ) {
    delete it->second; // TODO why "->" ? un iterateur est un pointeur
  }
  return;
}

/* SpellBook& operator=( SpellBook const& src) { */
/*   return; */
/* } */


void SpellBook::learnSpell( ASpell* spell ) {
  _spells[spell->getName()] = spell->clone();
  return;
}

void SpellBook::forgetSpell( std::string const& spellName ) {
  std::map<std::string, ASpell*>::iterator it;

  it = _spells.find( spellName );
  if ( it == _spells.end() ) {
    return;
  }
  delete it->second;
  _spells.erase( it );
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
