// Textual description
//
//Place numbers from 1-N in some cells so that they do not repeat in rows and columns. One cell in every row and column will remain empty.
//In the skyscraper puzzle the numbers represent height of the buildings. The numbers around the grid would indicate the number of buildings you can see from the given viewpoint. The building is visible only when it is higher that all the buildings in front of it.
//In the As Easy As ABC puzzle the numbers around the grid would indicate the first number visible from the given viewpoint.
//The hints around the grid are sums of the Skyscraper and As Easy As ABC hints.
//
//
//  Example assignment
//
//Size and N
//
//  N: 4
//  size: 5
//
//  Now sums of hints are given as pairs for each row and column
//
//  Rows: [5, 5], [5, 5], [5, 4], [5, 3], [5, 5]
//  Columns: [4, 5], [5, 4], [4, 4], [4, 5], [5, 4]
//
//
//  Example solution
//
//  - 4 1 2 3
//  1 2 3 - 4
//  3 - 4 1 2
//  2 3 - 4 1
//  4 1 2 3 -
//
//
//  Real assignment -- not done
