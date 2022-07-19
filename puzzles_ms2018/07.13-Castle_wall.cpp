// Textual description
//
//Draw a single closed loop (without intersections or crossings) passing through some empty cells in the grid. The grid contains some bordered or colored cells that cannot be part of the loop. Black cells must be outside the loop; white cells with heavy borders must be inside the loop. For grey cells the information is unknown. Numbers and arrows refer to the total sum of the lengths of the segments in the given direction.
//
//
//  Example assignment
//
//Width: 6
//Height: 6
//
//Hints:
//  For hinted cell a color is always given: W for white with black borders, B for black, G for grey; also a number and a direction (NESW) may be given.
//
//  [1, 1]: G0S
//  [2, 4]: B1S
//  [3, 2]: B
//  [4, 5]: G2N
//  [5, 3]: W
//  [6, 6]: G2W
//
//
//  Example solution
//
//  -- -- -- -- ES WS
//  -- -- -- -- NS NS
//  -- -- ES EW NW NS
//  -- ES NW -- -- NS
//  -- NS -- ES EW NW
//  -- NE EW NW -- --
//
//
//  Real assignment -- not done
