#pragma once
#include "exists.h"
#include "undef.h"

//rekneme, ze si udelam vlastni implementaci, kde vsechno stoji na tuplech of
//  [name, ancestorName, value, descendantNames...]
  template<int I>
  struct name{};

  template<int I>
  struct value{};

  template<int I>
  using node = std::pair<name<I>, value<I>>;

namespace types_tree::__detail {
  struct root_name{};
  struct root_value{};
  struct root_ancestor{};
  using root_ = std::tuple<root_name, root_ancestor, root_value>;
  using root_node_ = std::tuple<root_>;

  inline bool operator<( const root_value&, const root_value& ) { return false; }
  inline bool operator==( const root_value&, const root_value& ) { return true; }
  inline std::ostream& operator<<( std::ostream& os, const root_value& ) { os << "root_value"; return os; }

  template<typename...>
  struct types_tree_impl;

  using types_tree = types_tree_impl<root_node_>;

  template<typename...>
  struct FindNode;

  template<typename Name, typename CurrentNode, typename... FurtherNodes>
  struct FindNode<Name, CurrentNode, FurtherNodes...> {
    using value = typename FindNode<Name, FurtherNodes...>::value;
  };

  template<typename Name, typename... CurrentNodeRestArgs, typename... FurtherNodes>
  struct FindNode<Name, std::tuple<Name, CurrentNodeRestArgs...>, FurtherNodes...> {
    using value = std::tuple<Name, CurrentNodeRestArgs...>;
  };

  template<typename...>
  struct MakeOutputNode;

  template<typename Name, typename Ancestor, typename Value, typename... Descendants>
  struct MakeOutputNode<std::tuple<Name, Ancestor, Value, Descendants...>> {
    using type = std::pair<Name, Value>;
  };

  template<typename... Descendants>
  struct MakeOutputNode<std::tuple<root_name, root_ancestor, root_value, Descendants...>> {
    using type = void;
  };

  template<typename...>
  struct AddToDescendantsIfAppropriate;

  //NewNodeAscendantName != Name, this is not the correct ImplementationNode
  template<typename Name, typename AscendantName, typename Value, typename... DescendantNames,
    typename NewNodeName, typename NewNodeAscendantName, typename NewNodeValue>
  struct AddToDescendantsIfAppropriate<
    std::tuple<Name, AscendantName, Value, DescendantNames...>,  
    std::tuple<NewNodeName, NewNodeAscendantName, NewNodeValue>> {
      using type = std::tuple<Name, AscendantName, Value, DescendantNames...>;
  };

  //NewNodeAscendantName == Name, this is the correct ImplementationNode, let's add NewNodeName
  //  to DescendantNames
  template<typename Name, typename AscendantName, typename Value, typename... DescendantNames,
    typename NewNodeName, typename NewNodeValue>
  struct AddToDescendantsIfAppropriate<
    std::tuple<Name, AscendantName, Value, DescendantNames...>,  
    std::tuple<NewNodeName, Name, NewNodeValue>> {
      using type = std::tuple<Name, AscendantName, Value, DescendantNames..., NewNodeName>;
  };

  template<typename... KnownImplementationNodes>
  struct types_tree_impl<std::tuple<KnownImplementationNodes...>> {
    template<typename...>
    struct Add;

    template<typename Name, typename Value>
    struct Add<std::pair<Name, Value>> {
      using type = typename Add<std::pair<Name, Value>, root_name>::type;
    };

    template<typename AscName, typename NewNodeName, typename NewNodeValue>
    struct Add<std::pair<NewNodeName, NewNodeValue>, AscName> {
      using NewImplementationNode = std::tuple<NewNodeName, AscName, NewNodeValue>;
      using type = types_tree_impl<std::tuple<
        typename AddToDescendantsIfAppropriate<KnownImplementationNodes, NewImplementationNode>::type...,
        NewImplementationNode>>;
    };

    template<typename Name>
    struct GetNode {
      using ImplementationNode = typename FindNode<Name, KnownImplementationNodes...>::value;
      using type = typename MakeOutputNode<ImplementationNode>::type;
    };

    template<typename Name>
    struct HasNode {
      template<typename...>
      struct HasName {
        static constexpr bool value = false;
      };

      template<typename CurrentNode, typename... FurtherNodes>
      struct HasName<std::tuple<CurrentNode, FurtherNodes...>> {
        using CurrentNodeName = typename std::tuple_element<0, CurrentNode>::type;
        static constexpr bool value = std::is_same_v< CurrentNodeName, Name > 
          || HasName<std::tuple<FurtherNodes...>>::value;
      };
      
      static constexpr bool value = HasName<std::tuple<KnownImplementationNodes...>>::value;
    };

    template<typename Name>
    struct GetAncestor {
      using ImplementationNode = typename FindNode<Name, KnownImplementationNodes...>::value;
      using AncestorName = typename std::tuple_element<1, ImplementationNode>::type;
      using AncestorImplementationNode = typename FindNode<AncestorName, KnownImplementationNodes...>::value;
      using type = typename MakeOutputNode<AncestorImplementationNode>::type;
    };

    template<typename Name>
    struct GetDescendants {
      template<typename...>
      struct FromImplementationNode;

      template<typename NodeName, typename AncestorName, typename Value, typename... DescendantNames>
      struct FromImplementationNode<std::tuple<NodeName, AncestorName, Value, DescendantNames...>> {
        using type = std::tuple<typename GetNode<DescendantNames>::type...>;
      };
    
      using NamedImplementationNode = typename GetNode<Name>::ImplementationNode;
      using type = typename FromImplementationNode<NamedImplementationNode>::type;
    };

    template<typename...>
    struct RemoveNameFromNames;

    template<typename Name, typename NodeName, typename NodeAscendantName, typename NodeValue, 
      typename... PassedNames, typename CurrentName, typename... FurtherNames>
    struct RemoveNameFromNames<Name, NodeName, NodeAscendantName, NodeValue, 
      std::tuple<PassedNames...>, std::tuple<CurrentName, FurtherNames...>> {
      using type = typename RemoveNameFromNames<Name, NodeName, NodeAscendantName, NodeValue,
            std::tuple<PassedNames..., CurrentName>, std::tuple<FurtherNames...>>::type;
    };

    template<typename Name, typename NodeName, typename NodeAscendantName, typename NodeValue, 
      typename... PassedNames, typename... FurtherNames>
    struct RemoveNameFromNames<Name, NodeName, NodeAscendantName, NodeValue,
      std::tuple<PassedNames...>, std::tuple<Name, FurtherNames...>> {
      using type = typename RemoveNameFromNames<Name, NodeName, NodeAscendantName, NodeValue,
          std::tuple<PassedNames...>, std::tuple<FurtherNames...>>::type;
    };

    template<typename Name, typename NodeName, typename NodeAscendantName, typename NodeValue,
      typename... PassedNames>
    struct RemoveNameFromNames<Name, NodeName, NodeAscendantName, NodeValue,
      std::tuple<PassedNames...>, std::tuple<>> {
      using type = std::tuple<NodeName, NodeAscendantName, NodeValue, PassedNames...>;
    };

    template<typename...>
    struct RemoveDescendantNameFromNode;

    template<typename Name, typename NodeName, typename NodeAscendantName, typename NodeValue,
      typename... DescendantNames>
    struct RemoveDescendantNameFromNode<Name, std::tuple<NodeName, NodeAscendantName, NodeValue,
      DescendantNames...>> {
        using type = typename RemoveNameFromNames<Name, NodeName, NodeAscendantName, NodeValue, 
          std::tuple<>, std::tuple<DescendantNames...>>::type;
    };

    template<typename...>
    struct RemoveLeaf;

    template<typename Name, typename AscendantName, typename Value>
    struct RemoveLeaf<std::tuple<Name, AscendantName, Value>> {
      template<typename...>
      struct FromImplementationNodes;

      //current node is not interesting, just forward the call
      template<typename... KnownResultNodes, 
        typename CurrentNodeName, typename... CurrentNodeRestArgs, 
        typename... FurtherKnownNodes>
      struct FromImplementationNodes<std::tuple<KnownResultNodes...>, 
        std::tuple<std::tuple<CurrentNodeName, CurrentNodeRestArgs...>, 
          FurtherKnownNodes...>> {
        using type = typename FromImplementationNodes<std::tuple<KnownResultNodes...,
            std::tuple<CurrentNodeName, CurrentNodeRestArgs...>>,
            std::tuple<FurtherKnownNodes...>>::type;
      };

      //current node is the ascendant node, remove Name from current node's descendants
      template<typename... KnownResultNodes,
        typename... CurrentNodeRestArgs, 
        typename... FurtherKnownNodes>
      struct FromImplementationNodes<std::tuple<KnownResultNodes...>,
        std::tuple<std::tuple<AscendantName, CurrentNodeRestArgs...>,
          FurtherKnownNodes...>> {
        using current_node = std::tuple<AscendantName, CurrentNodeRestArgs...>;
        using new_node = typename RemoveDescendantNameFromNode<Name, current_node>::type;
        using type = typename FromImplementationNodes<std::tuple<KnownResultNodes..., new_node>,
            std::tuple<FurtherKnownNodes...>>::type;
      };

      //current node is this node, ignore current node
      template<typename... KnownResultNodes, typename... FurtherKnownNodes> 
      struct FromImplementationNodes<std::tuple<KnownResultNodes...>,
        std::tuple<std::tuple<Name, AscendantName, Value>, FurtherKnownNodes...>> {
        using type = typename FromImplementationNodes<std::tuple<KnownResultNodes...>,
          std::tuple<FurtherKnownNodes...>>::type;
      };

      //there are no more nodes
      template<typename... KnownResultNodes>
      struct FromImplementationNodes<std::tuple<KnownResultNodes...>, std::tuple<>> {
        using type = types_tree_impl<std::tuple<KnownResultNodes...>>;
      };

      using type = 
        typename FromImplementationNodes<std::tuple<>, std::tuple<KnownImplementationNodes...>>::type;
    };

    template<typename...>
    struct RemoveImplementationNode;

    template<typename>
    struct Remove;

    template<typename Name, typename AscendantName, typename Value, typename CurrentDescendantName, typename... FurtherDescendantNames>
    struct RemoveImplementationNode<std::tuple<
      Name, AscendantName, Value, CurrentDescendantName, FurtherDescendantNames...>> {
      using Removed1 = typename Remove<CurrentDescendantName>::type;
      using type = typename Removed1::template RemoveImplementationNode<
        std::tuple<Name, AscendantName, Value,FurtherDescendantNames...>>::type;
    };

    template<typename Name, typename AscendantName, typename Value>
    struct RemoveImplementationNode<std::tuple<Name, AscendantName, Value>> {
      using type = typename RemoveLeaf<std::tuple<Name, AscendantName, Value>>::type;
    };

    template<typename Name>
    struct Remove {
      using NamedImplementationNode = typename GetNode<Name>::ImplementationNode;
      using type = typename RemoveImplementationNode<NamedImplementationNode>::type;
    };

    template<typename NewTree, typename Node, typename... AncestorName>
    struct AddToNewTree {
      //using NodeName = typename std::tuple_element<0, Node>::type;
      //using NodeValue = typename std::tuple_element<2, Node>::type;
      //using type = typename NewTree::template Add<std::pair<NodeName, NodeValue>, AncestorName...>::type;
      using type = typename NewTree::template Add<Node, AncestorName...>::type;
    };

    /*template<typename, typename, typename, typename>
    struct AddRemainingDescendantsToNewTree;

    template<typename NewTree, typename AncestorName, typename... ProcessedDescendants, 
      typename CurrentDescendant, typename... FurtherDescendants>
    struct AddRemainingDescendantsToNewTree<NewTree, AncestorName, std::tuple<ProcessedDescendants...>,
      std::tuple<CurrentDescendant, FurtherDescendants...>> {
        using NewTreeAfterCurrentAdd = 
          typename AddToNewTree<NewTree, CurrentDescendant, AncestorName>::type;
        using type = typename AddRemainingDescendantsToNewTree<NewTreeAfterCurrentAdd,
              AncestorName, std::tuple<ProcessedDescendants..., CurrentDescendant>,
              std::tuple<FurtherDescendants...>>::type;
    };*/

    template<typename, typename>
    struct AddDescendantsToNewTree;

    template<typename...>
    struct AddToNewTreeRecursive;

    template<typename NewTree, typename FirstDescendant, typename... Descendants>
    struct AddDescendantsToNewTree<NewTree, std::tuple<FirstDescendant, Descendants...>> {
      using FirstDescendantName = std::tuple_element_t<0, FirstDescendant>;
      using Ancestor = typename GetAncestor<FirstDescendantName>::type;
      using AncestorName = std::tuple_element_t<0, Ancestor>;
      using NewTreeWithFirstDescendant = typename 
        AddToNewTreeRecursive<NewTree, FirstDescendant, AncestorName>::type;
      using type = typename AddDescendantsToNewTree<NewTreeWithFirstDescendant, 
            std::tuple<Descendants...>>::type;
    };

    template<typename NewTree>
    struct AddDescendantsToNewTree<NewTree, std::tuple<>> {
      using type = NewTree;
    };

    template<typename NewTree, typename Node, typename... AncestorName>
    struct AddToNewTreeRecursive<NewTree, Node, AncestorName...> {
      //pridat do tree NodeName jako potomka AncestorName
      //zavolat sam sebe nad kazdym descendantem NodeName
      using NewTreeWithNode = typename AddToNewTree<NewTree, Node, AncestorName...>::type;
      using NodeName = std::tuple_element_t<0, Node>;
      using type = typename AddDescendantsToNewTree<NewTreeWithNode, 
            typename GetDescendants<NodeName>::type>::type;
    };

    template<typename Name>
    struct Subtree {
      //vytvorit novej strom
      //pridat node Name pomoci AddToNewTree
      using Node = typename GetNode<Name>::type;
      //zavolat AddToNewTreeRecursive nad kazdym descendantem Name
      using type = typename AddToNewTreeRecursive<types_tree, Node>::type;
    };

    template<typename...>
    struct Prune;

    template<typename...>
    struct PruneImpl;

    template<typename Pruner, typename FirstImplementationNode, typename... FurtherImplementationNodes>
    struct Prune<Pruner, std::tuple<FirstImplementationNode, FurtherImplementationNodes...>> {
      using type = typename PruneImpl<Pruner, std::tuple<FurtherImplementationNodes...>>::type;
    };

    template<typename Pruner, typename CurrentImplementationNode, typename... FurtherImplementationNodes>
    requires( Pruner::template prune<CurrentImplementationNode> )
    struct PruneImpl<Pruner, std::tuple<CurrentImplementationNode, FurtherImplementationNodes...>> {
      using CurrentName = typename std::tuple_element<0, CurrentImplementationNode>::type;
      using Remove1 = typename Remove<CurrentName>::type;
      using type = typename Remove1::template prune<Pruner>;
    };

    template<typename Pruner, typename CurrentImplementationNode, typename... FurtherImplementationNodes>
    requires( Pruner::template keep<CurrentImplementationNode> )
    struct PruneImpl<Pruner, std::tuple<CurrentImplementationNode, FurtherImplementationNodes...>> {
      using type = typename PruneImpl<Pruner, std::tuple<FurtherImplementationNodes...>>::type;
    };

    template<typename Pruner>
    struct PruneImpl<Pruner, std::tuple<>> {
      using type = types_tree_impl;
    };

    template<typename... InputNodes>
    using add = typename Add<InputNodes...>::type;

    template<typename Name>
    using get_node = typename GetNode<Name>::type;

    template<typename Name>
    static constexpr bool has_node = HasNode<Name>::value;

    template<typename Name>
    using get_ancestor = typename GetAncestor<Name>::type;

    template<typename Name>
    using get_descendants = typename GetDescendants<Name>::type;

    using get_roots = get_descendants<root_name>; 

    template<typename Name>
    using remove = typename Remove<Name>::type;

    template<typename Name>
    using subtree = typename Subtree<Name>::type;

    template<typename Pruner>
    using prune = typename Prune<Pruner, std::tuple<KnownImplementationNodes...>>::type;
  };
}//namespace types_tree::__detail
