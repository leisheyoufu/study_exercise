/*

Surrounded Regions

Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,
X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdio>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    /* BFS large data can not pass
    void solve(vector<vector<char>>& board) {
    	int m = board.size();
    	if(m<1) {
    		return;
    	}
    	int n = board[0].size();
    	unordered_map<int, bool> map;
    	for(int i=0;i<m;i++) {
    		for(int j=0;j<n;j++) {
    			if(board[i][j] == 'O' && map.find(i*m+j) == map.end()) {
    				vector<int> v;
    				unordered_map<int, bool> access;
    				if (fill(board, i*m+j, m, n, map, v, access)) {
    					putx(board,v,m,n);
    				}
    			}
    		}
    	}
    }
    bool fill(vector<vector<char>>& board, int pos, int m, int n, unordered_map<int, bool> &map, vector<int> &v, unordered_map<int, bool> &access) {
    	v.push_back(pos);
    	access[pos] = true;
    	int i = pos /m;
    	int j = pos % m;
    	if(i==0 || i== m-1) {
    		map[pos] = true;
    		return false;
    	}
    	if (board[i-1][j] == 'O' && map.find((i-1)*m+j) != map.end()) { // up
    		map[pos] = true;
    		return false;
    	}

    	if(j==0 || j==n-1) {
    		map[pos] = true;
    		return false;
    	}
    	if( board[i][j-1] == 'O' && map.find(i*m+j-1) != map.end()) { // left
    		map[pos] = true;
    		return false;
    	}
    	bool right = true, down = true, up = true, left = true;
    	if(board[i][j+1] == 'O' && access.find(i*m+j+1) == access.end()) {
    		right = fill( board, i*m+j+1, m, n, map,v, access);
    	}
    	if(board[i+1][j] == 'O' && access.find(i*m+j+m) == access.end()) {
    		down = fill( board, i*m+j+m, m, n, map,v, access);
    	}
    	if(board[i-1][j] == 'O' && access.find(i*m+j-m) == access.end()) {
    		up = fill (board, i*m+j-m, m, n, map, v, access);
    	}
    	if(board[i][j-1] == 'O' && access.find(i*m+j-1) == access.end()) {
    		left = fill (board, i*m+j-1, m, n, map, v, access);
    	}
    	if(left && up && down && right) {
    		return true;
    	}
    	return false;
    }
    void putx(vector<vector<char>>& board, vector<int> &v, int m, int n) {
    	for(int p =0; p<v.size();p++) {
    		int pos = v[p];
    		int i = pos/m;
    		int j = pos%m;
    		board[i][j] = 'X';
    	}
    }
    */

    void solve(vector<vector<char>>& board)
    {
        int m = board.size();
        if(m<1) {
            return;
        }
        int n = board[0].size();

        vector<vector<bool>> visited;
        visited.resize(m);
        for(int i=0; i<m; i++) {
            visited[i].assign(n,false);
        }
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(board[i][j] == 'O' && !visited[i][j]) {
                    vector<pair<int,int>> v;
                    if (bfs(board, i,j, m, n, visited, v)) {
                        //fill(board,v);
                        for(int p =0; p<v.size(); p++) {
                            board[v[p].first][v[p].second] = 'X';
                        }
                    }
                }
            }
        }
    }

    bool bfs(vector<vector<char>>& board, int i, int j,int m, int n, vector<vector<bool>> &visited, vector<pair<int,int>> &v)
    {
        queue<pair<int,int>> q;
        q.push(make_pair(i,j));
        bool flag = true;
        visited[i][j] = true;
        while(!q.empty()) {
            int i = q.front().first;;
            int j = q.front().second;
            v.push_back(q.front());
            q.pop();
            if(i==0 || i== m-1) {
                flag = false;
            }
            if(j==0 || j==n-1) {
                flag = false;
            }
            if(i>0 && board[i-1][j] == 'O' && !visited[i-1][j]) {
                q.push(make_pair(i-1,j));
                visited[i-1][j] = true;
            }
            if(i<m-1 && board[i+1][j] == 'O' && !visited[i+1][j]) {
                q.push(make_pair(i+1,j));
                visited[i+1][j] = true;
            }
            if(j > 0 && board[i][j-1] == 'O' && !visited[i][j-1]) {
                q.push(make_pair(i,j-1));
                visited[i][j-1] = true;
            }
            if(j<n-1 && board[i][j+1] == 'O' && !visited[i][j+1]) {
                q.push(make_pair(i,j+1));
                visited[i][j+1] = true;
            }
        }
        return flag;
    }
};

int main()
{
    /*
    X X X X
    X O O X
    X X O X
    X O X X
    */
    Solution sln;
    vector<vector<char>> board;
    char a1[] = "XXXX";
    vector<char> v1(a1, a1+4);
    board.push_back(v1);
    char a2[] = "XOOX";
    vector<char> v2(a2, a2+4);
    board.push_back(v2);
    char a3[] = "XXOX";
    vector<char> v3(a3, a3+4);
    board.push_back(v3);
    char a4[] = "XOXX";
    vector<char> v4(a4, a4+4);
    board.push_back(v4);
    sln.solve(board);
    system("pause");
    return 0;
}
