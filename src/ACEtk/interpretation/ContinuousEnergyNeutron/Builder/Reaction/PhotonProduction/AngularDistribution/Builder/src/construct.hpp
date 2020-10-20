AngularDistribution construct(){
  return AngularDistribution{
    std::move( energyGrid_.value() ),
    std::move( cosineBins_ )
  };
}

