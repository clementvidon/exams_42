#ifndef FWOOSH_HPP_
#define FWOOSH_HPP_

#include "ASpell.hpp"

/**
 * TODO
 */

class Fwoosh : public ASpell {
 public:
  Fwoosh( void );
  virtual ~Fwoosh( void );

  virtual Fwoosh* clone( void ) const;
};

#endif  // FWOOSH_HPP_
