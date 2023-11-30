#pragma once

#include <stdlib.h>

int example1();
int example2();
int example3();
int example4();

static void run_pbplot_example(int example_number) {
	switch (example_number)
	{
	case 1:
		example1();
		system("example1.png");
		return;
	case 2:
		example2();
		system("example2.png");
		return;
	case 3:
		example3();
		system("example3.png");
		return;
	case 4: 
		example4();
		system("example4.png");
		return;
	default:
		return;
	}
}
