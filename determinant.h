#ifndef DETERMINANT
#define DETERMINANT

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

#endif
