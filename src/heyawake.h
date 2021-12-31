#pragma once
#include "puzzle.h"
#include "rectangle.h"

class Heyawake {
/*template<typename Id, typename... FieldTypes>
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
};*/
  using Grids_ = Grids<
    Grid<Rectangle<DefaultGridId, Centers>>
  >;
  using Slots_ = Slots<
    Slot<CentersFieldId, AreaId, Index, Scalar>, 
    Slot<CentersFieldId, Value, BlackOrWhite, Scalar>, 
    Slot<AreaId, BlackCount, Count, Scalar>,
    Slots<AreaIds_, Values_, BlackCounts_>
  >;
  using Conditions = Conditions<
// - no 2 black fields touch vertically or horizontally
    Condition<//zacinam s komplet gridContents(), v horni urovni tedy Size, Width, Height, CentersFieldId
      Transform<
        NarrowTop<CentersFieldId>,//toto ma uriznout vse nad CenterFieldId
        NarrowDown<RowId, ColumnId, Value>,//toto ma nechat jen 
                //( DefaultGridId -> ) CentersFieldId -> [ RowId, ColumnId, Value ]
        Pairs<Neighbors<Rectangle::E, Rectangle::S>>//udela pary datatypu z predchoziho radku
      >, Assert<//zde mam na vstupu jeden pair
        CountOf<Value, Black>,//zde mam int >=0, odpovidajici poctu cernych Values
        Equal<Constant<1>>//zde mam bool, pokud je Count roven 1
      >
// potrebuju transformaci, ktera vezme getSlots<FieldId>() a vrati dvojice, kde druhy prvek sousedi
//  s prvnim prvkem povolenym zpusobem, tj. E nebo S
      //Pairs<FieldId, Neighbors<Rectangle::E, Rectangle::S>>,
      //Relation<Count<Value, White>, GT, 0>
    >/*,

// - all white (non-black) fields are interconnected (it's possible to get from a white field
//    to any other white field by moving vertically and horizontally through white fields only)
    Condition<
      Filter<FieldId, Value, White>,
      Interconnected<Rectangle::N, Rectangle::E, Rectangle::S, Rectangle::W>
    >,
// - no uninterrupted vertical or horizontal sequence of white fields may go through 3 or more rectangular areas
    Condition<
      HeyawakeTriplets<FieldId, AreaId>,
      Relation<Count<Value, Black>, GT, 0>
    >,
// - a rectangular area may be assigned a number specifying how many fields in the area must be black
// ??toto neni uspokojive dopsany, zda se, ze pro komplikovanejsi podminky potrebuju bud umet pojmenovat
//    promenne (napr. aktualni vysledek operace Filter) anebo zvolit ponekud jiny mechanismus 
//    zapisu/zpracovani podminek; pojmenovavani podminek lze napr. takto:
//    Filter<AreaId, BlackCount, IsKnown, Named<CurrentAreaId>>,
//    kde CurrentAreaId je drive vytvoreny StrongType. Tohle by melo fungovat, ale vlastne
//    je nutno uznat, ze o zpracovavani tech zapisu, co tu ted tvorim, mam jen matnou predstavu,
//    a proto ted jdu na to, jak ze Slotu vyse vytvorit fungujici nacitani a run-time reprezentaci
//    gridu (pro zacatek Solution, tj. kompletne vyplneny Grid).
    Condition<
      Filter<AreaId, BlackCount, IsKnown>,
      Condition<
        Filter<FieldId, AreaId>,
        Relation<Count<Value, Black>, EQ, SlotValue<AreaId>
      >
    >*/
  >;
};

