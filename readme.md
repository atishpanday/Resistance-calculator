THE PROBLEM STATEMENT: WE NEED TO TAKE AS INPUT THE CIRCUIT BETWEEN TWO END JUNCTIONS, SAY A AND B, AND DETERMINE THE EQUIVALENT RESISTANCE BETWEEN THEM.

EXAMPLE:

A ---------5-----------B
|----------3-----------|

Suppose A and B are connected by two wires in parallel having resistances 5 ohms and 3 ohms. In this case the equivalent resistance would be:

R(eq) = 1/(1/5 + 1/3) = 15/8 = 1.99ohms

Our job is to use the methods of physics that we know to design an algorithm that can achieve the same answer, but for more complex circuits as well.

What is a circuit: it is a wire connected between the terminals of a battery.
The wire may have other connections to it which may or may not contribute to the passing of current through them

The main wire can be thought of as a group of 2 nodes ( the terminals of the battery ) which can be represented as class.

Every node has a resistance associated to it which comes right next to it.

Every wire has two junctions, and every junction has a unique id to identify it.
Now we have a vector of junctions and a vector of wires. To solve this network, we need to assign potentials to the junctions.

Input: we take the junction ids one by one in ascending order and create new class for each junction. we then take the pairs of junctions that are connected assuming that junction with id 0 is the first junction and junction with the greatest id is the last junction. while taking the pair of junctions that are connected, we also take the values of the resistances in those wires.

we need to add a pointer inside each junction that points to the wires it is connected to.
we also add a pointer inside each wire to point to its end junctions. Now every wire knows its end junctions and every junction knows the wires connected to them.

so we may represent them as:

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

Method: 

We use basic knowledge of the properties of current, ie, current is more in wires that have lower resistance and vice versa.
thus we follow the simple equation: V = IR
However, in a complex circuit, it is difficult to determine the exact amount of current flowing through each wire since the exact potential diffference between the junctions is not known a priori. Thus we might apply the methods of iteration to find the right amount of current flowing through each wire. In this case, the final answer may be obtained by putting V = IRe where I will be the sum of the currents flowing through the wires connected to the first junction that is junction 0.

Challenge: how do we determine the potential difference between any two junctions?

Possible solution: We start with a random voltage at the first junction junction 0 which can be any value since the answer does not depend on it.
We then assign equal currents to all wires connected to junction 0. Then we move to the junctions connected to those wires at the other end. We might then reach an interesting point where the voltage at one junction coming from different wires give different values due to differences in their resistances. Thus we must iterate and change the current values in those previous wires so that they must agree with one another. 

Challenge: How much and which current should we change?

possible solution: we start with an initial voltage of say 10V, as the answer does not depend on it. we then move down each wire and create an equation for the currents in the wires. If there are N wires, then there must be N simultaneous equations to solve them. Each junction will give us the relationship between the currents by the logic that at each juntion, the sum of the inward flowing current must be equal to the sum of the outflowing current.

This will create a matrix of equations that can be simultaneoussly solved to get the answer I1 I2 I3.... Finally, the value of R(eq) would be simple V/I where V is the assumed value of potential at junction 0 and I is the sum of currents flowing out from this junction.









	
