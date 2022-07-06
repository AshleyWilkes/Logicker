// Textual description
//
//For given N draw squares of sizes from 1x1 to NxN in the grid. The borders of squares do no overlap, nor touch in corner, bt they can cross each other. The numbers indicate the sum of the square sizes of all the squares covering the cell.
//
//
//  Example assignment
//
//Fir give N
//
//  N: 4
//
//Now give number in the grid; 0 for no given
//
//  0 0 0 0 0 0
//  0 0 7 0 0 0
//  0 0 0 0 5 0
//  0 0 0 0 0 0
//  0 0 0 6 0 0
//  0 0 0 0 0 0
//
//
//  Example solution
//
//Each square is considered to be an area; their ids are powers of 2. For each field the sum of all areas containg that cell is given; 0 for cells no squares contain
//
//   1  1  1  0  0  0
//   1  1  3  2  2  2
//   1  1  3  2  6  2
//   0  0  2  2  2  2
//   0  0  2 10 10  2
//   0  0  0  8  8  0
//
//
//   Real assignment -- not done
