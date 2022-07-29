// Textual description
//
//Draw 2 snakes in the grid.
//The snake goes from cell to cell vertically or horizontally, but not diagonally. The snake does not touch itself, not even diagonally. The numbers outside the grid indicate how many squares are used by the snake in that row or column. The two snakes cannot touch each other not even diagonally except for the crossings. At the crossings both snakes must go straight (cross each other).
//The heads and tails are marked, but you have to learn their pairing. All the crossings between the two snakes are marked as well.
//The numbers on the right indicate the number of cells occupied by one snake. The numbers below indicate the number of cells occupied by the other snake.
//
//
//  Example assignment
//
//Size: 6
//
//Heads, tails: 
//  [1,3], [1,5], [4,6], [6,5]
//
//Crossings:
//  [2,3], [4,3]
//
//Right hints (Snake: B):
//  1 1 1 1 1 3
//
//Bottom hints (Snake: A):
//  3 2 2 2 3 1
//
//
//  Example solution
//  - for empty cells, + for crossings, AB for single snake cells
//
//  - - B - A -
//  A A + A A -
//  A - B - - -
//  A A + A A A
//  - - B - - -
//  - - B B B -
//
//
//  Real assignment -- not done
