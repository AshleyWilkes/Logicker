// Textual description
//
//Draw a closed loop through the grid, connecting the centers of cells horizontally and vertically. The loop runs through all boldly marked areas once (it means that there is a single entry and exit). Two adjacent cells in different areas cannot both be unused by the loop. The numbers in the grid indicate how many cells in that region the loop runs through.
//
//
//  Example assignment
//
//Width: 6
//Height: 6
//
//AreaIds:
//
//  1 1 1 1 2 2
//  1 1 3 3 4 2
//  5 3 3 4 4 2
//  5 3 4 4 6 6
//  5 3 4 6 6 6
//  5 5 6 6 6 6
//
//Area hints:
//  1: 2
//  2: 3
//
//
//  Example solution
//
//  -- -- ES EW EW WS
//  -- -- NS -- ES NW
//  ES EW NW ES NW --
//  NS -- ES NW ES WS
//  NS -- NE EW NW NS
//  NE EW EW EW EW NW
//  
//
//  Real assignment -- not done
