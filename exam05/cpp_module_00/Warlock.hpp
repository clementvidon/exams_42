#pragma once

#include <string>

class Warlock {
 public:
  Warlock( std::string name, std::string title );
  ~Warlock( void );

  std::string const& getName( void ) const;
  std::string const& getTitle( void ) const;
  void               setTitle( std::string const& title );
  void               introduce( void ) const;

 private:
  Warlock( void );
  Warlock( Warlock const& src );
  Warlock operator=( Warlock const& rhs );

  std::string _name;
  std::string _title;
};
