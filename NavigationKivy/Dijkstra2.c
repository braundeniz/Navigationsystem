// Der Algorithmus von Dijkstra


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//define city names for the dijkstra algorithm so you can write the names into the dijkstra2() and dijkstra3() function
#define KARLSRUHE 0 
#define STUTTGART 1
#define MANNHEIM  2
#define PFORZHEIM 3
#define RASTATT   4
#define BADENBADEN 5
#define FREIBURG 6
#define OFFENBURG 7
#define KEHL 8
#define FREUDENSTADT 9
#define REUTLINGEN 10 
#define TUEBINGEN 11
#define ULM 12
#define LOERRACH 13
#define KONSTANZ 14

#define ANZAHL 15

//define not directly connected nodes as 10000 so dijkstra does not misunderstand it as a "short path"
//should be much greater than greatest distance in matrix
#define xxx 10000

//declare array of strings containing city names
char cities[ANZAHL][ANZAHL] = {
	"Karlsruhe",      //1
	"Stuttgart",      //2
	"Mannheim",       //3
	"Pforzheim",      //4
	"Rastatt",        //5
	"Baden-Baden",    //6
	"Freiburg",       //7
	"Offenburg",      //8
    "Kehl",           //9
	"Freudenstadt",   //10
	"Reutlingen",     //11
	"Tuebingen",       //12
	"Ulm",            //13
	"Loerrach",        //14
	"Konstanz"        //15
};


//adjacency matrix of the graph
unsigned int adistance[ANZAHL][ANZAHL] ={ 
  // 1   2   3   4   5   6   7   8   9  10  11  12  13  14  15 
	0  ,xxx,71 ,30 ,27 ,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx, //1
    xxx,0  ,133,49 ,xxx,xxx,xxx,xxx,xxx,81 ,40 ,44 ,93 ,xxx,xxx, //2
    71 ,133,0  ,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx, //3
    30 ,49 ,xxx,0  ,xxx,xxx,xxx,xxx,xxx,65 ,xxx,xxx,xxx,xxx,xxx, //4
    27 ,xxx,xxx,xxx,0  ,14 ,xxx,55 ,54 ,65 ,xxx,xxx,xxx,xxx,xxx, //5
    xxx,xxx,xxx,xxx,14 ,0  ,xxx,52 ,xxx,55 ,xxx,xxx,xxx,xxx,xxx, //6
    xxx,xxx,xxx,xxx,xxx,xxx,0  ,67 ,xxx,94 ,xxx,xxx,xxx,73 ,125, //7
    xxx,xxx,xxx,xxx,55 ,52 ,67 ,0  ,18 ,50 ,xxx,xxx,xxx,xxx,xxx, //8
    xxx,xxx,xxx,xxx,54 ,xxx,xxx,18 ,0  ,xxx,xxx,xxx,xxx,xxx,xxx, //9
    xxx,81 ,xxx,65 ,65 ,55 ,94 ,50 ,xxx,0  ,xxx,61 ,xxx,xxx,xxx, //10
	xxx,40 ,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx,0  ,15 ,73 ,xxx,129, //11
    xxx,44 ,xxx,xxx,xxx,xxx,xxx,xxx,xxx,61 ,15 ,0  ,xxx,xxx,128, //12
    xxx,93 ,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx,73 ,xxx,0  ,xxx,125, //13
	xxx,xxx,xxx,xxx,xxx,xxx,73 ,xxx,xxx,xxx,xxx,xxx,xxx,0  ,142, //14
	xxx,xxx,xxx,xxx,xxx,xxx,125,xxx,xxx,xxx,129,128,125,142,  0  //15
};


int dist;


char done[ANZAHL];
int distanz[ANZAHL];
int predecessor[ANZAHL];



//print path with end node -> Needed for first part of 3 point route and for 2 point route
void print_path2(int i)
{	
	//recursion of print_path -> if function has found a city with no predecessor, print starting point and jump to stack adress of previous function  call until done
	if (predecessor[i] != -1) {
		print_path2(predecessor[i]); 
		//print path
		printf(" ->(%dkm)-> ", adistance[i][predecessor[i]]); 
		printf(cities[i]);
	}
	else{
		printf(cities[i]); //print starting point
	}
		
}
//print path without end node -> needed for second part of 3 point route
void print_path(int i)
{	
	//recursion of print_path -> if function has found a city with no predecessor, print starting point and jump to stack adress of previous function call until done
	if (predecessor[i] != -1) {
		print_path(predecessor[i]);
		
		//cout << " ->" <<"("<<adistance[i][predecessor[i]]<<"km)-> "; 
		printf(" ->(%dkm)-> ", adistance[i][predecessor[i]]);
		printf(cities[i]);
	}
		
}

//writing distance from starting point to every node from the graph into the n_info class
//mark starting point as done initalizing and having no predecessor 
void init(int start_n){
	for (int i = 0; i < ANZAHL; i++) {
		done[i] = 0; //mark nodes as unvisited
		distanz[i] = adistance[start_n][i]; //write distance from adjacency matrix to n_info.distance
		predecessor[i] = start_n;  //mark starting point as predecessor
	}
	done[start_n] = 1;  //mark start node as done
	predecessor[start_n] = -1; //start node has no predecessor
}

int node_select(){
	int min = xxx;  //set minimum distance to a high value (at least equal or greater than maximum distance in adjacency matrix)
	int node_minpos = -1; //set node with the least distance to -1 for showing, that there hasn't been a node yet
	for (int i = 0; i < ANZAHL; i++) {
		//sort nodes after distance and return node with the least distance to the predecessor
		if (distanz[i] < min && !done[i]) {
			min = distanz[i];
			node_minpos = i;
		}
	}
	return node_minpos;
}


//calculate shortest path for every combination with the starting point
void dijkstra(int start_n){
	
	
	init(start_n);
	for (int i = 0; i < ANZAHL - 1; i++) { //ANZAHL-1 because you dont need to calculate minimal distance to the starting point itself
		int node = node_select();  //iterate through nodes and begin with node with the least distance from starting point
		done[node] = 1; //mark visited note as done
		for (int k = 0; k < ANZAHL; k++) {
			// if node was not visited yet, calculate minimum distance to every other node(if there is one),add it to the total distance and mark node as predecessor (????????)
			if (!(done[k] == 1)) {
				int d = distanz[node] + adistance[node][k];
				//if dijkstra found a shorter total path, write it into n_info[k].distance and mark the node as predecessor
				if (d < distanz[k]) {
					distanz[k] = d;
					predecessor[k] = node;
				}
			}
		}
	}
}
//dijkstra with additional node 
int dijkstra3(int start_n,int over_n,int end_n){

	int error=0; //initialize error as zero in case there was no error


	//check if start node,connection node and end node is equal. If yes, error=1 and print error message
	if ((start_n==end_n)&&(end_n==over_n)){
		printf("Es konnte keine Route berechnet werden!\nFehler: Startpunkt,Zwischenpunkt und Endpunkt sind identisch! END \n");
		error=1;
	//check if start node, or end node is equal to connection node. If yes, dont print connection node. -> No error though
	}else if ((start_n==over_n)||(end_n==over_n)){
		//printf("Die kürzeste Route von "<< cities[start_n]<<" nach "<<cities[end_n]<<" ist: \n\n" ;
		printf("Die kuerzeste Route von  %s nach %s ist: \n\n" ,cities[start_n],cities[end_n]) ;
	//Else print following message:
	}else{
		//cout<< "Die kürzeste Route von "<< cities[start_n]<<" über "<<cities[over_n]<<" nach "<<cities[end_n]<<" ist: \n\n";
		printf( "Die kuerzeste Route von %s ueber %s nach %s ist: \n\n", cities[start_n],cities[over_n],cities[end_n]);
	}

	//In case there was no error
	if (error == 0){
		dijkstra(start_n); //Dijkstra algorithm for start node ->calculates min distance to all nodes 
		print_path2(over_n); //Only print path to the connection node (first destination)
		int dist1=distanz[over_n]; //dist1 is the distance of the first part of the route

		dijkstra(over_n); //Dijkstra algorithm for the connection node
		print_path(end_n); //Only print path to the end node without the connection node because it has already been printed on the first path
		int dist2=distanz[end_n]; //dist2 is the distance of the second part of the route

		printf("\n\nGesamtdistanz: %d km \n\n\n",dist1+dist2) ; //print total distance
		
	}

}
//dijkstra with no additional node

int dijkstra2(int start_n,int end_n){
	int dist2=0;
	
	//print error message if start node equals end node
	if (start_n==end_n){
		//cout<< "Es konnte keine Route berechnet werden! \nFehler: Startpunkt und Endpunkt sind identisch";
		printf("Es konnte keine Route berechnet werden! \nFehler: Startpunkt und Endpunkt sind identisch");
	//else print following message:
	}else{
		//cout<< "Die kürzeste Route von "<< cities[start_n]<<" nach "<<cities[end_n]<<" ist: \n\n" ;
		printf( "Die kuerzeste Route von %s nach %s ist: \n\n", cities[start_n], cities[end_n]);

		//same as in function above -> only one dijkstra needed 
		dijkstra(start_n);
		print_path2(end_n);
		//cout << "\n\nGesamtdistanz: " << distanz[end_n] << "km" << endl;
		printf("\n\nGesamtdistanz: %d km  \n\n\n",distanz[end_n]) ;
	}
	
 

}
int main(){
	
	return 0;
	
}

