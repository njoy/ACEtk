ThermalScatteringDiscreteCosines() = default;

ThermalScatteringDiscreteCosines( const ThermalScatteringDiscreteCosines& ) = default;
ThermalScatteringDiscreteCosines( ThermalScatteringDiscreteCosines&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energy     the outgoing energy value
 *  @param[in] cosines    the discrete cosine values
 */
ThermalScatteringDiscreteCosines( double energy,
                                  std::vector< double > cosines ) :
  Base( "ThermalScatteringDiscreteCosines",
        generateXSS( energy, std::move( cosines ) ) ),
  ncosines_( cosines.size() ) {

  verifySize( this->XSS().size(), this->numberDiscreteCosines() );
}

/**
 *  @brief Constructor
 *
 *  @param[in] ncosines    the number of discrete cosines
 *  @param[in] begin       the begin iterator of the equiprobable bin data
 *  @param[in] end         the end iterator of the equiprobable bin data
 */
ThermalScatteringDiscreteCosines( std::size_t ncosines,
                                  Iterator begin, Iterator end ) :
  Base( "ThermalScatteringDiscreteCosines", begin, end ),
  ncosines_( ncosines ) {

  verifySize( this->begin(), this->end(), this->numberDiscreteCosines() );
}

ThermalScatteringDiscreteCosines& operator=( const ThermalScatteringDiscreteCosines& ) = default;
ThermalScatteringDiscreteCosines& operator=( ThermalScatteringDiscreteCosines&& ) = default;
