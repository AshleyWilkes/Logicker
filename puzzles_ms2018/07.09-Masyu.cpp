// Textual description
//
//Draw a single loop that travels horizontally and vertically between centers of some cells such that the loop does not visit any cell more than once. At every cell containing a white circle the loop must pass straight through that circle and make a 90 degree turn in at least one of the cells adjacent to the circle. At every cell containing a black circle the loop must make a 90 degree turn and travel straight through both cells adjacent to that circle. Shaded cells cannot be used by the loop.
//
//
//  Example assignment
//
//Width: 6
//Height: 6
//
//Grid:
//O for white circles, B for black circles, X for shaded cells (not present in the example)
//
//  - - - - - -
//  - - B B - -
//  - - - - - -
//  O O - - - B
//  - - - - - -
//  - - O - - -
//
//
//  Example solution
//
//  ES EW EW EW EW WS
//  NE EW WS ES EW NW
//  ES WS NS NS -- --
//  NS NS NS NE EW WS
//  NS NE NW ES WS NS
//  NE EW EW NW NE NW
//
//
//  Real assignment -- not done
