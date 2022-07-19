// Textual description
//
//Draw a snake in the grid passing through all the numbered cells. Head and tail of the snake are marked with darker background. The snake goes from cell to cell vertically or horizontally, but not diagonally. The snake does not touch itself, not even diagonally. The numbers arond the grid indicate the number of cells occupied by the snake in the corresponding row/column. Some of the snake cells are numbered. The numbers follow the sequence 123123123... from head to tail (1212... in the example). Each row and column contains each number exactly once.
//
//
//  Example assignment
//
//Width: 7
//Height: 7
//
//Head and tail: [3, 1], [6, 6]
//
//Grid:
//  - - - 1 - - -
//  - - - - - - -
//  1 - - - - - -
//  - - - 2 - - -
//  - 2 - - - - -
//  - - - - - 2 -
//  - - - - - - -
//
//Rows: 4 5 3 4 3 3 5
//Columns: 5 3 4 4 4 4 3
//
//
//  Example solution
//
//A digit or X for a cell with the snake, - for empty cell
//
//  - - - 1 2 X X
//  2 X X X - - 1
//  1 - - - - X 2
//  - - X 2 X 1 -
//  X 2 1 - - - -
//  X - - - 1 2 -
//  X 1 2 X X - -
//
//
//  Real assignment -- not done
