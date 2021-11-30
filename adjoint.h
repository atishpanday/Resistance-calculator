#ifndef ADJOINT
#define ADJOINT

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

#endif
