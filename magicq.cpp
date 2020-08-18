// File: newMagicq.cpp
// Compile: g++ newMagicqTst.cpp newMagicq.cpp -o magicq
// Execute: ./magicq

#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
    
#include "newMagicq.h"
    
using namespace std;


// initializes queens board and magic square matrices based on user input
NewMagicQ::NewMagicQ() 
{   
  ofstream outputFile("combos.txt");
  solNum = 0;  
  exists = false;
    
  int n;
    
  do {
    cout << "Please enter a desired matrix size (nxn): ";
    cin >> n;
    if (n < 1)
        cout << "Invalid input. Must be a positive number" << endl;
    else if (n <= 3)
        cout << "Queens solution does not exist. Must be larger than 3" << endl;
  } while (n <= 3);
  cout << endl;
    
  size = n;
  maxNum = size * size;
  magicC = (size * (maxNum + 1)) / 2;
    
  for(int i = 1; i <= maxNum; ++i)
    range.push_back(i);
    
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
    
  int data[size];
 
  cout << "Generating combinations...\n" << endl;
  generateCombos(data, 0, range.size() - 1, 0, outputFile);
  
  outputFile.close();
}


// deletes both queens board and magic square matrices
NewMagicQ::~NewMagicQ()
{
  for(int i = 0; i < size; ++i)
    delete[] mSquare[i];
  delete[] mSquare;
  
  for(int i = 0; i < size; ++i)
    delete[] qBoard[i];
  delete[] qBoard;  
}


// prints queens board
void NewMagicQ::printQBoard()
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


// prints magic square, * and + next to primes depending on their placements
void NewMagicQ::printMSquare()
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


// solves for all queens solutions of size n and executes search for magic squares
bool NewMagicQ::solveQueensTil(int col)
{   
  if (col == size) {
    printQBoard();
    if (solveMagicTil() == false)
      cout << "A relationship between the queen's solution and magic square does not exist...\n" << endl;
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
bool NewMagicQ::solveMagicTil()
{
  ifstream inputFile("combos.txt");
   
  int data[size];
    
  /*for(int i = 0; i < size; ++i) {
      inputFile >> data[i];
      cout << data[i] << "  ";
  }*/
    
  cout << endl;
  
  
  return exists;
}


// checks if a matrix is a magic square, equalsMagicC() already checks rows
bool NewMagicQ::checkMagic()
{    
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


// checks if the sum of the data set equals the magic constant
bool NewMagicQ::equalsMagicC(int data[])
{
  int total = 0;
  bool flag = false;
    
  for(int i = 0; i < size; ++i) {
    if(isPrime(data[i]) == true)
       flag = true;
    total += data[i];
  }
      
  if(total == magicC && flag == true) 
    return true;
  else
    return false;
}
    

// checks if number is prime
bool NewMagicQ::isPrime(int num)
{
  if (num > 1) {
    for(int i = 2; i <= num / 2; ++i) {
        if (num % i == 0)
            return false;
    }
    return true;
  } else
    return false;
}
   

// checks if a spot in a nxn matrix is safe for a queen
bool NewMagicQ::isSafeForQ(int row, int col)
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
void NewMagicQ::generateCombos(int data[], int start, int end, int idx, ofstream& file)
{   
  if(idx == size) {
      if(equalsMagicC(data) == true) {
        printToFile(data, file);
      }
      return;
  }
     
  for (int i = start; i <= end && end - i + 1 >= size - idx; ++i) {
     data[idx] = range[i];
     generateCombos(data, i + 1, end, idx + 1, file);
 }
}


// displays the contents in an array
void NewMagicQ::printToFile(int data[], ofstream& file) 
{ 
    for (int i = 0; i < size; i++) { 
        file << data[i] << "  "; 
    }
    file << endl; 
}


// generates all permutations in primeData[]
/*void MagicQ::findPrimePermutations(int primeData[])
{   
  sort(primeData, primeData + size);
   
  do {
      findPermutations(primeData);
  } while(next_permutation(primeData, primeData + size));
}*/


// generates all permutations not in primeData[]
/*void MagicQ::findPermutations(int primeData[])
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
*/

// fills magic square matrix with prime and non prime numbers
void NewMagicQ::fillMSquare(int primeData[], int remNum[])
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


// creates a file containing all combinations
/*void NewMagicQ::fileOpen(fstream& file, char name[], char mode)
{
  if(mode == 'r')
    file.open(name, ios::in);
  if(mode == 'w')
    file.open(name, ios::out);

  if(file.fail())
  {
    cout << "Error opening " << name << " file..." << endl;
    exit(EXIT_FAILURE);
  }
}*/


// executes program
void NewMagicQ::goMagicQ() 
{
  if(solveQueensTil(0) == false) {
      cout << "Queens solution does not exist..." << endl;
      return;
  } //else if(exists == true) {
    cout << "Magic constant: " << magicC << endl;
    cout << "Primes from 1 to n^2: ";
    for(int i = 1; i <= maxNum; ++i) {
      if (isPrime(i) == true)
         cout << i << " ";
    }
    cout << endl;
 
    cout << "Legend:" << endl;
    cout << "* = queens location (prime number)" << endl;
    cout << "+ = prime number" << endl;
    cout << endl;
    //cout << "Number of combos: " << num << endl;
  //}
    
  return;       
}