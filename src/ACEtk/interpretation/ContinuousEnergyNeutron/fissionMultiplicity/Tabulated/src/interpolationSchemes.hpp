  auto interpolationSchemes() const{ 
    static const std::vector< double > defaultSchemes = {1};
    
    return this->INT.value_or( Table::slice( defaultSchemes ) );
  }

