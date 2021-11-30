#ifndef MATRIX_MULTIPLICATION
#define MATRIX_MULTIPLICATION

void matrixmultiply(std::vector<float>& solution_vector, std::vector<std::vector<float>>& inverse_matrix, std::vector<float>& target_vector){
	int N = inverse_matrix.size();
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			solution_vector[i] += inverse_matrix[i][j] * target_vector[j];
		}
	}
}

#endif
