#include<iostream>
#include<vector>
#include <stdlib.h>
using namespace std;
int main() {
	int no_of_states; 

	cout << "Enter the number of states  ( Enter  -1 when there's no action between two states ): ";
	cin >> no_of_states; 
	cout << endl;

	cout << "Enter the reword table: " << endl;
	vector<vector<int>> reword_table(no_of_states,vector<int>(no_of_states,-1)); // initialize the reword table with -1 indicating that there is no path between these states
	for (int i = 0; i < no_of_states; i++) {
		for (int j = 0; j < no_of_states; j++) {
			cin >> reword_table[i][j]; 
		}
	}
	cout << endl;

	vector<vector<int>>	q_table(no_of_states, vector<int>(no_of_states, 0)); // initialize the q table with 0

	int goal_state;
	float gama;
	cout << "Enter the goal state and the learning rate: " << endl;
	cin >> goal_state >> gama; 
	cout << endl;

	int no_of_episods;
	cout << "Enter the number  of  episods: " << endl;
	cin >> no_of_episods;

	
	while (no_of_episods--) { 
		
		int curr_state = rand() % no_of_states; // select initial state randomly
		while (true) { // while goal is not reached
		
			vector<int> possible_actions;
			for (int i = 0; i < no_of_states; i++) {
				if (reword_table[curr_state][i] == -1)
					continue;
				possible_actions.push_back(i);
			}
		
			int action = possible_actions[rand() % possible_actions.size()]; // select the action randomly among all of the possible actions
			int max_q = -1;

			// calculate maximum Q based on all possible actions
			for (int i = 0; i < no_of_states; i++) {
				max_q =max(max_q, q_table[action][i]);
			}
			q_table[curr_state][action] = reword_table[curr_state][action] + gama * max_q; // update the q_table of the current state and the current action 
			
			if(curr_state == goal_state && action == goal_state)
				break;
				
			curr_state = action; 
			
		}
	}
	cout << "Q-Table:  " << endl;
	//output the  Q_table
	for (int i = 0; i < no_of_states; i++) {
		for (int j = 0; j < no_of_states; j++) {
			if (j)
				cout << " ";
			cout << q_table[i][j];
		}
		cout << endl;
	}
	return 0;
}
// Input sample
/*
6
-1 -1  -1  -1 0 -1
-1 -1 -1  0 -1 100
-1 -1  -1  0 -1  -1
-1  0  0 -1 0  -1
0  -1 -1 0  -1 100
-1 0 -1 -1  0  100
5  0.8
27

*/

// output
/*
0 0 0 0 396 0
0 0 0 316 0 496
0 0 0 316 0 0
0 396 252 0 396 0
316 0 0 316 0 496
0 396 0 0 396 496
*/