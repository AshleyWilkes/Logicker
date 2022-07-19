// Textual description
//
//Draw a snake in the grid and draw a single closed loop going horizontally and vertically through all the remaining cells in the grid. The snake goes from cell to cell vertically or horizontally, but not diagonally. The snake does not touch itself, not even diagonally. The numbers outside the grid indicate how many squares are used by the snake in that row or column. Head and tail of the snake are given.
//
//
//  Example assignment
//
//Width: 7
//Height: 7
//
//Now grid: initially empty cells are marked -, head and tail are marked S, cells not in the grid are marked x
//
//  - - - - - - -
//  - - - - - - -
//  - - - - S - -
//  - - - - - - -
//  - - - - - - -
//  - - - - - - S
//  - - - - - - x
//
//NOw given numbers
//
//Rows: - - - 3 - 3 -
//Columns: - 2 - 2 - - -
//
//
//  Example solution
//
//For loop cells direction in which loop goes are indicated NESW, for snake cells xx is given, cells outside the grid are marked --
//
//  ES EW EW EW EW EW WS
//  NW ES EW EW EW WS NS
//  NE NW xx xx xx NW NW
//  xx xx xx ES EW NW NS
//  xx ES EW NW ES EW NW
//  xx NE EW EW NW xx xx
//  xx xx xx xx xx xx --
//
//
//  Real assignment -- not done
