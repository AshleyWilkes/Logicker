// Textual description
//
//Blacken as many cells in each reagion as indicated by the number in the upper left corner of the region. The cells may not touch each other by sides. Then draw a closed loop travelling between the centers of adjacent cells horizontally or vertically and going through all the unpainted cells in the grid.
//
//
//  Example assignment
//
//Size: 6
//
//AreadIds:
//  a a a a a b
//  c d d d e b
//  c d d e e b
//  c d d e e b
//  c d e e e b
//  c f f f f f
//
//Area hints:
//  a: 2
//  b: 1
//  c: 1
//  d: 1
//  e: 1
//  f: 0
//
//
//  Example solution
//
//  -- ES WS -- ES WS
//  ES NW NE EW NW NS
//  NE WS -- ES EW NW
//  -- NE WS NE WS --
//  ES EW NW -- NE WS
//  NE EW EW EW EW NW
//
//
//  Real assignment -- not done
