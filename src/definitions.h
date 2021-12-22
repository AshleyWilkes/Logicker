#pragma once

#include "Slot/slot.h"
#include "Topology/grid.h"
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

template<typename>
class CountOf;

template<int>
class Constant;

class Equal;

template<typename LHS, typename OP, typename RHS>
class Assert;

template<typename Transform_, typename Assert_>
class Constraint {
  public:
    using Transform = Transform_;
    using Assert = Assert_;
};

template<typename... Ts>
using Constraints = std::tuple<Ts...>;
