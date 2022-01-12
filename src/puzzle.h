#pragma once

#include <tuple>

#include "contents_view.h"
#include "definitions.h"
#include "Puzzle/constraintsSet.h"
#include "Puzzle/slotTree.h"

template<typename Slot>
class HasSlot;

template<CSlot Slot>
class HasSlot<Slot> : public
  Slot::ValuePart::SlotImplT::template Impl<typename Slot::KeyPart, typename Slot::ValuePart> {};

template<typename... Ts>
class HasSlots;

template<typename... Ts>
class HasSlots<std::tuple<Ts...>> : public HasSlot<Ts>... {};

template<>
class HasSlots<std::tuple<>> {};

template<typename Slots_>
class GridImpl : public HasSlots<Slots_> {//je to Impl, protoze Grid uz je pouzit jinde; spravne reseni jsou namespacy
  public:
    using Slots = Slots_;

    //ano, tady staci najit spravny Slot, kde ValueName je ValueSlotPart::Name
    //a pak se zeptat HasSlot<Slot>::get
    template<typename ValueName, typename KeyT>
    auto get( const KeyT& key ) const {
      using Slot = typename Finder<Slots, ValueSlotPartHasName<ValueName>>::type;
      return HasSlot<Slot>::get( key );
    }

    template<typename ValueName>
    auto get() const {
      return get<ValueName>( Singleton{} );
    }

    //najde SlotPart, jehoz Name je Value
    //pak najde Slot, jehoz je ten SlotPart ValuePart
    //a vrati range-of-values toho Slotu
    template<typename ValueName>
    auto unique_values() const {
      using Slot = typename Finder<Slots, ValueSlotPartHasName<ValueName>>::type;
      return HasSlot<Slot>::unique_values();
    }

    template<typename ValueName>
    auto values() const {
      using Slot = typename Finder<Slots, ValueSlotPartHasName<ValueName>>::type;
      return HasSlot<Slot>::values();
    }

};

template<typename PuzzleType, typename Slots, typename SlotsTypesTree>
#ifndef DEBUG_Puzzle_h
requires( exists<typename ConstraintsSet<PuzzleType, 
    ContentsView<GridImpl<typename SlotTree<PuzzleType>::Slots>, SlotsTypesTree>>::Constraints> )
#endif
class PuzzleImpl {
  static_assert( std::is_same_v<Slots, typename SlotTree<PuzzleType>::Slots> );
  //??types_tree is not ready to use more than one root at the moment??
  static_assert( std::tuple_size<typename PuzzleType::Grids_>{} == 1 );

  GridImpl<typename SlotTree<PuzzleType>::Slots> grid;

  public:
    using Slots_ = Slots;

    using GridI = GridImpl<typename SlotTree<PuzzleType>::Slots>;

    GridI& getGrid () { return grid; }

    template<typename ValueName, typename KeyT>
    auto get( const KeyT& key ) const {
      return grid.template get<ValueName, KeyT>( key );
    }

    template<typename ValueName>
    auto get() const {
      return grid.template get<ValueName>();
    }

    template<typename ValueName>
    auto unique_values() const {
      return grid.template unique_values<ValueName>();
    }

    template<typename ValueName>
    auto values() const {
      return grid.template values<ValueName>();
    }

    using Constraints_ = typename ConstraintsSet<PuzzleType, 
          ContentsView<GridI, SlotsTypesTree>>::Constraints;

    ContentsView<GridI, SlotsTypesTree> getContents() const {
      return { &grid };
    }
};

template<typename...>
struct PuzzleT;

template<typename PuzzleType>
#ifndef DEBUG_Puzzle_h
requires( exists<PuzzleImpl<PuzzleType, typename SlotTree<PuzzleType>::Slots, 
    typename SlotTree<PuzzleType>::SlotsTypesTree > > )
#endif
struct PuzzleT<PuzzleType> {
  using type = PuzzleImpl<PuzzleType, typename SlotTree<PuzzleType>::Slots,
    typename SlotTree<PuzzleType>::SlotsTypesTree >;
};

template<typename PuzzleType, typename Slots, typename SlotsTypesTree>
#ifndef DEBUG_Puzzle_h
requires( exists<PuzzleImpl<PuzzleType, Slots, SlotsTypesTree>> )
#endif
struct PuzzleT<PuzzleType, Slots, SlotsTypesTree> {
  using type = PuzzleImpl<PuzzleType, Slots, SlotsTypesTree>;
};

template<typename... Ts>
using Puzzle = typename PuzzleT<Ts...>::type;

template<typename...>
class SlotReader;

//SlotReader for when there are no more slots in the Puzzle; the DataPresenter has nothing more to use
template<typename Grid, typename DataPresenter>
class SlotReader<Grid, DataPresenter, std::tuple<>> {
  public:
    static bool tryReadSlots( Grid&, const DataPresenter& ) {
      return false;
    }
};

template<typename Grid, typename DataPresenter, typename CurrentSlot, typename... FurtherSlots>
class SlotReader<Grid, DataPresenter, std::tuple<CurrentSlot, FurtherSlots...>> {
  public:
    static bool tryReadSlots( Grid& grid, const DataPresenter& dataPresenter ) {
      //sloty prochazim vzdy od prvniho, kazdymu reknu Zkus se nacist; zpatky dostanu true,
      //  kdyz se neco do tohoto slotu nacetlo a false kdyz ne
      if ( static_cast<HasSlot<CurrentSlot>&>( grid ).tryInput( grid, dataPresenter ) ) {
        //nacitaci metoda slotu neco nacetla; chci zacit znova od 1. slotu, tj. vratim zde true
        return true;
      } else {
        //nacitaci metoda nic nenacetla, jdu na dalsi slot, tj. "rekurzivne" volam "sebe"
        return SlotReader<Grid, DataPresenter, std::tuple<FurtherSlots...>>
          ::tryReadSlots( grid, dataPresenter );
      }
    }
};

template<typename Slots, typename DataPresenter>
GridImpl<Slots>& operator<<( GridImpl<Slots>& grid, const DataPresenter& dataPresenter ) {
  while ( SlotReader<GridImpl<Slots>, DataPresenter, Slots>
      ::tryReadSlots( grid, dataPresenter ) ) {}
  return grid;
}

template<typename PuzzleType, typename Slots, typename SlotsTypesTree, typename DataPresenter>
PuzzleImpl<PuzzleType, Slots, SlotsTypesTree>& operator<<( 
    PuzzleImpl<PuzzleType, Slots, SlotsTypesTree>& puzzle, const DataPresenter& dataPresenter ) {
  using Puzzle = Puzzle<PuzzleType>;
  while ( SlotReader<typename Puzzle::GridI, DataPresenter, Slots>
      ::tryReadSlots( puzzle.getGrid(), dataPresenter ) ) {}
  return puzzle;
}
