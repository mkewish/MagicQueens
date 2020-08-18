// File: newMagicq.h

#ifndef NEWMAGICQ_H
#define NEWMAGICQ_H
#include <vector>
#include <fstream>
    
class NewMagicQ
{
    public:
        NewMagicQ();
        ~NewMagicQ();
        void printQBoard();
        void printMSquare();
        bool solveQueensTil(int col);
        bool solveMagicTil(); 
        bool checkMagic();
        bool equalsMagicC(int data[]);
        bool isPrime(int num);
        bool isSafeForQ(int row, int col);
        void generateCombos(int primeData[], int start, int end, int idx, std::ofstream& file);
        void printToFile(int data[], std::ofstream& file);
        //void display(std::ifstream& file);
        //void findPrimePermutations(int primeData[]);
        //void findPermutations(int primeData[]);
        void fillMSquare(int primeData[], int remNum[]);
        //void fileOpen(fstream& file, char name[], char mode);
        void goMagicQ();
     
    private:
        int size;
        int maxNum;
        int magicC;
        int solNum;
        //int num = 0;
        bool exists;
        char** qBoard;
        int** mSquare;
        std::vector <int> range;
        std::vector <int> combos;

};

#endif