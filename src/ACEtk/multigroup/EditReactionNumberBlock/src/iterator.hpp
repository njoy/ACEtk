auto iterator( unsigned int mt ) const {
    
    return std::find_if( 
                        this->begin(), 
                        this->end(), 
                        [mt] ( auto&& value ) {

                            return static_cast< unsigned int >( std::round( value ) )
                               == mt;
                        }
                    );
}