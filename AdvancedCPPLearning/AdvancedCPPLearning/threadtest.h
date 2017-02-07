//Author: Nikhil Krishnan

// Tutorial taken from:
/* http://stackoverflow.com/questions/4989451/mutex-example-tutorial */

#pragma once // used instead of #ifdef

//#ifdef THREAD_TEST
//# define THREAD_TEST

#include <iostream>
#include <mutex>
#include <thread>

extern std::mutex m;//you can use std::lock_guard if you want to be exception safe
extern int i;
extern int a;


void threadDemo();
void makeACallFromPhoneBooth(int, int);
void makeACallFromPhoneBooth2(int, int *);

//#endif
