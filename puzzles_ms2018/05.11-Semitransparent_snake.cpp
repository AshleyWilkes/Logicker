// Textual description
//
//Draw a snake in the grid. The snake goes from cell to cell vertically or horizontally, but not diagonally.
//The snake does not touch itself, not even horizontally. The numbers outside the grid indicate how many squares are used by the snake in that row or column.
//In this puzzle however every time the snake goes 4 or more cells in a straight line (counting from Start) every fourth cell along that line is invisible and is not counted.
//
//
//  Example assignment
//
//  size: 6
//
//Start and end
//  Start: [6, 1]
//  End: [5, 3]
//
//Givens as single ints, since they do not depend on the direction you look at the grid
//
//  Rows: 4 3 1 3 2 1
//  Column: 4 2 2 2 1 3
//
//
//  Example solution
//
//  - x x x x x
//  x x - - - x
//  x - - - - x
//  x - x x x x
//  x - x - - -
//  x - - - - -
//
//
//  Real assignment -- not done
