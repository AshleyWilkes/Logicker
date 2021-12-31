#pragma once

template<typename Grid, typename SlotsTree>
class ContentsView {
  private:
    const Grid *grid;
  public:
    ContentsView( const Grid* grid_ ) : grid{ grid_ } {}

    template<typename SlotsTree2>
    ContentsView( const ContentsView<Grid, SlotsTree2>& orig ) : grid{ orig.get_grid_p() } {}

    const Grid *get_grid_p() const { return grid; }
};
