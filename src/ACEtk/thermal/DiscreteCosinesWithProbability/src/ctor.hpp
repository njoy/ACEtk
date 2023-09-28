DiscreteCosinesWithProbability() = default;

DiscreteCosinesWithProbability( const DiscreteCosinesWithProbability& ) = default;
DiscreteCosinesWithProbability( DiscreteCosinesWithProbability&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energy     the outgoing energy value
 *  @param[in] pdf        the pdf value
 *  @param[in] cdf        the cdf value
 *  @param[in] cosines    the cosine values
 */
DiscreteCosinesWithProbability(
    double energy, double pdf, double cdf,
    std::vector< double > cosines ) :
  Base( "DiscreteCosinesWithProbability",
        generateXSS( energy, pdf, cdf, std::move( cosines ) ) ),
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
DiscreteCosinesWithProbability(
    std::size_t ncosines,
    Iterator begin, Iterator end ) :
  Base( "DiscreteCosinesWithProbability", begin, end ),
  ncosines_( ncosines ) {

  verifySize( this->begin(), this->end(), this->numberDiscreteCosines() );
}

DiscreteCosinesWithProbability& operator=( const DiscreteCosinesWithProbability& ) = default;
DiscreteCosinesWithProbability& operator=( DiscreteCosinesWithProbability&& ) = default;
