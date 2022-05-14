#include<bits/stdc++.h>
using namespace std;

struct matrix_puzzle {
    
    public:
    // vector so it works for any number of rows
        vector<vector<int> > puzzle;
        int g_cost;
        int h_cost;
        int blank_x; // x co-ordinates of blank 
        int blank_y;// y co-ordinates of blank 
    
        // constructor for the puzzle
        matrix_puzzle() {
            g_cost = 0;
            h_cost = 0;
            blank_x=0;
            blank_y=0;
        }
        
       // constructor for the puzzle
        matrix_puzzle(vector<vector<int> > puzzle) {
            this->puzzle = puzzle;
            g_cost = 0;
            h_cost = 0;
            pair<int, int> p = positionOfBlank();
            blank_x = p.first;
            blank_y = p.second;
        }

        pair<int, int> positionOfBlank() {
            for (int i = 0; i < puzzle.size(); ++i) {
                for(int j = 0; j < puzzle.size(); ++j) {
                    if (puzzle[i][j] == 0) {
                        pair<int, int> bl(i, j);
                        return bl;
                    }
                }
            }
            return make_pair(-1, -1);
        }
        
        int getFcost() const{
            return this->g_cost+this->h_cost;
        }
        
        // comparator for priority queue
        bool operator<(const matrix_puzzle &lhs)  const{
            return (this->getFcost() > lhs.getFcost());
        }
};


void printCst(matrix_puzzle pz) {
        cout << "value of g_cost: " << pz.g_cost << endl;
        cout << "value of h_cost: " << pz.h_cost << endl;
        cout << "value of f_cost: " << pz.g_cost + pz.h_cost << endl;
}
// cost function for MH
int costOfManhattanDistance(vector<vector<int> >puzzle) {
    int totalCost = 0;
    int n = 1;
    for (int i = 0; i < puzzle.size(); ++i) {
        for (int j = 0; j < puzzle.size() && n != puzzle.size() * puzzle.size(); ++j) {
            if (puzzle[i][j] != n) {
                int flag = false;
                for(int k = 0; k < puzzle.size(); ++k) {
                    for (int l = 0; l < puzzle.size(); ++l) {
                        if (n == puzzle[k][l]) {
                            totalCost += abs(i - k) + abs(j - l);
                            flag = true;
                            break;
                        }
                    }
                    if(flag)
                        break;
                }
            }
            ++n;
        }
    }
    if (puzzle[puzzle.size()-1][puzzle.size()-1] != 0) {
        for (int i = 0; i < puzzle.size(); ++i) {
            for (int j = 0; j < puzzle.size(); ++j) {
                if (puzzle[i][j] == 0) {
                    int sz = puzzle.size()-1;
                    totalCost += abs(sz - i) + abs(sz- j);
                }
            }
        }
    }
    return totalCost;
}

// cost function for MT
int costOfTiles(vector<vector<int> >puzzle) {
    int totalCost = 0;
    vector<int> puzzleVec;
    for (int i = 0; i < puzzle.size(); ++i) {
        for (int j = 0; j < puzzle.size(); ++j) {
            puzzleVec.push_back(puzzle[i][j]);
        }
    }
    for (int i = 0; i < puzzleVec.size() - 1; ++i) {
        if (puzzleVec[i] != i + 1) {
            totalCost += 1;
        }
    }
    if (puzzleVec[puzzleVec.size() - 1] != 0) {
        totalCost += 1;
    }
    return totalCost;
}
 void populateCost(matrix_puzzle &pz, string h) {
    pz.g_cost += 1;
    if (h == "MT") {
        pz.h_cost = costOfTiles(pz.puzzle);
    }
    else if (h == "MD") {
        pz.h_cost = costOfManhattanDistance(pz.puzzle);
    }
    else {
        pz.h_cost = 0;
    }
}

matrix_puzzle MoveNorth(matrix_puzzle pz) {
    pair<int, int> blank = make_pair(pz.blank_x, pz.blank_y);
    if (blank.first != 0) {
        int temp = pz.puzzle[blank.first - 1][blank.second];
        pz.puzzle[blank.first - 1][blank.second] = 0;
        pz.puzzle[blank.first][blank.second] = temp;
        pz.blank_x--;
    }
    return pz;
}
matrix_puzzle MoveSouth(matrix_puzzle pz) {
    pair<int, int> blank = make_pair(pz.blank_x, pz.blank_y);
    if (blank.first != pz.puzzle.size()-1) {
        int temp = pz.puzzle[blank.first + 1][blank.second];
        pz.puzzle[blank.first + 1][blank.second] = 0;
        pz.puzzle[blank.first][blank.second] = temp;
        pz.blank_x++;
    }
    return pz;
}
matrix_puzzle MoveWest(matrix_puzzle pz) {
    pair<int, int> blank = make_pair(pz.blank_x, pz.blank_y);
    if (blank.second != 0) {
        int temp = pz.puzzle[blank.first][blank.second - 1];
        pz.puzzle[blank.first][blank.second - 1] = 0;
        pz.puzzle[blank.first][blank.second] = temp;
        pz.blank_y--;
    }
    return pz;
}
matrix_puzzle MoveEast(matrix_puzzle pz) {
    pair<int, int> blank = make_pair(pz.blank_x, pz.blank_y);
    if (blank.second != pz.puzzle.size()-1) {
        int temp = pz.puzzle[blank.first][blank.second + 1];
        pz.puzzle[blank.first][blank.second + 1] = 0;
        pz.puzzle[blank.first][blank.second] = temp;
        pz.blank_y++;
    }
    return pz;
}

void printPuzzle(vector<vector<int> >puzzle) {
    for (int i = 0; i < puzzle.size(); ++i) {
        for (int j = 0; j < puzzle.size(); ++j) {
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }
}

vector<int> userInpt(string s, int puzzle_size) {
    getline(cin, s);
   s.erase(remove(s.begin(), s.end(), ' '), s.end());
    vector<int> puzzle_row;
    for (int i = 0; i < puzzle_size; ++i) {
        int x = stoi(string(1, s[i]));
        puzzle_row.push_back(x);
    }
    return puzzle_row;
}

void delimiter() {
    for (unsigned i = 0; i < 15; ++i) {
        cout << "+";
    }
    cout << endl;
}

void PrintState(matrix_puzzle my_puzzle) {
    delimiter();
    printPuzzle(my_puzzle.puzzle);
    delimiter();
    printCst(my_puzzle);
    delimiter();
}

string convertToString(vector<vector<int> > state) {
    string st_map;
    for (int i = 0; i < state.size(); ++i) {
        for (int j = 0; j < state.size(); ++j) {
            char z = state[i][j]+'0';
            st_map+=z;
        }
    }
    return st_map;
}

void visit(matrix_puzzle curr, priority_queue<matrix_puzzle> &pq, 
                map<string, bool> &visited, string h) {
    matrix_puzzle puzzle_up = MoveNorth(curr);
    matrix_puzzle puzzle_down = MoveSouth(curr);
    matrix_puzzle puzzle_left = MoveWest(curr);
    matrix_puzzle puzzle_right = MoveEast(curr);

    visited[convertToString(curr.puzzle)] = 1;
    if (visited[convertToString(puzzle_up.puzzle)] == 0) {
        populateCost(puzzle_up, h);
        pq.push(puzzle_up);
    }
    if (visited[convertToString(puzzle_down.puzzle)] == 0) {
        populateCost(puzzle_down, h);
        pq.push(puzzle_down);
    }
    if (visited[convertToString(puzzle_left.puzzle)] == 0) {
        populateCost(puzzle_left, h);
        pq.push(puzzle_left);
    }
    if (visited[convertToString(puzzle_right.puzzle)] == 0) {
        populateCost(puzzle_right, h);
        pq.push(puzzle_right);
    }
}

bool CheckGoalState(matrix_puzzle my_puzzle) {
    string goal = "123456780";
    string my_st = convertToString(my_puzzle.puzzle);
    if (goal == my_st) {
        return true;
    }
    return false;
}
//for custom input
void populate(vector<vector<int> >&matrix, string choice){
    
    if(choice =="1"){
        matrix[0][0]=1;matrix[0][1]=2;matrix[0][2]=3;
        matrix[1][0]=4;matrix[1][1]=5;matrix[1][2]=6;
        matrix[2][0]=0;matrix[2][1]=7;matrix[2][2]=8;
    }
    else if(choice == "2"){
        cin.ignore();
        int m = matrix.size();
        for(int i=0;i<m;i++){
            string s;
            cout<<"enter row wise"<<endl;
            getline(cin, s);
            int num = 0;
            for(int j=0;j<m;j++){
                matrix[i][j]=s[num]-'0';num+=2;
            }
        }
    }
    else
        cout<<"invalid"<<endl;
}

int main() {
    // vector to store m*m puzzle of any size
    vector<vector<int> > puzzle;
    string input;
        cout << "Enter 1 for default puzzle(which would be 3*3), 2 for custom puzzle: " << endl;
        cin >> input;
        int rows;
        if(input == "1"){ // default size is 3
            rows=3;
        }
        else{
            cout<<"enter the rows of the puzzle"<<endl;
            cin>>rows;
        }
        if (input == "1") {
            puzzle = { {1, 2, 3},
                      {4, 0, 6},
                      {7, 5, 8} };
        }
        else if (input == "2") {
            cin.ignore();
            cout << "Input your puzzle, use zero for the blank: " << endl;
            cout << "Input your first row " << endl;
            puzzle.push_back(userInpt(input, rows));
            cout << "Input your second row " << endl;
            puzzle.push_back(userInpt(input, rows));
            cout << "Input your third row " << endl;
            puzzle.push_back(userInpt(input, rows));
        }

    string algo;
    cout << "Pick your algorithm: MisplacedTiles, ManhattanDistance, or UCS" << endl;
    cin >> algo; // default UCS

    matrix_puzzle my_puzzle(puzzle);
    //using a prioirty queue since I need the lowest cost path
    priority_queue<matrix_puzzle> puzzle_states;

    // map to keep track of visited states
    map<string, bool> visited_states;
    puzzle_states.push(my_puzzle);
    int maximum_queue_size = states.size();
    int nodes_expanded = 0;
    while(!puzzle_states.empty()) {
        matrix_puzzle current = puzzle_states.top();
        puzzle_states.pop();
        if (CheckGoalState(current)) {
            cout << "Found Solution: " << endl;
            PrintState(current);
            cout << "Depth: " << current.g_cost << endl;
            cout << "Nodes expanded: " << nodes_expanded << endl;
            cout << "Maximum queue size: " << maximum_queue_size << endl;
            vector<matrix_puzzle> path;
            return 0;
        }
        if (maximum_queue_size != 1) {
            cout << "The best state for expansion: " << endl;
        }
        else {
            cout << "Initial state is: " << endl;
        }
        PrintState(current);
        visit(current, puzzle_states, visited_states, algo);
        ++nodes_expanded;
        if (maximum_queue_size < states.size()) {
            maximum_queue_size = states.size();
        }
    }
    cout << "Puzzle has no sol!" << endl;
    return 0;
}
