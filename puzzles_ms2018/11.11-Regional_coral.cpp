// Textual description
//
//Blacken some of the cells in the grid to create a coral. All black cells in the coral must be orthogonally connected. And all white cells must be connected to the edge of the grid. The numbers on the edge indicate the lengths of successive blocks of coral cells, but not necessarily in the correct order. There must be at least one blank cell between two blocks.
//All the regions contain the same number of black cells.
//
//
//  Example assignment
//
//Size: 6
//Rows:
//  1
//  -
//  1 1
//  2 2
//  -
//  3
//
//Columns:
//  4
//  -
//  1 2
//  1 1
//  -
//  3
//
//AreaIds:
//  a a a b b b
//  a a a b b b
//  c c c d d d
//  c c c d d d
//  e e e f f f
//  e e e f f f
//
//
//  Example solution
//  X - - - - -
//  X - X X X X
//  X - - - - X
//  X X - - X X
//  - X X - X -
//  - - X X X -
//
//  
//  Real assignment -- not done
