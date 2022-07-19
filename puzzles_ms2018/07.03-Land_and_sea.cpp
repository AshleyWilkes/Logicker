// Textual description
//
//Draw a single closed loop through all squares in the grid by connecting the centers of cells horizontally and vertically. The loop does not touch or cross itself. The loop does not run through more than 2 white squares consecutively anywhere in the grid.
//
//
//  Example assignment
//
//Width: 6
//Height: 6
//
//Grid:
//x for dark cells, - for white cells
//
//  x - - x - -
//  - - - x - x
//  - x - - - x
//  - - x - x -
//  x - x - - -
//  - - x - - x
//
//
//  Example solution
//
//directions NESW in which the loop goes
//
//  ES EW EW EW EW WS
//  NE WS ES WS ES NW
//  ES NW NS NS NE WS
//  NS ES NW NE WS NS
//  NS NE EW WS NS NS
//  NE EW EW NW NE NW
//
//
//  Real assignment -- not done
