#pragma once

#include "contents_view.h"
#include "Narrow.h"

//NarrowTop -- odstranim node, ktery zaroven:
//  a) neni potomkem zadneho z vyjmenovanych nodu
//  b) neni predkem zadneho z vyjmenovanych nodu

template<typename... BottomNodeNames>
struct NarrowTop {
  template<typename Tree>
  struct Pruner {
    template<typename Node>
    static constexpr bool keep = 
      ( ( IsAncestor<Tree, Node, typename Tree::get_node<BottomNodeNames>>::value
          || IsAncestor<Tree, typename Tree::get_node<BottomNodeNames>, Node>::value ) || ... );

    template<typename Node>
    static constexpr bool prune = ! keep<Node>;
  };

  template<typename>
  struct NarrowTopImpl;

  template<typename Grid, typename InputSlots>
  struct NarrowTopImpl<ContentsView<Grid, InputSlots>> {
    using OutputT = ContentsView<Grid, typename InputSlots::prune<Pruner<InputSlots>>>;
  };

  template<typename InputView>
  using OutputT = typename NarrowTopImpl<InputView>::OutputT;

  template<typename InputT>
  OutputT<InputT> operator()( const InputT& inputContentsView ) { return inputContentsView; }
};
