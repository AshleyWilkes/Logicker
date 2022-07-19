// Textual description
//
//Locate the given fleet in the grid. The ships cannot touch each other, not even diagonally. The ships may be rotated. The clues outside the grid indicate the number of ship cells in the corresponding directions. Ships may not be placed on the cells with fish.
//Each ship contains a fisherman. His position is given, but the ship can be rotated.
//Fishermen are fishing the fish in the grid. Each fisherman has caught exactly one fish. The number in the fisherman cell denotes the length of the fishing line (in units of cell size) starting in the center of a cell with the number and fishing in the center of a cell with the fish. The fishing lines travel horizontally and vertically, may not touch each other. All the cells are used either by ships, fish or fishing rods.
//
//
//  Example assignment
//
//The fleet: each boat is given as a sequence of digits: 0 for empty boat cell, positive number for a boat cell with a fisherman
//
//  1 0 0
//  5 0
//  5 0
//  3
//  6
//  6
//
//Width: 6
//Height: 6
//
//Now grid: - for empty cell, F for a cell with a fish
//
//  - - F - F -
//  - - F - - -
//  - - - - - -
//  - F F - - -
//  - - - - - -
//  - - F - - -
//
//Rows: 3 1 3 0 2 1
//Columns: 2 1 2 2 2 1
//
//
//  Example solution
//
//A digit is given for a cell with a boat, F for a cell with a fish, directions in which the fishing line travels for a cell with a fishing line
//
//  -0 ES -F -3 -F -6
//  -5 NS -F NE NW NS
//  NE NW -1 -0 -0 NS
//  ES -F -F EW EW NW
//  NS -5 -0 ES EW WS
//  NE NW -F NW -6 NW
//
//
//  Real assignment -- not done
