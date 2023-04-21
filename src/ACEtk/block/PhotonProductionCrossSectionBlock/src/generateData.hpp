static PhotonProductionData
generateData( std::size_t, Iterator left, Iterator right ) {

  if ( *left == 13 ) {

    return PhotonProductionCrossSectionData( left, right );
  }
  else {

    return TabulatedSecondaryParticleMultiplicity( left, right );
  }
}
