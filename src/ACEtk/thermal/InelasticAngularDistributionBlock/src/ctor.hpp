private:

/**
 *  @brief Private intermediate constructor
 */
template < typename Data >
InelasticAngularDistributionBlock(
    std::vector< std::vector< Data > >&& cosines,
    unsigned int ifeng,
    unsigned int nc,
    std::optional< unsigned int > nieb,
    unsigned int ne,
    std::size_t locb ) :
  Base( "InelasticAngularDistributionBlock",
        generateXSS( std::move( cosines ), locb ) ),
  ifeng_( ifeng ), nc_( nc ), nieb_( nieb ), ne_( ne ), locb_( locb ) {

  this->generateBlocks();
}

public:

InelasticAngularDistributionBlock() = default;

InelasticAngularDistributionBlock( const InelasticAngularDistributionBlock& base ) :
  Base( base ), ifeng_( base.ifeng_ ),
  nc_( base.nc_ ), nieb_( base.nieb_ ), ne_( base.ne_ ),
  locb_( base.locb_ ), data_( base.data_ ) {

  if ( Base::owner() ) {

    this->data_.clear();
    this->generateBlocks();
  }
}

InelasticAngularDistributionBlock( InelasticAngularDistributionBlock&& base ) :
  Base( std::move( base ) ), ifeng_( base.ifeng_ ),
  nc_( base.nc_ ), nieb_( base.nieb_ ), ne_( base.ne_ ),
  locb_( base.locb_ ), data_( std::move( base.data_ ) ) {

  if ( Base::owner() ) {

    this->data_.clear();
    this->generateBlocks();
  }
}

/**
 *  @brief Constructor
 *
 *  @param[in] cosines    the discrete cosine data for each incident and outgoing
 *                        energy value
 *  @param[in] skewed     flag to indicate whether or not the distribution is
 *                        skewed or equiprobable
 *  @param[in] locb       the starting xss index for the ITXE block (default = 1)
 */
InelasticAngularDistributionBlock(
    std::vector< std::vector< DiscreteCosines > > cosines,
    bool skewed, std::size_t locb = 1 ) :
  InelasticAngularDistributionBlock(
      std::move( cosines ),
      static_cast< unsigned int >( skewed ),
      cosines.front().front().NC(),
      cosines.front().size(),
      cosines.size(),
      locb ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] cosines    the discrete cosine data for each incident and outgoing
 *                        energy value
 *  @param[in] locb       the starting xss index for the ITXE block (default = 1)
 */
InelasticAngularDistributionBlock(
    std::vector< std::vector< DiscreteCosinesWithProbability > > cosines,
    std::size_t locb = 1 ) :
  InelasticAngularDistributionBlock(
      std::move( cosines ), 2, cosines.front().front().NC(),
      std::nullopt, cosines.size(), locb ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] ifeng      the inelastic format flag
 *  @param[in] nieb       the number of outgoing energy values (for ifeng < 2 only)
 *  @param[in] nc         the number of discrete cosine values
 *  @param[in] begin      the begin iterator of the angular distribution data
 *  @param[in] end        the end iterator of the angular distribution data
 */
InelasticAngularDistributionBlock(
    unsigned int ifeng, std::size_t nieb, std::size_t nc, std::size_t ne,
    std::size_t locb, Iterator begin, Iterator end ) :
  Base( "InelasticAngularDistributionBlock", begin, end ),
  ifeng_( ifeng ), nc_( nc ),
  nieb_( ifeng < 2 ? std::optional< std::size_t >( nieb ) : std::nullopt ),
  ne_( ne ),locb_( locb ) {

  if ( ifeng < 2 ) {

    this->verifySize( this->begin(), this->end(), this->NE(),
                      this->nieb_.value(), this->NC() );
  }
  this->generateBlocks();
}

InelasticAngularDistributionBlock&
operator=( const InelasticAngularDistributionBlock& base ) {

  new (this) InelasticAngularDistributionBlock( base );
  return *this;
}

InelasticAngularDistributionBlock&
operator=( InelasticAngularDistributionBlock&& base ) {

  new (this) InelasticAngularDistributionBlock( std::move( base ) );
  return *this;
}
