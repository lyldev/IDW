#include "IDW.h"

IDW::IDW()
{
}


IDW::~IDW(void)
{
}

// ���ɸ�����
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

// ���������ɢ��
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

// �������Ȩ��ֵ
void IDW::Interpolate(vector<MyPoint> gg, vector<MyPoint> dd, int pp, int rr) //grid,discrete,power,radius
{
	vector<MyPoint>::iterator it_g, it_d;
	// ��ÿһ��դ���
	for(it_g=gg.begin(); it_g!=gg.end(); it_g++) 
	{
		vector<MyPoint> near_pnts;
		vector<double> dists;

		// ��ȡ�����뾶�ڵ���ɢ�㼰�����
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

		// ���뷴��֮��
		double sum = 0;
		for(it_dist=dists.begin(); it_dist!=dists.end(); it_dist++)
		{
			double inv = 1 / *it_dist;  // inverse
			sum += pow(inv, pp);
		}

		// ÿ�����Ȩ�أ�����ֵ
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