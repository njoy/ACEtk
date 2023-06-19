private:

/**
 *  @brief Private intermediate constructor
 */
template < typename Data >
ThermalScatteringInelasticAngularDistributionBlock(
    std::vector< std::vector< Data > >&& cosines,
    unsigned int ifeng,
    unsigned int nc,
    std::optional< unsigned int > nieb,
    unsigned int ne,
    std::size_t locb ) :
  Base( "ThermalScatteringInelasticAngularDistributionBlock",
        generateXSS( std::move( cosines ), locb ) ),
  ifeng_( ifeng ), nc_( nc ), nieb_( nieb ), ne_( ne ), locb_( locb ) {

  this->generateBlocks();
}

public:

ThermalScatteringInelasticAngularDistributionBlock() = default;

ThermalScatteringInelasticAngularDistributionBlock(
    const ThermalScatteringInelasticAngularDistributionBlock& base ) :
  Base( base ), ifeng_( base.ifeng_ ),
  nc_( base.nc_ ), nieb_( base.nieb_ ), ne_( base.ne_ ),
  locb_( base.locb_ ), data_( base.data_ ) {

  if ( Base::owner() ) {

    this->data_.clear();
    this->generateBlocks();
  }
}

ThermalScatteringInelasticAngularDistributionBlock(
    ThermalScatteringInelasticAngularDistributionBlock&& base ) :
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
ThermalScatteringInelasticAngularDistributionBlock(
    std::vector< std::vector< ThermalScatteringDiscreteCosines > > cosines,
    bool skewed, std::size_t locb = 1 ) :
  ThermalScatteringInelasticAngularDistributionBlock(
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
ThermalScatteringInelasticAngularDistributionBlock(
    std::vector< std::vector< ThermalScatteringDiscreteCosinesWithProbability > > cosines,
    std::size_t locb = 1 ) :
  ThermalScatteringInelasticAngularDistributionBlock(
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
ThermalScatteringInelasticAngularDistributionBlock(
    unsigned int ifeng, std::size_t nieb, std::size_t nc, std::size_t ne,
    std::size_t locb, Iterator begin, Iterator end ) :
  Base( "ThermalScatteringInelasticAngularDistributionBlock", begin, end ),
  ifeng_( ifeng ), nc_( nc ),
  nieb_( ifeng < 2 ? std::optional< std::size_t >( nieb ) : std::nullopt ),
  ne_( ne ),locb_( locb ) {

  if ( ifeng < 2 ) {

    this->verifySize( this->begin(), this->end(), this->NE(),
                      this->nieb_.value(), this->NC() );
  }
  this->generateBlocks();
}

ThermalScatteringInelasticAngularDistributionBlock&
operator=( const ThermalScatteringInelasticAngularDistributionBlock& base ) {

  new (this) ThermalScatteringInelasticAngularDistributionBlock( base );
  return *this;
}

ThermalScatteringInelasticAngularDistributionBlock&
operator=( ThermalScatteringInelasticAngularDistributionBlock&& base ) {

  new (this) ThermalScatteringInelasticAngularDistributionBlock( std::move( base ) );
  return *this;
}
