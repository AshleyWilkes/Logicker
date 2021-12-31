#pragma once
//
//NarrowTop a NarrowBottom jsou si velmi blizce pribuzne operace, u obou jde o to,
//  aby se gridContents zacaly tvarit jako svoje podmnozina, runtime implementaci
//  jsem zatim nepromyslel, ale je to nejaka fasada, ktera zakryva detaily, jichz 
//  neni potreba
//pri compile time se jedna o to, odstranit z types_tree nektere nody, pro urcovani,
//  ktere to maji byt, se hodi IsAncestor:
//
//ma vratit true, kdyz Node2 ma stejne jmeno jako Node1 anebo 
//ma Node1 stejne jmeno jako nektery z nodu, ktere jsou v tree
//ancestorem Node2
//
//cili prochazim Node2, get_ancestor..., 
//pokud nektery node je void, vracim false
//pokud nektery node ma jmeno name, vracim true
template<typename...>
struct IsAncestor;

template<typename tree, typename Node1, typename Node2>
requires( std::is_void_v<Node2> )
struct IsAncestor<tree, Node1, Node2> {
  static constexpr bool value = false;
};

template<typename tree, typename Node1, typename Node2>
requires( std::is_same_v<typename std::tuple_element<0, Node1>::type, 
    typename std::tuple_element<0, Node2>::type> )
struct IsAncestor<tree, Node1, Node2> {
  static constexpr bool value = true;
};

template<typename tree, typename Node1, typename Node2>
struct IsAncestor<tree, Node1, Node2> {
  static constexpr bool value =
    IsAncestor<tree, Node1, typename tree::get_ancestor<
        typename std::tuple_element<0, Node2>::type>>::value;
};
