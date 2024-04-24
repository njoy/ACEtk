InterpolationData() = default;

InterpolationData( const InterpolationData& ) = default;
InterpolationData( InterpolationData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] name           the name of the data
 *  @param[in] boundaries     the interpolation range boundaries
 *  @param[in] interpolants   the interpolation types for each range
 */
InterpolationData( std::string name,
                   std::vector< long > boundaries,
                   std::vector< long > interpolants ) :
  ColumnData( std::move( name ),
              generateXSS( std::move( boundaries ),
                           std::move( interpolants ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] name     the name of the data
 *  @param[in] begin    the begin iterator of the interpolation data
 *  @param[in] end      the end iterator of the interpolation data
 */
InterpolationData( std::string name, Iterator begin, Iterator end ) :
  ColumnData( std::move( name ), begin, end, 2 ) {}

InterpolationData& operator=( const InterpolationData& ) = default;
InterpolationData& operator=( InterpolationData&& ) = default;
