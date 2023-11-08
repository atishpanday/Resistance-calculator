class wire;

class junction {
	int id;
	double voltage;
	int num_wires = 0;
	
	public:
	
	wire* connected_wires[10];
	
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
	
	void set_connected_wires(wire* w) {
		connected_wires[num_wires] = w;
		num_wires++;
	}

	
};

class wire {
	int id;
	double resistance;
	double current;
	junction* begin;
	junction* end;
	
	public:
	
	wire(): id(0), resistance(0), current(0) {}
	
	wire(int id, double res, junction* beg, junction* end): id(id), resistance(res), begin(beg), end(end) {}
	
	int get_id() {
		return id;
	}
	
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
	
	junction* get_begin() {
		return begin;
	}
	
	junction* get_end() {
		return end;
	}
	
	junction* get_other_end(int jid) {
		if(jid == begin -> get_id()) {
			return end;
		}
		else {
			return begin;
		}
	}
};
