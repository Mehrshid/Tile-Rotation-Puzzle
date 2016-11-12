//
//  main.cpp
//  RotatePuzzle
//
//  Created by Mehrshid Fadaei Nejad on 1/25/1395 AP.
//  Copyright (c) 1395 Mehrshid Fadaei Nejad. All rights reserved.
//

#include <bits/stdc++.h>
using namespace std;


typedef long long ll;
typedef vector<int> vi;
typedef vector<string, int> vis;
typedef unordered_map<string, int> umsi;
typedef map<string,int> msi;
typedef pair<string, int> psi;
typedef pair<int,string> pis;
typedef map<string, psi> mspsi;
typedef pair<string, string> pss;


const string goal = "ABCDLNNEKNNFJIHG";

string do_rotate (string, int);
string gr1_rotate (string);
string gr2_rotate (string);
string gr3_rotate (string);
string gr4_rotate (string);
string gr5_rotate (string);
string bfs (string);
string a_star_bfs (string);
int heuristic (string);
void time_calculation ();

bool is_goal (string);
bool is_visited (string);
void print (string);

//char root_input[16];
//char child[5][16];
msi visit;
msi:: iterator m_iterator;
mspsi parent;
vi my_vec;
vi::iterator vit;
vi::reverse_iterator rvit;

int main (int argc, const char * argv[]) {
	
	string input;
	
	while (cin >> input) {
		
		//string result1 = bfs(input);
		string result = a_star_bfs(input);
		cout << visit.size() << endl;

		cout << "Done." << endl;
		//cout << result << endl;
	}
	
	return 0;
}

bool is_goal (string goal_arr) {
	
	if (goal_arr[0] == 'A' && goal_arr[1] == 'B' &&
		goal_arr[2] == 'C' && goal_arr[3] == 'D' &&
		goal_arr[4] == 'L' && goal_arr[5] == 'N' &&
		goal_arr[6] == 'N' && goal_arr[7] == 'E' &&
		goal_arr[8] == 'K' && goal_arr[9] == 'N' &&
		goal_arr[10] == 'N' && goal_arr[11] == 'F' &&
		goal_arr[12] == 'J' && goal_arr[13] == 'I' &&
		goal_arr[14] == 'H' && goal_arr[15] == 'G')
		return true;
	
	return false;
}

string do_rotate (string state, int index) {
	
	string temp;
	
	if (index == 1)
		temp = gr1_rotate(state);
	
	if (index == 2)
		temp = gr2_rotate(state);
	
	if (index == 3)
		temp = gr3_rotate(state);
	
	if (index == 4)
		temp = gr4_rotate(state);
	
	if (index == 5)
		temp = gr5_rotate(state);
	
	return temp;
}

string gr1_rotate (string puzzle_state) {
	
	swap (puzzle_state[1], puzzle_state[5]);
	swap (puzzle_state[0], puzzle_state[1]);
	swap (puzzle_state[0], puzzle_state[4]);
	
	return puzzle_state;
}

string gr2_rotate (string puzzle_state) {
	
	swap (puzzle_state[3], puzzle_state[7]);
	swap (puzzle_state[2], puzzle_state[3]);
	swap (puzzle_state[2], puzzle_state[6]);
	
	return puzzle_state;
}

string gr3_rotate (string puzzle_state) {
	
	swap (puzzle_state[9], puzzle_state[13]);
	swap (puzzle_state[8], puzzle_state[9]);
	swap (puzzle_state[8], puzzle_state[12]);
	
	return puzzle_state;
}

string gr4_rotate (string puzzle_state) {
	
	swap (puzzle_state[11], puzzle_state[15]);
	swap (puzzle_state[10], puzzle_state[11]);
	swap (puzzle_state[10], puzzle_state[14]);
	
	return puzzle_state;
}

string gr5_rotate (string puzzle_state) {
	
	swap (puzzle_state[6], puzzle_state[10]);
	swap (puzzle_state[5], puzzle_state[6]);
	swap (puzzle_state[5], puzzle_state[9]);
	
	return puzzle_state;
}

bool is_visited(string puzzle_states) {
	
	bool isVisited = true;
	
	if (visit.find(puzzle_states) != visit.end())
		return isVisited;
	
	return !isVisited;
}

string bfs (string root_input) {
	
	queue <string> puzzle_queue;
	puzzle_queue.push(root_input);
	queue <string> temp;
	
	string node_child;
	
	visit[root_input] = 0;
	bool is_solved = false;
	
	if (root_input == goal)
		is_solved = true;
	
	while (!puzzle_queue.empty() && !is_solved) {
		
		string front_puzzle_queue = puzzle_queue.front();
		puzzle_queue.pop();
		
		for (int i = 1; i < 6; i++) {
			
			node_child = do_rotate(front_puzzle_queue, i);
			
			if (!is_visited(node_child)) {
				
				parent[node_child] = psi(front_puzzle_queue, i);
				puzzle_queue.push(node_child);
				visit[node_child] = i;
				
				if (is_goal(node_child)) {
					is_solved = true;
					break;
				}
			}
		}
	}
	
	time_calculation();
	
	//pair <string, int> endResult(root_input, 1);
	
	cout << node_child << endl;

	
	while (parent.find(node_child) != parent.end()) {
  
		my_vec.push_back(visit[node_child]);
		node_child = parent[node_child].first;
		cout << node_child << endl;

	}
	
	cout << "Size of My Vector: (# of Rotations) " << my_vec.size() << endl;
	
	for (rvit = my_vec.rbegin(); rvit != my_vec.rend(); rvit++) {
		
		cout << "rotate: " << *rvit << endl;
		
	}
	
	return node_child;
}

string a_star_bfs (string root_input) {
	
	int h = heuristic(root_input);
	msi depth, cost;
	
	priority_queue<pis> bfs_queue;					// vazn o state
	bfs_queue.push(make_pair(-h, root_input));
	
	bool is_solved = false;
	depth[root_input] = 0;
	cost[root_input] = depth[root_input] + h;		// f(n)
	string node_child;
	
	//int node_cost = 0;
	int child_cost = 0;
	int child_depth = 0;
	
	while (!bfs_queue.empty() && !is_solved) {
		
		pis node = bfs_queue.top();
		node.first = node.first * -1;
		bfs_queue.pop();
		
		if (is_goal(node.second)) {
			
			is_solved = true;
			break;
		}
		
		visit[node_child] = 1;
		
		for (int i = 1; i < 6; i++) {
			
			node_child = do_rotate(node.second, i);
			h = heuristic(node_child);
			child_depth = depth[node.second] + 1;
			child_cost = child_depth + h;
			
			if (!is_visited(node_child) && (cost.find(node_child) == cost.end() || child_cost < cost[node_child])) {
				
				//node_cost = h + depth[node.second] + 1;
				parent[node_child] = psi(node.second, i);
				//depth[node_child] = depth[node.second] + 1;
				//child_depth = depth[node.second] + 1;
				depth[node_child] = child_depth;
				cost[node_child] = child_cost;
				//cost[node_child] = depth[node_child] + h;
				//cout << "Depth: " << depth[node.second] << endl;
				bfs_queue.push(make_pair(-1*(depth[node_child] + h), node_child));
			}
		}
	}
	
	cout << node_child << endl;

	
	time_calculation();
	
	while (parent.find(node_child) != parent.end()) {
  
		my_vec.push_back(parent[node_child].second);
		node_child = parent[node_child].first;
		cout << node_child << endl;
	}
	
	
	
	cout << "Size of My Vector (# of Rotations): " << my_vec.size() << endl;
	
	for (rvit = my_vec.rbegin(); rvit != my_vec.rend(); rvit++) {
		
		cout << "rotate: " << *rvit << endl;
		
	}
	
	
	return node_child;
}

int heuristic (string root_input) {
	
	int count = 0;
	
	for (int i  = 0; i < 16; i++) {
		
		if (root_input[i] != goal[i])
			count++;
	}
	
	return count/4;
}

void time_calculation () {
	
	clock_t INIT = clock();
	cout << "time elapsed: " << (1000 * (double) (clock() - INIT) / CLOCKS_PER_SEC) << endl;;
	//printf("time elapsed : %lfms\n", 1000 * (double) (clock() - INIT) / CLOCKS_PER_SEC);
}

// ---------------------
// tst: LACDNBNEKNNFJIHG
// tst: ABCDLNNEKNNFJIHG
// tst: LACDNBNEKNNFJIHG

