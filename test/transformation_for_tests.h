#pragma once
#include "contents_view.h"
#include "Util/types_tree_impl.h"

//using types_tree::__detail::types_tree;

//GridTrans<Out> ma OutputT = Out, prave kdyz InputSlots je std::tuple
template<typename...>
struct TypesTreesOnly;

template<typename... Ts, typename Out>
struct TypesTreesOnly<types_tree::__detail::types_tree_impl<Ts...>, Out> {
  using OutputT = Out;
};

template<typename Out>
struct GridTrans {
  template<typename>
  struct GridTransImpl;

  template<typename Grid, typename InputSlots>
  struct GridTransImpl<ContentsView<Grid, InputSlots>> {
    using OutputT = typename TypesTreesOnly<InputSlots, Out>::OutputT;
  };
   
  template<typename InputView>
    using OutputT = typename GridTransImpl<InputView>::OutputT;
};

//Trans<In, Out> ma OutputT = Out, prave kdyz InputSlots == In
template<typename In, typename Input, typename Out>
struct InOnly;

template<typename In, typename Out>
struct InOnly<In, In, Out> {
  using OutputT = Out;
};

template<typename In, typename Out>
struct Trans {
  using InputT = In;

  template<typename InputSlots>
  using OutputT = typename InOnly<In, InputSlots, Out>::OutputT;
};

