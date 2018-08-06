class Bremsstrahlung {
  std::reference_wrapper<const Table> table_;
  
public:
  Bremsstrahlung( const Table& table ) : table_( std::cref(table) ) {}

protected:
  using Slice = decltype(this->table.get().data.XSS( 10, 20 ));

  using IsEnergy =
    std::integral_constant
    < bool, Energy::units().dimensionality() == dimension::energy >;
  
  static constexpr auto cm = centi(meter);
  static constexpr auto MeV = mega(electronVolts);
  
  const Table& table() const { return this->table; }
  
public:
  #include "ACEtk/EL03/Bremsstrahlung/Production.hpp"
  
  auto production() const {
    const auto& table = this->table();

    const auto energyStart = table.data.JXS( 5 );
    const auto energyLength = table.data.NXS( 5 );    
    const auto electronEnergies = table.data.XSS( energyStart, energyLength );

    const auto ratioStart = energyStart + energyLength;
    const auto ratioLength = table.data.NXS( 6 );
    const auto energyRatios = table.data.XSS( ratioStart, ratiolength );

    const auto xsStart = ratioStart + ratioLength;
    const auto xsLength = energyLength * ratioLength;
    const auto crossSections = table.data.XSS( xsStart, xsLength );

    return Production{ electronEnergies, energyRatios, crossSections };
  }

  template<typename Energy,
	   utility::Require< true, IsEnergy, Energy > = true > >
  class ReferenceEnergies {
    std::reference_wrapper<const Table> table_;    
    Energy electronEnergy;

    const Table& table() const { return this->table_; }
    
    auto get(int index) const {
      const auto start  = this->table().data.JXS( index );
      const auto length = this->table().data.NXS( index );
      return
	this->table().data.XSS( start, length )
	| ranges::view::transform( scaleBy( this->electronEnergy ) );
    }
    
  public:
    ReferenceEnergies( const table& table, Energy electronEnergy ) :
      table_( std::cref(table) ),
      electronEnergy( std::move(electronEnergy) ){}

    auto photonSpectrum() const { return this->get(9); }
    auto photonAngularDistribution() const { return this->get(10); }
  };

  template<typename Energy,
	   utility::Require< true, IsEnergy, std::decay_t<Energy> > = true > >
  auto referenceEnergies( Energy&& electronEnergy ) const {
    return ReferenceEnergies< std::decay_t<Energy> >
      { this->table(), std::forward<Energy>(electronEnergy) };
  }
};
