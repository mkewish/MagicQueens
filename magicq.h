// File: magicq.h

#ifndef MAGIC_H
#define MAGIC_H
#include <vector>
#include <fstream>
    
class MagicQ
{
    public:
        MagicQ();
        ~MagicQ();
        void printQBoard();
        void printMSquare();
        bool solveQueensTil(int col);
        bool solveMagicTil(); 
        bool checkMagic();
        bool equalsMagicC(int data[])
        bool isPrime(int num);
        bool isSafeForQ(int row, int col);
        void generateCombos(int primeData[], int start, int end, int idx);
        void printToFile(int data[], ofstream& file) 
        //void findPrimePermutations(int primeData[]);
        //void findPermutations(int primeData[]);
        void fillMSquare(int primeData[], int remNum[]);
        void goMagicQ();
     
    private:
        int size;
        int maxNum;
        int magicC;
        int solNum;
        bool exists;
        char** qBoard;
        int** mSquare;
        std::vector <int> range;
        std::vector <int> combos;

};

#endif