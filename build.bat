@echo off
g++ ^
-fdiagnostics-color=always -g ^
main.cpp ^
sortingAlgorithms/insertionSort.cpp ^
sortingAlgorithms/mergeSort.cpp ^
sortingAlgorithms/sortingVisualiser.cpp ^
GraphBuilding/runGraphBuilder.cpp ^
GraphBuilding/traversal.cpp ^
draw.cpp initialize.cpp button.cpp GraphBuilding/node.cpp ^
-Iheaders ^
-I"SFML-3.0.0/include" ^
-Wall ^
-o algoVisualiser.exe ^
-L"SFML-3.0.0/lib" ^
-lsfml-graphics -lsfml-window -lsfml-system

echo Done! main.exe is ready.
pause