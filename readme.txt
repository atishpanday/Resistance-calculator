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

Method to find all the loops in the circuit:
	suppose: junc0 is connected to junc1, junc1 is connected to junc2 and junc2 is connected to junc0.
	then, junc0 junc1 and junc2 form a loop which satisfies the following condition: -i0r0 - i1r1 + i2r2 = 0 => assuming that current is positive when 
	going from a lower junction number to a higher junction number.

suppose a function calcLoops that finds the number of loops:

function calcLoops(junction_set, wire_set):
	 for(junction in junction_set):
		findLoop(junction)

where findLoop is a recursive function that takes in the root junction as argument and finds all the paths that reach back to the root junction

A loop from junc0 following a wire0 and coming back through wireA and a loop from junc0 following a wire0 and coming back through wireB implies a loop from wireA to wireB

Method 2:
Instead of trying to solve using the kirchoffs laws, we use basic knowledge of the properties of current, ie, current is more in wires that have lower resistance and vice versa.
thus we follow the simple equation: V = IR
However, in a complex circuit, it is difficult to determine the exact amount of current flowing through each wire since the exact potential diffference between the junctions is not known a priori. Thus we might apply the methods of iteration to find the right amount of current flowing through each wire. In this case, the final answer may be obtained by putting V = IRe where I will be the sum of the currents flowing through the wires connected to the first junction that is junction 0.

Challenge: how do we determine the potential difference between any two junctions?

Possible solution: We start with a random voltage at the first junction junction 0 which can be any value since the answer does not depend on it.
We then assign equal currents to all wires connected to junction 0. Then we move to the junctions connected to those wires at the other end. We might then reach an interesting point where the voltage at one junction coming from different wires give different values due to differences in their resistances. Thus we must iterate and change the current values in those previous wires so that they must agree with one another. 

Challenge: How much and which current should we change?

Possible solution: We start with a value of 10V at junction 0 and then after each wire we subtract inrn for the nth wire having resistance rn and current in. For each junction, we check the incoming current and the outgoing currents and they must be equal. This will create a matrix of equations that can be simultaneoussly solved to get the answer Re.










	
