#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define ABS(x) (x > 0 ? x : -(x))
#define CONVERGENCE 0.5

struct point
{
	double x;									// Assuming 2 attributes
	double y;
	int cluster;
};

void print_clusters(struct point *points, struct point *clusters, int k, int n)
{
	int i, j;

	for(i = 0; i < k; i++)
	{
		printf("Cluster #%d: x = %f y = %f\n", i, clusters[i].x, clusters[i].y);
		for(j = 0; j < n; j++)
			if(points[j].cluster == i)
				printf("x = %f y = %f\n", points[j].x, points[j].y);
		printf("-----------------------------\n");
	}
}

int main(int argc, char **argv)
{
	double sumx, sumy, dist, mindist, avgx, avgy;
	int n, k, i, j, count, mincluster, val, itrs, flag;
	scanf("%d%d", &n, &k);									//total points & k
	struct point points[n], clusters[k];

	for(i = 0; i < n; i++)
		scanf("%lf%lf", &points[i].x, &points[i].y);		//points (x,y)

	for(i = 0; i < n; i++)
		printf("x = %f y = %f\n", points[i].x, points[i].y);

	for(i = 0; i < k; i++)
	{
		val = random() % n;
		clusters[i].x = points[val].x;
		clusters[i].y = points[val].y;
		clusters[i].cluster = i;
	}

	for(i = 0; i < k; i++)
		printf("Cluster #%d: x = %f y = %f\n", i, clusters[i].x, clusters[i].y);

	itrs = 0;
	do
	{
		for(i = 0; i < n; i++)
		{
			mindist = DBL_MAX;
			for(j = 0; j < k; j++)
			{
				dist = ABS(clusters[j].x - points[i].x) + ABS(clusters[j].y - points[i].y);
				if(mindist > dist)
				{
					mindist = dist;
					mincluster = j;
				}
			}
			points[i].cluster = mincluster;
		}
	
		flag = 0;
		for(i = 0; i < k; i++)
		{
			count = sumx = sumy = 0;
			for(j = 0; j < n; j++)
			{
				if(points[j].cluster == i)
				{
					count++;
					sumx = sumx + points[j].x;
					sumy = sumy + points[j].y;
				}
			}
			if(count)
			{
				avgx = sumx / count;
				avgy = sumy / count;
				if(!flag && (pow(clusters[i].x - avgx, 2) + pow(clusters[i].y - avgy, 2) > pow(CONVERGENCE, 2)))
					flag = 1;

				clusters[i].x = avgx;
				clusters[i].y = avgy;
			}
		}

		printf("After iteration %d :\n", ++itrs);
		print_clusters(points, clusters, k, n);
	}while(flag);

	return 0;
}
