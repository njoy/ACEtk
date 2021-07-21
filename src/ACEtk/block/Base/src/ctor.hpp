Base() = default;

Base( const Base& ) = default;
Base( Base&& ) = default;

Base( std::string&& name, const Iterator& begin, const Iterator& end ) :
  name_( std::move( name ) ), xss_( std::nullopt ),
  begin_( begin ), end_( end ),
  length_( std::distance( begin, end ) ) {}

Base( std::string&& name, std::vector< double >&& xss ) :
  name_( std::move( name ) ), xss_( std::move( xss ) ) {

  this->begin_ = this->xss_->begin();
  this->end_ = this->xss_->end();
  this->length_ = this->xss_->size();
}

Base& operator=( const Base& ) = default;
Base& operator=( Base&& ) = default;
