// File: magicqTst.cpp

#include <iostream>
#include <fstream>
#include "magicq.h"

using namespace std;

int main()
{
  MagicQ* M = new MagicQ();
  M -> goMagicQ();
  M -> ~MagicQ();
  
  return 0;
}