DiscreteCosines() = default;

DiscreteCosines( const DiscreteCosines& ) = default;
DiscreteCosines( DiscreteCosines&& ) = default;

DiscreteCosines& operator=( const DiscreteCosines& ) = default;
DiscreteCosines& operator=( DiscreteCosines&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energy     the outgoing energy value
 *  @param[in] cosines    the discrete cosine values
 */
DiscreteCosines( double energy, std::vector< double > cosines ) :
  Base( "DiscreteCosines", generateXSS( energy, std::move( cosines ) ) ),
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
DiscreteCosines( std::size_t ncosines, Iterator begin, Iterator end ) :
  Base( "DiscreteCosines", begin, end ),
  ncosines_( ncosines ) {

  verifySize( this->begin(), this->end(), this->numberDiscreteCosines() );
}
