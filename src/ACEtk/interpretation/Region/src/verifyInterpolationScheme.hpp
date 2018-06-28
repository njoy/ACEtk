int verifyInterpolationScheme( int INT ){
  if( not ( ( ( INT >  0 ) and ( INT <  7 ) ) or
            ( ( INT > 10 ) and ( INT < 16 ) ) or
            ( ( INT > 20 ) and ( INT < 26 ) ) )
    ){
      njoy::Log::error( "Invalid interpolation scheme: {}", INT );
      throw std::exception();
    }
  return INT;
}
