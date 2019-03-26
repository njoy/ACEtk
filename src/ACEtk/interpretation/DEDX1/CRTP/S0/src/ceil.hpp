template<typename T>
auto ceil(T value) const {
  auto range = static_cast<const Range&>( *this );
  auto identity = [](auto&& it){ return std::forward<decltype(it)>(it); };
  return this->lowerBound(range, value, identity);
}
