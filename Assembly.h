#pragma once

/*
	Assembly class must be able to...

	- Replace UG's list of static global variables used by thousands of patches 
	- Support replacing register values, but also allowing comparing, and even simple patches to be done
	- Allow JMP opcodes to be used inside this new hook (allow JA/JE/JAE...)

	So yeah, main goal is to make sure I don't have to keep declaring so many static variables, return addresses for each x86 patch, and making sure patches won't make such a big mess again
	
	Will require some thinking.
*/

class Assembly
{

};