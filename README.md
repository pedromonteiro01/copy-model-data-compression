# Algorithmic Information Theory - 1st Project

Development Team:
| Nmec  | Name            | Email                    |
|-------|----------------|--------------------------|
| 97484 | Pedro Monteiro | pmapm@ua.pt              |
| 98512 | Eduardo Fernandes | eduardofernandes@ua.pt |
| 98597 | José Trigo        | josetrigo@ua.pt          |

This repository contains the implementation of an automatic text generator and data compression tool based on the copy model approach. The copy model exploits self-similarities within data sources to efficiently represent data through references to previously occurring parts with minor modifications. This project aims to provide an understanding of copy models in the context of algorithmic information theory and their application in data compression and automatic text generation.

## How to run cpm program
Change to src folder
```
cd src/
```

Compile
```
g++ -std=c++11 cpm.cpp -o cpm
```

Just run the executable file with the parameters
```
./cpm <filename> <k> <alpha> <fail_threshold>
```

## How to run cpm_gen program
Change to src folder
```
cd src/
```

Compile
```
g++ -std=c++11 cpm_gen.cpp -o cpm_gen
```

Just run the executable file with the parameters
```
./cpm_gen <filename> <k> <size>
```

## Example for cpm
Run the cpm program with the test.txt file in examples folder. First it is necessary to change to src/ folder
```
cd src/
```

After that, you should compile the cpm program code
```
g++ -std=c++11 cpm.cpp -o cpm
```

Finally, just run the executable with the filename, k, alpha and threshold parameters. In this case was used a k=4, alpha=1 and threshold=3
```
./cpm ../examples/test.txt 4 1 3
```

This should be printed in the terminal
```
Hits: 8
Fails: 0
Estimated total bits: 2.32193
Average bits per symbol: 0.17861
```

## Example for cpm_gen
Run the cpm_gen program with the chry.txt file in examples folder. First it is necessary to change to src/ folder
```
cd src/
```

After that, you should compile the cpm program code
```
g++ -std=c++11 cpm_gen.cpp -o cpm_gen
```

Finally, just run the executable with the filename, k, size of output text. In this case was used a k=4 and size=10
```
./cpm_gen ../examples/chry.txt 4 10
```

This should be printed in the terminal
```
AATTCTGCCT
```