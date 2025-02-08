# BB5-contiguous-1s

This repository was made with the intent of finding the length of the longest string of contiguous 1s a halting 5-state Turing machine can leave on a tape after halting.

## Before Running

Please download the ```bb5_verified_enumeration.csv.zst``` file [here](https://docs.bbchallenge.org/bb5_final_release/bb5_verified_enumeration.csv.zst), then decompress it. Make sure the decompressed file is called ```bb5_verified_enumeration.csv``` and is located in the same folder as both programs. Due to file size limitations, these files, along with others generated by the programs, cannot be included directly in this repository.

## Programs

```isolate_halting_machines.cpp``` reads the ```bb5_verified_enumeration.csv``` file (created by the [Busy Beaver Challenge Community](https://bbchallenge.org)), which contains all 5-state Turing machines, then generates the ```bb5_halting_machines.csv``` file containing only the halting machines.

```main.cpp``` runs all of the halting machines and records a few metrics for each one in a ```bb5_machine_results.csv``` file:
- ```steps```: The number of steps the machine will run for before halting
- ```score```: The number of 1s written on the tape after the machine has halted
- ```space```: The number of cells the machine visits before halting
- ```contiguous_1s```: The length of the longest string of contiguous 1s written on the tape after the machine has halted

The program then records the largest values found for each metric in a ```bb5_best_results.txt``` file.

Please run the programs in this order, as they will not work otherwise.

## Results

The largest value found for ```contiguous_1s``` is 164, achieved by two machines: ```0RB1LD_1LC1RB_1LD1RE_1LA1LE_---0RC``` and ```1RB1LA_1RC1LE_1RD1RE_0LA1RC_---0LB```.