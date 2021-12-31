#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "contents_view.h"

#include "Util/types_tree_impl.h"

#include "Transformation/NarrowBottom.h"

namespace {
  using types_tree::__detail::types_tree;

  TEST( NarrowBottom, trivial_no_change ) {
    using tree = ContentsView<int, typename types_tree::add<node<1>>>;
    using after_prune = typename NarrowBottom<name<1>>::OutputT<tree>;
    static_assert( std::is_same_v<tree, after_prune> );
  }

  TEST( NarrowBottom, non_trivial_no_change ) {
    using tree = typename types_tree::add<node<1>>::add<node<2>, name<1>>;
    static_assert( NarrowBottom<name<2>>::Pruner<tree>::keep<node<1>> );
    using after_prune = typename NarrowBottom<name<2>>::OutputT<ContentsView<int, tree>>;
    static_assert( std::is_same_v<ContentsView<int, tree>, after_prune> );
  }

  TEST( NarrowBottom, test ) {
    using firstBranch = typename types_tree::add< node<1> >::add< node<2>, name<1> >;
    using secondBranch = typename firstBranch::add< node<3> >::add< node<4>, name<3> >;
    using beforePrune = typename secondBranch::add< node<5> >::add< node<6>, name<5> >;
    using afterPrune = typename NarrowBottom< name<3>, name<6> >
      ::OutputT< ContentsView<int, beforePrune> >;
    using expectedResult = typename types_tree::add< node<3> >::add< node<5> >::add< node<6>, name<5> >;
    static_assert( std::is_same_v< ContentsView<int, expectedResult>, afterPrune > );
  }
}//namespace

//potrebuju dve branche, ktere zustanou,
//jedna at je pred prunovanim delsi nez po nem
//potrebuju branch, ktera nezustane
