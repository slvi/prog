
public class KMeans 
{

	public static void main(String[] args) {
		int data[]={2,4,-10,12,3,20,30,11,25,17,23};    // initial data
		int noofclusters=3;
		int centroid[][]=new int[][]{
			{0,0,0},
			{2,4,10}
		};
		getCentroid(data,noofclusters,centroid);
		
	}

	public static int[][] getCentroid(int data[],int noofclusters,int centroid[][]){
		
		int distance[][]=new int[noofclusters][data.length];
		int cluster[]=new int[data.length];
		int clusternodecount[]=new int[noofclusters];
		
		centroid[0]=centroid[1];
		centroid[1]=new int[]{0,0,0};
		System.out.println("========== Starting to get new centroid =========");
		
		for(int i=0;i<noofclusters;i++){
			for(int j=0;j<data.length;j++){
				distance[i][j]=Math.abs(data[j]-centroid[0][i]);
				System.out.print(distance[i][j]+" ,");				
			}
			System.out.println();
		}
		
		for(int j=0;j<data.length;j++){
			int smallerDistance=0;
			if(distance[0][j]<distance[1][j] && distance[0][j]<distance[2][j])
				smallerDistance=0;
			if(distance[1][j]<distance[0][j] && distance[1][j]<distance[2][j])
				smallerDistance=1;
			if(distance[2][j]<distance[0][j] && distance[2][j]<distance[1][j])
				smallerDistance=2;
			
			centroid[1][smallerDistance]=centroid[1][smallerDistance]+data[j];
			clusternodecount[smallerDistance]=clusternodecount[smallerDistance]+1;
			cluster[j]=smallerDistance;			
		}
		System.out.println("New centroid is ");
		
		for(int j=0;j<noofclusters;j++){
			centroid[1][j]=centroid[1][j]/clusternodecount[j];
			System.out.print(centroid[1][j]+",");
		}
		System.out.println();
		
		boolean isAchived=true;
		for(int j=0;j<noofclusters;j++){
			if(isAchived && centroid[0][j] == centroid[1][j]){
				isAchived=true;
				continue;
			}
			isAchived=false;
		}
		
		if(!isAchived){
			getCentroid(data,noofclusters,centroid);
		}
		
		if(isAchived){
			System.out.println("======================================== ");
			System.out.println(" Final Cluster is ");
			for(int i=0;i<noofclusters;i++){				
				for(int j=0;j<data.length;j++){
					if(cluster[j]==i)
						System.out.print(data[j]+" ,");
					
				}
				System.out.println();
			}
		}
		
		return centroid;
		
	}
}

/*
OUTPUT:

========== Starting to get new centroid =========
0 ,2 ,12 ,10 ,1 ,18 ,28 ,9 ,23 ,15 ,21 ,
2 ,0 ,14 ,8 ,1 ,16 ,26 ,7 ,21 ,13 ,19 ,
8 ,6 ,20 ,2 ,7 ,10 ,20 ,1 ,15 ,7 ,13 ,
New centroid is 
-1,4,19,
========== Starting to get new centroid =========
3 ,5 ,9 ,13 ,4 ,21 ,31 ,12 ,26 ,18 ,24 ,
2 ,0 ,14 ,8 ,1 ,16 ,26 ,7 ,21 ,13 ,19 ,
17 ,15 ,29 ,7 ,16 ,1 ,11 ,8 ,6 ,2 ,4 ,
New centroid is 
-10,5,21,
========== Starting to get new centroid =========
12 ,14 ,0 ,22 ,13 ,30 ,40 ,21 ,35 ,27 ,33 ,
3 ,1 ,15 ,7 ,2 ,15 ,25 ,6 ,20 ,12 ,18 ,
19 ,17 ,31 ,9 ,18 ,1 ,9 ,10 ,4 ,4 ,2 ,
New centroid is 
-10,6,23,
========== Starting to get new centroid =========
12 ,14 ,0 ,22 ,13 ,30 ,40 ,21 ,35 ,27 ,33 ,
4 ,2 ,16 ,6 ,3 ,14 ,24 ,5 ,19 ,11 ,17 ,
21 ,19 ,33 ,11 ,20 ,3 ,7 ,12 ,2 ,6 ,0 ,
New centroid is 
-10,6,23,
======================================== 
 Final Cluster is 
-10 ,
2 ,4 ,12 ,3 ,11 ,
20 ,30 ,25 ,17 ,23 ,

*/
