#pragma once

#include "exists.h"

namespace __processed {
  template<typename Input, typename Transform, typename Output>
  class Transformation {
    public:
      using InputT = Input;
      using TransformationT = Transform;
      using OutputT = Output;
  };

  /*template<typename Transformation_>
  class Constraint {
    public:
      using Transformation = Transformation_;
  };*/
}//namespace __processed

template<typename...>
class TransformationsProcessor;

template<typename... FinishedTransformations, typename CurrentInputT, 
  typename CurrentTransformation, typename... FurtherTransformations>
#ifndef DEBUG_Puzzle_h
requires( exists<typename CurrentTransformation::template OutputT<CurrentInputT>> &&
    exists<typename TransformationsProcessor<
      std::tuple<FinishedTransformations..., __processed::Transformation<
      CurrentInputT, CurrentTransformation, typename CurrentTransformation::template OutputT<CurrentInputT>>>,
      typename CurrentTransformation::template OutputT<CurrentInputT>,
      std::tuple<FurtherTransformations...>>::result> )
#endif
class TransformationsProcessor<std::tuple<FinishedTransformations...>, CurrentInputT, 
    std::tuple<CurrentTransformation, FurtherTransformations...>> {
  public:
    using ProcessedCurrentTransformation = __processed::Transformation<
      CurrentInputT, CurrentTransformation, 
      typename CurrentTransformation::template OutputT<CurrentInputT>>;
    using result = typename TransformationsProcessor<
      std::tuple<FinishedTransformations..., ProcessedCurrentTransformation>,
      typename ProcessedCurrentTransformation::OutputT,
      std::tuple<FurtherTransformations...>>::result;
};

template<typename... FinishedTransformations, typename CurrentInputT>
class TransformationsProcessor<std::tuple<FinishedTransformations...>, CurrentInputT, std::tuple<>> {
  public:
    using result = std::tuple<FinishedTransformations...>;
};

template<typename...>
class ProcessTransformation;

template<typename... Transformation, typename GridSlots>
#ifndef DEBUG_Puzzle_h
requires( exists<typename TransformationsProcessor<
      std::tuple<>, GridSlots, std::tuple<Transformation...>>::result> )
#endif
class ProcessTransformation<Transform<Transformation...>, GridSlots> {
  public:
    using result = typename TransformationsProcessor<
      std::tuple<>, GridSlots, std::tuple<Transformation...>>::result;
};

template<typename Constraint, typename GridSlots, typename = typename ProcessTransformation<
    typename Constraint::Transform, GridSlots>::result>
#ifndef DEBUG_Puzzle_h
requires( exists<typename ProcessTransformation<
    typename Constraint::Transformations, GridSlots >::result> )
#endif
class ProcessConstraint {
  public:
    using Transformation = typename ProcessTransformation<
      typename Constraint::Transformations, GridSlots >::result;
    using result = Transformation;
    //using result = __processed::Constraint<Transformation>;
};

template<typename...>
class ProcessConstraints;

template<typename... Constraint, typename GridSlots>
#ifndef DEBUG_Puzzle_h
requires( exists<std::tuple<typename ProcessConstraint<Constraint, GridSlots>::result...>> )
#endif
class ProcessConstraints<Constraints<Constraint...>, GridSlots> {
  public:
    using result = std::tuple<typename ProcessConstraint<Constraint, GridSlots>::result...>;
};

template<typename PuzzleType, typename GridSlots/*, typename = ProcessConstraints<
    typename PuzzleType::Constraints_, GridSlots >::result*/>
#ifndef DEBUG_Puzzle_h
requires( exists<typename ProcessConstraints<
      typename PuzzleType::Constraints_, GridSlots >::result> )
#endif
class ConstraintsSet {
  public:
    using Constraints = typename ProcessConstraints<
      typename PuzzleType::Constraints_, GridSlots >::result;
};
