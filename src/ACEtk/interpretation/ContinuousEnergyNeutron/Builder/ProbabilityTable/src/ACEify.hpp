void ACEify( ACEtk::Table::Data& tData){
  decltype( auto ) xss = tData.XSS();

  xss.push_back( this->incidentEnergies.size() );             // N
  xss.push_back( this->tables.size() );                       // M
  xss.push_back( this->interpolationParameter );              // INT
  xss.push_back( this->inelasticCompetition );                // ILF
  xss.push_back( this->otherAbsorption );                     // IOA
  xss.push_back( static_cast< int >( this->factors ) );       // IFF

  xss |= ranges::action::push_back( this->incidentEnergies );

  for( decltype( auto ) table : this->tables ){
    details::ACEify( tData, table );
  }
}
