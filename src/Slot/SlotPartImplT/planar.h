#pragma once

#include "Slot/slotPartImplT.h"
#include "Slot/slotPartName.h"
#include "Slot/slotPartValueT.h"

template<typename, typename>
class PlanarHeightImpl {
  private:
    std::vector<std::optional<Count>> valueVector;
  public:
    template<typename Puzzle, typename DataPresenter>
    bool tryInput( const Puzzle& puzzle, const DataPresenter& ) {
      if ( !valueVector.empty() && getValue().has_value() ) { return false; }

      auto size = puzzle.template get<Size>();
      valueVector.push_back( std::get<1>( ( *size ).getValue() ) );
      return true;
    }

    std::optional<Count> getValue() const {
      if ( valueVector.empty() ) throw 1;
      return *(valueVector.begin());
    }

    auto get( const Singleton& ) const { return getValue(); }

    auto values() const {
      return std::ranges::subrange{ valueVector };
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
  public:
    template<typename Puzzle, typename DataPresenter>
    bool tryInput( const Puzzle& puzzle, const DataPresenter& ) {
      if ( !valueVector.empty() && getValue().has_value() ) { return false; }

      auto size = puzzle.template get<Size>();
      valueVector.push_back( std::get<0>( ( *size ).getValue() ) );
      return true;
    }

    std::optional<Count> getValue() const {
      if ( valueVector.empty() ) throw 1;
      return *(valueVector.begin());
    }

    auto get( const Singleton& ) const { return getValue(); }

    auto values() const {
      return std::ranges::subrange{ valueVector };
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
  public:
    template<typename Puzzle, typename DataInput>
    bool tryInput( const Puzzle&, const DataInput& dataInput ) {
      if ( !valueVector.empty() && getValue().has_value() ) { return false; }

      const auto& slotInput = dataInput.template getSlotInput<KeySlotPart, ValueSlotPart>().value();
      valueVector.push_back( CountPair{ std::make_pair<Count, Count>(
        slotInput.get( Singleton{} ).value(), slotInput.get( Singleton{} ).value() ) } );
      return true;
    }

    std::optional<CountPair> getValue() const {
      if ( valueVector.empty() ) throw 1;
      return *(valueVector.begin());
    }

    auto get( const Singleton& ) const { return getValue(); }

    auto values() const {
      return std::ranges::subrange{ valueVector };
    }
};

class PlanarSize : public SlotPartImplT {
  public:
    template<typename KeySlotPart, typename ValueSlotPart>
    using Impl = PlanarSizeImpl<KeySlotPart, ValueSlotPart>;
};
