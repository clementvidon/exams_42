#ifndef ASPELL_HPP_
#define ASPELL_HPP_

#include <iosfwd>
#include <string>

class ATarget;

class ASpell {
 public:
  ASpell( void );
  ASpell( std::string const& name, std::string const& effects );
  ASpell( ASpell const& src );
  virtual ~ASpell( void );
  ASpell&      operator=( ASpell const& rhs );
  virtual void print( std::ostream& o ) const;

  virtual ASpell* clone( void ) const = 0;
  void            launch( ATarget const& target ) const;

  std::string const& getName( void ) const;
  std::string const& getEffects( void ) const;

 protected:
  std::string _name;
  std::string _effects;

 private:
};

std::ostream& operator<<( std::ostream& o, ASpell const& i );

#endif  // ASPELL_HPP_
