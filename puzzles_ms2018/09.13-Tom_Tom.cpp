// Textual description
//
//Place a digit from 1 to 9, resp. 1 to 6 into each cell so that no digit repeats in any row or column. Also, the number in the upper=left corner of each bold cage indicates the value of a mathematical operation (addition, subtraction, multiplication, division) applied successively to all digits in the cage, starting with the largest digit for subtraction and division (e.g. 1,2,4 with subtraction is a 1- clue as 4 - 2 -1 = 1). The operation may or may not be given in the cage, but at least one of the four operations must apply. If only an operation is given (not number), the result of the operation must be a whole number greater or equal to 0. Digits can repeat within a cage.
//
//
//  Example assignment
//
//Size: 6
//
//AreaIds:
//   1  1  2  2  3  3
//   1  1  4  5  3  3
//   6  4  4  5  5  7
//   6  8  8  9  9  7
//  10 10  8  9 11 11
//  10 10 12 12 11 11
//
//Area hints:
//  1: 11
//  2: 3/
//  3: 200
//  4: 4+
//  6: 10*
//  7: 24*
//  9: 7+
// 10: 17
// 11: 0
// 12: 8+
//
//
// Example solution
// 1 3 6 2 4 5
// 3 4 1 6 5 2
// 5 1 2 4 3 6
// 2 6 3 5 1 4
// 6 5 4 1 2 3
// 4 2 5 3 6 1
//
//
// Real assignment -- not done
