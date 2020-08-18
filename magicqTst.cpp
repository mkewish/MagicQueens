// File: newMagicqTst.cpp

#include <iostream>
#include <fstream>
#include "newMagicq.h"

using namespace std;

int main()
{
  NewMagicQ* M = new NewMagicQ();
  M -> goMagicQ();
  M -> ~NewMagicQ();
  
  return 0;
}