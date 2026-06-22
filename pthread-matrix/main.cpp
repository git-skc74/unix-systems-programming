// file: matrix_product.cpp
// author: Bo Seong Kim
// date: 12/04/2025
// purpose: CS3377 assignment 6
// description:
// 	this program reads matrices from two text files, performs matrix multiplication 
//  by using pthread and produces a new matrix text file.

#include <iostream>
#include <fstream>
#include <cstdlib> // exit()
#include <pthread.h>
#include <vector>
#include <string>

using namespace std;

struct ThreadData {
	vector<vector<int> >* A;
	vector<vector<int> >* B;
	vector<vector<int> >* C;
	int row, col; // row and col where thread saves sum
	int K; // A cols = B rows
};

vector<vector<int> > readMatrix(const string& filename, int& rows, int& cols) {
	ifstream fin(filename.c_str());
	if (!fin) {
		cerr << "Cannot open the file: " << filename << endl;
		exit(1);
	}
		
	fin >> rows >> cols; // row and col are first two elements of the file
	
	vector<vector<int> > matrix(rows, vector<int>(cols));
	
	// initialize matrix with data from the file
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			fin >> matrix[i][j];
		}
	}
	fin.close();
	return matrix;
}	

void saveMatrix(const string& filename, const vector<vector<int> >& mat) {
    ofstream fout(filename.c_str());
    if (!fout) {
        cerr << "Cannot open or create the file: " << filename << endl;
        exit(1);
    }
    
    int rows = mat.size();
    int cols = mat[0].size();
    
    fout << rows << " " << cols << "\n"; // first row: rows and cols
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fout << mat[i][j] << " ";
        }
        fout << "\n"; // newline
    }
    fout.close();
}

void* worker(void* arg) {
    ThreadData* td = (ThreadData*) arg; // casts struct given as an argument
    int sum = 0;
    
    // perform multiplication and add the result to sum
    for (int x = 0; x < td->K; x++) {
        sum += (*(td->A))[td->row][x] * (*(td->B))[x][td->col];
    }
    (*(td->C))[td->row][td->col] = sum; // saves sum to C[row][col]
    
    pthread_exit(NULL);
}

int main() {
	int M, K, rowsB, N;
	
	// initialize vectors
	vector<vector<int> > A = readMatrix("matrixA.txt", M, K);
	vector<vector<int> > B = readMatrix("matrixB.txt", rowsB, N);
    
    // dimension check
    if (K != rowsB) { 
        cerr << "Matrix multiplication cannot be done: A cols != B rows" << endl;
        return 1;
    }
    
    vector<vector<int> > C(M, vector<int>(N, 0)); // initialize matrix C
    
    int s = M * N;
    pthread_t threads[s]; // creates M * N threads and stores thread IDs
    ThreadData td[s]; // creates M * N threadData structs
    int idx = 0; // thread index
    
    // initialize struct
    for (int i  = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            td[idx].row = i;
            td[idx].col = j;
            td[idx].K = K;
            td[idx].A = &A;
            td[idx].B = &B;
            td[idx].C = &C;
            
            // create threads
            if (0 != pthread_create(&threads[idx], NULL, worker, (void*)&td[idx])) {
                cerr << "Error when calling pthread_create" << endl;
                return 1;
            }
            idx++;
        }
    }
    
    // wait until every thread finishes
    for (int i = 0; i < M * N; i++) {
       if (0 != pthread_join(threads[i], NULL)) {
            cerr << "Error when calling pthread_join" << endl;
            return 1;
        }
    }
    
    saveMatrix("matrix.txt", C); // saves result
    cout << "Result saved to matrix.txt" << endl;
	return 0;
}
