// Textual description
//
//Blacken some cells in the grid so that blackened cells do not touch each other from the sides. All remaining cells (except the grey cells) should be traversed by a single continuous loop, moving horizontally and vertically. Clues inside the grid indicate the number of blackened cells in the corresponding directions. There may exist some blackened cells that are not pointed by any arrow.
//
//
//  Example assignment
//
//Width: 5
//Height: 5
//
//Hints:
//A number and direction (NESW) is given for some cells
//
//  [1, 1]: 2E
//  [4, 4]: 1W
//
//
//  Example solution
//
// -- for a cell with a hint, BB for blackened cell, directions (NEWS) where loop goes for loop cells
//
//  -- BB ES WS BB
//  ES WS NS NE WS
//  NS NE NW BB NS
//  NE WS BB -- NS
//  BB NE EW EW NW
//
//
//  Real assignment -- not done
