#pragma once

#include <string>

#include "ASpell.hpp"

class Fireball : public ASpell {
  public:
    Fireball( void );
    ~Fireball( void );

    virtual Fireball* clone( void ) const;
};
