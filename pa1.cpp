#include <iostream>
using namespace std;

void printMagic (int precutMagic[][15],int n, int squareNum){
	int magic[n][n];	//function prints square with spacing and adds
						//and displays all sums
	cout << endl << "Magic square #" << squareNum << " is: \n" << endl;
	for (int j = 0; j < n; j++){
			for (int i = 0; i < n; i++){
				magic[i][j] = precutMagic[i][j];
				if (i < n-1){
					if (n > 3 && n < 10){
						if (magic[i][j] < 10){
							cout << " ";
						}
					}
					else if (n > 10){
						if (magic[i][j] < 100){
							cout << " ";
						}
						if(magic[i][j]< 10){
							cout << " ";
						}
					}
					cout<< magic[i][j] << " ";
				}
				
				else{
					if (n > 3 && n < 10){
						if (magic[i][j] < 10){
							cout << " ";
						}
					}
				else if (n > 10){
					if (magic[i][j] < 100){
						cout << " ";
					}
					if(magic[i][j]<10){
						cout << " ";
					}
				}
					 cout<< magic[i][j] << endl;
				 }
			}
		} 
	int rowSum = 0;
	int colSum = 0;
	int fdiagSum = 0;
	int bdiagSum = 0;
	cout << endl << "Checking sums of every row:         "; 
	for (int j = 0; j<n; j++){
		rowSum = 0;
		for (int i = 0; i < n; i++){
			rowSum = rowSum + magic[i][j];
			if (i == j){
				fdiagSum += magic[i][j];
			}
			if (i == (n-1)-j){
				bdiagSum += magic[i][j];
			}
		}
		cout<< " " << rowSum;
	}
	cout << endl << "Checking the sums of every column:  ";
	for (int i = 0; i<n; i++){
		colSum = 0;
		for (int j = 0; j < n; j++){
			colSum = colSum + magic[i][j];
		}
		cout<< " " << colSum;
	}
	
	
	cout << endl << "Checking the sums of every diagonal: "<<
		fdiagSum << " " << bdiagSum << endl;	
	}

int main()
{
	
	int n = 0;
	double tries;
	while (n == 0){
		cout << "Enter the size of a magic square: ";
		cin >> tries;
		if (tries != (int)tries){
			cout << "number picking error" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else if (tries < 16 && tries > 2 && (int)tries %2 == 1){
			n = (int)tries;
		}
		
		else{
			cout << "number picking error" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} 
	
	int magic[n][n];
	for (int i = 0; i < n; i++){
		for (int j = 0; j<n; j++){
			magic[j][i] = 0;
		}
	}
	
	//https://www.math.hmc.edu/funfacts/ffiles/10001.4-8.shtml# 
	//web source for algorithm used below
	
	int newRow,
			newCol;

  int i= (n / 2);
  int j =0 ;

  for ( int value = 1; value <= n*n; value++ )
  {
     magic[i][j] = value;
     newCol = (i + 1) % n;
     newRow = (n + j - 1) % n;
     if ( magic[newCol][newRow] == 0 )
     {
        i = newCol;
        j = newRow;
     }
     else
     {
        j = (j + 1 + n) % n;
     }

  }
	//
	int newMagic[n][15];
	for (int i = 0; i < 15; i++){
		for (int j = 0; j<n; j++){
			if (i<n){
			newMagic[j][i] = magic[j][i];
			}
		}
	}
	printMagic(newMagic,n,1);
	//
	
	int magic2[n][n];
	for (int j = 0; j < n;j++){
		for (int i  = 0; i < n;i++){
			magic2[i][n-j - 1] = magic[i][j];
		} 
	}
	for (int i = 0; i < 15; i++){
		for (int j = 0; j<n; j++){
			if (i<n){
			newMagic[j][i] = magic2[j][i];
			}
		}
	}
	printMagic(newMagic,n,2);
	//
	
	int magic3[n][n];
	for (int j = 0; j < n;j++){
		for (int i  = 0; i < n;i++){
			magic3[n-i - 1][j] = magic[i][j];
		}
	}
	for (int i = 0; i < 15; i++){
		for (int j = 0; j<n; j++){
			if (i<n){
			newMagic[j][i] = magic3[j][i];
			}
		}
	}
	printMagic(newMagic,n,3);
	//
return 0;
}
