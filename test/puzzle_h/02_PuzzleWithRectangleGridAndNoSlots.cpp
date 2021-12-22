#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <tuple>

#include "input.h"
#include "puzzle.h"
#include "Topology/Rectangle/rectangle.h"

namespace {
  struct PuzzleWithRectangleGrid {
    using Grids_ = Grids<Grid<Rectangle<DefaultGridId, Centers>>>;
    using Slots_ = Slots<>;
    using Constraints_ = Constraints<>;
  };

  class MockSlotInput : public Logicker::core::SlotInput<Singleton, Count> {
    public:
      MOCK_METHOD( std::optional<Count>, get, ( const Singleton& ), ( const override ) );
  };

  class TestDataInput {
    private:
      std::optional<MockSlotInput> slotInput{ std::in_place };
    public:
      const std::optional<MockSlotInput>& getSlotInputImpl() const { return slotInput; }

      template<typename KeySlotPart, typename ValueSlotPart>
      const std::optional<MockSlotInput>& getSlotInput() const { return getSlotInputImpl(); }
  };

  TEST( puzzle, PuzzleWithRectangleGridAndNoSlots ) {
    Puzzle<PuzzleWithRectangleGrid> puzzle;
    TestDataInput dataInput;
    EXPECT_CALL( dataInput.getSlotInputImpl().value(), get( Singleton{} ) )
      .WillOnce( testing::Return( 3 ))
      .WillOnce( testing::Return( 5 ));
    puzzle << dataInput;

    auto range = puzzle.unique_values<CentersFieldId>();
    ASSERT_EQ( range.size(), 15 );
    int curId = 1;
    for ( Index fieldId : range ) {
      ASSERT_EQ( fieldId, Index{ curId } );
      int rowId = puzzle.get<RowId>( fieldId ).value();
      int columnId = puzzle.get<ColumnId>( fieldId ).value();
      ASSERT_GE( rowId, 1 );
      ASSERT_LE( rowId, 5 );
      ASSERT_GE( columnId, 1 );
      ASSERT_LE( columnId, 3 );
      ASSERT_EQ( (rowId - 1) * 3 + columnId, curId );
      
      curId++;
    }
  }
}//namespace
