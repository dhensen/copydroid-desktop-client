#include <QtCore/QCoreApplication>

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
using std::ios;

#include <fstream>
using std::ofstream;



int main(int argc, char *argv[])
{
    if (argc != 4) {
        cout << "Usage: version.exe <MAJOR> <MINOR> <VERSION_HEADER>" << endl;
    } else {
        ofstream outHeaderFile(argv[3], ios::out);

        if (!outHeaderFile) {
            cerr << "File could not be opened" << endl;
            return 1;
        }

        outHeaderFile << "#ifndef VERSION_H" << endl;
        outHeaderFile << "#define VERSION_H" << endl;
        outHeaderFile << endl;
        outHeaderFile << "namespace Version" << endl;
        outHeaderFile << "{" << endl;
        outHeaderFile << " static const int MAJOR = " << argv[1] << ";" << endl;
        outHeaderFile << " static const int MINOR = " << argv[2] << ";" << endl;
        outHeaderFile << " static const int REVISION = " << "1234" << ";" << endl;
        outHeaderFile << " static const int BUILD = " << "5678" << ";" << endl;
        outHeaderFile << "}" << endl;
        outHeaderFile << endl;
        outHeaderFile << "#endif // VERSION_H" << endl;

    }

    // ofstream destructor will close file for us.

    return 0;
}
