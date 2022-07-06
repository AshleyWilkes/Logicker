// Textual description
//
//Place some of the given words in the grid following the rules of scrabble. The words may be entered only horizontally from top to botton or vertically from left to right, one letter per cell. The words may cross each other, but you are not allowed to create any other words (2 letters or more long) than the ones on the list. All the words must be orthogonally connected. All the cells where the words are crossing are given and you have to use all of them. Some letter are given as well.
//
//
//  Example assignment
//
//First given words are given:
//  ANDY
//  FRANK
//  HENRY
//  JOHN
//  PAUL
//
//The grid is rectangle, first it's width and height are given
//
//  width: 6
//  height: 6
//
//Now for some fields we get given letter and/or the fact it is a crossing; when nothing is given, we're not given the letter and the cells doesn't contain a crossing. Format: [row, column] - {0/1 - 1 for crossing, letter or nothing}
//
//  [1, 3] - 1
//  [4, 3] - 1, R
//  [4, 5] - 1
//
//  
//  Example solution
//
//For each field a letter or a dash is given; dash stands for no letter
//
//  J O H N - -
//  - - E - - -
//  - - N - A -
//  - F R A N K
//  - - Y - D -
//  - - - - Y -
//
//
//  Real assignment -- not done
