/* 01/ATarget */
/* Created: 230817 08:59:15 by clem@ghost */
/* Updated: 230817 08:59:18 by clem@ghost */
/* Maintainer: Clément Vidon */

#pragma once

#include <string>

class ASpell;

class ATarget {
 public:
  ATarget( void );
  ATarget( std::string type );
  ATarget( ATarget const& src );
  virtual ~ATarget( void );
  ATarget& operator=( ATarget const& rhs );

  std::string      getType( void ) const;
  virtual ATarget* clone( void ) const = 0;
  void             getHitBySpell( ASpell const& spell ) const;

 private:
  std::string _type;
};
