# AStarSimulation

## About

A simulation written in C++/SFML. The idea was to simulate bots hanging around the map and avoiding obstacles. Bots goal is to reach the destination point which is the mouse cursor position. Each of them computes the shortest path between its position and the end node with an A* algorithm, then follows it. Obstacle nodes are excluded from the graph.
There are two modes of displaying. The first shows what an average player is able to see in such games. The second, beside that, includes drawn shortest paths, end point marked with blue, start points marked with red and and visited nodes during the algorithm proceeding - marked with green. Instensity of the green colour represents a number of bots which were searching on the given node. Thus, this mode visualizes the processes taking place in such games beyond the observer's eye. The bigger number of nodes, the more accurate the algorithm will be, and the nicer look we would get. For the purpose of this AI project, i implemented small graph/grid just to have it working and to be showing what it is supposed to show. That's why there is no collision implemented too. 
I have used pre-coded with my mate in advance engine-like stuff.

## Toolbox

- Space (switch between modes)
- Mouse click (put/remove obstacle)
- Shift (pause/unpause)
- Ctrl (switch between A* search modes)
- Alt (set end point to node pointed by cursor)

## Compilation

You need :
- C++17 compliant compiler
- SFML 2.5.1

If you are using Visual Studio 2019 you can simply run generate_project.bat script and the project will be ready for compiling and running.

## Screenshots

<p align="center">
	<img src="https://media.giphy.com/media/SQgLptpZfPYZ3Q6gZq/giphy.gif" alt="animated">
</p> 

