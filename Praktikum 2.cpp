/**
 *
 * Kelompok 7 Teori Graf E
 * 1. Aria Nalini Farzana       - 5025221016
 * 2. Abillidya Nofianto Putri  - 5025221164
 * 3. Bianca Shaummaya Aryan    - 5025221184
 *
 * Implementasikan sebuah program untuk menyelesaikan permasalahan
 * Bidak kuda seperti pada gambar, jika diinginkan:
 * 1. Mengakhiri perjalanan pada attacking square (closed tour)
 * 2. Mengakhiri perjalanan di sembarang kotak (open tour)
 *
 * **/

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> point;

int N = 8;
int board[8][8];
int counter = 0;

map<point , bool> vis;
map<point , list<point> > adj;

point endPoint;

void addEdge(point  v, point  w)
{
	adj[v].push_back(w);
	adj[w].push_back(v);
}

int cx[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int cy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

bool Access(int x, int y, point source) {

	if (!(x >= 0 && x < N && y >= 0 && y < N)) {
        return false;
    }

    point dest = {x, y};

    for (const auto &neighbor : adj[source]) {
        if (neighbor == dest) {
            return false;
        }
    }
    return true;
}

int getDegree(point v) {
	int count = 0;
	list<point>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); i++) {
		if (!vis[*i]) {
			count++;
		}
	}

	return count;
}


void buildGraph() {
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			for (int i = 0; i < 8; i++) {
				int nextX = row+cx[i];
				int nextY = col+cy[i];

				if(Access(nextX, nextY, {row, col})) {
					addEdge({row,col}, {nextX,nextY});
				}
			}
		}
	}
}

void checkMoves(point v) {
	list<point>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); i++) {
		cout << "(" << i->first << ", " << i->second << ")" << endl;
	}
}


void printBoard() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << board[i][j] << "\t";
		}
		cout << endl;
	}
}

void DFS(point v)
{
	vis[v] = true;
	board[v.first][v.second] = counter;
	if (counter == N*N-1) {
		endPoint = v;
		return;
	}
	point min_deg_point = {-1,-1};
	int count, min_deg = N+1;

	list<point>::iterator i;
	int j = 0;
	for (i = adj[v].begin(); i != adj[v].end(); i++) {
		j++;
		if (!vis[*i]) {
			count = getDegree(*i);
			if (count < min_deg) {
				min_deg_point = *i;
				min_deg = count;
			}
		}
	}

	if (min_deg_point.first == -1) return;

	counter++;
	DFS(min_deg_point);
	vis[min_deg_point] = false;
	counter--;
}

bool isNeighbour(point v, point w) {

	list<point>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); i++) {
		if (*i == w) {
			return true;
		}
	}
	return false;
}

bool findTour(bool isClosedTour) {

	int startX = rand()%N;
	int startY = rand()%N;

	point startPoint = {startX, startY};

	for (auto &pair : vis) {
        pair.second = false;
    }

	DFS(startPoint);

	if (isClosedTour) {
		if(!isNeighbour(endPoint, startPoint)) {
			return false;
		}
	}
	printBoard();
	return true;
}

int main()
{
	srand(time(NULL));
	buildGraph();

	//open tour
	cout << "--------------------------OPEN TOUR-------------------------" << endl;
	findTour(0);

	//closed tour
	cout << "--------------------------CLOSED TOUR-------------------------" << endl;
	while(!findTour(1));

}

