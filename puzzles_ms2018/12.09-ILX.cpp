// Textual description
//
//Place letters I, L and X in the grid (maximum one letter per cell) so that each letter appears exactly ones in each row and column. Then draw a single closed loop travelling verticall and horizontally between centers of the adjacent cells. The loop cannot visit painted cells and the cells containing letter X and has to visit all the other cells exactly ones. The loop has to make right turn in cells with letter L and has to go straigth in cells with letter I. The hints around the grid show the order in which the letters appear in the given row and column (from left to right resp. top to bottom). To score the point you have to draw the loop and place the letters in the grid.
//
//
//  Example solution
//
//Size: 9
//
//Rows:
//  XLI LXI XIL LXI ILX IXL ILX XLI XIL
//
//Columns:
//  LIX LXI XLI LIX ILX XLI ILX XLI IXL
//
//Black cells:
//  [6,2]
//  [7,2]
//
//
//  Example solution
//
//Letters
//  - - X L I - - - -
//  - L - - - X I - - 
//  - X - I - - L - -
//  L - - X - - - - I
//  - I L - - - - X -
//  I - - - - - X L -
//  - - I - L - - - X
//  - - - - X L - I -
//  X - - - - I - - L
//
//Loop
//  ES WS -- ES EW EW WS ES WS
//  NS NE WS NE WS -- NS NS NS
//  NS -- NE EW NS ES NW NS NS
//  NE EW WS -- ES NW ES NW NS
//  ES EW NW ES NW ES NW -- NS
//  NS -- ES NW ES NW -- ES NW
//  NS -- NW ES NW ES EW NW --
//  NE WS NE NW -- NE EW EW ES
//  -- NE EW EW EW EW EW EW NW
//
//
//  Real assignment -- not done
