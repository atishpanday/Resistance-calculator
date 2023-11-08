#include <iostream>
#include "classes.h"
#include "utils.h"

#define max_jns 50
#define max_wires 100

double calculate_resistance(int num_wires, int num_jns, junction jn_set[], wire w_set[]) {
	
	double kcl_mat[max_jns][max_jns] = {0}; // stores the coefficients of the equations of nodal analysis
	double rhs_vec[max_jns] = {0}; // right hand side vector of the equations of nodal analysis
	double inv_mat[max_jns][max_jns] = {0}; // inverse matrix to solve the equations
	double sol_vec[max_jns] = {0}; // solution vector that will store the values of the potentials of all junctions except 0th and last

	
	for(int jid = 1; jid < num_jns - 1; jid++) {
		for(int i = 0; i < jn_set[jid].get_num_wires(); i++) {
		
			kcl_mat[jid - 1][jid - 1] += 1 / jn_set[jid].connected_wires[i] -> get_resistance(); // sum of inverse of resistances of all connected wires
			
			if(jn_set[jid].connected_wires[i] -> get_other_end(jid) -> get_id() == 0) {
				rhs_vec[jid - 1] = jn_set[0].get_voltage() / jn_set[jid].connected_wires[i] -> get_resistance(); 
				// if this wire is connected to the first junction, then simply add the corresponding inverse of resistance to the rhs vector 
			}
			
			else if(jn_set[jid].connected_wires[i] -> get_other_end(jid) -> get_id() == num_jns - 1) {
				// no code to run if the other end is the last junction since the potential there is 0
			}
			
			else {
				kcl_mat[jid - 1][jn_set[jid].connected_wires[i] -> get_other_end(jid) -> get_id() - 1] = 
					-1 / jn_set[jid].connected_wires[i] -> get_resistance();
				// all other wires are added with the negative of inverse of their resistances
			}
		}
	}
	
	for(int i = 0; i < num_jns - 2; i++) {
		for(int j = 0; j < num_jns - 2; j++) {
			std::cout << kcl_mat[i][j] << "\t";
		}
		std::cout << "\n";
	}
	
	std::cout << "\n";
	
	if(!inverse(kcl_mat, inv_mat, num_jns - 2)) {
		return -1;
	}
	
	matrix_multiply(sol_vec, inv_mat, rhs_vec, num_jns - 2);
	
	std::cout << "Sol Rhs\n";
	for(int i = 0; i < num_jns - 2; i++) {
		std::cout << sol_vec[i] << " " << rhs_vec[i] << "\n";
	}
	
	// set the potential at each junction
	for(int i = 0; i < num_jns - 2; i++) {
		jn_set[i + 1].set_voltage(sol_vec[i]);
	}
	
	// set the current in each wire using the potential difference
	for(int i = 0; i < num_wires; i++) {
		double v = w_set[i].get_begin() -> get_voltage() - w_set[i].get_end() -> get_voltage();
		w_set[i].set_current(v / w_set[i].get_resistance());
	}
	
	double total_current = 0;
	
	// set the total current flowing through the circuit
	for(int i = 0; i < jn_set[0].get_num_wires(); i++) {
		total_current += jn_set[0].connected_wires[i] -> get_current();
	}
	
	return jn_set[0].get_voltage() / total_current;
	
}

int main() {
	junction jn_set[max_jns];
	wire w_set[max_wires];
	
	double resistance = 0;
	double voltage = 0;
	int begin, end;
	int num_jns = 0;
	int num_wires = 0;
	
	std::cout << "Enter the number of junctions in your circuit (max max_jns): ";
	std::cin >> num_jns;
	
	for(int i = 0; i < num_jns; i++) {
		jn_set[i] = junction(i);
	}
	
	std::cout << "Enter the voltage of the battery (potential at the first junction): \n";
	std::cin >> voltage;
	
	jn_set[0].set_voltage(voltage);

	std::cout << "To add multiple wires between the same junctions, just add them one by one\n";
	
	char ch = 'y';
	while(ch == 'y' && num_wires < max_jns) {
		std::cout << "\nEnter the beginning junction id: ";
		std::cin >> begin;
		std::cout << "\nEnter the end junction id: ";
		std::cin >> end;
		std::cout << "\nEnter the resistance value: ";
		std::cin >> resistance;
		 
		w_set[num_wires] = wire(num_wires, resistance, &jn_set[begin], &jn_set[end]);
		jn_set[begin].set_connected_wires(&w_set[num_wires]);
		jn_set[end].set_connected_wires(&w_set[num_wires]);
		
		std::cout << "\nMore wires?(y/n): ";
		std::cin >> ch;
		
		num_wires++;
	}
	
	resistance = 0;
	
	if(num_wires == 2) {
		for(int i = 0; i < num_wires; i++) {
			resistance += 1 / w_set[i].get_resistance();
		}
		resistance = 1 / resistance;
		std::cout << "\n\nThe equivalent resistance is: " << resistance << " ohms\n";
	} 
	
	else {
		std::cout << "\nb\tr\te\n";
		
		for(int i = 0; i < num_wires; i++) {
			std::cout << w_set[i].get_begin() -> get_id() << "\t" << 
			w_set[i].get_resistance() << "\t" << w_set[i].get_end() -> get_id() << "\n";
		}
		
		std::cout << "\n";
		
		resistance = calculate_resistance(num_wires, num_jns, jn_set, w_set);
		
		if(resistance == -1) {
			std::cout << "\n\nYou entered a redundant circuit\n\n";
		}
		else {
			std::cout << "\n\n\nThe equivalent resistance is: " << resistance << " ohms\n";
			
			for(int i = 0; i < num_jns; i++) {
				std::cout << "\nThe voltage at junction " << i << " is: " << jn_set[i].get_voltage();
			}
			
			std::cout << "\n";
			
			for(int i = 0; i < num_wires; i++) {
				std::cout << "\nThe current between junctions " << w_set[i].get_begin() -> get_id() << 
					" and " << w_set[i].get_end() -> get_id() << " is: " << w_set[i].get_current();
			}
		}
	}
	
	std::cout << "\n";
	
	return 0;
}

