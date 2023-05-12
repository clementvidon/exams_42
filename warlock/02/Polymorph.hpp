#pragma once

#include <string>

#include "ASpell.hpp"

class Polymorph : public ASpell {
  public:
    Polymorph( void );
    ~Polymorph( void );

    virtual Polymorph* clone( void ) const;
};
