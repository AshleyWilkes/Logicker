// Textual description
//
//Draw a single loop using only horizontal and vertical lines between the centers of some cells sch that the loop does not visit any cell more than once. At every cell containing a white circle the loop must pass straight through that circle and make a 90 degrees turn in at least one of the cells adjacent to the circle. At every cell containing a black circle the loop must make a 90 degrees turn and travel straight through both cells adjacent to the circle.
//Each outlined region contains exactly 4 turns of the loop.
//
//
//  Example assignment
//
//Size: 6
//
//Grid:
//O for white circles, B for black circles
//
//  - - B B - -
//  - - - - - -
//  - - - - O -
//  - - - - - -
//  - - - - - -
//  - - - O - -
//
//AreaIds:
//  a a a a a a
//  b b b b b b
//  c c c c d d
//  e e e e d d
//  e e e e d d
//  f f f f f f
//
//
//  Example solution
//
//  ES EW WS ES EW WS
//  NE WS NS NS ES NW
//  ES NW NE NW NS --
//  NS ES EW WS NE WS
//  NS NS ES NS ES NW
//  NE NW NE EW NW --
//
//
//  Real assignment -- not done
