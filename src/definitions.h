#pragma once

#include "Slot/slot.h"
#include "Topology/grid.h"
#include "Transformation/AllOf.h"
#include "Util/finder.h"

template<typename...>
class NarrowImpl;

//zde je tedy treba udelat tu skutecnou praci, v tomto pripade tj.
//overit, ze WantedSlots je podmnozina InputSlots
//vratit WantedSlots
template<typename... AlreadyFoundSlots, typename... InputSlots, 
  typename CurrentWantedSlotName, typename... FurtherWantedSlotNames>
class NarrowImpl<std::tuple<AlreadyFoundSlots...>, std::tuple<InputSlots...>, 
      std::tuple<CurrentWantedSlotName, FurtherWantedSlotNames...>> {
  public:
    using CurrentFoundSlot = 
      typename Finder<std::tuple<InputSlots...>, ValueSlotPartHasName<CurrentWantedSlotName>>::type;
    using OutputT = typename NarrowImpl<std::tuple<AlreadyFoundSlots..., CurrentFoundSlot>,
          std::tuple<InputSlots...>, std::tuple<FurtherWantedSlotNames...>>::OutputT;
};

template<typename... AlreadyFoundSlots, typename... InputSlots>
class NarrowImpl<std::tuple<AlreadyFoundSlots...>, std::tuple<InputSlots...>, std::tuple<>> {
  public:
    using OutputT = std::tuple<AlreadyFoundSlots...>;
};

template<typename... WantedSlotNames>
class Narrow {
  public:
    template<typename InputSlots>
    using Impl = NarrowImpl<std::tuple<>, InputSlots, std::tuple<WantedSlotNames...>>;

    template<typename InputSlots>
    using OutputT = typename Impl<InputSlots>::OutputT;
};

template<typename...>
class Transform;

//tady to zacina bejt husty, cili: CountOf<Name, Value> je pocet polozek v inputu,
//jejichz Slot Name obsahuje hodnotu Value
//pokud dany Slot obsahuje literal hodnoty, pak Value je Constant prislusneho typu
template<typename SlotName, typename ValueToCount>
struct CountOf {
  template<typename InputT>
  auto operator()( const InputT& input ) {
    Count value = input.template get<SlotName>();
    return ( value == ValueToCount::value ? 1 : 0 );
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
