// Textual description
//
//Draw a single path that travels horizontally and vertically between centers of the adjacent cells. The path visits all the unpainted cells and does not touch or intersect itself. Every third turn of the path (from either side) is marked.
//
//
//  Example assignment
//
//Width: 5
//Height: 5
//
//Grid: X for field not in the grid, o for field with a mark, - for empty field
//
//  X o - - -
//  X - - o -
//  - - o - -
//  - - - - o
//  - - X X X
//
//
//  Example solution
//
//XX for field not in the grid, for path field directions NESW in which the path goes
//
//  XX ES WS ES WS
//  XX NS NE NW NS
//  ES NE ES WS NS
//  NS ES NW NE NW
//  -N -N XX XX XX
//
//
//  Real assignment -- not done
