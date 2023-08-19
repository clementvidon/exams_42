#pragma once

#include <string>
#include <map>

class ASpell;
class ATarget;

class SpellBook {
  public:
    SpellBook( void );
    ~SpellBook( void );

    void learnSpell( ASpell *spell );
    void forgetSpell( std::string spellName );
    ASpell *createSpell( std::string spellName );

  private:
    SpellBook( SpellBook const& src );
    SpellBook& operator=( SpellBook const& rhs );

    std::map<std::string, ASpell*> _spells;
};
