#pragma once

#include "contents_view.h"
#include "Narrow.h"

//NarrowBottom -- odstranim node, ktery:
//  a) neni predkem zadneho z vyjmenovanych nodu

template<typename... BottomNodeNames>
struct NarrowBottom {
  template<typename Tree>
  struct Pruner {
    template<typename Node>
    static constexpr bool keep = 
      ( IsAncestor<Tree, Node, typename Tree::get_node<BottomNodeNames>>::value || ... );

    template<typename Node>
    static constexpr bool prune = ! keep<Node>;
  };

  template<typename>
  struct NarrowBottomImpl;

  template<typename Grid, typename InputSlots>
  struct NarrowBottomImpl<ContentsView<Grid, InputSlots>> {
    using OutputT = ContentsView<Grid, typename InputSlots::prune<Pruner<InputSlots>>>;
  };

  template<typename InputView>
  using OutputT = typename NarrowBottomImpl<InputView>::OutputT;

  template<typename InputT>
  OutputT<InputT> operator()( const InputT& inputContentsView ) { return inputContentsView; }
};
