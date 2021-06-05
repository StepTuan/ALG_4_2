#include <iostream>
#include "RBTree.h"
#include "List.h"
#include "Line.h"

using namespace std;

int main()
{
    cout << "input string: ";
    string input;
    getline(cin, input);
    try
    {
        Line Str(input);
        cout << "Code: " << Str.get_code() << endl;
        cout << "Decode: " << Str.get_decode() << endl;
        cout << "Compression ratio: " << Str.get_compression_ratio() << endl << endl;
        Str.print_freq_table();
        Str.print_code_table();
    }
    catch (exception& exception)
    {
        cout << exception.what();
    }
}
