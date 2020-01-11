#include <iostream>
#include <fstream>
#include <cstring>
#include "hashChains.h"

using namespace std;

// constants
const int DIVISOR = 4099,       // hash function DIVISOR
          MAX_CODES = 4096,     // 2^12
          BYTE_SIZE = 8,
          EXCESS = 4,           // 12 - BYTE_SIZE
          ALPHA = 256,          // 2^BYTE_SIZE
          MASK1 = 255,          // ALPHA - 1
          MASK2 = 15;           // 2^EXCESS - 1
// data type for code table
// pair.first = key, pair.second = code
typedef pair<const long, int> pairType;

// globals
int leftOver;              // code bits yet to be output
bool bitsLeftOver = false; // false means no bits in leftOver
ifstream in;               // input file
ofstream out;              // output file


namespace lzwcompress
{
    void setFiles(int argc, char* argv[])
    {
        char inputFile[150], outputFile[150];
        if(argc == 3)
            strcpy(inputFile, argv[2]);
        else
        {
            cout << "Enter name of file to compress" << endl;
            cin >> inputFile;
        }

        // open files in binary mode
        in.open(inputFile, ios::binary);
        if (in.fail())
        {
            cerr << "Cannot open " << inputFile << endl;
            exit(1);
        }
        strcpy(outputFile, inputFile);
        strcat(outputFile, ".zzz");
        out.open(outputFile, ios::binary);
    }

    void output(long code);

    void compress()
    {
        // Lempel-Ziv-Welch compressor.
        // define and initialize the code dictionary
        hashChains<long, int> h(DIVISOR);
        for(int i = 0; i < ALPHA; ++i)
            h.insert(pairType(i, i));
        int codesUsed = ALPHA;
        // input and compress
        int c = in.get(); // first character of input file
        if(c != EOF)
        {// input file is not empty
            long pcode = c;
            while((c = in.get()) != EOF)
            {//process character c
                long theKey = (pcode << BYTE_SIZE) + c;
                pairType* thePair = h.find(theKey);
                if(thePair == NULL)
                {//theKey is not in the table
                    output(pcode);
                    if(codesUsed < MAX_CODES) //create new code
                        h.insert(pairType((pcode << BYTE_SIZE) | c, codesUsed++));
                    pcode = c;
                }
                else
                    pcode = thePair->second;
            }

            //output last code
            output(pcode);
            if(bitsLeftOver)
                out.put(leftOver << EXCESS);
        }
        out.close();
        in.close();
    }

    void output(long pcode)
    {// Output 8 bits, save rest in leftOver.
        int c, d;
        if(bitsLeftOver)
        {// half byte remains from before
            d = int(pcode & MASK1);
            c = int((leftOver << EXCESS) | (pcode >> BYTE_SIZE));
            out.put(c);
            out.put(d);
            bitsLeftOver = false;
        }
        else
        {// no bits remain from before
            leftOver = pcode & MASK2; // right EXCESS bits
            c = int(pcode >> EXCESS);
            out.put(c);
            bitsLeftOver = true;
        }
    }
}

namespace lzwdecompress
{
    typedef pair<int, char> pairType;
    pairType ht[MAX_CODES];
    char s[MAX_CODES];
    int size;
    void setFiles(int argc, char* argv [])
    {// Determine file name.
        char inputFile[150], outputFile[150];

           // see if file name provided
        if (argc == 3)
            strcpy(outputFile, argv[2]);
        else
        {// name not provided, ask for it
             cout << "Enter name of file to decompress"
                  << endl;
             cout << "Omit the extension .zzz"  << endl;
             cin >> outputFile;
        }

        strcpy(inputFile, outputFile);
        strcat(inputFile, ".zzz");

        // open files in binary mode
        in.open(inputFile, ios::binary);
        if(in.fail())
        {
            cerr << "Cannot open " << inputFile << endl;
            exit(1);
        }
        out.open(outputFile, ios::binary);
    }

    bool getCode(int &code);
    void output(int code);

    void decompress()
    {//decompress a compressed file
        int codesUsed = ALPHA;

        //input and decompress
        int pcode,
            ccode;
        if(getCode(pcode))
        {//file is not empty
            s[0] = pcode;
            out.put(s[0]);
            size = 0;

            while(getCode(ccode))
            {
                if(ccode < codesUsed)
                {//code is defined
                    output(ccode);
                    if(codesUsed < MAX_CODES)
                    {//create new code
                        ht[codesUsed].first = pcode;
                        ht[codesUsed++].second = s[size];
                    }
                }
                else
                {//specical case, undefined code
                    ht[codesUsed].first = pcode;
                    ht[codesUsed++].second = s[size];
                    output(ccode);
                }
                pcode = ccode;
            }
        }
        out.close();
        in.close();
    }

    bool getCode(int& code)
    {// Put next code in compressed file into code.
     // Return false if no more codes.
        int c, d;
        if((c = in.get()) == EOF)
            return false;

        // see if any left over bits from before
        // if yes, concatenate with left over 4 bits
        if(bitsLeftOver)
            code = (leftOver << BYTE_SIZE) | c;
        else
        {// no left over bits, need four more bits
         // to complete code
            d = in.get();
            code = (c << EXCESS) | (d >> EXCESS);
            leftOver = d & MASK2;    //save 4 bits
        }
        bitsLeftOver = !bitsLeftOver;
        return true;
    }
    void output(int code)
    {// Output string corresponding to code.
        size = -1;
        while (code >= ALPHA)
        {// suffix in dictionary
            s[++size] = ht[code].second;
            code = ht[code].first;
        }
        s[++size] = code;  // code < ALPHA

        // decompressed string is s[size] ... s[0]
        for (int i = size; i >= 0; i--)
            out.put(s[i]);
    }
}

int main(int argc, char* argv[])
{
    if(argc < 3)
        cout << "usage: <compress/decompress> <filename>" << endl;
    else
    {
        if(strcmp(argv[1], "compress") == 0)
        {
           lzwcompress::setFiles(argc, argv);
           lzwcompress::compress();
        }
        else
        {
            lzwdecompress::setFiles(argc, argv);
            lzwdecompress::decompress();
        }
    }

   return 0;
}
