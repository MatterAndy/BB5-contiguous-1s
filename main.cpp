#include <fstream>
#include <set>

using namespace std;

struct machine_results {
    unsigned long long steps; // The number of steps the machine takes before halting
    unsigned long long score; // The number of 1s written on the tape after halting
    unsigned long long space; // The number of cells the machine visits before halting
    unsigned long long contiguous_1s; // The length of the longest string of contiguous 1s on the tape after halting
};

// Function to calculate the length of the longest string of contiguous 1s on a given tape
unsigned long long contiguous_1s(set<long long> tape) {
    unsigned long long count = 0;
    unsigned long long best_count = 0;
    // Check all cells that contain a 1 (from left to right)
    for (long long cell : tape) {
        // If the previous cell also contains a 1, increase the counter
        if (tape.count(cell-1)) {
            count++;
        // Else, reset the counter
        } else {
            count = 1;
        }
        best_count = max(best_count, count);
    }
    return best_count;
}

machine_results run_machine(string program) {
    set<long long> tape; // Store the cells that contain a 1
    set<long long> visited; // Store the visited cells
    unsigned long long steps = 0; // Store the number of steps taken
    long long head = 0; // Store the head's position
    char state = 'A'; // Store the current state

    while (true) {
        steps++;
        visited.insert(head);

        bool read_symbol = tape.count(head); // true -> a 1 is written at the head's position, false -> a 0 is written at the head's position
        int program_idx = (state - 'A') * 7 + read_symbol * 3; // The index of the starting character that corresponds to the next action in the program

        state = program[program_idx+2]; // Transition to the next state

        // Halt if the next action is undefined
        if (state == '-') {
            machine_results results;
            results.steps = steps;
            results.score = tape.size();
            results.space = visited.size();
            results.contiguous_1s = contiguous_1s(tape);
            return results;
        }

        // Write to the tape according to the defined action
        if (program[program_idx] == '0') {
            tape.erase(head);
        } else {
            tape.insert(head);
        }

        // Move according to the defined action
        if (program[program_idx+1] == 'L') {head--;}
        else {head++;}
    }
}

int main() {
    // Store the best (largest) values for each metric
    unsigned long long best_steps = 0;
    unsigned long long best_score = 0;
    unsigned long long best_space = 0;
    unsigned long long best_contiguous_1s = 0;

    ifstream read_file("bb5_halting_machines.csv");
    ofstream write_file("bb5_machine_results.csv");

    string line;
    getline(read_file, line);
    write_file << "machine,steps,score,space,contiguous_1s";

    // Run every machine and record the results
    while (getline(read_file, line)) {
        string program = line.substr(0, 34);
        machine_results results = run_machine(program);
        best_steps = max(best_steps, results.steps);
        best_score = max(best_score, results.score);
        best_space = max(best_space, results.space);
        best_contiguous_1s = max(best_contiguous_1s, results.contiguous_1s);
        write_file << '\n' << program << ',' << results.steps << ',' << results.score << ',' << results.space << ',' << results.contiguous_1s;
    }

    write_file.close();
    read_file.close();

    // Record the best results
    ofstream best_results_file("bb5_best_results.txt");
    best_results_file << "steps: " << best_steps << '\n';
    best_results_file << "score: " << best_score << '\n';
    best_results_file << "space: " << best_space << '\n';
    best_results_file << "contiguous_1s: " << best_contiguous_1s;
    best_results_file.close();

    return 0;
}