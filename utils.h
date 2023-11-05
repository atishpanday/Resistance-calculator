
// Matrix multiplication

void matrix_multiply(double sol_row[], double inv_mat[][100], double target[], int N) {
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			sol_row[i] += inv_mat[i][j] * target[j];
		}
	}
}

// Cofactor of a matrix

void cofactor(double A[][100], double temp[][100], int p, int q, int N) {
	int i = 0, j = 0;
	
	for (int row = 0; row < N; row++) { 
    		for (int col = 0; col < N; col++) {
            		if (row != p && col != q) {
                	temp[i][j++] = A[row][col];
                		if (j == N - 1) {
                    			j = 0;
                    			i++;
                		}
            		}
        	}
	}
}

// Determinant of a matrix

double determinant(double vec[][100], int N){

	if(N == 1) {
		return vec[0][0];
	}

	double temp[100][100] = {0};
	int sign = 1;
	double D = 0;
	
	for(int i = 0; i < N; i++){
		cofactor(vec, temp, 0, i, N);
		D += sign * vec[0][i] * determinant(temp, N - 1);
		sign = -sign;
	}
	
	return D;
}

// Adjoint of a matrix

void adjoint(double A[][100], double adj[][100], int N){
	if (N == 1) {
        	adj[0][0] = 1;
        	return;
    	}
    
	int sign = 1;
	double temp[100][100];
    	for (int i=0; i<N; i++) {
        	for (int j=0; j<N; j++) {
		    	cofactor(A, temp, i, j, N);
		    	sign = ((i+j) % 2 == 0) ? 1 : -1;
		    	adj[j][i] = sign * determinant(temp, N-1);
        	}
    	}
}

// Inverse of a matrix

bool inverse(double A[][100], double inverse[][100], int N) {
	double det = determinant(A, N);
	
	if (det == 0) {
		return false;
	}
 
	double adj[100][100];
    	adjoint(A, adj, N);
    	
	for (int i = 0; i < N; i++) {
        	for (int j = 0; j < N; j++) {
            		inverse[i][j] = adj[i][j] / double(det);
            	}
        }
        return true;
}

