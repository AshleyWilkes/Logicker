#pragma once

//node_factory API:
//  build_node<Name, Args...> pro nejake Args je validni typ
//    chtelo by to concept, ale neumim ho napsat, takze proted nic
//    ono je ostatne ke zvazeni, jak velkou by mel cenu, i kdyz of course
//      pokud zadny build_node neexistuje, jiste by melo vyznam detekovat
//      to jako error hned pri vytvareni types_tree
//    na druhou stranu je zrejme, ze types_tree muze fungovat i bez node_factory
//      cili plan je udelat types_tree s node_factory az jako nadstavbu nad
//      types_tree bez ni
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
//
//
//
//    Nasleduji rovnez gettery nodu, ktere ale nepatri do zakladni implementace, ale do utility nadstavby
//        types_tree::get_value<name> -- vraci node::value
//        types_tree::get_ancestor_name<name> -- je-li ancestorem neviditelny root, void, jinak name
//        types_tree<...>::get_descendant_names<name> -- std::tuple<names...>
//    Tak a abych mel jednotnej pristup k metodam z implementace i z nadstavby, tak 
//        types_tree::__detail::types_tree je uz ta nadstavba
//        types_tree::__detail::types_tree_impl je implementace
//     gettery edgu v impl nejsou, edge lze snadno rucne vytvorit z dat ziskanych jinymi prostredky
//        stoji za uvahu, jestli by nebyl uzitecny nejaky utility bazmek, ktery by gettery 
//          na edge podporoval
//
//types_tree_impl<args> {
//template<typename name>
//using get_node<name>
//
//template<typename new_node>
//using add = types_tree_impl<new args>
//};
//
//types_tree<types_tree_impl> {
//template<typename new_node>
//using add = types_tree<typename types_tree_impl::add<new_node>>;
//};
//
//
//
