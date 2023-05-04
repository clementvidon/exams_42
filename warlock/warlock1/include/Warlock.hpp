#ifndef WARLOCK_HPP_
#define WARLOCK_HPP_

#include <iosfwd>
#include <map>
#include <string>

#include "ASpell.hpp"

/**
 * Warlock
 */

class Warlock {
 public:
  Warlock( void );
  Warlock( Warlock const& src );
  Warlock& operator=( Warlock const& rhs );
  Warlock( std::string const& name, std::string const& title );
  virtual ~Warlock( void );

  void introduce( void ) const;

  void learnSpell( ASpell* spell );
  void forgetSpell( std::string name );
  void launchSpell( std::string name, ATarget& target );

  std::string const& getName( void ) const;
  std::string const& getTitle( void ) const;
  void               setTitle( std::string const& title );

  std::string                    _name;
  std::string                    _title;
  std::map<std::string, ASpell*> _spells;
};

#endif  // WARLOCK_HPP_
