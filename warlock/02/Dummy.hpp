#pragma once

#include <string>

#include "ATarget.hpp"

class Dummy : public ATarget {
  public:
    Dummy( void );
    ~Dummy( void );

    virtual Dummy* clone( void ) const;
};

