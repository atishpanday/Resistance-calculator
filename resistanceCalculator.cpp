#include<iostream>
#include<vector>
#include"cofactor.h"
#include"determinant.h"
#include"adjoint.h"
#include"inverse.h"
#include"matrixmultiplication.h"

class junction;
class wire;

class junction{
	public:
	int id;
	float voltage;
	std::vector<wire*> connected_wires;
	junction(): id(0) {}
	junction(int id): id(id) {}
};

class wire{
	public:
	float resistance;
	float current;
	junction* begin,* end;
	wire(float resistance, junction* begin, junction* end): resistance(resistance), begin(begin), end(end) {}
};

float calculateResistance(int max_junction_id, std::vector<junction>& junction_set, std::vector<wire*>& wire_set){
	std::vector<std::vector<float>> transformation_matrix(max_junction_id, std::vector<float> (max_junction_id+1));
	std::vector<float> transformation_matrix_row(max_junction_id+1);
	std::vector<float> target_vector(max_junction_id-1);
	std::vector<std::vector<float>> solution_matrix(max_junction_id-1, std::vector<float> (max_junction_id-1));
	std::vector<float> solution_vector(max_junction_id-1);
	std::vector<std::vector<float>> inverse_matrix(max_junction_id-1, std::vector<float> (max_junction_id-1));	
	float total_current = 0.0f;

	for(int junc=1; junc<=max_junction_id; junc++){
		if(junc == max_junction_id){
			for(auto wire:junction_set[junc].connected_wires){
				transformation_matrix_row[junc] -= (1/wire->resistance);
				if(wire->begin->id == junc)
					transformation_matrix_row[wire->end->id] += 1/(wire->resistance);
				else
					transformation_matrix_row[wire->begin->id] += 1/(wire->resistance);
			}
			for(auto wire:junction_set[0].connected_wires){
				transformation_matrix_row[0] -= (1/wire->resistance);
				if(wire->begin->id == 0)
					transformation_matrix_row[wire->end->id] += 1/(wire->resistance);
				else
					transformation_matrix_row[wire->begin->id] += 1/(wire->resistance);
			}
		} else {
			for(auto wire:junction_set[junc].connected_wires){
				transformation_matrix_row[junc] -= (1/wire->resistance);
				if(wire->begin->id == junc)
					transformation_matrix_row[wire->end->id] += 1/(wire->resistance);
				else
					transformation_matrix_row[wire->begin->id] += 1/(wire->resistance);
			}
		}
		transformation_matrix[junc-1] = transformation_matrix_row;
		for(int i=0; i<=max_junction_id; i++)
			transformation_matrix_row[i] = 0;
	}

	// assigning the values of transformation matrix to target matrix and solution matrix
	for(int i=0; i<max_junction_id-1; i++){
		target_vector[i] -= transformation_matrix[i][0];
		for(int j=1; j<max_junction_id; j++){
			solution_matrix[i][j-1] = transformation_matrix[i][j];
		}
	}

//	for(auto i:solution_matrix){
//		for(auto j:i){
//			std::cout << j << "\t";
//		}
//		std::cout << "\n";
//	}


//	for(auto i:target_vector){
//		std::cout << i << "\t";
//	}

	if(inverse(solution_matrix, inverse_matrix)){
	} else {
		std::cout << "You entered an invalid circuit. Please make sure the circuit isn't redundant!";
	}

	matrixmultiply(solution_vector, inverse_matrix, target_vector);

	for(auto wire:junction_set[0].connected_wires){
		if(wire->begin->id == 0){
			total_current += (1 - (solution_vector[wire->end->id-1]))/wire->resistance;
		} else {
			total_current += (1 - (solution_vector[wire->end->id-1]))/wire->resistance;
		}
	}

	return (1/total_current);
}

int main(){
	std::cout << "Number all the junctions in your circuit and enter them one by one starting from 0\n";
	std::cout << "After you enter all the junctions, enter the resistance of all the wires between each pair of junctions\n";
	std::cout << "For example: add 1, 2, 2.5, for a resistance of 2.5 between the junctions 1 and 2\n";
	std::cout << "To add multiple wires between the same junctions, just add them one by one\n";
	std::vector<junction> junction_set;
	std::vector<wire*> wire_set;
	float jn_id;
	char ch='y';
	float resistance = 0.0f;
	int begin, end;
	while(ch=='y'){
		std::cout << "\nAdd a junction: ";
		std::cin >> jn_id;
		junction jn = junction(jn_id);
		junction_set.push_back(jn);
		std::cout << "\nAnother junction?(y/n) ";
		std::cin >> ch;
	}
	ch='y';
	while(ch=='y'){
		std::cout << "\nEnter the beginning junction id: ";
		std::cin >> begin;
		std::cout << "\nEnter the end junction id: ";
		std::cin >> end;
		std::cout << "\nEnter the resistance value: ";
		std::cin >> resistance;
		wire* w = new wire(resistance, &junction_set[begin], &junction_set[end]);
		wire_set.push_back(w);
		junction_set[begin].connected_wires.push_back(w);
		junction_set[end].connected_wires.push_back(w);
		std::cout << "\nMore wires?(y/n) ";
		std::cin >> ch;
	}
	resistance = 0.0f;
	if(wire_set.size() == 2){
		for(auto wire:wire_set){
			resistance += 1/wire->resistance;
		}
		resistance = 1/resistance;
		std::cout << "\n\nThe equivalent resistance is: " << resistance << " ohms\n";
	} else {
		std::cout << "\n";
		std::cout << "begin junction\tresistance\tend junction\n";
		for(auto wire:wire_set){
			std::cout << wire->begin->id << "\t" << wire->resistance << "\t" << wire->end->id << "\n";
		}
		std::cout << "\n";

		std::cout << "\n\nThe equivalent resistance is: " << calculateResistance(junction_set.size()-1, junction_set, wire_set) << " ohms\n";
	}
	return 0;
}

