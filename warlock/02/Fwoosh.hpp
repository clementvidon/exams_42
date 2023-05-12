#pragma once

#include <string>

#include "ASpell.hpp"

class Fwoosh : public ASpell {
  public:
    Fwoosh( void );
    ~Fwoosh( void );

    virtual Fwoosh* clone( void ) const;
};
