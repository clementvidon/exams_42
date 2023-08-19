#pragma once

#include "ATarget.hpp"

class Dummy : public ATarget {
 public:
  Dummy( void );
  virtual Dummy* clone( void ) const;
};
