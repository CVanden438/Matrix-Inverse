
// Matrix Inverse
// Reads in a matrix from a file and calculates its inverse using the gaussian elimination method
// then writes its inverse out to another file

//---------------------------------------------------------Includes-------------------------------------------------
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
//------------------------------------------------------------------------------------------------------------------

// Removes need to type std::
using namespace std;

//-------------------------------------------------------MAIN PROGRAM-----------------------------------------------
int main() {

	//------------------------------------------------DECLARING VARIABLES-------------------------------------------
	// 2D vector to store matrix
	vector< vector<double> > data;
	vector< vector<double> > id;
	// 1D vector to store each line of matrix
	vector <double> idtemp;
	vector <double> temp;
	// 1D vector to store rows of matrix for row swaps
	vector <double> swaptemp;
	vector <double> swapidtemp;
	// Variabled used in reading in data
	string Num, line, FirstNum;
	int length, j, CommaPos, FirstCommaPos, k, tsize;
	// Variables used in creating identity matrix
	double idA, idB;
	double id1pos = 0;
	// Variables used in finding inverse
	double i, c;
	double a = 0;
	int z = 1;
	double num1;
	double num2;
	//-------------------------------------------------------------------------------------------------------------


	//------------------------------------------------READING IN MATRIX--------------------------------------------
	ifstream theFile("Matrix.txt");
	// Opens the file
	if (theFile.is_open()) {
		// Loops through each line until the end of the file
		while (!theFile.eof()) {
			// Gets each line of the file and sets it to variable 'line'
			getline(theFile, line);
			// Adds the first number from each line to the 1D temp vector, this is done as each line doesn't start with a comma
			FirstCommaPos = line.find(',', 0);
			FirstNum = line.substr(0, FirstCommaPos);
			temp.push_back(atof(FirstNum.c_str()));
			// Loops through every character in each line
			for (int i = 0; i < line.length(); i++) {
				if (line[i] == ',') {
					// Gets here if character is a ','
					// Finds the next comma after the comma i is currently on
					CommaPos = line.find(',', i + 1);
					// Finds the length of the number between the 2 commas
					length = CommaPos - i + 1;
					// Sets the number to the variable Num
					Num = line.substr(i + 1, length);
					// Adds the number to the end of the 1D vctor
					temp.push_back(atof(Num.c_str()));
				}
			}
			// Gets here once it reaches the end of each line
			// Adds the 1D vector (which has all the numbers of the line sepereated into its elements) to the end of the 2D vector
			data.push_back(temp);
			// Finds how many elements are in each line (aka how many numbers in each line)
			tsize = temp.size();
			// Clears the 1D vector so the next line can now be stored in it without the previous line already being there
			temp.clear();
		}
		// Closes te file
		theFile.close();
	}
	else {
		// Gets here if it can't open the file
		cout << "Error\n";
		exit(1);
	}
	//----------------------------------------------------------------------------------------------------------------

	if (tsize == data.size()) {
		// Checks if matrix has same number of rows and columns

		//----------------------------------------------CREATING IDENTITY MATRIX--------------------------------------
		for (idB = 0; idB < tsize; idB++) {
			// Loop to create the same amount of columns as data matrix
			for (idA = 0; idA < tsize; idA++) {
				// Loop to create the same amount of rows as data matrix
				if (idA == id1pos) {
					// Will only add a 1 if the current position is in the trace of the matrix
					idtemp.push_back(1);
				}
				else {
					// Adds a 0 otherwise
					idtemp.push_back(0);
				}
			}
			// The position of the 1 is increased by 1 for each row
			id1pos++;
			// Adds each row to a 2D vector to create the matrix
			id.push_back(idtemp);
			// Clears the temp vector after each row
			idtemp.clear();
		}
		//------------------------------------------------------------------------------------------------------------


		//-------------------------------------------------FINDING INVERSE--------------------------------------------
		for (k = 0; k < tsize; k++) {
			// Loops over each column of the matrix
			if (data[k][k] == 0) {
				// Checks if the number in the trace element of each column is 0
				// If it is 0 then need to switch the row with the first row containing a non 0 number in the same column underneath it
				for (a = 0; a < tsize; a++) {
					// Stores the row in a vector so it can be swapped with another row
					swaptemp.push_back(data[k][a]);
					swapidtemp.push_back(id[k][a]);
				}
				for (double o = k; o < tsize; o++) {
					// Checks each element under the 0 to find the first non 0
					if (data[o][k] == 0) {
						// Stops it from doing anything if it finds a 0
					}
					else {
						if (z == 1) {
							// z variable used to stop it from swapping rows again once it swaps the row with other one
							for (double e = 0; e < tsize; e++) {
								// Swaps the row with the first non 0 row it finds
								id[k][e] = id[o][e];
								id[o][e] = swapidtemp[e];
								data[k][e] = data[o][e];
								data[o][e] = swaptemp[e];
								z = 0;
							}
						}
					}
				}
				z = 1;
				// Clears the vector containing the swapping row so it can be used again
				swaptemp.clear();
				swapidtemp.clear();
			}
			// Now that the trace element is ensured to not be 0, divide the row by that element to make it equal to 1
			// Stores the trace element of the column in num1
			num1 = data[k][k];
			for (i = 0; i < tsize; i++) {
				// Divides the entire row by the trace element
				id[k][i] = id[k][i] / num1;
				data[k][i] = data[k][i] / num1;
			}
			// Now that the trace element in the column is 1, use it as a pivot, making the other elements in that column 0
			for (j = 0; j < tsize; j++) {
				// Loops over each row
				num2 = data[j][k];
				// In order to make the other elements in the column 0, multiply the pivot row by the number in the pivot column and add it to the row containing that number
				// Stores the number in the pivot column as num2 to be used to multiply the pivot row by
				if (j == k) {
					// Stops it doing anything to the pivot row
				}
				else {
					for (c = 0; c < tsize; c++) {
						// Each row has the pivot row multiplied by the number in the pivot column added to it
						id[j][c] = id[j][c] - num2 * id[k][c];
						data[j][c] = data[j][c] - num2 * data[k][c];
					}
				}
			}
		}
		//----------------------------------------------------------------------------------------------------------------


		//---------------------------PRINTING INVERSE TO CONSOLE(After checking if it can be inverted)--------------------
		if (num1 != 0) {
			// If num1 = 0 then the matrix cannot be inverted
			cout << "The inverse of the matrix is:\n";
			for (k = 0; k < tsize; k++) {
				// Loops over the rows in the 2D matrix
				for (j = 0; j < data.size(); j++) {
					// For each value of k (each row), writes out all the data points in that row
					if (j == data.size() - 1) {
						// This is to stop it adding a comma at the end of each row
						cout << id[k][j];
					}
					else {
						cout << id[k][j] << ",";
					}
				}
				// Adds a return at the end of each row
				cout << "\n";
			}
			cout << "The inverse has been saved to the file \"Matrix_Inverse.txt\"\n";
		}
		else {
			// Gets here is the matrix could not be inverted
			cout << "This matrix is singular and so cannot be inverted\n";
		}
		//----------------------------------------------------------------------------------------------------------------


		//------------------------WRITING INVERSE TO A FILE(After checking if it can be inverted)-------------------------
		ofstream aFile("Matrix_Inverse.txt");
		if (aFile.is_open()) {
			if (num1 != 0) {
				// If num1 = 0 then the matrix cannot be inverted
				// Loops over the rows in the 2D matrix
				for (k = 0; k < tsize; k++) {
					// Loops over the columns in the 2D matrix
					for (j = 0; j < data.size(); j++) {
						// For each value of k (each row), writes out all the data points in that row
						if (j == data.size() - 1) {
							// Stops it adding a comma at the end of each row
							aFile << setw(7) << setprecision(5) << id[k][j];
						}
						else {
							aFile << setw(7) << setprecision(5) << id[k][j] << ",";
						}
					}
					// Adds a return at the end of each row
					aFile << "\n";
				}
			}
			else {
				aFile << "This matrix is singular and so cannot be inverted";
			}
			aFile.close();
		}
		//----------------------------------------------------------------------------------------------------------------
	}
	else {
		// Gets here if read in matrix doesn't have same number or rows and columns
		cout << "The matrix must have the same number of rows and columns\n";
	}
	return 0;
}

