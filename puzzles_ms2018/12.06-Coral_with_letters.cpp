// Textual description
//
//Blacken some of the cells in the grid to create a coral. All black cells in the coral must be orthogonally connected. There must be no 2x2 squares of black cells. And all white cells must be connected to the edge of the grid. Then place letters A, B, C in the painted cells so that each letter appears exactly once in each row and column. The hints around the grid show all the letters that can be found on the first coral segment from the given side, in correct order (from top to bottom resp. from left to right. Dash means there is no letter on the first segment.
//
//
//  Example assignment
//
//Letters: A, B
//
//Size: 5
//
//Rows:
//  AB -
//  BA BA
//  BA BA
//  BA -
//  AB AB
//
//Columns:
//  A B
//  B A
//  B A
//  AB -
//  - AB
//
//
//  Example solution
//
//A,B for coral fields with appropriate letters, X for coral fields with no letter, - for empty fields
//
//  A B - X X
//  - X B A -
//  - - - B A
//  B A - - X
//  - X A X B
//
//
//  Real assignment -- not done
