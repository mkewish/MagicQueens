// File: magicq.cpp

#include <iostream>
#include <bits/stdc++.h> 
#include <vector>
    
#include "magicq.h"
    
using namespace std;


MagicQ::MagicQ() 
{   
  int n;
    
  do {
    cout << "Please enter a desired matrix size (nxn): ";
    cin >> n;
    if (n < 1)
    cout << "Invalid input... must be a positive number" << endl;
  } while (n < 1);
  cout << endl;
    
  size = n;
  maxNum = size * size;
  magicC = (size * (maxNum + 1)) / 2;
    
  for(int i = 1; i <= maxNum; ++i) {
    if (isPrime(i) == true)
        primes.push_back(i);
  }
    
  mSquare = new int*[size];
  for(int i = 0; i < size; ++i)
    mSquare[i] = new int[size];

  for(int i = 0; i < size; ++i)
    for(int j = 0; j < size; ++j) {
        mSquare[i][j] = 0;
  }
  
  qBoard = new char*[size];
  for(int i = 0; i < size; ++i)
    qBoard[i] = new char[size];

  for(int i = 0; i < size; ++i)
    for(int j = 0; j < size; ++j) {
        qBoard[i][j] = '_';
  }
}


MagicQ::~MagicQ()
{
  for(int i = 0; i < size; ++i)
    delete[] mSquare[i];
  delete[] mSquare;
  
  for(int i = 0; i < size; ++i)
    delete[] qBoard[i];
  delete[] qBoard;  
}


void MagicQ::printQBoard()
{
  cout << "Queens board: " << endl;
  for(int i = 0; i < size; ++i)
  {
    cout << "|";
    for(int j = 0; j < size; ++j)
      cout << setw(2) << qBoard[i][j] << setw(2) <<  "|";
    cout << endl;
  }
  cout << endl;
}


void MagicQ::printMSquare()
{   
  for(int i = 0; i < size; ++i)
  {
    cout << "|";
    for(int j = 0; j < size; ++j) {
      if (isPrime(mSquare[i][j]) == true) {
          if (qBoard[i][j] == 'Q') {
            if (mSquare[i][j] / 10 == 0)
                cout << " *" << mSquare[i][j] << "|";
            else
                cout << "*" << mSquare[i][j] << "|";
          } else {
              if (mSquare[i][j] / 10 == 0)
                cout << " +" << mSquare[i][j] << "|";
              else
                cout << "+" << mSquare[i][j] << "|";
          }
     } else
         cout << setw(3) << mSquare[i][j] << "|";
    }
    cout << endl;
  }
  cout << endl;
}


bool MagicQ::solveQueensTil(int col)
{   
  if (col == size) {
    printQBoard();
    if (solveMagicTil() == false)
      cout << "A relationship between magic squares and queens problem does not exist...\n" << endl;
    return true;
  }
 
  bool check = false;  
  
  for(int i = 0; i < size; ++i) {
    if (isSafeForQ(i, col) == true) {
        qBoard[i][col] = 'Q';
        check = solveQueensTil(col + 1) || check;
        qBoard[i][col] = '_';
    }
  } 
  return check;
}


bool MagicQ::solveMagicTil()
{
  int primeData[size];
  
  generateCombos(primeData, 0, primes.size() - 1, 0); 
 
  if (exists == true)
    cout << "Magic square(s): " << endl;
 
  return exists;
}


bool MagicQ::checkMagic()
{   
  int currRow = 0;
    
  for(int i = 0; i < size; ++i) {
    for(int j = 0; j < size; ++j)
        currRow += mSquare[i][j];
    if (currRow != magicC)
        return false;
    currRow = 0;
  }
    
  int currCol = 0;
    
  for(int i = 0; i < size; ++i) {
    for(int j = 0; j < size; ++j)
        currCol += mSquare[j][i];
    if (currCol != magicC)
        return false;
    currCol = 0;      
  }

  int currDiag = 0;
    
  for(int i = 0; i < size; ++i)
    currDiag += mSquare[i][i];
  if (currDiag != magicC)
    return false;
    
  currDiag = 0;

  for(int i = size - 1; i >= 0; --i)
    currDiag += mSquare[i][i];
  if (currDiag != magicC)
    return false;
    
  return true;
}
    

bool MagicQ::isPrime(int num)
{
 if (num > 1) {
    for(int i = 2; i <= num / 2; ++i) {
      if (num % i == 0)
        return false;
    }
    return true;
 } else {
    return false;
  }
}
    

bool MagicQ::isSafeForQ(int row, int col)
{
  int i , j;
  for(i = 0; i < col; i++)
    if (qBoard[row][i] == 'Q')
      return false;

  for(i = row, j = col; i >= 0 && j >= 0; i--, j--)
    if (qBoard[i][j] == 'Q')
      return false;

  for(i = row, j = col; i < size && j >= 0; i++, j--)
    if (qBoard[i][j] == 'Q')
      return false;

  return true;
}

    
void MagicQ::generateCombos(int primeData[], int start, int end, int idx)
{   
  if(idx == size) {
      findPermutations(primeData);
      return;
  }
     
  for (int i = start; i <= end && end - i + 1 >= size - idx; ++i) {
     primeData[idx] = primes[i];
     generateCombos(primeData, i + 1, end, idx + 1);
 }
}


void MagicQ::findPrimePermutations(int primeData[])
{   
  sort(primeData, primeData + size);
   
  do {
      findPermutations(primeData);
  } while(next_permutation(primeData, primeData + size));
}


void MagicQ::findPermutations(int primeData[])
{
  int newSize = maxNum - size;
  int remNum[newSize]; 
 
  int i = 1;
  int j = 0;
  int k = 0;
    
  while(i <= maxNum) {
      if(primeData[j] == i) {
        j++;
      } else {
        remNum[k] = i;
        k++;
      }
      i++;
  }
 
  sort(remNum, remNum + (maxNum - size));
    
  do {
    fillMSquare(primeData, remNum);
    if(checkMagic() == true) {
        printMSquare();
        exists = true;
        return;
    }
    printMSquare();
  } while(next_permutation(remNum, remNum + (maxNum - size)));
}


void MagicQ::fillMSquare(int primeData[], int remNum[])
{
  int n = 0;
    
  for(int i = 0; i < size; ++i) {
    for(int j = 0; j < size; ++j) {
        if (qBoard[i][j] == 'Q')
            mSquare[i][j] = primeData[i];
        else {
            mSquare[i][j] = remNum[n];
            n++;
        }
    }
  }
}


void MagicQ::goMagicQ() 
{
  if(solveQueensTil(0) == false) {
      cout << "Queens solution does not exist..." << endl;
      return;
  }
  cout << "Magic constant: " << magicC << endl;
  cout << "Primes from 1 to n^2: ";
  for(int i = 1; i <= maxNum; ++i) {
    if (isPrime(i) == true) {
        cout << i << " ";
    }
  }
  cout << endl;
 
  cout << "Legend:" << endl;
  cout << "* = queens location (prime number)" << endl;
  cout << "+ = prime number" << endl;
  cout << endl;
    
  return;       
}
