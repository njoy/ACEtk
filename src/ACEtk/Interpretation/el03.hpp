template< >
class Interpretation< El03 >{

  const Table& table;

public:
  Interpretation( const Table& table ) : table( table ) {}


  
  template< typename Tag >
  auto energyGrid( const Tag ) const {
    return table.data.XSS( table.data.JXS( Tag::energyGridBegin ),
			   table.data.NXS( Tag::energyGridLength ) )
      | ranges::view::reverse
      | ranges::view::transform( []( const auto& entry ){ return entry * mega( electronVolt ); } );
  }

  auto bremsstrahlungCorrection() const {  
    auto length = table.data.NXS( 3 );
    auto start  = table.data.JXS( 2 ) + 2 * length;
    return table.data.XSS( start, length ) | ranges::view::reverse;
  }
  
  auto atomicNumber() const {
    return table.data.NXS( 2 );
  }

  auto radiativeStoppingPower( ) const {

    const auto atomicNumber = this->atomicNumber();

    constexpr Quantity< Mega< ElectronVolt > > massEquivalent =
      constant::electronMass * constant::lightSpeed * constant::lightSpeed;
    
    auto totalEnergy = this->energyGrid( El03::RadiativeStopping{} )
      | ranges::view::transform( [massEquivalent]( const auto& entry )
				 { return entry + massEquivalent; } );


    constexpr auto multiplier = constant::classicalElectronRadius
                              * constant::classicalElectronRadius
                              * constant::fineStructure ;

    auto predecate = [m=multiplier, z=atomicNumber]( const auto& tup )
      { return m * z * ( z + std::get<0>(tup) ) * std::get<1>(tup) * std::get<2>(tup); };      

    auto length = table.data.NXS( 3 );
    auto start  = table.data.JXS( 2 ) + length;
    auto radiativeStopping = table.data.XSS( start, length ) | ranges::view::reverse;;
    
    return ranges::view::zip( this->bremsstrahlungCorrection(),
			      radiativeStopping,
			      totalEnergy )
      | ranges::view::transform( predecate );

  }

};
  
