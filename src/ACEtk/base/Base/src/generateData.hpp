void generateData( const Base& base ) {

  if ( this->owner() ) {

    this->begin_ = this->xss_->begin();
    this->end_ = this->xss_->end();
    this->length_ = this->xss_->size();
  }
  else {

    this->begin_ = base.begin_;
    this->end_ = base.end_;
    this->length_ = base.length_;
  }
}
