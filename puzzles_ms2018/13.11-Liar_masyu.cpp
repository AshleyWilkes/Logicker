// Textual description
//
//Draw a single loop that travels horizontally and vertically between centers of some cells such that the loop does not visit any cell more than once. At every cell containing a white circle the loop must pass straight through that circle and make a 90 degree turn in at least one of the cells adjacent to the circle. At every cell containing a black circle the loop must make a 90 degree turn and travel straight through both cells adjacent to the circle.
//The circles are not in their correct positions however. To be able to solve the puzlle you have to move every circle to a horizontally of vertically adjacent cell first. The circles may not overlap after they are all shifted. But the circle can move to a position previously occupied by another circle. To score the points only the loop is required.
//
//
//  Example assignment
//
//Size: 4
//
//Grid:
//  - O - B
//  - - - -
//  - - - -
//  O B O -
//
//
//  Example solution
//
//  -- -- -- --
//  ES EW EW WS
//  NS -- -- NS
//  NE EW EW NW
//
//
//  Real assignment -- not done
