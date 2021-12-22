#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <tuple>

#include "input.h"
#include "puzzle.h"

namespace {
  template<typename Id>
  struct Topology {
    public:
      using Root_ = SlotPart<Id>;
      using ValueSlot = Slot<Root_, Value, Count>;
      using Slots_ = Slots<ValueSlot>;
  };

  struct TheSimplestOfAllPuzzlesT {
    using Grids_ = Grids<Grid<Topology<DefaultGridId>>>;
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

  TEST( puzzle, TheSimplestOfAllPuzzlesT ) {
    Puzzle<TheSimplestOfAllPuzzlesT> puzzle;
    TestDataInput dataInput;
    EXPECT_CALL( dataInput.getSlotInputImpl().value(), get( Singleton{} ) )
      .WillOnce( testing::Return( 42 ));
    puzzle << dataInput;
    ASSERT_EQ( puzzle.get<Value>().value(), Count( 42 ) );
  }
}//namespace
