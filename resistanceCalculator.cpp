#include<iostream>
#include<vector>

struct junction{
	int id;
	junction(): id(0) {}
	junction(int id): id(id) {}
};

class wire{
	public:
	float resistance;
	junction* begin,* end;
	wire(float resistance, junction* begin, junction* end): resistance(resistance), begin(begin), end(end) {}
};

int main(){
	std::cout << "Number all the junctions in your circuit and enter them one by one starting from 0\n";
	std::cout << "After you enter all the junctions, enter the resistance of all the wires between each pair of junctions\n";
	std::cout << "For example: add 1, 2, 2.5, for a resistance of 2.5 between the junctions 1 and 2\n";
	std::cout << "To add multiple wires between the same junctions, just add them one by one\n";
	std::vector<junction> junction_set;
	std::vector<wire> wire_set;
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
		wire w = wire(resistance, &junction_set[begin], &junction_set[end]);
		wire_set.push_back(w);
		std::cout << "\nMore wires?(y/n) ";
		std::cin >> ch;
	}
	std::cout << "\n";
	for(auto i:wire_set){
		std::cout << i.resistance << "\t" << i.begin->id << "\t" << i.end->id << "\n";
	}

	return 0;
}
