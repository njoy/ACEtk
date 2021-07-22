/**
 *  @class
 *  @brief Convenience interface for cross section data from the SIG block
 */
template < typename Range >
class CrossSectionData {

  /* fields */
  Range chunk;

public:

  /* constructor */
  CrossSectionData( Range&& chunk ) : chunk( std::move( chunk ) ) {}

  /**
   *  @brief Return the energy index
   */
  std::size_t energyIndex() const { return this->chunk[0]; }

  /**
   *  @brief Return the number of cross section values
   */
  std::size_t numberValues() const { return this->chunk[1]; }

  /**
   *  @brief Return the cross section values
   */
  auto crossSections() const {

    return this->chunk | ranges::views::drop_exactly( 2 );
  }
};
