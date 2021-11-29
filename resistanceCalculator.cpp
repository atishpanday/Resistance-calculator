#include<iostream>
#include<vector>

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

void calculateResistance(int max_junction_id, std::vector<junction>& junction_set, std::vector<wire*>& wire_set){
	std::vector<std::vector<float>> transformation_matrix(max_junction_id, std::vector<float> (max_junction_id+1));
	std::vector<float> transformation_matrix_row(max_junction_id+1);
	std::vector<float> target_vector(max_junction_id);
	std::vector<std::vector<float>> solution_matrix(max_junction_id, std::vector<float> (max_junction_id));

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

	for(int i=0; i<max_junction_id; i++){
		target_vector[i] = transformation_matrix[i][0];
		for(int j=1; j<=max_junction_id; j++){
			solution_matrix[i][j-1] = transformation_matrix[i][j];
		}
	}

	for(auto i:solution_matrix){
		for(auto j:i){
			std::cout << "\t" << j;
		}
		std::cout << "\n";
	}

	std::cout << "\n";

	for(auto i:target_vector){
		std::cout << "\t" << i;
	}

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
	float resistance;
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
	std::cout << "\n";
	for(auto junction:junction_set){
		for(auto wire:junction.connected_wires){
			std::cout << wire->begin->id << "\t" << wire->resistance << "\t" << wire->end->id << "\n";
		}
		std::cout << "\n";
	}

	calculateResistance(junction_set.size()-1, junction_set, wire_set);
	return 0;
}

