#pragma once

#include "ASpell.hpp"

class Polymorph : public ASpell {
  public:
    Polymorph( void );
    virtual ~Polymorph( void );

    virtual Polymorph* clone( void ) const;

  private:
};
