#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "puzzle.h"
#include "../data_input_for_tests.h"
#include "Topology/Rectangle/rectangle.h"
#include "Transformation/Contents.h"

namespace {
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
    auto contents = Contents<SlotsTypesTree>( std::ranges::single_view{ grid } );
    ASSERT_EQ( contents.begin() != contents.end(), true );
    using DataSet = std::set<typename decltype( contents.begin() )::value_type>;
    DataSet actualData;
    std::ranges::copy( contents, std::inserter( actualData, actualData.begin() ));

  //- overit, ze range obsahuje ocekavana data
    DataSet expectedData{ 
      std::make_tuple<>( types_tree::__detail::root_value{}, Singleton{}, Count{ 42 } ) 
    };
    ASSERT_EQ( actualData, expectedData );
  }

  TEST( Contents, SimpleContents1x1 ) {
  //- vytvorit tree jako typ podle predpokladu testu
    struct TestGrid {
      using Grid_ = Grid<Rectangle<DefaultGridId, Centers>>;
      using Grids_ = Grids<Grid_>;
      using Values_ = Slot<CentersFieldId, Value, Count, Scalar>;
      using Slots_ = Slots<Values_>;
      using Constraints_ = Constraints<>;
    };
  //- vytvorit grid, ktery umi obsahovat tree data 
    using Puzzle_ = Puzzle<TestGrid>;
    Puzzle_ puzzle;
    using SizeInputData = SlotInputData<Size, Singleton, Count>;
    using ValueInputData = SlotInputData<Value, Count>;
    using TestDataInputT = TestDataInput<SizeInputData, ValueInputData>;

    SizeInputData sizeInputData {{
      { Singleton{}, 1 },
      { Singleton{}, 1 }
    }};
    ValueInputData valueInputData {{ 42 }};
    TestDataInputT testInput{ sizeInputData, valueInputData };
    puzzle << testInput;
  //- pomoci Contents vytvorit range, odpovidajici datum v gridu
    auto contents = Contents<typename Puzzle_::SlotsTypesTree_>( 
        std::ranges::single_view{ puzzle.getGrid() } );
    
  //- overit, ze range obsahuje ocekavana data
    using DataSet = std::set<typename decltype( contents.begin() )::value_type>;
    DataSet actualData;
    std::ranges::copy( contents, std::inserter( actualData, actualData.begin() ));
    DataSet expectedData {
      std::make_tuple<>( types_tree::__detail::root_value{}, Singleton{}, 
          CountPair( std::make_pair<Count, Count>( Count{ 1 }, Count { 1 } ) ), Count{ 1 }, 
          Count{ 1 }, Index{ 1 }, Index{ 1 }, Index{ 1 }, Count{ 42 } )
    };
    ASSERT_EQ( actualData, expectedData );
  }

  TEST( Contents, SimpleContents2x2 ) {
  //- vytvorit tree jako typ podle predpokladu testu
    struct TestGrid {
      using Grid_ = Grid<Rectangle<DefaultGridId, Centers>>;
      using Grids_ = Grids<Grid_>;
      using Values_ = Slot<CentersFieldId, Value, Count, Scalar>;
      using Slots_ = Slots<Values_>;
      using Constraints_ = Constraints<>;
    };
  //- vytvorit grid, ktery umi obsahovat tree data 
    using Puzzle_ = Puzzle<TestGrid>;
    Puzzle_ puzzle;
    using SizeInputData = SlotInputData<Size, Singleton, Count>;
    using ValueInputData = SlotInputData<Value, Count>;
    using TestDataInputT = TestDataInput<SizeInputData, ValueInputData>;

    SizeInputData sizeInputData {{
      { Singleton{}, 2 },
      { Singleton{}, 2 }
    }};
    ValueInputData valueInputData {{
      23, 42, 
       1, 988
    }};
    TestDataInputT testInput{ sizeInputData, valueInputData };
    puzzle << testInput;
  //- pomoci Contents vytvorit range, odpovidajici datum v gridu
    auto contents = Contents<typename Puzzle_::SlotsTypesTree_>( 
        std::ranges::single_view{ puzzle.getGrid() } );
    
  //- overit, ze range obsahuje ocekavana data
    using DataSet = std::set<typename decltype( contents.begin() )::value_type>;
    DataSet actualData;
    std::ranges::copy( contents, std::inserter( actualData, actualData.begin() ));
    DataSet expectedData {
      std::make_tuple<>( types_tree::__detail::root_value{}, Singleton{}, 
          CountPair( std::make_pair<Count, Count>( Count{ 2 }, Count { 2 } ) ), Count{ 2 }, 
          Count{ 2 }, Index{ 1 }, Index{ 1 }, Index{ 1 }, Count{ 23 } ),
      std::make_tuple<>( types_tree::__detail::root_value{}, Singleton{}, 
          CountPair( std::make_pair<Count, Count>( Count{ 2 }, Count { 2 } ) ), Count{ 2 }, 
          Count{ 2 }, Index{ 2 }, Index{ 1 }, Index{ 2 }, Count{ 42 } ),
      std::make_tuple<>( types_tree::__detail::root_value{}, Singleton{}, 
          CountPair( std::make_pair<Count, Count>( Count{ 2 }, Count { 2 } ) ), Count{ 2 }, 
          Count{ 2 }, Index{ 3 }, Index{ 2 }, Index{ 1 }, Count{ 1 } ),
      std::make_tuple<>( types_tree::__detail::root_value{}, Singleton{}, 
          CountPair( std::make_pair<Count, Count>( Count{ 2 }, Count { 2 } ) ), Count{ 2 }, 
          Count{ 2 }, Index{ 4 }, Index{ 2 }, Index{ 2 }, Count{ 988 } )
    };
    ASSERT_EQ( actualData, expectedData );
  }
}//namespace
