#include <fstream>

using namespace std;

int main() {
    ifstream read_file("bb5_verified_enumeration.csv");
    ofstream write_file("bb5_halting_machines.csv");

    string line;
    getline(read_file, line);
    write_file << line;

    // All halting machines (and only halting machines) have an 'h' at character 35
    while (getline(read_file, line)) {
        if (line[35] == 'h') {
            write_file << '\n' << line;
        }
    }

    write_file.close();
    read_file.close();

    return 0;
}