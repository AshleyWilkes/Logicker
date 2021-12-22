#pragma once

template<typename Topology_>
class Grid{
  public:
    using Topology = Topology_;
};

template<typename... Ts>
using Grids = std::tuple<Ts...>;

template<typename FieldType, typename Topology>
class HasFields;
