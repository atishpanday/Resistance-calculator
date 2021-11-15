What is a circuit: it is a wire connected between the terminals of a battery.
The wire may have other connections to it which may or may not contribute to the passing of current through them

The main wire can be thought of as a group of 2 nodes ( the terminals of the battery ) which can be represented as struct.

Every node has a resistance associated to it which comes right next to it.

junction { int id }
wire { float resistance, junction* begin, junction* end }

Every wire has two junctions, and every junction has a unique id to identify it.
Now we have a vector of junctions and a vector of wires. To solve this network, we need to assign potentials to the junctions.

We will apply kirchoffs laws to solve for the equivalent resistance value

then v1 + v2 + v3 + ... = 0 where v1, v2, v3, ... are the voltages dropped in each wire that forms a closed loop
we need to add a pointer inside each junction that points to the wires it is connected to.

so

struct junction{
	int id;
	vector<wire>* connected_wires;
}

	-i1r1 + i2r2 + i3r3 +    0 +    0 = v
	    0 +    0 + i3r3 - i4r4 + i5r5 = 0
	-i1r1 + i2r2 +    0 + i4r4 - i5r5 = v
	    0 +   i2 -   i3 -   i4 +    0 = 0
	   i1 +    0 +   i3 +    0 -   i5 = 0

	-r1	r2	r3	 0	 0
	  0	 0	i3	r4	r5
	-r1	r2	 0	r4     -r5
	  0	r2     -r3      r4       0
	 r1	 0      r3       0     -r5
