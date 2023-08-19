#include <map>
#include <string>

#include "ASpell.hpp"
#include "ATarget.hpp"
#include "SpellBook.hpp"

SpellBook::SpellBook( void ) {}

SpellBook::~SpellBook( void ) {
  std::map<std::string, ASpell*>::iterator it;

  for( it = _spells.begin(); it != _spells.end(); ++it ) {
    delete it->second;
  }
  _spells.clear();
}

void SpellBook::learnSpell( ASpell* spell ) {
  if( spell != NULL ) {
    std::string spellName = spell->getName();
    if( _spells.find( spellName ) == _spells.end() ) {
      _spells[spellName] = spell->clone();
    }
  }
}

void SpellBook::forgetSpell( std::string spellName ) {
  std::map<std::string, ASpell*>::iterator it = _spells.find( spellName );

  if( it != _spells.end() ) {
    delete it->second;
    _spells.erase( it );
  }
}

ASpell* SpellBook::createSpell( std::string spellName ) {
  std::map<std::string, ASpell*>::iterator it = _spells.find( spellName );

  if( it != _spells.end() ) {
    return it->second->clone();
  }
  return NULL;
}

/* SpellBook& operator=( SpellBook const& rhs ); */

/* SpellBook( SpellBook const& src ); */
