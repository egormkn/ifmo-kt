#include <cstdio>
#include <vector>
#include <set>
#include <queue>
#include <map>

using namespace std;

FILE *fin = fopen("fastminimization.in", "r");
FILE *fout = fopen("fastminimization.out", "w");

struct State {
    int id, inclass;
    bool fromStart, isTerminal, toTerminal;
    State *to[26];
    State *from[26];
    State(): fromStart(false), isTerminal(false), toTerminal(false) {
        for(int i = 0; i < 26; i++) {
            to[i] = NULL;
            from[i] = NULL;
        }
    }
};

int n, m, k;
vector<State *> states;
set<int> alphabet;

void dfs_fromstart(State *v) {
    if(v->fromStart) {
        return;
    }
    v->fromStart = true;
    for(int c: alphabet) {
        if(v->to[c] != NULL) {
            dfs_fromstart(v->to[c]);
        }
    }
}

void dfs_terminal(State *v) {
    if(v->toTerminal) {
        return;
    }
    v->toTerminal = true;
    
    for(int c: alphabet) {
        if(v->from[c] != NULL) {
            dfs_terminal(v->from[c]);
        }
    }
}

typedef set<State *> Class;
vector<Class*> p;
Class R1class, R2class;
queue<pair<Class*, int>> q;
int h, t;
map<int, Class> involved;
vector<vector<vector<State *>>> Inv;

void findEquivalenceClasses() {
    for(int i = 0; i < n; i++) {
        State *state = states[i];
        
        if(!state->toTerminal || !state->fromStart) {
            continue;
        }
        
        for(int c : alphabet) {
            State *to = state->to[c];
            
            if(to != NULL) {
                Inv[to->id][c].push_back(state);
            }
        }
    }
    
    for(int i = 0; i < n; i++) {
		State *s = states[i];
        if(!s->toTerminal || !s->fromStart) {
			s->inclass = -1;
            continue;
        }
        
        if(s->isTerminal) {
            R1class.insert(s);
            s->inclass = 0;
        } else {
            R2class.insert(s);
            s->inclass = 1;
        }
    }
    
    Class *ff = new Class(R1class);
    Class *ss = new Class(R2class);
    
    if(R1class.size() > 0) {
        p.push_back(ff);
    }
    
    if(R2class.size() > 0) {
        p.push_back(ss);
    }
    
    for(int c : alphabet) {
        q.push(make_pair(ff, c));
        q.push(make_pair(ss, c));
    }
    
    R1class.clear();
    R2class.clear();
    
    while(!q.empty()) {
        pair<Class *, int> &cur = q.front();
        involved.clear();
        
        for(State *q: *(cur.first)) {
            for(State *r: Inv[q->id][cur.second]) {
                int i = r->inclass;
                involved[i].insert(r);
            }
        }
        
        for(auto & pr : involved) {
            int i = pr.first;
            
            if(pr.second.size() < p[i]->size()) {
                int j = p.size();
                p.push_back(new Class());
                
                for(State *r : pr.second) {
                    p[i]->erase(r);
                    p[j]->insert(r);
                    r->inclass = j;
                }
                
                for(int c : alphabet) {
                    q.push(make_pair(p[j], c));
                    t++;
                }
            }
        }
        
        q.pop();
    }
}



int main() {
    fscanf(fin, "%d %d %d", &n, &m, &k);
    states.resize(n);
    
    for(int i = 0; i < n; i++) {
        states[i] = new State();
        states[i]->id = i;
    }
    
    for(int i = 0, t; i < k; i++) {
        fscanf(fin, "%d", &t);
        states[--t]->isTerminal = true;
    }
    
    char c;
    for(int i = 0, a, b; i < m; i++) {
        fscanf(fin, "%d %d %c", &a, &b, &c);
        c -= 'a';
        alphabet.insert(c);
        states[--b]->from[(int)c] = states[--a];
        states[a]->to[(int)c] = states[b];
    }
    
    Inv.resize(n);
    
    for(size_t i = 0; i < Inv.size(); i++) {
        Inv[i].resize(26);
    }
    
    dfs_fromstart(states[0]);
    for(int i = 0; i < n; i++) {
        if(states[i]->isTerminal) {
            dfs_terminal(states[i]);
        }
    }

    findEquivalenceClasses();
    int startClass = states[0]->inclass;
    
    if(startClass != -1) {
        for(int i = 0; i < n; i++) {
			State *s = states[i];
			if(s->inclass == startClass) {
                s->inclass = 0;
            } else if(s->inclass == 0) {
                s->inclass = startClass;
            }
        }
    }
    
    int n2 = p.size(), m2 = 0, k2 = 0;
    
    vector<State *> newStates(n2);
    for(size_t i = 0; i < newStates.size(); i++) {
        newStates[i] = new State();
        newStates[i]->id = i;
    }
    
    for(int i = 0; i < n; i++) {
        State *state = states[i];
        int from = state->inclass;
        
        if(from == -1) {
            continue;
        }
        
        if(state->isTerminal && !newStates[from]->isTerminal) {
            k2++;
            newStates[from]->isTerminal = true;
        }
        
        for(int c : alphabet) {
            if(state->to[c] == NULL) {
                continue;
            }
            
            int to = state->to[c]->inclass;
            
            if(to == -1) {
                continue;
            }
            
            if(newStates[from]->to[c] == NULL) {
                m2++;
                newStates[from]->to[c] = newStates[to];
            }
        }
    }
    
    fprintf(fout, "%d %d %d\n", n2, m2, k2);
    
    for(size_t i = 0; i < newStates.size(); i++) {
        if(newStates[i]->isTerminal) {
            fprintf(fout, "%d ", newStates[i]->id + 1);
        }
    }
    
    fprintf(fout, "\n");
    
    for(size_t i = 0; i < newStates.size(); i++) {
        for(int c : alphabet) {
            if(newStates[i]->to[c] != NULL) {
                fprintf(fout, "%d %d %c\n", newStates[i]->id + 1, newStates[i]->to[c]->id + 1, (char)('a' + c));
            }
        }
    }
    
    return 0;
}

