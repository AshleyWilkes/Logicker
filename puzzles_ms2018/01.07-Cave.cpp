// Textual description
//
//Blacken some cells in the grid so that a cave system is formed which has the following properties: All the cave cells (the white cells) are orthogonally connected. ALl the walls (the black cells) are connected with the border of the grid, that is, there are no walls which are completely surrounded by white cells. Cells with numbers must not be blackened. Each number indicates how many cave cells are horizontally ar vertically visible from that position, including the cell with the number itself.
//
//
//  Example assignment
//
//0 for a field with no number given, other ints indicate the given number for thar cell
//
//  5 0 0 0 0 2
//  0 0 0 0 0 0
//  0 5 0 0 2 0
//  3 0 0 0 0 0
//  0 0 0 0 0 3
//  0 0 0 6 0 0
//
//
//  Example solution
//
//0 for white field, 1 for blackened field
//
//  0 0 0 0 1 0
//  0 0 0 0 0 0
//  1 0 0 1 0 1
//  0 0 0 1 1 1
//  1 1 0 1 0 0
//  0 0 0 0 0 0
//
//
//  Real assignment -- not done
