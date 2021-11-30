#ifndef INVERSE
#define INVERSE
bool inverse(std::vector<std::vector<float>>& A, std::vector<std::vector<float>>& inverse){
    int N = A.size();
	int det = determinant(A, N);
    if (det == 0){
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

#endif
