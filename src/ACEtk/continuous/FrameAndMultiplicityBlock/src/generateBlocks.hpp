void generateBlocks() {

  this->frames_.clear();
  this->multiplicities_.clear();

  for ( std::size_t index = 1; index <= this->NTR(); ++index ) {

    this->frames_.emplace_back( this->XSS( index ) < 0
                                ? ReferenceFrame::CentreOfMass
                                : ReferenceFrame::Laboratory );
    this->multiplicities_.emplace_back(
               static_cast< unsigned int >( std::abs( this->IXSS( index ) ) ) );
  }
}
