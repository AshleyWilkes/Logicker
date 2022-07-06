// Textual description
//
//Paint a triangle (diagonal half of the square) in some white cells. Some white cells may remain empty.
//A number in a gray cell indicates how many sides of triangles in orthogonally adjacent cells touch this cell.
//The remaining white space must form rectangular areas, oriented either horizontally, vertically or diagonally.
//Two white rectangles must not be orthogonally adjacent.
//
//
// Example assignment
//
//0 is a field which is empty in the assignment; positive number is a gray field with that number in it.
//
//2 0 0 3 0 0
//0 0 0 0 0 0
//0 0 0 0 0 0
//0 2 0 0 0 0
//0 0 0 0 0 0
//0 0 0 3 0 0
//
//
// Example solution
//
//0 is an empty field; positive number is a gray field with that number in it; negative numbers have the
//following meaning: -1 is black top left corner; -2 is black top right corner; -3 is black bottom right corner
//-4 is black bottom left corner; in other words -1 means North and West quarters of the field are black.
//
// 2 -1 -2  3 -1 -2
//-1  0 -3 -1  0 -3
//-4 -3  0 -4 -3  0
// 0  2  0 -1 -2  0
// 0 -1 -2 -4  0 -2
// 0 -4 -3  3 -4 -3
//
//
// Real assignment -- not done
//
//0 is a field which is empty in the assignment; positive number is a gray field with that number in it.
//Negative number signifies which small triangles (N: -1, E: -2, S: -4, N: -8) lie outside the grid.
//I.e. -15 is a field comletely outside, Hmm, tohle se musí víc promyslet...
//
