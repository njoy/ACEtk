void generateBlocks() {

  this->data_ = base::TabulatedData( this->name(), this->begin() + 1, this->end() );
}
