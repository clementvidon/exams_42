#pragma once

#include <string>

class ATarget;

#include "ASpell.hpp"

using namespace std;

class ATarget {
 private:
  string type;

 public:
  ATarget( void );
  virtual ~ATarget( void );

  ATarget( const ATarget& from );

  ATarget& operator=( const ATarget& from );

  const string& getType( void ) const;

  virtual ATarget* clone( void ) const = 0;

  ATarget( string type );

  void getHitBySpell( const ASpell& spell ) const;
};
