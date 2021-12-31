#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "puzzle.h"
#include "../data_input_for_tests.h"

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
    
  //- vytvorit grid, ktery umi obsahovat tree data 
    GridImpl<Slots_> grid;
    using WidthInputData = SlotInputData<Width, Singleton, Count>;
    using TestDataInputT = TestDataInput<WidthInputData>;

    WidthInputData widthInputData {{ { Singleton{}, 42 } }};
    TestDataInputT testData{ widthInputData };
    grid << testData;

  //- pomoci Contents vytvorit range, odpovidajici datum v gridu
    auto contents = Contents{}( grid );

  //- overit, ze range obsahuje ocekavana data
    struct DataT {
      Singleton defaultGridId;
      Count width;
    };
    std::set<DataT> expectedData{ { Singleton{}, 42 } };
    std::set<DataT> actualData{ contents };
    ASSERT_EQ( actualData, expectedData );
  }
}//namespace
