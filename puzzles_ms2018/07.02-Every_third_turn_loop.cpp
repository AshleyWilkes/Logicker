// Textual description
//
//Draw a single loop that travels horizontally and vertically between centers of the adjacent cells. The loop visits all the unpainted cells and does not touch or intersect itself. Every third turn of the loop is marked.
//
//
//  Example assignment
//
//Width: 6
//Height: 6
//
//Grid: o for field with a mark, - for empty field
//
//  o - - - - -
//  - o - - - o
//  - - - o - o
//  - - - - o -
//  - - - - - -
//  - - - - - -
//
//
//  Example solution
//
//directions NESW in which the loop goes
//
//  ES EW WS ES EW WS
//  NS ES NW NS ES NW
//  NS NS ES NW NE WS
//  NS NS NE NW WS NS
//  NS NE EW EW NW NS
//  NE EW EW EW EW NW
//
//
//  Real assignment -- not done
