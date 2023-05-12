#pragma once

#include <string>
#include <map>

class ASpell;

class SpellBook {
  public:
    SpellBook( void );
    SpellBook( SpellBook const& src );
    ~SpellBook( void );
    SpellBook& operator=( SpellBook const& rhs );

    void learnSpell( ASpell* spell );
    void forgetSpell( std::string const& spellName );
    ASpell* createSpell( std::string const& spellName );

  private:
    std::map<std::string, ASpell*> _spells;
};
