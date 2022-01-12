#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Util/types_tree_impl.h"
namespace {
  using types_tree::__detail::types_tree;

  TEST( types_tree_impl, add_root_node ) {
    using tree = typename types_tree::add< node<1> >;
    static_assert( tree::has_node< name<1> > );
    static_assert( std::is_same_v< typename tree::get_roots, std::tuple< node<1> > > );
    static_assert( std::is_same_v< typename tree::get_node< name<1> >, node<1> > );
    static_assert( std::is_same_v< typename tree::get_ancestor< name<1> >, void > );
    static_assert( std::is_same_v< typename tree::get_descendants< name<1> >, std::tuple<> > );
  }

  TEST( types_tree_impl, add_child_node ) {
    using tree = typename types_tree::add< node<1> >::add< node<2>, name<1> >;
    static_assert( tree::has_node< name<1> > );
    static_assert( tree::has_node< name<2> > );
    static_assert( std::is_same_v< typename tree::get_node< name<2> >, node<2> > );
    static_assert( std::is_same_v< typename tree::get_ancestor< name<2> >, node<1> > );
    static_assert( std::is_same_v< typename tree::get_descendants< name<1> >, std::tuple< node<2> > > );
  }

  TEST( types_tree_impl, remove_child_node ) {
    using temp = typename types_tree::add< node<1> >::add< node<2>, name<1> >;
    static_assert( temp::has_node< name<1> > );
    static_assert( temp::has_node< name<2> > );
    using tree = typename temp::remove< name<2> >;
    static_assert( tree::has_node< name<1> > );
    static_assert( ! tree::has_node< name<2> > );
    static_assert( std::is_same_v< typename tree::get_node< name<1> >, node<1> > );
    static_assert( std::is_same_v< typename tree::get_ancestor< name<1> >, void > );
    static_assert( std::is_same_v< typename tree::get_descendants< name<1> >, std::tuple<> > );
  }

  TEST( types_tree_impl, remove_root_node ) {
    using temp = typename types_tree::add< node<1> >::add< node<2>, name<1> >;
    static_assert( temp::has_node< name<1> > );
    static_assert( temp::has_node< name<2> > );
    using tree = typename temp::remove< name<1> >;
    static_assert( ! tree::has_node< name<1> > );
    static_assert( ! tree::has_node< name<2> > );
    static_assert( std::is_same_v< typename tree::get_roots, std::tuple<>> );
  }

  TEST( types_tree_impl, subtree ) {
    using tree = typename types_tree::add< node<1> >::add< node<2>, name<1> >
      ::add< node<3>, name<2> >::add< node<4>, name<3> >::add< node<5>, name<4> >;
    using subtree = typename tree::subtree< name< 4 > >;
    using expected = typename types_tree::add< node<4> >::add< node<5>, name<4> >;
    static_assert( std::is_same_v<subtree, expected> );
  }

  struct brutal_pruner {
    template<typename>
    static constexpr bool prune = true;
    template<typename>
    static constexpr bool keep = false;
  };
  TEST( types_tree_impl, prune_brutal_small ) {
    using tree = typename types_tree::add< node<1> >;
    static_assert( tree::has_node< name<1> > );
    static_assert( ! tree::has_node< name<2> > );
    using after_prune = typename tree::prune<brutal_pruner>;
    static_assert( ! after_prune::has_node< name<1> > );
    static_assert( ! after_prune::has_node< name<2> > );
  }

  TEST( types_tree_impl, prune_brutal_large ) {
    using tree = typename types_tree::add< node<1> >::add< node<2>, name<1> >
      ::add< node<3>, name<2> >::add< node<4>, name<3> >;
    static_assert( tree::has_node< name<1> > );
    static_assert( tree::has_node< name<2> > );
    static_assert( tree::has_node< name<3> > );
    static_assert( tree::has_node< name<4> > );
    using after_prune = typename tree::prune<brutal_pruner>;
    static_assert( ! after_prune::has_node< name<1> > );
    static_assert( ! after_prune::has_node< name<2> > );
    static_assert( ! after_prune::has_node< name<3> > );
    static_assert( ! after_prune::has_node< name<4> > );
  }
}//namespace
//cili komplet api types_tree_impl je:
//konstruktor -- tedy deklarace structu types_tree_impl
//      types_tree types_tree::add<node>
//      types_tree types_tree::add<new_node, parent_node_name>
//
//      types_tree types_tree::remove<name>
//
//      types_tree::get_node<name> -- vraci node
//      types_tree::get_ancestor<name> -- je-li ancestorem neviditelny root, vrati se void, jinak node
//      types_tree::get_descendants<name> -- std::tuple<nodes...>
//
//types_tree<>:
//1) zalozi se jako
//      types_tree<>, 
//   cimz vznikne prazdnej strom, v nemz je jenom "neviditelnej" root
//
//2) rozlisujeme 3 druhy "objektu", fakticky typu:
//  a) celej strom jako entitu; vznikne, jak popsano v bodu 1), a vsechny modifikatory
//        z bodu 3), 4) a 5) vraceji vzdy nove vytvoreny strom
//    implementovanej je v types_tree::__detail::types_tree
//  b) node v tom stromu; implementovanej v types_tree::__detail::node; je to 
//      std::pair<name, value>
//    pri implementaci neni treba jakkoli omezovat typy, ktere mohou byt pouzite jako 
//        name a value, ale z uzivatelskeho hlediska by to mohlo byt uzitecne, cili jako
//        dalsi nadstavbu si lze predstavit strom, kde toto bude nejak omezeno
//    getters:
//        types_tree::get_node<name> -- vraci node
//     node ma predchudce
//        types_tree::get_ancestor<name> -- je-li ancestorem neviditelny root, vrati se void, jinak node
//     node ma nasledniky
//        types_tree::get_descendants<name> -- std::tuple<nodes...>
//  c) edge v tom stromu; implementovanej v types_tree::__detail::edge; je to 
//        std::pair<node, node> (node je types_tree::__detail::node)
//
//3) pridavani nodu
//  a) viditelnej root se prida
//      types_tree::add<node>
//  b) edge (mozno nahlizet ze non-root node) se prida
//      types_tree::add<new_node, parent_node>
//
//4) ubirani nodu
//  a) node a vsechny jeho prime i neprime descendanty lze odstranit pomoci
//      types_tree::remove<node>
