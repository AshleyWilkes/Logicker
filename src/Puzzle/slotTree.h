#pragma once

#include "Util/finder.h"
#include "Util/types_tree_impl.h"

//######### SlotTreeImpl
template<typename...>
class SlotTreeImpl;

//when there is nothing to process anymore
template<typename TypesTree, typename... KnownSlotParts, typename... KnownSlots>
class SlotTreeImpl<TypesTree, std::tuple<KnownSlotParts...>, std::tuple<KnownSlots...>> {
  public:
    //using slotParts = std::tuple<KnownSlotParts...>;
    using slots = std::tuple<KnownSlots...>;
    using slots_types_tree = TypesTree;
};

//when Slot is to be processed
template<typename TypesTree, CSlotPart... KnownSlotParts, CSlot... KnownSlots,
  CSlot CurrentSlot, typename... FurtherDefs>
class SlotTreeImpl<TypesTree, std::tuple<KnownSlotParts...>, std::tuple<KnownSlots...>, 
      CurrentSlot, FurtherDefs...> {
  public:
    using CurrentSlotPartTypesPair = 
      std::pair<typename CurrentSlot::ValuePart::Name, typename CurrentSlot::ValuePart::ValueT>;
    using value = SlotTreeImpl<
      typename TypesTree::template add<CurrentSlotPartTypesPair, typename CurrentSlot::KeyName>,
      std::tuple<KnownSlotParts..., typename CurrentSlot::ValuePart>, 
      std::tuple<KnownSlots..., CurrentSlot>, FurtherDefs...>;
    using slots = typename value::slots;
    using slots_types_tree = typename value::slots_types_tree;
};

template<typename TypesTree, CSlotPart... KnownSlotParts, CSlot... KnownSlots,
  CSlotPartName KeyName_, CSlotPartName ValueName, CSlotPartValueT ValueT, CSlotPartImplT ImplT,
  typename... FurtherDefs>
class SlotTreeImpl<TypesTree, std::tuple<KnownSlotParts...>, std::tuple<KnownSlots...>, 
  Slot<KeyName_, ValueName, ValueT, ImplT>, FurtherDefs...> {
    public:
      using KeySlotPart = typename Finder<std::tuple<KnownSlotParts...>, SlotPartHasName<KeyName_>>::type; 
      using ValueSlotPart = SlotPart<ValueName, ValueT, ImplT>;
      using CurrentSlotPartTypesPair = std::pair<ValueName, ValueT>;
      using value = SlotTreeImpl<
        typename TypesTree::template add<CurrentSlotPartTypesPair, KeyName_>,
        std::tuple<KnownSlotParts..., ValueSlotPart>,
        std::tuple<KnownSlots..., Slot<KeySlotPart, ValueSlotPart>>, 
        FurtherDefs...>;
      using slots = typename value::slots;
      using slots_types_tree = typename value::slots_types_tree;
};

//when SlotPart is to be processed
//TODO: we should check CurrentSlotPart's name is not present in KnownSlotParts
template<typename TypesTree, CSlotPart... KnownSlotParts, CSlot... KnownSlots,
  CSlotPart CurrentSlotPart, typename... FurtherDefs>
class SlotTreeImpl<TypesTree, std::tuple<KnownSlotParts...>, std::tuple<KnownSlots...>,
      CurrentSlotPart, FurtherDefs...> {
  public:
    using CurrentSlotPartTypesPair = 
      std::pair<typename CurrentSlotPart::Name, typename CurrentSlotPart::ValueT>;
    using value = SlotTreeImpl<
      typename TypesTree::template add<CurrentSlotPartTypesPair>,
      std::tuple<KnownSlotParts..., CurrentSlotPart>,
      std::tuple<KnownSlots...>, FurtherDefs...>;
    using slots = typename value::slots;
    using slots_types_tree = typename value::slots_types_tree;
};

//when Grid is to be processed
template<typename TypesTree, typename... KnownSlotParts, typename... KnownSlots,
  typename Topology, typename... FurtherDefs>
class SlotTreeImpl<TypesTree, std::tuple<KnownSlotParts...>, std::tuple<KnownSlots...>,
      Grid<Topology>, FurtherDefs...> {
  public:
    using value = SlotTreeImpl<TypesTree, std::tuple<KnownSlotParts...>, std::tuple<KnownSlots...>,
          typename Topology::Root_, typename Topology::Slots_, FurtherDefs...>;
    using slots = typename value::slots;
    using slots_types_tree = typename value::slots_types_tree;
};

//when tuple is to be processed
template<typename TypesTree, typename... KnownSlotParts, typename... KnownSlots, 
  typename... CurrentDefs, typename... FurtherDefs>
class SlotTreeImpl<TypesTree, std::tuple<KnownSlotParts...>, std::tuple<KnownSlots...>, 
      std::tuple<CurrentDefs...>, FurtherDefs...> {
  public:
    using value = SlotTreeImpl<TypesTree, std::tuple<KnownSlotParts...>, std::tuple<KnownSlots...>,
          CurrentDefs..., FurtherDefs...>;
    using slots = typename value::slots;
    using slots_types_tree = typename value::slots_types_tree;
};

template<typename PuzzleType>
class SlotTree {
  private:
    using Tree_ = typename SlotTreeImpl<types_tree::__detail::types_tree, std::tuple<>, std::tuple<>, 
          typename PuzzleType::Grids_, typename PuzzleType::Slots_>::value;
  public:
    using Slots = typename Tree_::slots;
    using SlotsTypesTree = typename Tree_::slots_types_tree;
};
