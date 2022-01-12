#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "puzzle.h"
#include "../data_input_for_tests.h"
#include "Transformation/Contents.h"

namespace {
  //postup:
  //- vytvorit tree jako typ podle predpokladu testu
  //- vytvorit grid, ktery umi obsahovat tree data 
  //- pomoci Contents vytvorit range, odpovidajici datum v gridu
  //- overit, ze range obsahuje ocekavana data
  //
  //1. test
  //  tree ma 1 slot, cili tree data jsou struct s 1 memberem
  //  grid obsahuje 1 hodnotu
  TEST( Contents, TheSimplestContents ) {
  //- vytvorit tree jako typ podle predpokladu testu
    using Root_ = SlotPart<DefaultGridId>;
    using Width_ = Slot<Root_, Width, Count, Scalar>;
    using Slots_ = Slots<Width_>;
    using SlotsWithParts_ = Slots<Root_, Width_>;
    using SlotsTypesTree = typename SlotTreeImpl<types_tree::__detail::types_tree, std::tuple<>, 
          std::tuple<>, SlotsWithParts_>::value::slots_types_tree;

  //- vytvorit grid, ktery umi obsahovat tree data 
    using GridI = GridImpl<Slots_>;
    GridI grid;
    using WidthInputData = SlotInputData<Width, Singleton, Count>;
    using TestDataInputT = TestDataInput<WidthInputData>;

    WidthInputData widthInputData {{ { Singleton{}, 42 } }};
    TestDataInputT testData{ widthInputData };
    grid << testData;

  //- pomoci Contents vytvorit range, odpovidajici datum v gridu
    using ContentsV = ContentsView<GridImpl<Slots_>, SlotsTypesTree>;
    ContentsV gridView{ &grid };
    auto contents = Contents{}( gridView );
    ASSERT_EQ( contents.begin() != contents.end(), true );

  //- overit, ze range obsahuje ocekavana data
    using DataT = typename Contents::DataT<ContentsV>;
    std::set<DataT> expectedData{ std::make_tuple<>( types_tree::__detail::root_value{}, Singleton{}, Count{ 42 } ) };
    std::set<DataT> actualData{ contents.begin(), contents.end() };
    ASSERT_EQ( actualData, expectedData );
  }
}//namespace
