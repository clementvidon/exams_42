#pragma once

#include <string>

/* #include "ATarget.hpp" */
class ATarget; // TODO why?

class ASpell {
  public:
    ASpell( void );
    ASpell( std::string name, std::string effects );
    ASpell( ASpell const& src );
    virtual ~ASpell( void );
    ASpell& operator=( ASpell const& rhs );

    std::string getName( void ) const;
    std::string getEffects( void ) const;

    virtual ASpell* clone( void ) const = 0;
    void launch( ATarget const& target ) const;

  protected:
    std::string _name;
    std::string _effects;
};
