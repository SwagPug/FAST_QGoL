#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;




int neighbors=0;
int currentx=0,currenty=0;

int main(){

	int size=30;

	int matrix[size][size];
	int previous[size][size];

	
	char filename[21];
	int maxgen=0;
	int currentgen=1;
	int population=0;

	cout<<"Enter file name : ";	
	cin>>filename;

	ifstream myfile(filename);

	if (!myfile.is_open()){
	cout<<"Failure\n";
	exit(0);}
	
	for (int i=0;i<30;i++){

		for (int j=0; j<30; j++){
			myfile>>matrix[i][j];
			previous[i][j]=matrix[i][j];
			if (matrix[i][j])
				population++;
		}	
	}

	myfile.close();

	
	cout<<"Enter number of generations to run : ";
	cin>>maxgen;
	
	
	//now we will use matrix as a base.
	
	while (currentgen<=maxgen){
	
		usleep(60000);
		system("clear");
	
		cout<<"Current Generation : "<<currentgen<<endl;
		cout<<"Total Population : "<<population<<endl;
		
		population=0;
	
		for (currenty=0; currenty<30; currenty++){
			
			for (currentx=0; currentx<30; currentx++){
			
				//count neighbors:
				neighbors=0;
				
				//neighbors on sides
				if (previous[currenty-1][currentx] && currenty-1>=0 )
					neighbors++;	
				if (previous[currenty+1][currentx] && currenty+1<30)
					neighbors++;
				if (previous[currenty][currentx-1] && currentx-1>=0)
					neighbors++;
				if (previous[currenty][currentx+1] && currentx+1<30)
					neighbors++;
					
				//neighbors on diagonals
				if (previous[currenty-1][currentx-1] && currentx-1>=0 && currenty-1>=0)
					neighbors++;
				if (previous[currenty-1][currentx+1] && currentx+1<30 && currenty-1>=0)
					neighbors++;
				if (previous[currenty+1][currentx-1] && currentx-1>=0 && currenty+1<30)
					neighbors++;
				if (previous[currenty+1][currentx+1] && currentx+1<30 && currenty+1<30)
					neighbors++;				
					
				
				if ((neighbors==2 || neighbors==3) && previous[currenty][currentx]){
					matrix[currenty][currentx]=1;
					continue;}
				
				if (neighbors>3 && previous[currenty][currentx]){
					matrix[currenty][currentx]=0;
					continue;}
				
				if (neighbors<2 && previous[currenty][currentx]){
					matrix[currenty][currentx]=0;
					continue;}
					
				if (neighbors==3 && !previous[currenty][currentx]){
					matrix[currenty][currentx]=1;
				}
					
				
					
			}	
			
		}
		
		//here, a generation has been simulated. now we increment the generation number.
		//but first, output to terminal and the file:
		
		ofstream myfile(filename);
		
		for (int i=0; i<30; i++){
		
			for (int j=0; j<30; j++){
			
				myfile << matrix[i][j]<<' ';
			
				
				cout<<" ";
				
				//cout<<matrix[i][j];
				
				//if alive, output o
				if (matrix[i][j]){
					cout<<'o';
					population++;	
				}
				else
					cout<<'.';
					
				if (matrix[i][j])
					previous[i][j]=1;
				else previous[i][j]=0;
					
			}
			cout<<endl;
			myfile<<endl;
		}
		
		currentgen++;
	}
	
	myfile.close();

return 0;}
