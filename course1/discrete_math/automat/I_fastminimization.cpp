#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <utility>
#include <map>

using namespace std;

FILE *fin = fopen("fastminimization.in", "r");
FILE *fout = fopen("fastminimization.out", "w");

vector<vector<int>> g;
vector<bool> used;
vector<bool> T;
vector<int> terminal;

vector<vector<unordered_set<int>>> Inv; // массив состояний, из которых есть ребра по символу a в состояние r 
vector<unordered_set<int>> P; // Все классы разбиения 
vector<int> Class; // индекс класса в P, которому принадлежит состояние i
queue<pair<unordered_set<int>, char>> S; // очередь из пар (C, a)
map<int, vector<int>> Involved; // ассоциативный массив из номеров классов в векторы из номеров вершин. 

int main(int argc, char **argv) {
    int n, m, k;
    fscanf(fin, "%d %d %d", &n, &m, &k);

    T.assign(n, false);
    for(int i = 0, t; i < k; i++) {
        fscanf(fin, "%d", &t);
        T[--t] = true;
        terminal.push_back(t);
    }
    
    g.resize(n);
    Inv.resize(n);
    Class.resize(n);
    for(int i = 0; i < n; i++) {
		g[i].assign(26, -1);
		Inv[i].resize(26);
	}
    char c;
    for(int i = 0, a, b; i < m; i++) {
        fscanf(fin, "%d %d %c", &a, &b, &c);
        c -= a;
        g[--a][c] = --b;
        Inv[b][c].emplace(a);
    }




    /* HOPCROFT ALGORITHM */
    P.resize(2);
    for (int i = 0; i < n; i++) {
		P[T[i] ? 0 : 1].emplace(i); // P[0] - terminal, P[1] - not terminal
	}

	for (int i = 0; i < 26; i++) {
		S.emplace(make_pair(P[0], i));
		S.emplace(make_pair(P[1], i));
	}

	while (!S.empty()) {
		pair<unordered_set<int>, char> elem = S.front();
		S.pop();
		Involved.clear();
        
        for (auto q = elem.first.begin(); q != elem.first.end(); q++) {
			for (auto r = Inv[*q][elem.second].begin(); r != Inv[*q][elem.second].end(); r++) {
				int i = Class[*r];
				if (Involved.find(i) == Involved.end()) {
					vector<int> vec;
				    Involved[i] = vec;
				}
				Involved[i].push_back(*r);
		    }
		}

		for (auto i = Involved.begin(); i != Involved.end(); i++) {
			if (Involved[i->first].size() < P[i->first].size()) {
				int j = P.size();
				P.resize(j + 1);
				for (int k = 0; k < Involved[i->first].size(); k++) {
					P[i->first].erase(Involved[i->first][k]);
					P[j].push_back(Involved[i->first][k]);
				}
				if (P[j].size() > P[i->first].size()) {  // Парный класс должен быть меньшего размера
				    P[i].swap(P[j]); //swap за O(1) - просто переставить указатели
				}
				for r \in \mathtt{P}[j] //Обновляем номера классов для вершин, у которых они изменились
				  \mathtt{Class}[r] = j
				for c \in \Sigma
				  push \langle j, c \rangle into \mathtt{Queue}
			}
		}
	}

    
    /* HOPCROFT ALGORITHM */




    
    fprintf(fout, "NO");
    fclose(fin);
    fclose(fout);
    return 0;
}
