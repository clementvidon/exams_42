#pragma once

#include <string>
#include <map>

#include "ATarget.hpp"

class ASpell;

class SpellBook {
  public:
    SpellBook( void );
    SpellBook( std::string name, std::string title );
    SpellBook( SpellBook const& src );
    ~SpellBook( void );
    SpellBook& operator=( SpellBook const& src);

    void learnSpell( ASpell* spell );
    void forgetSpell( std::string const& spellName );
    ASpell* createSpell( std::string const& spellName );

  private:
    std::map<std::string, ASpell*> _spells;
};
