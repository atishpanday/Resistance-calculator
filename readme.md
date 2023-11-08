This code takes in a complete circuit of resistors and solves it to calculate the equivalent resistance, the potential at each junction and the current flowing through each wire.

The method used to calculate these is nodal analysis. 

Assume the ith junction, with n connected wires, then according to Kirchoff's current law, the total inward (or outward) flowing current is 0.

	\sum_{k = 1}^n \frac{V_i - V_k}{r_k} = 0
