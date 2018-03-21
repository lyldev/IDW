#include "IDW.h"

IDW::IDW()
{
}


IDW::~IDW(void)
{
}

// 生成格网点
vector<MyPoint> IDW::CreateGrid()
{
	vector<MyPoint> grid;
	for(double yi = 0; yi <= 100; yi += 10)
	{
		for(double xi = 0; xi <= 100; xi += 10)
		{
			MyPoint c(xi, yi);
			grid.push_back(c);
		}
	}
	return grid;
}

// 生成随机离散点
vector<MyPoint> IDW::CreateDiscretePoints()
{
	vector<MyPoint> DiscretePnts;
	srand(1);
	for(int i=0; i<150; i++)
	{
		double x = rand()/(double)RAND_MAX*100;
		double y = rand()/(double)RAND_MAX*100;
		double z = rand()/(double)RAND_MAX*1000;
		//cout<<"rand:"<<x<<","<<y<<","<<z<<endl;

		MyPoint pnt(x, y, z);
		DiscretePnts.push_back(pnt);
	}
	return DiscretePnts;
}

// 反距离加权插值
void IDW::Interpolate(vector<MyPoint> gg, vector<MyPoint> dd, int pp, int rr) //grid,discrete,power,radius
{
	vector<MyPoint>::iterator it_g, it_d;
	// 对每一个栅格点
	for(it_g=gg.begin(); it_g!=gg.end(); it_g++) 
	{
		vector<MyPoint> near_pnts;
		vector<double> dists;

		// 获取给定半径内的离散点及其距离
		for(it_d=dd.begin(); it_d!=dd.end(); it_d++)
		{
			double dist = sqrt(pow(it_g->x - it_d->x, 2) + pow(it_g->y - it_d->y, 2));
			if(dist <= rr)
			{
				near_pnts.push_back(*it_d);
				dists.push_back(dist);
			}
		}

		vector<MyPoint>::iterator it_n;
		vector<double>::iterator it_dist;

		// 距离反比之和
		double sum = 0;
		for(it_dist=dists.begin(); it_dist!=dists.end(); it_dist++)
		{
			double inv = 1 / *it_dist;  // inverse
			sum += pow(inv, pp);
		}

		// 每个点的权重，并插值
		double z = 0;
		for(it_dist=dists.begin(),it_n=near_pnts.begin(); it_dist!=dists.end(); it_dist++,it_n++)
		{
			double inv = 1 / *it_dist;  // inverse
			double Weight = pow(inv, pp) / sum;
			//Weights.push_back(Weight);

			z += it_n->z * Weight;
		}

		it_g->z = z;
		cout<< "(" << it_g->x << "," << it_g->y << "," << it_g->z << ")" <<endl;
	}

}