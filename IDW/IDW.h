#include <iostream>
#include <vector>
#include "MyPoint.h"
using namespace std;

#pragma once

class IDW
{
public:
	IDW();
	~IDW(void);

	vector<MyPoint> CreateGrid();
	vector<MyPoint> CreateDiscretePoints();
	void IDW::Interpolate(vector<MyPoint> gg, vector<MyPoint> dd, int pp = 2, int rr = 10);

};

