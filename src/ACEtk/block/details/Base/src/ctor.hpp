Base() = default;

Base( const Base& base ) {

  *this = base;
}

Base( Base&& base ) {

  *this = std::move( base );
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

Base& operator=( const Base& right ) {

  this->name_ = right.name_;
  this->xss_ = right.xss_;
  if ( this->xss_ ) {

    this->begin_ = this->xss_->begin();
    this->end_ = this->xss_->end();
    this->length_ = this->xss_->size();
  }
  else {

    this->begin_ = right.begin_;
    this->end_ = right.end_;
    this->length_ = right.length_;
  }
  return *this;
}

Base& operator=( Base&& right ) {

  this->name_ = std::move( right.name_ );
  this->xss_ = std::move( right.xss_ );
  if ( this->xss_ ) {

    this->begin_ = this->xss_->begin();
    this->end_ = this->xss_->end();
    this->length_ = this->xss_->size();
  }
  else {

    this->begin_ = right.begin_;
    this->end_ = right.end_;
    this->length_ = right.length_;
  }
  return *this;
}
