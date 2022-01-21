#pragma once

template<typename Grid, typename SlotsTree>
class ContentsView {
  private:
    const Grid grid;
  public:
    using Grid_ = Grid;
    using Slots_ = SlotsTree;

    ContentsView( const Grid& grid_ ) : grid{ grid_ } {}

    template<typename SlotsTree2>
    ContentsView( const ContentsView<Grid, SlotsTree2>& orig ) : grid{ orig.get_grid() } {}

    Grid get_grid() const { return grid; }
};
