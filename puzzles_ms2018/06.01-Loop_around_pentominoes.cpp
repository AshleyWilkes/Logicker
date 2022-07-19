// Textual description
//
//Paint some cells black. The black cells form pentominoes. One cell from each pentomino is already given. The cell is marked with the letter corresponding to the shape of the pentomino. The pentominoes may not touch each other, not even by a corner. Then draw a single continuous loop travelling horizontally or vertically between centers of adjacent cells through all the unpainted cells.
//
//
//  Example assignment
//
//Width: 7
//Height: 5
//
//Now give the grid: x for field that are not part of the grid, - for a field that is initially empty, pentomino letter for fields with letters
//
//  x - - - - x x
//  x - Z - - - -
//  - - - - - - -
//  - - - - - - -
//  - - - - - x x
//
//
//  Example solution
//
//All fields with a pentomino contain the pentomino letter twice. Loop field contain the directions NESW in which there is the loop segment. xx for a field not part of the grid.
//
//  xx ES EW EW WS xx xx
//  xx NS zz zz NE EW WS
//  ES WN zz ES EW WS NS
//  NS zz zz NE WS NE NW
//  NE EW EW EW NW xx xx
//
//
//  Real assignment -- not done
