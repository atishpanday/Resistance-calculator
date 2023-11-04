
// Matrix multiplication

void matrixmultiply(double sol_row[], double& inverse_matrix[100][], double& target[]){
	int N = 100;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			sol_row[i] += inv_mat[i][j] * target[j];
		}
	}
}

// Inverse of a matrix

bool inverse(std::vector<std::vector<float>>& A, std::vector<std::vector<float>>& inverse){
    int N = A.size();
	float det = determinant(A, N);
    if (det == 0.0f){
		std::cout << "Singular matrix, can't find its inverse";
        return false;
    }
 
	std::vector<std::vector<float>> adj(A.size(), std::vector<float> (A.size()));
    adjoint(A, adj);
 
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            inverse[i][j] = adj[i][j]/float(det);
 
    return true;
}

// Determinant of a matrix

float determinant(std::vector<std::vector<float>>& vec, int n){

	if(n == 1) return vec[0][0];

	std::vector<std::vector<float>> temp(n, std::vector<float> (n));
	int sign = 1;
	float D = 0;
	
	for(int i=0; i<n; i++){
		getCofactor(vec, temp, 0, i, n);
		D += sign * vec[0][i] * determinant(temp, n-1);
		sign = -sign;
	}
	return D;
}

// Cofactor of a matrix

void getCofactor(std::vector<std::vector<float>>& A, std::vector<std::vector<float>>& temp, int p, int q, int n)
{
    int i = 0, j = 0;
 
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

// Adjoint of a matrix

void adjoint(std::vector<std::vector<float>>& A,std::vector<std::vector<float>>& adj){
    int N = A.size();
	if (N == 1){
        adj[0][0] = 1;
        return;
    }
    int sign = 1;
	std::vector<std::vector<float>> temp(A.size(), std::vector<float> (A.size()));
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            getCofactor(A, temp, i, j, N);
            sign = ((i+j)%2==0)? 1: -1;
            adj[j][i] = (sign)*(determinant(temp, N-1));
        }
    }
}
