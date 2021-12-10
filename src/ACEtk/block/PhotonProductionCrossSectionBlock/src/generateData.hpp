static PhotonProductionData generateData( Iterator left, Iterator right ) {

  if ( *left == 13 ) {

    return PhotonProductionCrossSectionData( left, right );
  }
  else {

    return TabulatedSecondaryParticleMultiplicity( left, right );
  }
}
