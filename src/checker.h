#pragma once

#include "Slot/slotPartValueT.h"

#include "undef.h"

namespace Checker {
  template<typename Slot>
  class SlotSanityChecker {
    public:
      template<typename Puzzle>
      static auto getSlotKeys( const Puzzle& puzzle ) {
        if constexpr( std::is_same_v<typename Slot::KeyPart::ValueT, Singleton> ) {
          return std::vector<Singleton>{ {} };
        } else {
          return puzzle.template unique_values<typename Slot::KeyPart::Name>();
        }
      }

      template<typename Puzzle>
      static bool check( const Puzzle& assignment, const Puzzle& solution ) {
        //auto assignmentKeys = assignment.template unique_values<typename Slot::KeyPart::Name>();
        //auto solutionKeys = solution.template unique_values<typename Slot::KeyPart::Name>();
        auto assignmentKeys = getSlotKeys( assignment );
        auto solutionKeys = getSlotKeys( solution );
//      jinymi slovy kazdy klic v assignmentu
        for ( auto key : assignmentKeys ) {
//        musi byt i v solution
          if ( std::ranges::find( solutionKeys, key ) == solutionKeys.end() ) {
            return false;
          }
//        a ma-li hodnotu
          auto assignmentValueOpt = assignment.template get<typename Slot::ValuePart::Name>( key );
          if ( assignmentValueOpt.has_value() ) {
//          hodnota v solution je stejna
            auto solutionValueOpt = solution.template get<typename Slot::ValuePart::Name>( key );
            if ( ! solutionValueOpt.has_value() 
                || solutionValueOpt.value() != assignmentValueOpt.value() ) {
              return false;
            }
          }
        }
        return true;
      }
  };
  template<typename...>
  class SlotsSanityChecker;

  template<typename CurrentSlot, typename... FurtherSlots>
  class SlotsSanityChecker<std::tuple<CurrentSlot, FurtherSlots...>> {
    public:
      template<typename Puzzle>
      static bool check( const Puzzle& assignment, const Puzzle& solution ) {
        return SlotSanityChecker<CurrentSlot>::check( assignment, solution )
          && SlotsSanityChecker<std::tuple<FurtherSlots...>>::check( assignment, solution );
      }
  };

  template<>
  class SlotsSanityChecker<std::tuple<>> {
    public:
      template<typename Puzzle>
      static bool check( const Puzzle& /*assignment*/, const Puzzle& /*solution*/ ) {
        return true;
      }
  };

  template<typename Transformation>
  struct TransformationPerformer {
    static Transformation::OutputT transform( const Transformation::InputT& input ) {
      return typename Transformation::TransformationT{}( input );
    }
  };

  template<typename...>
  struct TransformationsPerformer;

  template<typename CurrentTransformation, typename... FurtherTransformations>
  struct TransformationsPerformer<std::tuple<CurrentTransformation, FurtherTransformations...>> {
    static auto transform( const typename CurrentTransformation::InputT& input ) {
      return TransformationsPerformer<std::tuple<FurtherTransformations...>>::transform(
          TransformationPerformer<CurrentTransformation>::transform( input ) );
    }
  };

  template<>
  struct TransformationsPerformer<std::tuple<>> {
    static auto transform( const auto& input ) {
      return input;
    }
  };

  template<typename Constraint>
  struct ConstraintValidityChecker {
    template<typename Puzzle>
    static bool check( const Puzzle& solution ) {
      return TransformationsPerformer<Constraint>::transform( solution.getContentsView() );
    }
  };

  template<typename...>
  struct ConstraintsValidityChecker;

  template<typename CurrentConstraint, typename... FurtherConstraints>
  struct ConstraintsValidityChecker<std::tuple<CurrentConstraint, FurtherConstraints...>> {
    public:
      template<typename Puzzle>
      static bool check( const Puzzle& solution ) {
        return ConstraintValidityChecker<CurrentConstraint>::check( solution ) 
          && ConstraintsValidityChecker<std::tuple<FurtherConstraints...>>::check( solution );
      }
  };

  //when there are no more constraints
  template<>
  struct ConstraintsValidityChecker<std::tuple<>> {
    public:
      template<typename Puzzle>
      static bool check( const Puzzle& /*solution*/ ) {
        return true;
      }
  };

  template<typename Puzzle>
  class Checker {
    public:
      bool checkSanity( const Puzzle& assignment, const Puzzle& solution ) {
        return SlotsSanityChecker<typename Puzzle::Slots_>::check( assignment, solution );
      }

      bool checkValidity( const Puzzle& solution ) {
        return ConstraintsValidityChecker<typename Puzzle::Constraints_>::check( solution );
      }
  };
}//namespace Checker
