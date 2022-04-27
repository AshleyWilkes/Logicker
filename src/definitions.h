#pragma once

#include "Slot/slot.h"
#include "Topology/grid.h"
#include "Transformation/AllOf.h"
#include "Util/finder.h"

template<typename...>
class Transform;

//tady to zacina bejt husty, cili: CountOf<Name, Value> je pocet polozek v inputu,
//jejichz Slot Name obsahuje hodnotu Value
//pokud dany Slot obsahuje literal hodnoty, pak Value je Constant prislusneho typu
template<typename SlotName, typename ValueToCount>
struct CountOf {
  template<typename T>
  struct InputSet {
    using type = Set<T>;
  };

  template<typename T>
  struct InputSet<Pair<T>> {
    using type = Set<T>;
  };

  template<typename InputT>
  auto operator()( const InputT& input ) {
    typename InputSet<InputT>::type inputSet{ input };
    using T = typename decltype( inputSet )::value_type;
    return std::ranges::count_if( inputSet.toSet(), []( const T& inputValue ) { 
        return inputValue.template get<SlotName>() == ValueToCount::value; } );
  }

  template<typename InputT>
  using OutputT = decltype( std::declval<CountOf>()( std::declval<InputT>() ) );
};

template<int Value>
struct Constant{
  template<typename>
  using OutputT = int;

  static constexpr int value = Value;

  template<typename InputT>
  constexpr int operator()( const InputT& ) {
    return Value;
  }
};

struct LessOrEqual{
  template<typename, typename>
  using OutputT = bool;

  template<typename Lhs, typename Rhs>
  constexpr bool operator()( const Lhs& lhs, const Rhs& rhs ) { return lhs <= rhs; }
};

struct Equal{
  template<typename, typename>
  using OutputT = bool;

  template<typename Lhs, typename Rhs>
  OutputT<Lhs, Rhs> operator()( const Lhs& lhs, const Rhs& rhs ) {
    if ( lhs == rhs ) {
      return true;
    } else {
      return false;
    }
  }
};

template<typename...>
struct ConstraintTransformationsBuilder;

template<typename... Transforms, typename Assert>
struct ConstraintTransformationsBuilder<Transform<Transforms...>, Assert> {
  using type = Transform<Transforms..., Logicker::Transformation::AllOf<Assert>>;
};

template<typename Transform_, typename Assert_>
class Constraint {
  public:
    using Transform = Transform_;
    using Assert = Assert_;
    using Transformations = 
      typename ConstraintTransformationsBuilder<Transform_, Assert_>::type;
};

template<typename... Ts>
using Constraints = std::tuple<Ts...>;
