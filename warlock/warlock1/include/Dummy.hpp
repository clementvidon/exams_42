#ifndef DUMMY_HPP_
#define DUMMY_HPP_

#include "ATarget.hpp"

class Dummy : public ATarget {
 public:
  Dummy( void );
  virtual ~Dummy( void );

  Dummy* clone( void ) const;
};

#endif  // DUMMY_HPP_
