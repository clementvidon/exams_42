#ifndef ATARGET_HPP_
#define ATARGET_HPP_

#include <iosfwd>
#include <string>

class ASpell; // TODO forward declare "error:" "has not been declared"

class ATarget {
 public:
  ATarget( void );
  ATarget( std::string const& type );
  ATarget( ATarget const& src );
  virtual ~ATarget( void );
  ATarget&     operator=( ATarget const& rhs );
  virtual void print( std::ostream& o ) const;

  virtual ATarget* clone( void ) const = 0;
  void             getHitBySpell( ASpell const& spell ) const;

  std::string const& getType( void ) const;

 private:
  std::string _type;
};

std::ostream& operator<<( std::ostream& o, ATarget const& i );

#endif  // ATARGET_HPP_
