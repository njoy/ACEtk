ColumnData() = default;

ColumnData( const ColumnData& ) = default;
ColumnData( ColumnData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] name           the name of the data
 *  @param[in] columns        the columns
 */
ColumnData( std::string name, std::vector< std::vector< double > > columns ) :
  Base( std::move( name ), generateXSS( std::move( columns ) ) ),
  nc_( columns.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] name           the name of the data
 *  @param[in] column1        the first column
 *  @param[in] column2        the second column
 */
ColumnData( std::string name, std::vector< double > column1,
            std::vector< double > column2 ) :
  Base( std::move( name ),
        generateXSS( std::move( column1 ), std::move( column2 ) ) ),
  nc_( 2 ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] name           the name of the data
 *  @param[in] column1        the first column
 *  @param[in] column2        the second column
 *  @param[in] column3        the third column
 */
ColumnData( std::string name, std::vector< double > column1,
            std::vector< double > column2, std::vector< double > column3 ) :
  Base( std::move( name ),
        generateXSS( std::move( column1 ), std::move( column2 ),
                     std::move( column3 ) ) ),
  nc_( 3 ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] name     the name for this data piece
 *  @param[in] begin    the begin iterator of the SIG block in the XSS array
 *  @param[in] end      the end iterator of the SIG block in the XSS array
 *  @param[in] nc       the number of columns
 */
ColumnData( std::string name, Iterator begin, Iterator end, std::size_t nc ) :
  Base( std::move( name ), begin, end ), nc_( nc ) {

  verifySize( this->begin(), this->end(),
              this->begin() == this->end() ? 0 : *( this->begin() ), nc );
}

ColumnData& operator=( const ColumnData& ) = default;
ColumnData& operator=( ColumnData&& ) = default;
