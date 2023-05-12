#pragma once

#include <string>

#include "ATarget.hpp"

class BrickWall : public ATarget {
  public:
    BrickWall( void );
    ~BrickWall( void );

    virtual BrickWall* clone( void ) const;
};

