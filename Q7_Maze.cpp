// CPP program to solve Rat in a maze 
// problem with backtracking using stack 
  
#include <cstring> 
#include <iostream> 
#include <stack> 
  
using namespace std; 
  
#define N 4 
#define M 5 
  
class node { 
public: 
    int x, y; 
    int dir; 
  
    // establishes coordinates of the rat
    node(int i, int j) 
    { 
        x = i; 
        y = j; 
          
        // sets initial direction to 0 
        dir = 0; 
    } 
}; 
  
// creates the maze from an n*m matrix 
int n = N, m = M; 
  
// establishes the coordinats for the food
int fx, fy;
//returns if the cell of the maze was visited or not
bool visited[N][M]; 
//returns if the cell of the maze is reachable or not  
bool isReachable(int maze[N][M]) 
{ 
    // starts the rat at coordinates (0, 0). 
    int i = 0, j = 0; 
      
    // creates the stack
    stack<node> s; 
      
    node temp(i, j); 
      
    s.push(temp); 
  
    //while the stack is not empty
    while (!s.empty()) { 
  
        //pops off the top node and moves it based on the value of the node's direction variable
        temp = s.top(); 
        int d = temp.dir; 
        i = temp.x, j = temp.y; 
  
        //increases the direction variable and pushes the node in the stack again
        temp.dir++; 
        s.pop(); 
        s.push(temp); 
  
        // if the rat reaches the food coordinate, we return true
        if (i == fx and j == fy) { 
            return true; 
        } 
  
        // checks the Up direction 
        if (d == 0) { 
            if (i - 1 >= 0 and maze[i - 1][j] and  
                                    visited[i - 1][j]) { 
                node temp1(i - 1, j); 
                visited[i - 1][j] = false; 
                s.push(temp1); 
            } 
        } 
  
        // checks the left direction 
        else if (d == 1) { 
            if (j - 1 >= 0 and maze[i][j - 1] and  
                                    visited[i][j - 1]) { 
                node temp1(i, j - 1); 
                visited[i][j - 1] = false; 
                s.push(temp1); 
            } 
        } 
  
        // checks the down direction 
        else if (d == 2) { 
            if (i + 1 < n and maze[i + 1][j] and  
                                    visited[i + 1][j]) { 
                node temp1(i + 1, j); 
                visited[i + 1][j] = false; 
                s.push(temp1); 
            } 
        } 
        // checks the right direction 
        else if (d == 3) { 
            if (j + 1 < m and maze[i][j + 1] and  
                                    visited[i][j + 1]) { 
                node temp1(i, j + 1); 
                visited[i][j + 1] = false; 
                s.push(temp1); 
            } 
        } 

        // if none of the directions lead to the food, we take the rat back to where it came from
        else { 
            visited[temp.x][temp.y] = true; 
            s.pop(); 
        } 
    } 
  
    // if we run through the whole stack and there is no path available, we return false
    return false; 
} 
  
// shows how the code works in the main function
int main() 
{ 
    // initially sets the visited array to true array to true (unvisited) 
    memset(visited, true, sizeof(visited)); 
      
    // creates the matrix for the maze
    int maze[N][M] = { 
        { 1, 0, 1, 1, 0 }, 
        { 1, 1, 1, 0, 1 }, 
        { 0, 1, 0, 1, 1 }, 
        { 1, 1, 1, 1, 1 } 
    }; 
  
    // establishes coordinates for the food 
    fx = 2; 
    fy = 3; 
  
    if (isReachable(maze)) { 
        cout << "Path Found!" << '\n'; 
    } 
    else
        cout << "No Path Found!" << '\n'; 
          
    return 0; 
} 