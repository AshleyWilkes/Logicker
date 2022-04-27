#pragma once
#include "Slot/slot.h"
#include "Slot/SlotPartImplT/planar.h"
#include "Slot/SlotPartImplT/scalar.h"
#include "Topology/Rectangle/slotPartImplT.h"

class Centers;

class E{
  public:
    template<typename Pair>
    static bool apply( const Pair& pair ) {
      auto values = pair.getValue();
      auto val1 = std::get<0>( values ), val2 = std::get<1>( values );

      Index row1 = val1.template get<RowId>(), col1 = val1.template get<ColumnId>(),
            row2 = val2.template get<RowId>(), col2 = val2.template get<ColumnId>();
      return row1 == row2 && col1 + 1 == col2;
    }
}; 
class W{
  public:
    template<typename Pair>
    static bool apply( const Pair& pair ) {
      auto values = pair.getValue();
      auto val1 = std::get<0>( values ), val2 = std::get<1>( values );

      Index row1 = val1.template get<RowId>(), col1 = val1.template get<ColumnId>(),
            row2 = val2.template get<RowId>(), col2 = val2.template get<ColumnId>();
      return row1 == row2 && col1 == col2 + 1;
    }
}; 
class N{
  public:
    template<typename Pair>
    static bool apply( const Pair& pair ) {
      auto values = pair.getValue();
      auto val1 = std::get<0>( values ), val2 = std::get<1>( values );

      Index row1 = val1.template get<RowId>(), col1 = val1.template get<ColumnId>(),
            row2 = val2.template get<RowId>(), col2 = val2.template get<ColumnId>();
      return row1 == row2 + 1 && col1 == col2;
    }
};
class S{
  public:
    template<typename Pair>
    static bool apply( const Pair& pair ) {
      auto values = pair.getValue();
      auto val1 = std::get<0>( values ), val2 = std::get<1>( values );

      Index row1 = val1.template get<RowId>(), col1 = val1.template get<ColumnId>(),
            row2 = val2.template get<RowId>(), col2 = val2.template get<ColumnId>();
      return row1 + 1== row2 && col1 == col2;
    }
};

template<typename Id, typename... FieldTypes>
struct Rectangle : public HasFields<FieldTypes, SlotPart<Id>>... {
  public:
    using Root_ = SlotPart<Id>;
    using Size_ = Slot<Root_, Size, CountPair, PlanarSize>;
    using Width_ = Slot<Root_, Width, Count, PlanarWidth>;
    using Height_ = Slot<Root_, Height, Count, PlanarHeight>;
    using Slots_ = Slots<Size_, Width_, Height_, 
          typename HasFields<FieldTypes, SlotPart<Id>>::Slots_...>;
};

template<typename RootSlotPart>
class HasFields<Centers, RootSlotPart> {
  public:
    using FieldId = CentersFieldId;
    using FieldIds_ = Slot<RootSlotPart, CentersFieldId, Index, RectangleCenterFields>;
    using RowId_ = Slot<CentersFieldId, RowId, Index, RectangleRowId>;
    using ColumnId_ = Slot<CentersFieldId, ColumnId, Index, RectangleColumnId>;
    using Slots_ = Slots<FieldIds_, RowId_, ColumnId_>;
};
