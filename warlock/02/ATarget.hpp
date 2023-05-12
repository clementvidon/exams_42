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

    std::string const& getType( void ) const;

    virtual ATarget* clone( void ) const = 0;

    void getHitBySpell( ASpell const& spell ) const;

  protected:
    std::string _type;
};
