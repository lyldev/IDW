#include "MyPoint.h"
#include "IDW.h"

int main()
{
	IDW mIDW = IDW();
	vector<MyPoint> grid = mIDW.CreateGrid();
	vector<MyPoint> discretePoints = mIDW.CreateDiscretePoints();

	mIDW.Interpolate(grid, discretePoints, 2, 20);
}