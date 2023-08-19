#pragma once

#include "ASpell.hpp"

class Fwoosh : public ASpell {
  public:
    Fwoosh( void );
    virtual Fwoosh *clone( void ) const;
};
