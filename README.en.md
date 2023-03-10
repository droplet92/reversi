# reversi

A simple reversi(othello) game.   
It was implemented using SFML(Simple and Fast Multimedia Library) and C++17.  

Development Environment: Visual Studio 2019(https://www.sfml-dev.org/tutorials/2.5/start-vc.php)

#Algorithm 
I used the minimax algorithm(https://en.wikipedia.org/wiki/Minimax) for implement the game AI.   
   
In the reversi game, every time a player places a stone, the stones on the board are flipped over again.   
This makes it difficult for him to determine whether he has an advantage at the time he places a stone.   
So the AI's goal is to minimize the number of stones its opponent can place on its next turn.   
   
The leaf nodes of the number tree generated by the AI are the number of stones (l) that can be placed on the opponent's (player's) turn.   
The parent nodes of the leaf nodes are called group nodes.   
The value g of that group node chooses the maximum of the values l of its child nodes.
> g = max(l1, l2, ..., ln)
   
On the AI's turn, it chooses the minimum of the child nodes' values of g.
> c = min(g1, g2, ..., gn)

Repeat the process to select a stone for the next turn.