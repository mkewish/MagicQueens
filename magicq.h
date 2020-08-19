// File: magicq.h

#ifndef MAGIC_H
#define MAGIC_H
#include <vector>
#include <fstream>
#include <string>
    
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
        bool equalsMagicC(int data[]);
        bool isPrime(int num);
        bool isSafeForQ(int row, int col);
        void generateCombos(int primeData[], int start, int end, int idx, std::fstream& file);
        void printToFile(int data[], std::fstream& file); 
        void findPermutations(int data[], std::fstream& file);
        void fillMSquare(int primeData[], int remNum[]);
        void fileOpen(std::fstream& file, std::string name, char mode);
        void goMagicQ();
     
    private:
        int size;
        int maxNum;
        int magicC;
        int solNum;
        char** qBoard;
        int** mSquare;
        std::vector <int> range;

};

#endif