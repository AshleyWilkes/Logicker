#pragma once

#include <tuple>

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

template<typename PuzzleType, typename Slots = typename SlotTree<PuzzleType>::Slots>
requires( exists<typename ConstraintsSet<PuzzleType, Slots>::Constraints> )
class Puzzle : public HasSlots<typename SlotTree<PuzzleType>::Slots> {
  //??types_tree is not ready to use more than one root at the moment??
  static_assert( std::tuple_size<typename PuzzleType::Grids_>{} == 1 );

  using TheGrid = std::tuple_element_t<0, typename PuzzleType::Grids_>;

  public:
    using Slots_ = Slots;

    //ano, tady staci najit spravny Slot, kde ValueName je ValueSlotPart::Name
    //a pak se zeptat HasSlot<Slot>::get
    template<typename ValueName, typename KeyT>
    auto get( const KeyT& key ) const {
      using Slot = typename Finder<Slots_, ValueSlotPartHasName<ValueName>>::type;
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
      using Slot = typename Finder<Slots_, ValueSlotPartHasName<ValueName>>::type;
      return HasSlot<Slot>::unique_values();
    }

    template<typename ValueName>
    auto values() const {
      using Slot = typename Finder<Slots_, ValueSlotPartHasName<ValueName>>::type;
      return HasSlot<Slot>::values();
    }

    using Constraints_ = typename ConstraintsSet<PuzzleType, Slots_>::Constraints;
};

template<typename...>
class SlotReader;

//SlotReader for when there are no more slots in the Puzzle; the DataPresenter has nothing more to use
template<typename Puzzle, typename DataPresenter>
class SlotReader<Puzzle, DataPresenter, std::tuple<>> {
  public:
    static bool tryReadSlots( Puzzle&, const DataPresenter& ) {
      return false;
    }
};

template<typename Puzzle, typename DataPresenter, typename CurrentSlot, typename... FurtherSlots>
class SlotReader<Puzzle, DataPresenter, std::tuple<CurrentSlot, FurtherSlots...>> {
  public:
    static bool tryReadSlots( Puzzle& puzzle, const DataPresenter& dataPresenter ) {
      //sloty prochazim vzdy od prvniho, kazdymu reknu Zkus se nacist; zpatky dostanu true,
      //  kdyz se neco do tohoto slotu nacetlo a false kdyz ne
      if ( static_cast<HasSlot<CurrentSlot>&>(puzzle).tryInput( puzzle, dataPresenter ) ) {
        //nacitaci metoda slotu neco nacetla; chci zacit znova od 1. slotu, tj. vratim zde true
        return true;
      } else {
        //nacitaci metoda nic nenacetla, jdu na dalsi slot, tj. "rekurzivne" volam "sebe"
        return SlotReader<Puzzle, DataPresenter, std::tuple<FurtherSlots...>>
          ::tryReadSlots( puzzle, dataPresenter );
      }
    }
};

template<typename PuzzleType, typename DataPresenter>
Puzzle<PuzzleType>& operator<<( Puzzle<PuzzleType>& puzzle, const DataPresenter& dataPresenter ) {
  using Puzzle = Puzzle<PuzzleType>;
  using Slots = typename Puzzle::Slots_;
  while ( SlotReader<Puzzle, DataPresenter, Slots>::tryReadSlots( puzzle, dataPresenter ) ) {}
  return puzzle;
}
