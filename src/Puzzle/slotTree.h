#pragma once

#include "Util/finder.h"

//######### SlotTreeImpl
template<typename...>
class SlotTreeImpl;

//when there is nothing to process anymore
template<typename... KnownSlotParts, typename... KnownSlots>
class SlotTreeImpl<std::tuple<KnownSlotParts...>, std::tuple<KnownSlots...>> {
  public:
    using slotParts = std::tuple<KnownSlotParts...>;
    using slots = std::tuple<KnownSlots...>;
};

//when Slot is to be processed
template<CSlotPart... KnownSlotParts, CSlot... KnownSlots,
  CSlot CurrentSlot, typename... FurtherDefs>
class SlotTreeImpl<std::tuple<KnownSlotParts...>, std::tuple<KnownSlots...>, 
      CurrentSlot, FurtherDefs...> {
  public:
    using value = SlotTreeImpl<std::tuple<KnownSlotParts..., typename CurrentSlot::ValuePart>, 
          std::tuple<KnownSlots..., CurrentSlot>, FurtherDefs...>;
    using slots = typename value::slots;
};

template<CSlotPart... KnownSlotParts, CSlot... KnownSlots,
  CSlotPartName KeyName_, CSlotPartName ValueName, CSlotPartValueT ValueT, CSlotPartImplT ImplT,
  typename... FurtherDefs>
class SlotTreeImpl<std::tuple<KnownSlotParts...>, std::tuple<KnownSlots...>, 
  Slot<KeyName_, ValueName, ValueT, ImplT>, FurtherDefs...> {
    public:
      using KeySlotPart = typename Finder<std::tuple<KnownSlotParts...>, SlotPartHasName<KeyName_>>::type; 
      using ValueSlotPart = SlotPart<ValueName, ValueT, ImplT>;
      using value = SlotTreeImpl<std::tuple<KnownSlotParts..., ValueSlotPart>,
            std::tuple<KnownSlots..., Slot<KeySlotPart, ValueSlotPart>>, 
            FurtherDefs...>;
      using slots = typename value::slots;
};

//when SlotPart is to be processed
//TODO: we should check CurrentSlotPart's name is not present in KnownSlotParts
template<CSlotPart... KnownSlotParts, CSlot... KnownSlots,
  CSlotPart CurrentSlotPart, typename... FurtherDefs>
class SlotTreeImpl<std::tuple<KnownSlotParts...>, std::tuple<KnownSlots...>,
      CurrentSlotPart, FurtherDefs...> {
  public:
    using value = SlotTreeImpl<std::tuple<KnownSlotParts..., CurrentSlotPart>,
          std::tuple<KnownSlots...>, FurtherDefs...>;
    using slots = typename value::slots;
};

//when Grid is to be processed
template<typename... KnownSlotParts, typename... KnownSlots,
  typename Topology, typename... FurtherDefs>
class SlotTreeImpl<std::tuple<KnownSlotParts...>, std::tuple<KnownSlots...>,
      Grid<Topology>, FurtherDefs...> {
  public:
    using value = SlotTreeImpl<std::tuple<KnownSlotParts...>, std::tuple<KnownSlots...>,
          typename Topology::Root_, typename Topology::Slots_, FurtherDefs...>;
    using slots = typename value::slots;
};

//when tuple is to be processed
template<typename... KnownSlotParts, typename... KnownSlots, 
  typename... CurrentDefs, typename... FurtherDefs>
class SlotTreeImpl<std::tuple<KnownSlotParts...>, std::tuple<KnownSlots...>, 
      std::tuple<CurrentDefs...>, FurtherDefs...> {
  public:
    using value = SlotTreeImpl<std::tuple<KnownSlotParts...>, std::tuple<KnownSlots...>,
          CurrentDefs..., FurtherDefs...>;
    using slots = typename value::slots;
};

template<typename PuzzleType>
class SlotTree {
  private:
    using Tree_ = typename SlotTreeImpl<std::tuple<>, std::tuple<>, 
          typename PuzzleType::Grids_, typename PuzzleType::Slots_>::value;
  public:
    using Slots = typename Tree_::slots;
};
