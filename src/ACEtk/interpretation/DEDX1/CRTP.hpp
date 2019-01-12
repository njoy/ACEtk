template<typename Derived>
class CRTP{
  std::reference_wrapper<const Table> table;

  static constexpr auto cm = dimwits::centi(dimwits::meter);
  static constexpr auto cc = cm*cm*cm;  
  static constexpr auto mev = dimwits::mega(dimwits::electronVolt);
  using DenT = decltype(1.0/cc);
  using TempT = decltype(1.0*mev);

  #include "ACEtk/interpretation/DEDX1/CRTP/src/S0.hpp"

protected:
  auto numEnergies() const {return this->table.get().data.NXS( 4 );}
  auto numDensities() const {return this->table.get().data.NXS( 5 );}
  auto numTemperatures() const {return this->table.get().data.NXS( 6 );}
  auto gridStart() const {return this->table.get().data.JXS( 2 );}    

public:
  CRTP( const Table& table ) : table(table) {}

  auto logEnergies() const {
    const auto length = this->numEnergies();
    const auto start = this->gridStart();
    return this->table.get().data.XSS( start, length );    
  }
  
  auto energies() const {
    return this->logEnergies()
      | ranges::view::transform( []( auto&& entry ){
	  return std::exp(entry) * mega(electronVolt); } );
  }

  auto densities() const {    
    return this->logDensities()
      | ranges::view::transform( [cc=this->cc]( auto&& entry ){
	  return std::exp(entry)/cc; } );
  }
  
  auto logDensities() const {
    const auto length = this->numDensities();
    const auto start = this->gridStart() + this->numEnergies();
    return this->table.get().data.XSS( start, length );    
  }

  auto logTemperatures() const {
    const auto length = this->numTemperatures();
    const auto start = this->gridStart() + this->numEnergies() + this->numDensities();
    return this->table.get().data.XSS( start, length );    
  }  

  auto temperatures() const {
    return this->logTemperatures()
      | ranges::view::transform( []( auto&& entry ){
	  return std::exp(entry) * mega(electronVolt); } );
  }      

  #include "ACEtk/interpretation/DEDX1/CRTP/src/stoppingPowers.hpp"    

};
