class Coherent{
  std::reference_wrapper<const Table> table;

#include "ACEtk/interpretation/EPRData/Coherent/FormFactors.hpp"
  
public:
  Coherent( const Table& table ) : table(table) {}

  auto logEnergies() const {
    const auto length = this->table.get().data.NXS( 3 );
    const auto start  = this->table.get().data.JXS( 1 );
    return this->table.get().data.XSS( start, length );
  }

  auto energies() const {
    return this->logEnergies()
      | ranges::view::transform( []( auto&& entry ){
	  return std::exp(entry) * mega(electronVolt); } );
  }  

  auto logCrossSection() const {
    const auto length = this->table.get().data.NXS( 3 );
    const auto start  = this->table.get().data.JXS( 1 ) + 2*length;
    return this->table.get().data.XSS( start, length );
  }

  auto crossSection() const {
    return this->logCrossSection()
      | ranges::view::transform( []( auto&& entry ){
	  return std::exp(entry) * barn; } );  ;
  }  

  auto formFactors() const {
    return FormFactors{ this->table.get() };
  }
  
};
