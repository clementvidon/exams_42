#ifndef WARLOCK_HPP_
#define WARLOCK_HPP_

#include <iosfwd>
#include <string>

/**
 * Warlock
 */

class Warlock {
 public:
  Warlock( std::string const& name = "default_name",
           std::string const& title = "default_title" );
  virtual ~Warlock( void );

  void introduce( void ) const;

  std::string const& getName( void ) const;
  std::string const& getTitle( void ) const;
  void               setTitle( std::string const& title );

 private:
  Warlock( void );
  Warlock( Warlock const& src );
  Warlock& operator=( Warlock const& rhs );

  std::string _name;
  std::string _title;
};

#endif  // WARLOCK_HPP_
