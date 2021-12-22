#pragma once

#include "Slot/slotPartImplT.h"
#include "Slot/slotPartName.h"
#include "Slot/slotPartValueT.h"

template<typename, typename>
class PlanarHeightImpl {
  private:
    std::optional<Count> height_;
  public:
    template<typename Puzzle, typename DataPresenter>
    bool tryInput( const Puzzle& puzzle, const DataPresenter& ) {
      if ( height_.has_value() ) { return false; }

      auto size = puzzle.template get<Size>();
      height_ = std::get<1>( *size );
      return true;
    }

    const auto& get( const Singleton& ) const { return height_; }
};

class PlanarHeight : public SlotPartImplT {
  public:
    template<typename KeySlotPart, typename ValueSlotPart>
    using Impl = PlanarHeightImpl<KeySlotPart, ValueSlotPart>;
};

template<typename, typename>
class PlanarWidthImpl {
  private:
    std::optional<Count> width_;
  public:
    template<typename Puzzle, typename DataPresenter>
    bool tryInput( const Puzzle& puzzle, const DataPresenter& ) {
      if ( width_.has_value() ) { return false; }

      auto size = puzzle.template get<Size>();
      width_ = std::get<0>( *size );
      return true;
    }

    const auto& get( const Singleton& ) const { return width_; }
};

class PlanarWidth : public SlotPartImplT {
  public:
    template<typename KeySlotPart, typename ValueSlotPart>
    using Impl = PlanarWidthImpl<KeySlotPart, ValueSlotPart>;
};

template<typename KeySlotPart, typename ValueSlotPart>
class PlanarSizeImpl {
  private:
    std::optional<std::pair<Count, Count>> size_;
  public:
    template<typename Puzzle, typename DataInput>
    bool tryInput( const Puzzle&, const DataInput& dataInput ) {
      if ( size_.has_value() ) { return false; }

      const auto& slotInput = dataInput.template getSlotInput<KeySlotPart, ValueSlotPart>().value();
      size_ = std::pair<Count, Count>{ 
        slotInput.get( Singleton{} ).value(), slotInput.get( Singleton{} ).value() };
      return true;
    }

    const auto& get( const Singleton& ) const { return size_; }
};

class PlanarSize : public SlotPartImplT {
  public:
    template<typename KeySlotPart, typename ValueSlotPart>
    using Impl = PlanarSizeImpl<KeySlotPart, ValueSlotPart>;
};
