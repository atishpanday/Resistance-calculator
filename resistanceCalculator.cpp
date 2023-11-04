#include<iostream>
#include<vector>
#include"cofactor.h"
#include"determinant.h"
#include"adjoint.h"
#include"inverse.h"
#include"matrixmultiplication.h"

class wire;

class junction{
	int id;
	double voltage;
	int num_wires = 0;
	wire connected_wires[10];
	
	public:
	
	junction(): id(0) {}
	junction(int id): id(id) {}
	
	int get_id() {
		return id;
	}
	
	void set_voltage(double v) {
		voltage = v;
	}
	
	double get_voltage() {
		return voltage;
	}
	
	int get_num_wires() {
		return num_wires;
	}
	
	void set_connected_wires(wire w) {
		connected_wires[num_wires] = w;
		num_wires++;
	}
	
	wire[] get_connected_wires() {
		return connected_wires;
	}
	
};

class wire{
	double resistance;
	double current;
	junction begin;
	junction end;
	
	public:
	
	wire(double resistance, junction begin, junction end): resistance(resistance), begin(begin), end(end) {}
	
	void set_resistance(double res) {
		resistance = res;
	}
	
	double get_resistance() {
		return resistance;
	}
	
	void set_current(double curr) {
		current = curr;
	}
	
	double get_current() {
		return current;
	}
	
	junction get_begin() {
		return begin;
	}
	
	junction get_end() {
		return end;
	}
};

double cacluate_resistance(int num_jns, junction jn_set[100], wire w_set[100]) {

	double trans_mat[100][100] = {0};
	double trans_mat_row[100] = {0};
	double target[100] = {0};
	double sol_mat[100][100] = {0};
	double sol_row[100] = {0};
	double inv_mat[100][100] = {0};
		
	double total_current = 0;

	for(int junc = 1; junc < num_jns; junc++) {
		if(junc == (num_jns - 1)){
			for(int i = 0; i < jn_set[junc].get_num_wires(); i++) {
			
				wire w = jn_set[junc].get_connected_wires()[i];
				trans_mat_row[junc] -= 1 / w.get_resistance();
				
				if(w.get_begin().get_id() == junc) {
					trans_mat_row[w.get_end().get_id()] += 
					1 / w.get_resistance();
				}
				else {
					trans_mat_row[w.get_begin().get_id()] += 1 / w.get_resistance();
				}
			}
			
			for(int i = 0; i < jn_set[0].get_num_wires(); i++) {
			
				wire w = jn_set[junc].get_connected_wires()[i];
				trans_mat_row[0] -= 1 / w.get_resistance();
				
				if(w.get_begin().get_id() == 0)
					trans_mat_row[w.get_end().get_id()] += 1 / w.get_resistance();
				else
					trans_mat_row[w.get_begin().get_id()] += 1 / w.get_resistance();
			}
		} 
		else {
			for(int i = 0; i < jn_set[junc].get_num_wires; i++) {
				
				wire w = jn_set[junc].get_connected_wires()[i];
				trans_mat_row[junc] -= 1 / w.get_resistance();
				
				if(w.get_begin().get_id() == junc) {
					trans_mat_row[w.get_end().get_id()] += 1 / w.get_resistance();
				}
				else {
					trans_mat_row[w.get_begin().get_id()] += 1 / w.get_resistance();
				}
			}
		}
		trans_mat[junc-1] = trans_mat_row;
		for(int i = 0; i < num_wires; i++) {
			trans_mat_row[i] = 0;
		}
	}

	// assigning the values of transformation matrix to target matrix and solution matrix
	for(int i = 0; i < num_jns - 1; i++) {
		target[i] -= trans_mat[i][0];
		for(int j = 1; j < num_jns; j++) {
			sol_mat[i][j-1] = trans_mat[i][j];
		}
	}

//	for(auto i:sol_mat){
//		for(auto j:i){
//			std::cout << j << "\t";
//		}
//		std::cout << "\n";
//	}


//	for(auto i:target){
//		std::cout << i << "\t";
//	}

	if(inverse(sol_mat, inv_mat)) {
		matrixmultiply(sol_row, inv_mat, target);
		for(int i = 0; i < jn_set[0].get_num_wires(); i++) {
			
			wire w = jn_set[0].get_connected_wires()[i];
			
			if(w.get_begin().get_id() == 0) {
				total_current += (1 - (sol_row[w.get_end().get_id() - 1])) / w.get_resistance();
			} 
			else {
				total_current += (1 - (sol_row[w.get_end().get_id() - 1])) / w.get_resistance();
			}
		}
	} 
	else {
		std::cout << "You entered an invalid circuit. Please make sure the circuit isn't redundant!";
		return -1;
	}

	return 1 / total_current;
}

int main(){
	junction jn_set[100];
	wire w_set[100];
	
	int jn_id;
	char ch = 'y';
	double resistance = 0;
	int begin, end;
	int num_jns = 0;
	
	std::cout << "Enter the number of junctions in your circuit (max 100): ";
	std::cin >> num_jns;
	
	for(int i = 0; i < num_jns; i++) {
		jn_set[i] = junction(i);
	}
	
	std::cout << "Add 1, 2, 2.5, for a resistance of 2.5 between the junctions 1 and 2\n";
	std::cout << "To add multiple wires between the same junctions, just add them one by one\n";
	
	int i = 0;
	while(ch == 'y' && i < 100){
		std::cout << "\nEnter the beginning junction id: ";
		std::cin >> begin;
		std::cout << "\nEnter the end junction id: ";
		std::cin >> end;
		std::cout << "\nEnter the resistance value: ";
		std::cin >> resistance;
		
		w_set[i] = wire(resistance, jn_set[begin], jn_set[end]);
		jn_set[begin].set_connected_wires(w_set[i]);
		jn_set[end].set_connected_wires(w_set[i]);
		
		std::cout << "\nMore wires?(y/n) ";
		std::cin >> ch;
		
		i++;
	}
	
	resistance = 0;
	if(w_set.size() == 2){
		for(auto wire:w_set){
			resistance += 1/wire->resistance;
		}
		resistance = 1/resistance;
		std::cout << "\n\nThe equivalent resistance is: " << resistance << " ohms\n";
	} 
	else {
		std::cout << "\n";
		std::cout << "begin junction\tresistance\tend junction\n";
		for(auto wire:w_set) {
			std::cout << wire->begin->id << "\t" << wire->resistance << "\t" << wire->end->id << "\n";
		}
	std::cout << "\n";

	std::cout << "\n\nThe equivalent resistance is: " << calculate_resistance(jn_set.size()-1, jn_set, w_set) << " ohms\n";
	}
	
	return 0;
}

