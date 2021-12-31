#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Util/types_tree_impl.h"

#include "Transformation/NarrowTop.h"

#include "undef.h"

namespace {
  using types_tree::__detail::types_tree;

  TEST( NarrowTop, test ) {
    using tree = typename types_tree::add< node<1> >::add< node<2> >::add< node<3>, name<2> >
      ::add< node<4> >::add< node<5>, name<4> >::add< node<6>, name<5> >::add< node<7>, name<4> >;
    using afterPrune = typename NarrowTop< name<2>, name<6> >::OutputT<ContentsView<int, tree>>;
    using expectedResult = typename types_tree::add< node<2> >::add< node<3>, name<2> >
      ::add< node<4> >::add< node<5>, name<4> >::add< node<6>, name<5> >;
    static_assert( std::is_same_v< afterPrune, ContentsView<int, expectedResult> > );
  }
}//namespace
