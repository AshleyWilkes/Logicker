#pragma once

template<typename KeySlotPart, typename ValueSlotPart>
class RectangleCenterFieldsImpl {
  //chtelo by to asi assert, ze jde o mapu Singleton->Set<Index>
  private:
    std::vector<std::optional<Index>> vector_;
    std::set<Index> unique_values_;
  public:
    template<typename Puzzle, typename DataPresenter>
    bool tryInput( const Puzzle& puzzle, const DataPresenter& ) {
      if ( ! vector_.empty() ) { return false; }

      auto width = puzzle.template get<Width>();
      auto height = puzzle.template get<Height>();
      if ( width.has_value() && height.has_value() ) {
        for ( int i = 1; i <= *width * *height; ++i ) {
          vector_.push_back( Index{ i } );
          unique_values_.insert( Index{ i } );
        }
        return true;
      }
      return false;
    }

    const std::optional<std::vector<std::optional<Index>>>
    get( const Singleton& ) const {
      return vector_;
    }

    const auto&
    values() const {
      return vector_;
    }

    const auto&
    unique_values() const {
      return unique_values_;
    }
};

class RectangleCenterFields : public SlotPartImplT {
  public:
    template<typename KeySlotPart, typename ValueSlotPart>
    using Impl = RectangleCenterFieldsImpl<KeySlotPart, ValueSlotPart>;
};

template<typename, typename>
class RectangleRowIdImpl {
  private:
    std::map<Index, std::optional<Index>> map_;
  public:
    template<typename Puzzle, typename DataPresenter>
    bool tryInput( const Puzzle& puzzle, const DataPresenter& ) {
      if ( ! map_.empty() ) { return false; }

      auto fieldIds = puzzle.template values<CentersFieldId>();
      if ( fieldIds.empty() ) { return false; }

      auto width = puzzle.template get<Width>();

      for ( std::optional<Index> fieldId : fieldIds ) {
        map_.insert({ *fieldId, std::optional<Index>{ (*fieldId - 1)/ *width + 1 } });
      }
      return true;
    }

    const std::optional<Index>& 
    get( const Index& key ) const { return map_.at(key); }
};

class RectangleRowId : public SlotPartImplT {
  public:
    template<typename KeySlotPart, typename ValueSlotPart>
    using Impl = RectangleRowIdImpl<KeySlotPart, ValueSlotPart>;
};

template<typename, typename>
class RectangleColumnIdImpl {
  private:
    std::map<Index, std::optional<Index>> map_;
  public:
    template<typename Puzzle, typename DataPresenter>
    bool tryInput( const Puzzle& puzzle, const DataPresenter& ) {
      if ( ! map_.empty() ) { return false; }

      auto fieldIds = puzzle.template values<CentersFieldId>();
      if ( fieldIds.empty() ) { return false; }

      auto width = puzzle.template get<Width>();

      for ( std::optional<Index> fieldId : fieldIds ) {
        map_.insert({ *fieldId, std::optional<Index>{ (*fieldId - 1)% *width + 1 } });
      }
      return true;
    }

    const std::optional<Index>&
    get( const Index& key ) const { return map_.at(key); }
};

class RectangleColumnId : public SlotPartImplT {
  public:
    template<typename KeySlotPart, typename ValueSlotPart>
    using Impl = RectangleColumnIdImpl<KeySlotPart, ValueSlotPart>;
};
