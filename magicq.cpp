// File: magicq.cpp

#include <iostream>
#include <bits/stdc++.h> 
#include <vector>
    
#include "magicq.h"
    
using namespace std;


// initializes queens board and magic square matrices based on user input
MagicQ::MagicQ() 
{   
  int n;
    
  do {
    cout << "Please enter a desired matrix size (nxn): ";
    cin >> n;
    if (n < 1)
        cout << "Invalid input. Must be a positive number" << endl;
    else if (n <= 3)
        cout << "Queens solution does not exist. Must be larger than  3" << endl;
    cout << endl;
  } while (n <= 3);
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


// deletes both queens board and magic square matrices
MagicQ::~MagicQ()
{
  for(int i = 0; i < size; ++i)
    delete[] mSquare[i];
  delete[] mSquare;
  
  for(int i = 0; i < size; ++i)
    delete[] qBoard[i];
  delete[] qBoard;  
}


// prints queens board
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


// prints magic square
void MagicQ::printMSquare()
{   
  cout << "Magic square " << solNum << ": " << endl;
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


// solves for all queens solutions of size n
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


// solves for all magic squares for each queens solution
bool MagicQ::solveMagicTil()
{
  int primeData[size];
  
  //generateCombos(primeData, 0, primes.size() - 1, 0); 

  return exists;
}


// checks if a matrix is a magic square
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
    

// checks if numbers are prime
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
    

// checks if a spot in a nxn matrix is safe for a queen
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

    
// generates a series of prime combinations for each queen solution
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


// generates all permutations in primeData[]
void MagicQ::findPrimePermutations(int primeData[])
{   
  sort(primeData, primeData + size);
   
  do {
      findPermutations(primeData);
  } while(next_permutation(primeData, primeData + size));
}


// generates all permutations not in primeData[]
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
        solNum++;
        printMSquare();
        exists = true;
        return;
    }
    solNum++;
    printMSquare();
  } while(next_permutation(remNum, remNum + (maxNum - size)));
}


// fills magic square matrix with prime and non prime numbers
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


// executes program
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
