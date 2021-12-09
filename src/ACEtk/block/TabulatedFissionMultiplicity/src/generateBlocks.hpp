void generateBlocks() {

  this->data_ = block::details::BaseTabulatedData(
                    this->name(), 
                    this->begin() + 1, this->end() );
}
