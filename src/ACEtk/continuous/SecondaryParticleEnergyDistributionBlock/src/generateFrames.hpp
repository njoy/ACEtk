void generateFrames() {

  if ( this->TYRH().has_value() ) {

    this->frames_.insert( this->frames_.end(),
                          this->TYRH()->referenceFrames().begin(),
                          this->TYRH()->referenceFrames().begin() + this->NR() );
  }
  else {

    this->frames_ = { this->NR(), std::nullopt };
  }
}
