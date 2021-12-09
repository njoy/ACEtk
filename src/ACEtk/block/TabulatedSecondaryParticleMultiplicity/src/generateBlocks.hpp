void generateBlocks() {

  this->data_ = block::details::BaseTabulatedData(
                    this->name(),
                    this->begin() + 2, this->end() );
}
