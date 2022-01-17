#pragma once

#include "Slot/slotPartImplT.h"
#include "Slot/slotPartName.h"
#include "Slot/slotPartValueT.h"

template<typename, typename>
class PlanarHeightImpl {
  private:
    std::vector<std::optional<Count>> valueVector;
    decltype( std::ranges::subrange{ valueVector } ) range;
  public:
    template<typename Puzzle, typename DataPresenter>
    bool tryInput( const Puzzle& puzzle, const DataPresenter& ) {
      if ( !valueVector.empty() && getValue().has_value() ) { return false; }

      auto size = puzzle.template get<Size>();
      valueVector.push_back( std::get<1>( ( *size ).getValue() ) );
      range = std::ranges::subrange{ valueVector };
      return true;
    }

    std::optional<Count> getValue() const {
      if ( valueVector.empty() ) throw 1;
      return *(valueVector.begin());
    }

    auto get( const Singleton& ) const { return getValue(); }

    const auto& values() const {
      return range;
    }
};

class PlanarHeight : public SlotPartImplT {
  public:
    template<typename KeySlotPart, typename ValueSlotPart>
    using Impl = PlanarHeightImpl<KeySlotPart, ValueSlotPart>;
};

template<typename, typename>
class PlanarWidthImpl {
  private:
    std::vector<std::optional<Count>> valueVector;
    decltype( std::ranges::subrange{ valueVector } ) range;
  public:
    template<typename Puzzle, typename DataPresenter>
    bool tryInput( const Puzzle& puzzle, const DataPresenter& ) {
      if ( !valueVector.empty() && getValue().has_value() ) { return false; }

      auto size = puzzle.template get<Size>();
      valueVector.push_back( std::get<0>( ( *size ).getValue() ) );
      range = std::ranges::subrange{ valueVector };
      return true;
    }

    std::optional<Count> getValue() const {
      if ( valueVector.empty() ) throw 1;
      return *(valueVector.begin());
    }

    auto get( const Singleton& ) const { return getValue(); }

    const auto& values() const {
      return range;
    }
};

class PlanarWidth : public SlotPartImplT {
  public:
    template<typename KeySlotPart, typename ValueSlotPart>
    using Impl = PlanarWidthImpl<KeySlotPart, ValueSlotPart>;
};

template<typename KeySlotPart, typename ValueSlotPart>
class PlanarSizeImpl {
  private:
    std::vector<std::optional<CountPair>> valueVector;
    decltype( std::ranges::subrange{ valueVector } ) range;
  public:
    template<typename Puzzle, typename DataInput>
    bool tryInput( const Puzzle&, const DataInput& dataInput ) {
      if ( !valueVector.empty() && getValue().has_value() ) { return false; }

      const auto& slotInput = dataInput.template getSlotInput<KeySlotPart, ValueSlotPart>().value();
      Count value1 = slotInput.get( Singleton{} ).value();
      Count value2 = slotInput.get( Singleton{} ).value();
      valueVector.push_back( CountPair{ std::make_pair<Count, Count>( 
            std::move( value1 ), std::move( value2 ) ) } );
      range = std::ranges::subrange{ valueVector };
      return true;
    }

    std::optional<CountPair> getValue() const {
      if ( valueVector.empty() ) throw 1;
      return *(valueVector.begin());
    }

    auto get( const Singleton& ) const { return getValue(); }

    const auto& values() const {
      return range;
    }
};

class PlanarSize : public SlotPartImplT {
  public:
    template<typename KeySlotPart, typename ValueSlotPart>
    using Impl = PlanarSizeImpl<KeySlotPart, ValueSlotPart>;
};
