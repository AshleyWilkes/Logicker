// Textual description
//
//Place a digit from 1 to 9 into each white cell. The numbers in grey cells indicate the product of digits in the adjacent "word" across or down. (Across "words" are to the right of their products. Digits may not repeat within a "word".
//
//
//  Example assignment
//
//  width: 8
//  height: 7
//
//Now givens for some cells: [row, col]: [givenForRow, givenForColumn]
//  [1, 3]: [-, 2592]
//  [1, 4]: [-, 40]
//  [1, 6]: [-, 42]
//  [1, 7]: [-, 1344]
//  [2, 2]: [16, 288]
//  [2, 5]: [56, -]
//  [2, 8]: [-, 120]
//  [3, 1]: [40, -]
//  [3, 4]: [60, 8]
//  [4, 1]: [27, -]
//  [4, 4]: [48, 105]
//  [5, 1]: [90, -]
//  [5, 6]: [24, 24]
//  [6, 1]: [112, -]
//  [6, 5]: [12, -]
//  [7, 2]: [18, -]
//  [7, 5]: [28, -]
//
//
//  Example solution
//
//  - 2 8 - 7 8 -
//  8 1 5 - 3 4 5
//  3 9 - 8 2 1 3
//  6 3 5 1 - 3 8
//  2 8 7 - 6 2 1
//  - 6 3 - 4 7 -
//
//
//  Real assignment -- not done
