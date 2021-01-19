//
// Array Visualisation for CIS6007 WRIT1
//

#include <iostream>
#include <string>
#include <random>
#include "gl_stuff.h"
#include "Array2D.h"
#include <tbb/tbb.h>


using namespace std;
using namespace tbb;


#pragma region Function Prototypes

void initPattern(Array2D<int>& array); // Initialise grid with "alive" and "dead" cell patterns
void update(void); // Main update function - apply Game of Life rules here

#pragma endregion



//
// Example array
//
Array2D<int>	myArray = Array2D<int>(64, 64);


// Starting point for our program...
int main(int argc, char* argv[])
{
	// Initialise OpenGL window...
	gl_init(argc, argv, update, "CIS6007 WRIT1 - Game of Life Demo", true);

	// Initialise our Game of Life starting pattern...
	initPattern(myArray);

	// Start the main loop - this calls our update function (below) to update our game of life generations.
	// Note: We never return from glutMainLoop until we quit the application
	glutMainLoop();

    return 0;
}


// Initialise grid with "alive" and "dead" cell patterns
void initPattern(Array2D<int>& array) {

	// 1. First clear the array (set all cells to "dead" ie. 0)
	parallel_for(
		0,
		array.w * array.h,
		[&](int i) {

			int x = i % array.w;
			int y = i / array.h;
			array(x, y) = 0;
		}
	);

	// 2. Setup random number generator
	random_device						rd;
	mt19937								mt(rd());
	uniform_int_distribution<int>		iDist(0, 1);

	// 3. Set cells randomly to be "dead" (0) or "alive" (1)
	//parallel_for(
	//	0,
	//	myArray.w * myArray.h,
	//	[&](int i) {

	//		int x = i % myArray.w;
	//		int y = i / myArray.h;
	//		myArray(x, y) = iDist(mt);// (int)round(rDist(mt));
	//	}
	//);

#if 1

// Approach 1 - explicitly set each cell you want to be alive
	/*array(10, 10) = 1;
	array(11, 10) = 1;
	array(12, 10) = 1;
	array(9, 9) = 1;
	array(10, 9) = 1;
	array(11, 9) = 1;*/

	/*array(2, 2) = 1;
	array(2, 3) = 1;
	array(2, 4) = 1;
	array(1, 4) = 1;
	array(0, 3) = 1;*/

	/*array(2, 1) = 1;
	array(2, 3) = 1;
	array(3, 4) = 1;
	array(4, 4) = 1;
	array(5, 4) = 1;
	array(6, 4) = 1;
	array(6, 3) = 1;
	array(6, 2) = 1;
	array(5, 1) = 1;*/

	/*array(2, 1) = 1;
	array(2, 3) = 1;
	array(3, 4) = 1;
	array(4, 4) = 1;
	array(5, 4) = 1;
	array(6, 4) = 1;
	array(6, 3) = 1;
	array(6, 2) = 1;
	array(5, 1) = 1;*/

	array(1, 1) = 1;
	array(2, 1) = 1;
	array(1, 2) = 1;
	array(2, 2) = 1;
	array(3, 3) = 1;
	array(4, 3) = 1;
	array(3, 4) = 1;
	array(4, 4) = 1;

	/*array(1, 5) = 1;
	array(1, 6) = 1;
	array(2, 5) = 1;
	array(2, 6) = 1;

	array(11, 5) = 1;
	array(11, 6) = 1;
	array(11, 7) = 1;
	array(12, 4) = 1;
	array(12, 8) = 1;
	array(13, 3) = 1;
	array(13, 9) = 1;
	array(14, 3) = 1;
	array(14, 9) = 1;
	array(15, 6) = 1;
	array(17, 4) = 1;
	array(17, 8) = 1;
	array(18, 5) = 1;
	array(18, 6) = 1;
	array(18, 7) = 1;
	array(19, 6) = 1;

	array(22, 3) = 1;
	array(22, 4) = 1;
	array(22, 5) = 1;
	array(23, 3) = 1;
	array(23, 4) = 1;
	array(23, 5) = 1;
	array(24, 2) = 1;
	array(24, 6) = 1;
	array(26, 2) = 1;
	array(26, 6) = 1;
	array(26, 1) = 1;
	array(26, 7) = 1;

	array(36, 3) = 1;
	array(36, 4) = 1;
	array(37, 3) = 1;
	array(37, 4) = 1;*/



#else

	// Parallel for initialisation of cells...
	// NOTE: Uses 1D array approach, but can map single index to 2D coord if we know the width and height of the 2D array
	parallel_for(
		0,
		array.w * array.h,
		[&](int i) {

			int x = i % array.w;
			int y = i / array.h;

			// Example - checkerboard pattern
			if ((x & 0x01) == (y & 0x01))
				array(x, y) = 1;
		}
	);

#endif

	// NOTE: *** REPLACE STEP 3 WITH YOUR OWN CODE TO SETUP THE LIVE CELL PATTERNS
}


// Main update function - apply Game of Life rules here
// Note: This is called by FreeGLUT's main event loop - YOU DON'T NEED TO CALL THIS - IT'S CALLED FOR YOU!!!
void update(void) {

	//
	// *** ADD PARALLEL CODE HERE TO UPDATE GAME OF LIFE ***
	//
	Array2D<int>	myArrayB = Array2D<int>(64, 64);
	// 1. First clear the array (set all cells to "dead" ie. 0)
	parallel_for(
		0,
		myArrayB.w * myArrayB.h,
		[&](int i) {

		int x = i % myArrayB.w;
		int y = i / myArrayB.h;
		myArrayB(x, y) = 0;
	}
	);


	static int count = 25;

	count--;

	if (count == 0) {

	

	// for sequential version
	//for (int y = 0;y < myArray.h;y++) {
	//	//cout << "y = " << y << "\n";	//to know where y is
	//	for (int x = 0; x < myArray.w;x++) {
	//		int index = (y * myArray.h) + x;

	//		if (myArray(x, y) == 1) {		// live cell
	//					//cout << "Live Cell " << "\n";
	//			int liveCellCount = 0;

	//			if (y == 0) {	// first row
	//				if (x == 0) {	//first column
	//					/*if (myArray(x - 1, y - 1) == 1) {

	//					}
	//					if (myArray(x , y - 1) == 1) {

	//					}
	//					if (myArray(x + 1, y - 1) == 1) {

	//					}
	//					if (myArray(x - 1, y) == 1) {

	//					}*/
	//					if (myArray(x + 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x - 1, y + 1) == 1) {

	//					}*/
	//					if (myArray(x, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y + 1) == 1) {
	//						liveCellCount++;
	//					}

	//					myArrayB(x, y) = liveCellCount < 2 || liveCellCount>3 ? 0 : 1;
	//				}
	//				else if (x > 0 && x < myArray.w - 1) {	//middle columns
	//					/*if (myArray(x - 1, y - 1) == 1) {

	//					}
	//					if (myArray(x, y - 1) == 1) {

	//					}
	//					if (myArray(x + 1, y - 1) == 1) {

	//					}*/
	//					if (myArray(x - 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x - 1, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y + 1) == 1) {
	//						liveCellCount++;
	//					}

	//					myArrayB(x, y) = liveCellCount < 2 || liveCellCount>3 ? 0 : 1;
	//				}
	//				else if (x == myArray.w - 1) {		//last columns
	//					/*if (myArray(x - 1, y - 1) == 1) {

	//					}
	//					if (myArray(x, y - 1) == 1) {

	//					}
	//					if (myArray(x + 1, y - 1) == 1) {

	//					}*/
	//					if (myArray(x - 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x + 1, y) == 1) {

	//					}*/
	//					if (myArray(x - 1, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x + 1, y + 1) == 1) {

	//					}*/

	//					myArrayB(x, y) = liveCellCount < 2 || liveCellCount>3 ? 0 : 1;
	//				}
	//			}
	//			else if (y > 0 && y < myArray.h - 1) {	//middle rows
	//				if (x == 0) {		//first column
	//					/*if (myArray(x - 1, y - 1) == 1) {

	//					}*/
	//					if (myArray(x, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x - 1, y) == 1) {

	//					}*/
	//					if (myArray(x + 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x - 1, y + 1) == 1) {

	//					}*/
	//					if (myArray(x, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y + 1) == 1) {
	//						liveCellCount++;
	//					}

	//					myArrayB(x, y) = liveCellCount < 2 || liveCellCount>3 ? 0 : 1;
	//				}
	//				else if (x > 0 && x < myArray.w - 1) {		//middle columns
	//					if (myArray(x - 1, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x - 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x - 1, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y + 1) == 1) {
	//						liveCellCount++;
	//					}

	//					myArrayB(x, y) = liveCellCount < 2 || liveCellCount>3 ? 0 : 1;
	//				}
	//				else if (x == myArray.w - 1) {		//last columns
	//					if (myArray(x - 1, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x + 1, y - 1) == 1) {

	//					}*/
	//					if (myArray(x - 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x + 1, y) == 1) {

	//					}*/
	//					if (myArray(x - 1, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x + 1, y + 1) == 1) {

	//					}*/

	//					myArrayB(x, y) = liveCellCount < 2 || liveCellCount>3 ? 0 : 1;
	//				}
	//			}
	//			else if (y == myArray.h - 1) {		//last row
	//				if (x == 0) {		//first column
	//					/*if (myArray(x - 1, y - 1) == 1) {

	//					}*/
	//					if (myArray(x, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x - 1, y) == 1) {

	//					}*/
	//					if (myArray(x + 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x - 1, y + 1) == 1) {

	//					}
	//					if (myArray(x, y + 1) == 1) {

	//					}
	//					if (myArray(x + 1, y + 1) == 1) {

	//					}*/

	//					myArrayB(x, y) = liveCellCount < 2 || liveCellCount>3 ? 0 : 1;
	//				}
	//				else if (x > 0 && x < myArray.w - 1) {		//middle columns
	//					if (myArray(x - 1, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x - 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x - 1, y + 1) == 1) {

	//					}
	//					if (myArray(x, y + 1) == 1) {

	//					}
	//					if (myArray(x + 1, y + 1) == 1) {

	//					}*/

	//					myArrayB(x, y) = liveCellCount < 2 || liveCellCount>3 ? 0 : 1;
	//				}
	//				else if (x == myArray.w - 1) {		//last column
	//					if (myArray(x - 1, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x + 1, y - 1) == 1) {

	//					}*/
	//					if (myArray(x - 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x + 1, y) == 1) {

	//					}
	//					if (myArray(x - 1, y + 1) == 1) {

	//					}
	//					if (myArray(x, y + 1) == 1) {

	//					}
	//					if (myArray(x + 1, y + 1) == 1) {

	//					}*/

	//					myArrayB(x, y) = liveCellCount < 2 || liveCellCount>3 ? 0 : 1;
	//				}
	//			}
	//		}
	//		else {							// dead cell
	//			//cout << "Dead Cell ";

	//			// because dead cells need three neighbours to be live, we need to consider eight cells 
	//			// surrounding cells which would be 
	//			//	a   b   c
	//			//	d (x,y) e
	//			//	f   g   h
	//			// (x-1,y-1), (x,y-1), (x+1,y-1), (x-1,y), (x+1,y), (x-1,y+1), (x,y+1), (x+1,y+1)

	//			int liveCellCount = 0;
	//			if (y == 0) {	// first row
	//				if (x == 0) {	//first column
	//					/*if (myArray(x - 1, y - 1) == 1) {

	//					}
	//					if (myArray(x , y - 1) == 1) {

	//					}
	//					if (myArray(x + 1, y - 1) == 1) {

	//					}
	//					if (myArray(x - 1, y) == 1) {

	//					}*/
	//					if (myArray(x + 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x - 1, y + 1) == 1) {

	//					}*/
	//					if (myArray(x, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y + 1) == 1) {
	//						liveCellCount++;
	//					}

	//					if (liveCellCount == 3) {
	//						myArrayB(x, y) = 1;
	//					}
	//				}
	//				else if (x > 0 && x < myArray.w - 1) {	//middle columns
	//					/*if (myArray(x - 1, y - 1) == 1) {

	//					}
	//					if (myArray(x, y - 1) == 1) {

	//					}
	//					if (myArray(x + 1, y - 1) == 1) {

	//					}*/
	//					if (myArray(x - 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x - 1, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y + 1) == 1) {
	//						liveCellCount++;
	//					}

	//					if (liveCellCount == 3) {
	//						myArrayB(x, y) = 1;
	//					}
	//				}
	//				else if (x == myArray.w - 1) {		//last columns
	//					/*if (myArray(x - 1, y - 1) == 1) {

	//					}
	//					if (myArray(x, y - 1) == 1) {

	//					}
	//					if (myArray(x + 1, y - 1) == 1) {

	//					}*/
	//					if (myArray(x - 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x + 1, y) == 1) {

	//					}*/
	//					if (myArray(x - 1, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x + 1, y + 1) == 1) {

	//					}*/

	//					if (liveCellCount == 3) {
	//						myArrayB(x, y) = 1;
	//					}
	//				}
	//			}
	//			else if (y > 0 && y < myArray.h - 1) {	//middle rows
	//				if (x == 0) {		//first column
	//					/*if (myArray(x - 1, y - 1) == 1) {

	//					}*/
	//					if (myArray(x, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x - 1, y) == 1) {

	//					}*/
	//					if (myArray(x + 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x - 1, y + 1) == 1) {

	//					}*/
	//					if (myArray(x, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y + 1) == 1) {
	//						liveCellCount++;
	//					}

	//					if (liveCellCount == 3) {
	//						myArrayB(x, y) = 1;
	//					}
	//				}
	//				else if (x > 0 && x < myArray.w - 1) {		//middle columns
	//					if (myArray(x - 1, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x - 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x - 1, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y + 1) == 1) {
	//						liveCellCount++;
	//					}

	//					if (liveCellCount == 3) {
	//						myArrayB(x, y) = 1;
	//					}
	//				}
	//				else if (x == myArray.w - 1) {		//last columns
	//					if (myArray(x - 1, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x + 1, y - 1) == 1) {

	//					}*/
	//					if (myArray(x - 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x + 1, y) == 1) {

	//					}*/
	//					if (myArray(x - 1, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x, y + 1) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x + 1, y + 1) == 1) {

	//					}*/

	//					if (liveCellCount == 3) {
	//						myArrayB(x, y) = 1;
	//					}
	//				}
	//			}
	//			else if (y == myArray.h - 1) {		//last row
	//				if (x == 0) {		//first column
	//					/*if (myArray(x - 1, y - 1) == 1) {

	//					}*/
	//					if (myArray(x, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x - 1, y) == 1) {

	//					}*/
	//					if (myArray(x + 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x - 1, y + 1) == 1) {

	//					}
	//					if (myArray(x, y + 1) == 1) {

	//					}
	//					if (myArray(x + 1, y + 1) == 1) {

	//					}*/

	//					if (liveCellCount == 3) {
	//						myArrayB(x, y) = 1;
	//					}
	//				}
	//				else if (x > 0 && x < myArray.w - 1) {		//middle columns
	//					if (myArray(x - 1, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x - 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x + 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x - 1, y + 1) == 1) {

	//					}
	//					if (myArray(x, y + 1) == 1) {

	//					}
	//					if (myArray(x + 1, y + 1) == 1) {

	//					}*/

	//					if (liveCellCount == 3) {
	//						myArrayB(x, y) = 1;
	//					}
	//				}
	//				else if (x == myArray.w - 1) {		//last column
	//					if (myArray(x - 1, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					if (myArray(x, y - 1) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x + 1, y - 1) == 1) {

	//					}*/
	//					if (myArray(x - 1, y) == 1) {
	//						liveCellCount++;
	//					}
	//					/*if (myArray(x + 1, y) == 1) {

	//					}
	//					if (myArray(x - 1, y + 1) == 1) {

	//					}
	//					if (myArray(x, y + 1) == 1) {

	//					}
	//					if (myArray(x + 1, y + 1) == 1) {

	//					}*/

	//					if (liveCellCount == 3) {
	//						myArrayB(x, y) = 1;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}


	// for parallel version
	parallel_for(
		blocked_range2d<int, int>(0, myArray.h, 0, myArray.w),
		[&](const blocked_range2d<int>& r) {
			for (int y = r.rows().begin(); y != r.rows().end(); y++) {
				for (int x = r.cols().begin(); x != r.cols().end(); x++) {

					if (myArray(x, y) == 1) {		// live cell
						//cout << "Live Cell " << "\n";
						int liveCellCount = 0;

						if (y == 0) {	// first row
							if (x == 0) {	//first column
								/*if (myArray(x - 1, y - 1) == 1) {

								}
								if (myArray(x , y - 1) == 1) {

								}
								if (myArray(x + 1, y - 1) == 1) {

								}
								if (myArray(x - 1, y) == 1) {

								}*/
								if (myArray(x + 1, y) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x - 1, y + 1) == 1) {

								}*/
								if (myArray(x, y + 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y + 1) == 1) {
									liveCellCount++;
								}

								myArrayB(x, y) = liveCellCount < 2 || liveCellCount>3 ? 0 : 1;
							}
							else if (x > 0 && x < myArray.w - 1) {	//middle columns
								/*if (myArray(x - 1, y - 1) == 1) {

								}
								if (myArray(x, y - 1) == 1) {

								}
								if (myArray(x + 1, y - 1) == 1) {

								}*/
								if (myArray(x - 1, y) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y) == 1) {
									liveCellCount++;
								}
								if (myArray(x - 1, y + 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x, y + 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y + 1) == 1) {
									liveCellCount++;
								}

								myArrayB(x, y) = liveCellCount < 2 || liveCellCount>3 ? 0 : 1;
							}
							else if (x == myArray.w - 1) {		//last columns
								/*if (myArray(x - 1, y - 1) == 1) {

								}
								if (myArray(x, y - 1) == 1) {

								}
								if (myArray(x + 1, y - 1) == 1) {

								}*/
								if (myArray(x - 1, y) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x + 1, y) == 1) {

								}*/
								if (myArray(x - 1, y + 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x, y + 1) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x + 1, y + 1) == 1) {

								}*/

								myArrayB(x, y) = liveCellCount < 2 || liveCellCount>3 ? 0 : 1;
							}
						}
						else if (y > 0 && y < myArray.h - 1) {	//middle rows
							if (x == 0) {		//first column
								/*if (myArray(x - 1, y - 1) == 1) {

								}*/
								if (myArray(x, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y - 1) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x - 1, y) == 1) {

								}*/
								if (myArray(x + 1, y) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x - 1, y + 1) == 1) {

								}*/
								if (myArray(x, y + 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y + 1) == 1) {
									liveCellCount++;
								}

								myArrayB(x, y) = liveCellCount < 2 || liveCellCount>3 ? 0 : 1;
							}
							else if (x > 0 && x < myArray.w - 1) {		//middle columns
								if (myArray(x - 1, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x - 1, y) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y) == 1) {
									liveCellCount++;
								}
								if (myArray(x - 1, y + 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x, y + 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y + 1) == 1) {
									liveCellCount++;
								}

								myArrayB(x, y) = liveCellCount < 2 || liveCellCount>3 ? 0 : 1;
							}
							else if (x == myArray.w - 1) {		//last columns
								if (myArray(x - 1, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x, y - 1) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x + 1, y - 1) == 1) {

								}*/
								if (myArray(x - 1, y) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x + 1, y) == 1) {

								}*/
								if (myArray(x - 1, y + 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x, y + 1) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x + 1, y + 1) == 1) {

								}*/

								myArrayB(x, y) = liveCellCount < 2 || liveCellCount>3 ? 0 : 1;
							}
						}
						else if (y == myArray.h - 1) {		//last row
							if (x == 0) {		//first column
								/*if (myArray(x - 1, y - 1) == 1) {

								}*/
								if (myArray(x, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y - 1) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x - 1, y) == 1) {

								}*/
								if (myArray(x + 1, y) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x - 1, y + 1) == 1) {

								}
								if (myArray(x, y + 1) == 1) {

								}
								if (myArray(x + 1, y + 1) == 1) {

								}*/

								myArrayB(x, y) = liveCellCount < 2 || liveCellCount>3 ? 0 : 1;
							}
							else if (x > 0 && x < myArray.w - 1) {		//middle columns
								if (myArray(x - 1, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x - 1, y) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x - 1, y + 1) == 1) {

								}
								if (myArray(x, y + 1) == 1) {

								}
								if (myArray(x + 1, y + 1) == 1) {

								}*/

								myArrayB(x, y) = liveCellCount < 2 || liveCellCount>3 ? 0 : 1;
							}
							else if (x == myArray.w - 1) {		//last column
								if (myArray(x - 1, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x, y - 1) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x + 1, y - 1) == 1) {

								}*/
								if (myArray(x - 1, y) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x + 1, y) == 1) {

								}
								if (myArray(x - 1, y + 1) == 1) {

								}
								if (myArray(x, y + 1) == 1) {

								}
								if (myArray(x + 1, y + 1) == 1) {

								}*/

								myArrayB(x, y) = liveCellCount < 2 || liveCellCount>3 ? 0 : 1;
							}
						}
					}
					else {							// dead cell
						//cout << "Dead Cell ";

						// because dead cells need three neighbours to be live, we need to consider eight cells 
						// surrounding cells which would be 
						//	a   b   c
						//	d (x,y) e
						//	f   g   h
						// (x-1,y-1), (x,y-1), (x+1,y-1), (x-1,y), (x+1,y), (x-1,y+1), (x,y+1), (x+1,y+1)

						int liveCellCount = 0;
						if (y == 0) {	// first row
							if (x == 0) {	//first column
								/*if (myArray(x - 1, y - 1) == 1) {

								}
								if (myArray(x , y - 1) == 1) {

								}
								if (myArray(x + 1, y - 1) == 1) {

								}
								if (myArray(x - 1, y) == 1) {

								}*/
								if (myArray(x + 1, y) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x - 1, y + 1) == 1) {

								}*/
								if (myArray(x, y + 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y + 1) == 1) {
									liveCellCount++;
								}

								if (liveCellCount == 3) {
									myArrayB(x, y) = 1;
								}
							}
							else if (x > 0 && x < myArray.w - 1) {	//middle columns
								/*if (myArray(x - 1, y - 1) == 1) {

								}
								if (myArray(x, y - 1) == 1) {

								}
								if (myArray(x + 1, y - 1) == 1) {

								}*/
								if (myArray(x - 1, y) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y) == 1) {
									liveCellCount++;
								}
								if (myArray(x - 1, y + 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x, y + 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y + 1) == 1) {
									liveCellCount++;
								}

								if (liveCellCount == 3) {
									myArrayB(x, y) = 1;
								}
							}
							else if (x == myArray.w - 1) {		//last columns
								/*if (myArray(x - 1, y - 1) == 1) {

								}
								if (myArray(x, y - 1) == 1) {

								}
								if (myArray(x + 1, y - 1) == 1) {

								}*/
								if (myArray(x - 1, y) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x + 1, y) == 1) {

								}*/
								if (myArray(x - 1, y + 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x, y + 1) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x + 1, y + 1) == 1) {

								}*/

								if (liveCellCount == 3) {
									myArrayB(x, y) = 1;
								}
							}
						}
						else if (y > 0 && y < myArray.h - 1) {	//middle rows
							if (x == 0) {		//first column
								/*if (myArray(x - 1, y - 1) == 1) {

								}*/
								if (myArray(x, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y - 1) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x - 1, y) == 1) {

								}*/
								if (myArray(x + 1, y) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x - 1, y + 1) == 1) {

								}*/
								if (myArray(x, y + 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y + 1) == 1) {
									liveCellCount++;
								}

								if (liveCellCount == 3) {
									myArrayB(x, y) = 1;
								}
							}
							else if (x > 0 && x < myArray.w - 1) {		//middle columns
								if (myArray(x - 1, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x - 1, y) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y) == 1) {
									liveCellCount++;
								}
								if (myArray(x - 1, y + 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x, y + 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y + 1) == 1) {
									liveCellCount++;
								}

								if (liveCellCount == 3) {
									myArrayB(x, y) = 1;
								}
							}
							else if (x == myArray.w - 1) {		//last columns
								if (myArray(x - 1, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x, y - 1) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x + 1, y - 1) == 1) {

								}*/
								if (myArray(x - 1, y) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x + 1, y) == 1) {

								}*/
								if (myArray(x - 1, y + 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x, y + 1) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x + 1, y + 1) == 1) {

								}*/

								if (liveCellCount == 3) {
									myArrayB(x, y) = 1;
								}
							}
						}
						else if (y == myArray.h - 1) {		//last row
							if (x == 0) {		//first column
								/*if (myArray(x - 1, y - 1) == 1) {

								}*/
								if (myArray(x, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y - 1) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x - 1, y) == 1) {

								}*/
								if (myArray(x + 1, y) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x - 1, y + 1) == 1) {

								}
								if (myArray(x, y + 1) == 1) {

								}
								if (myArray(x + 1, y + 1) == 1) {

								}*/

								if (liveCellCount == 3) {
									myArrayB(x, y) = 1;
								}
							}
							else if (x > 0 && x < myArray.w - 1) {		//middle columns
								if (myArray(x - 1, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x - 1, y) == 1) {
									liveCellCount++;
								}
								if (myArray(x + 1, y) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x - 1, y + 1) == 1) {

								}
								if (myArray(x, y + 1) == 1) {

								}
								if (myArray(x + 1, y + 1) == 1) {

								}*/

								if (liveCellCount == 3) {
									myArrayB(x, y) = 1;
								}
							}
							else if (x == myArray.w - 1) {		//last column
								if (myArray(x - 1, y - 1) == 1) {
									liveCellCount++;
								}
								if (myArray(x, y - 1) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x + 1, y - 1) == 1) {

								}*/
								if (myArray(x - 1, y) == 1) {
									liveCellCount++;
								}
								/*if (myArray(x + 1, y) == 1) {

								}
								if (myArray(x - 1, y + 1) == 1) {

								}
								if (myArray(x, y + 1) == 1) {

								}
								if (myArray(x + 1, y + 1) == 1) {

								}*/

								if (liveCellCount == 3) {
									myArrayB(x, y) = 1;
								}
							}
						}
					}
				}
			}
		}
	);
	myArray = myArrayB;

	count = 25;
	}
	
	
	// Redraw the screen to show latest generation
	renderLatestGeneration(myArray);
}
