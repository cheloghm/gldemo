//
// Array Visualisation for CIS6007 WRIT1
//

#include <iostream>
#include <string>
#include <random>
#include "gl_stuff.h"
#include "Array2D.h"
#include <tbb/tbb.h>
#include <chrono>


using namespace std;
using namespace tbb;
using namespace std::chrono;


#pragma region Function Prototypes

void initPattern(Array2D<int>&array); // Initialise grid with "alive" and "dead" cell patterns
void update(void); // Main update function - apply Game of Life rules here
int validCells(int x, int y, int width, int height);
int CountLiveCell(int x, int y);

#pragma endregion



//
// Example array
//
Array2D<int>						myArray = Array2D<int>(50, 50);


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
void initPattern(Array2D<int>&array) {

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

	//3. Set cells randomly to be "dead" (0) or "alive" (1)
   parallel_for(
   	0,
   	myArray.w * myArray.h,
   	[&](int i) {

   		int x = i % myArray.w;
   		int y = i / myArray.h;
   		myArray(x, y) = iDist(mt);// (int)round(rDist(mt));
   	}
   );

   // set cells to test
#if 1

// Approach 1 - explicitly set each cell you want to be alive
	/*array(10, 10) = 1;
	array(11, 10) = 1;
	array(12, 10) = 1;
	array(9, 9) = 1;
	array(10, 9) = 1;
	array(11, 9) = 1;*/

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

int validCells(int x, int y, int width, int height) {		// checking for surrounding cells
	if (x >= 0 && x < width && y >= 0 && y < height) {
		return myArray(x, y);
	}
	else {
		return 0;
	}
}

int CountLiveCell(int x, int y) {		//counting neighbouring cells
	int a = validCells(x - 1, y - 1, myArray.w, myArray.h);
	int b = validCells(x, y - 1, myArray.w, myArray.h);
	int c = validCells(x + 1, y - 1, myArray.w, myArray.h);
	int d = validCells(x - 1, y, myArray.w, myArray.h);
	int e = validCells(x + 1, y, myArray.w, myArray.h);
	int f = validCells(x - 1, y + 1, myArray.w, myArray.h);
	int g = validCells(x, y + 1, myArray.w, myArray.h);
	int h = validCells(x + 1, y + 1, myArray.w, myArray.h);

	return a + b + c + d + e + f + g + h;
}

// Main update function - apply Game of Life rules here
// Note: This is called by FreeGLUT's main event loop - YOU DON'T NEED TO CALL THIS - IT'S CALLED FOR YOU!!!
void update(void) {

	//
	// *** ADD PARALLEL CODE HERE TO UPDATE GAME OF LIFE ***
	//
	static int times = 0;
	times++;

	Array2D<int>						myArrayB = Array2D<int>(50, 50);
	// first clearing the array (set all cells to "dead" ie. 0)
	parallel_for(
		0,
		myArrayB.w * myArrayB.h,
		[&](int i) {

			int x = i % myArrayB.w;
			int y = i / myArrayB.h;
			myArrayB(x, y) = 0;
		}
	);


	//for sequential version
	auto startTime = high_resolution_clock::now();
	for (int y = 0; y < myArray.h; y++) {
		//cout << "y = " << y << "\n";	//to know where y is
		for (int x = 0; x < myArray.w; x++) {

			int liveCells = CountLiveCell(x, y);
			if (myArray(x, y) == 1) {		// live cell

				if (liveCells < 2) {
					myArrayB(x, y) = 0;
				}
				else if (liveCells == 2 || liveCells == 3) {
					myArrayB(x, y) = 1;
				}
				else if (liveCells > 3) {
					myArrayB(x, y) = 0;
				}
			}
			else {							// dead cell

				myArrayB(x, y) = liveCells == 3 ? 1 : 0;
				if (liveCells == 3) {
					myArrayB(x, y) = 1;
				}
				else {
					myArrayB(x, y) = 0;
				}
			}
		}
	}
	auto endTime = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(endTime - startTime);
	cout << "Time Taken in Sequential version (" << times << ") = " << duration.count() << " microseconds\n";


	// for parallel version
	//auto startTime = high_resolution_clock::now();
	//parallel_for(
	//	blocked_range2d<int, int>(0, myArray.h, 0, myArray.w),
	//	[&](const blocked_range2d<int>& r) {
	//		for (int y = r.rows().begin(); y != r.rows().end(); y++) {
	//			for (int x = r.cols().begin(); x != r.cols().end(); x++) {

	//				int liveCells = CountLiveCell(x, y);
	//				if (myArray(x, y) == 1) {		// live cell

	//					myArrayB(x, y) = liveCells < 2 || liveCells > 3 ? 0 : 1;
	//				}
	//				else {							// dead cell

	//					myArrayB(x, y) = liveCells == 3 ? 1 : 0;
	//				}
	//			}
	//		}
	//	}
	//);
	//auto endTime = high_resolution_clock::now();

	//auto duration = duration_cast<microseconds>(endTime - startTime);
	//cout << "Time Taken in Parallel version (" << times << ") = " << duration.count() << " microseconds\n";

	myArray = myArrayB;


	// Redraw the screen to show latest generation
	renderLatestGeneration(myArray);
}
