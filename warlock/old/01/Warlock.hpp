#pragma once

#include <string>
#include <map>

class ASpell;
class ATarget;

class Warlock {
  public:
    Warlock( void );
    Warlock( std::string const& name, std::string const& title );
    Warlock( Warlock const& src );
    ~Warlock( void );
    Warlock& operator=( Warlock const& rhs );

    std::string const& getName( void ) const;
    std::string const& getTitle( void ) const;
    void setTitle( std::string const& title );

    void introduce( void ) const;
    void learnSpell( ASpell *spell );
    void forgetSpell( std::string spellName );
    void launchSpell( std::string spellName, ATarget &target );

  private:
    std::string _name;
    std::string _title;
    std::map<std::string, ASpell*> _spells;
};
