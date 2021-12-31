#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Util/types_tree_impl.h"

#include "Transformation/NarrowBottom.h"

namespace {
  using types_tree::__detail::types_tree;

  TEST( Narrow, IsAncestor ) {
    using tree = typename types_tree::add< node<1> >::add< node<2>, name<1> >
      ::add< node<3> >::add< node<4>, name<3> >;
    static_assert( std::is_same_v<std::tuple_element<0, node<1>>::type, name<1>> );
    static_assert( IsAncestor<tree, node<1>, node<1>>::value );
    static_assert( IsAncestor<tree, node<1>, node<2>>::value );
    static_assert( ! IsAncestor<tree, node<1>, node<3>>::value );
    static_assert( ! IsAncestor<tree, node<1>, node<4>>::value );
  }
}//namespace
