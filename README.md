# Algorithm visualiser

A simple C++ algorithm visualizer using SFML, visualising different common algorithms.

![Algorithm Visualiser](Images/Algorithm_Visualiser.gif)

# Features

I have implemented the visualisation of two sorts and two graph traversals.

## Sorting algorithms

I have implemented the visualisation of the insertion sort and merge sort algorithms. I have stored snapshots of every step of the sort so users can go through all the steps fast with the arrow keys or step by step with the mouse 1 and 2 buttons.

## Graph builder

I implemented a graph builder where the user can place nodes and edges and thereafter run a DFS or BFS on that graph.

# Installation/Build

This project is tested only on Windows. It may not work on Linux/macOS without modifications.

## Requirements
- WinLibs UCRT 14.2.0 (64-bit) (g++ compiler)
- SFML 3.0.0 is included in the repository,
- Windows 10 or later

## vscode
- Install WinLibs UCRT 14.2.0 (64-bit)
- Add it to PATH
- Press F5

## build.bat
- Install WinLibs UCRT 14.2.0 (64-bit)
- Add it to PATH
- Run build.bat
- Run algoVisualiser.exe

# Code structure

The main menu runs in main.cpp. 

## Sorting algorithms
The sorting window is run by a function in the sortingAlgorithms/sortingVisualiser.cpp, the sorting algorithms which create the snapshots are in the same folder. When the user presses one of the sorting buttons in the main menu the sorting algorithm is run, and the list of snapshots sent back to be displayed. 

## Graph builder
The graph builder window is run by a function in the GraphBuilding/runGraphBuilder.cpp, the DFS and BFS algorithms are in traversal.cpp in the same folder. When the user creates a graph the first node created is the startpoint, this can only be changed by clearing the graph and making a new one. The nodes save their neighbours in an adjacency list which is used in the searching algorithms.

# More information

More of the development process can be found on my [portfolio](https://arthurjerlstrom.wixsite.com/arthurjerlstrom/cpp).


