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

void calculateResistance(int max_junction_id, std::vector<junction> junction_set, std::vector<wire*> wire_set){
	float voltage=10.0f;
	std::vector<std::vector<float>> transformation_matrix;
	std::vector<float> transformation_matrix_row;
	std::vector<float> solution_vector;
	std::vector<float> target_vector;
	int num_of_wires;
	for(int i=1; i<max_junction_id; i++){
		num_of_wires = junction_set[i].connected_wires.size();
		transformation_matrix_row = {};
		for(int j=1; j<num_of_wires; j++){
			if(junction_set[i].connected_wires[j]->begin.id == junction_set[i].id
				      && junction_set[i].connected_wires[j]->end.id > junction_set[i].id){
				transformation_matrix_row.push_back(1);
			}
			else if(junction_set[i].connected_wires[j]->end.id == junction_set.id
					&& junction_set[i].connected_wires[j]->begin.id > junction_set[i].id){
				transformation_matrix_row.push_back(-1);
			}
			else {
				transformation_matrix_row.push_back(0);
			}
		}
		transformation_matrix.push_back(transformation_matrix_row);
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
			std::cout << wire->begin->id << "\t" << wire->resistance << "\t" << wire->end->id;
		}
		std::cout << "\n";
	}
	return 0;
}
