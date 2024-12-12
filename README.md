## Links

https://clear-galley-91d.notion.site/XXX-11113f3e202d80b0ad6bf873e742215a

## Build

```
mkdir build
cd build
cmake ..
cmake --build ./ -j4
```

## View Factorial Graph

```
./build/src/MAIN
```

## Run tests

```
./build/src/test_dfo
./build/src/test_dsu
./build/src/test_dom_tree
```

## Dump

```
IR Graph Structure:
Basic Block 0x5653964f4eb0:
  Predecessors: 
  Successors: 0x5653964f4f40 0x5653964f4fd0 
  Instructions:
    Instr ID: 1, Opcode: 4, Type: s32
    Instr ID: 2, Opcode: 5, Type: void

Basic Block 0x5653964f4f40:
  Predecessors: 0x5653964f4eb0 
  Successors: 0x5653964f5070 
  Instructions:
    Instr ID: 3, Opcode: 6, Type: s32

Basic Block 0x5653964f4fd0:
  Predecessors: 0x5653964f4eb0 
  Successors: 0x5653964f5070 
  Instructions:
    Instr ID: 4, Opcode: 2, Type: s32
    Instr ID: 5, Opcode: 7, Type: s32
    Instr ID: 6, Opcode: 1, Type: s32
    Instr ID: 7, Opcode: 6, Type: s32

Basic Block 0x5653964f5070:
  Predecessors: 0x5653964f4f40 0x5653964f4fd0 
  Successors: 
  Instructions:

```
