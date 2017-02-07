//Author: Nikhil Krishnan
#include "threadtest.h"

std::mutex m;//you can use std::lock_guard if you want to be exception safe
int i = 0;
int a = 5;

void threaddemo()
{
	//This is the main crowd of people uninterested in making a phone call
	int b = 5;

	//man1 leaves the crowd to go to the phone booth
	std::thread man1(makeACallFromPhoneBooth, 1, b);
	//Although man2 appears to start second, there's a good chance he might
	//reach the phone booth before man1
	std::thread man2(makeACallFromPhoneBooth, 2, b);
	//And hey, man3 also joined the race to the booth
	std::thread man3(makeACallFromPhoneBooth2, 3, &b);

	man1.join();//man1 finished his phone call and joins the crowd
	man2.join();//man2 finished his phone call and joins the crowd
	man3.join();//man3 finished his phone call and joins the crowd

}

void makeACallFromPhoneBooth(int threadno, int b)
{
	//
	m.lock();//man gets a hold of the phone booth door and locks it. The other men wait outside
			 //man happily talks to his wife from now....
	std::cout << std::endl << "Thread number = " << threadno;
	std::cout << std::endl << i << " Hello Wife" << std::endl;
	std::cout << std::endl << "b = " << b;
	i++;//no other thread can access variable i until m.unlock() is called
		//...until now, with no interruption from other men
	m.unlock();//man lets go of the door handle and unlocks the door
	(b)++;
}

void makeACallFromPhoneBooth2(int threadno, int *b)
{
	m.lock();//man gets a hold of the phone booth door and locks it. The other men wait outside
			 //man happily talks to his wife from now....
	std::cout << std::endl << "Thread number = " << threadno;
	std::cout << std::endl << i << " Hello Wife" << std::endl;
	std::cout << std::endl << "a = " << a;
	a++;
	i++;//no other thread can access variable i until m.unlock() is called
		//...until now, with no interruption from other men
	m.unlock();//man lets go of the door handle and unlocks the door
}