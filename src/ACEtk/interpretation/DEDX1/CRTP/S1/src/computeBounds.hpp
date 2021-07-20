auto computeBounds(const SubRange& range,
		   const Projection& projection) const {
  auto it = range.begin();
  decltype(auto) front = it[0];
  decltype(auto) back = it[this->size_ - 1];
  const auto min = projection(front);
  const auto max = projection(back);
  return std::make_pair(min, max);
}

