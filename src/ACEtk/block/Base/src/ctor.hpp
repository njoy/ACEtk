Base() = default;

Base( const Base& ) = default;
Base( Base&& ) = default;

Base( const std::vector< double >::iterator& begin,
      const std::vector< double >::iterator& end ) :
  xss_( std::nullopt ), begin_( begin ), end_( end ) {}

Base( std::vector< double >&& xss ) :
  xss_( std::move( xss ) ) {

  this->begin_ = this->xss_->begin();
  this->end_ = this->xss_->end();
}

Base& operator=( const Base& ) = default;
Base& operator=( Base&& ) = default;
