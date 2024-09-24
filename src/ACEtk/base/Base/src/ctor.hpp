Base() = default;

Base( const Base& base ) :
    name_( base.name_ ), xss_( base.xss_ ) {

  this->generateData( base );
}

Base( Base&& base ) :
    name_( std::move( base.name_ ) ), xss_( std::move( base.xss_ ) ) {

  this->generateData( base );
}

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

Base& operator=( const Base& base ) {

  if ( this != &base ) {

    this->name_ = base.name_;
    this->xss_ = base.xss_;
    this->generateData( base );
  }
  return *this;
}

Base& operator=( Base&& base ) {

  if ( this != &base ) {

    this->name_ = std::move( base.name_ );
    this->xss_ = std::move( base.xss_ );
    this->generateData( base );
  }
  return *this;
}
