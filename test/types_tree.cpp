#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Util/types_tree.h"

namespace {
  TEST( types_tree, createOk ) {
    template<typename Name, typename... Args>
    struct node_builder {
      using node = 
    };
    struct node_factory {
      template<typename Name, typename... Args>
      using build_node = node_builder<Name, Args...>::node;
    };
  }

  TEST( types_tree, createNOk ) {
  }
}//namespace
//1) tak rekneme, ze types_tree se zalozi jako
//  types_tree<node_factory>, 
//  cimz vznikne prazdnej strom, v nemz je jenom "neviditelnej" root
//  node_factory je typ s metodou build_node<...>
//  toto se pouzije pri pridavani node pomoci descendant_args...; do stromu se prida node
//    vzniklej jako build_node<name, args...>
//
//2) rozlisujeme 3 druhy "objektu"
//  a) celej strom jako takovej; garantuje se, ze je to skutecne strom s jedinym rootem, tim neviditelnym
//  b) nody v tom stromu; node je 
//        <name, value>
//     node lze ze stromu ziskat pomoci
//        types_tree<...>::get_node<name>
//     samotny value nodu lze ziskat pomoci
//        types_tree<...>::get_value<name>
//     node ma predchudce
//        types_tree<...>::get_ancestor_name<name> -- je-li to neviditelny root, vrati se void, jinak name
//        types_tree<...>::get_ancestor_node<name> -- je-li to neviditelny root, vrati se void, jinak node
//     node ma nasledniky
//        types_tree<...>::get_descendant_names<name> -- je to std::tuple<names...>
//        types_tree<...>::get_descendant_nodes<name> -- je to std::tuple<nodes...>
//  c) edge v tom stromu; edge je
//        <ancestor_node, descendant_node>
//     anebo
//        <ancestor_name, descendant_name, descendant_args...>
//     anebo proc ne i
//        <ancestor_node, descendant_name, descendant_args...>
//     tuple edgu jdoucich z daneho node se ziska pomoci
//        types_tree<...>::get_edges<name>
//
//3) do stromu lze pridat viditelnej root node pomoci
//        types_tree<...>::add<node>
//     anebo
//        types_tree<...>::add<name, args...>
//
//4) strom lze rozsirit o non-root nody pomoci
//        types_tree<...>::add<edge>
//   edge musi mit ancestor_name, kterej ve stromu existuje
//   ma-li edge ancestor_node, musi value odpovidat tomu, co uz ve stromu je
//   edge musi mit descendant_name, kterej ve stromu neexistuje
//   vysledkem je novej types_tree, vzniklej rozsirenim puvodniho o novej node (descendant_node),
//      jehoz ancestorem je ancestor_node
//
//5) strom lze zmensit pomoci
//        types_tree<...>::remove<node>
//   coz smaze node a vsechny jeho prime i neprime descendanty
//   pro vetsi pocit bezpeci lze pouzit 
//        types_tree<...>::remove_leaf<node>
//   coz predpoklada, ze node nema zadne descendanty; ma-li je, error
//
//6) vlastnosti stromu lze krom metod z bodu 2) zkoumat jeste pomoci
//        path_finder<types_tree>::find_path<start_name, end_name>, coz je tuple<name>, 
//              kdyz cesta existuje, a void, kdyz neexistuje
//  a dale
//        types_tree<...>::get_nodes
//        types_tree<...>::get_edges
//  tyto dve metody vrati v nedefinovanem poradi vsechny nody, resp. edge
