#include <cstdio>
#include <vector>
#include <set>
#include <queue>
#include <map>

using namespace std;

FILE *fin = fopen("minimization.in", "r");
FILE *fout = fopen("minimization.out", "w");

struct State {
    int id;
    bool fromStart, isTerminal, toTerminal;
    State *to[26];
    
    State(): fromStart(false), isTerminal(false), toTerminal(false) {
        for(int i = 0; i < 26; i++) {
            to[i] = NULL;
        }
    }
};

int n, m, k;
vector<State *> states;
set<int> alphabet;
vector<vector<int>> g;

void dfs1(State *v) {
    if(v->fromStart) {
        return;
    }
    
    v->fromStart = true;
    
    for(int c : alphabet) {
        if(v->to[c] != NULL) {
            dfs1(v->to[c]);
        }
    }
}


void dfs2(int v) {
    if(states[v]->toTerminal) {
        return;
    }
    
    states[v]->toTerminal = true;
    
    for(int i : g[v]) {
        dfs2(i);
    }
}



typedef set<State *> Class;
vector<Class*> p;
Class tmp1, tmp2;
queue<pair<Class*, int> > q;
int h, t;
map<int, Class > involved;
vector<vector<vector<int>>> _inv;
vector<int> _class;
vector<State *> newStates;

void findEqualientStates() {
    // inv precalc:
    for(int i = 1; i <= n; i++) {
        State *state = states[i];
        
        if(!state->toTerminal || !state->fromStart) {
            continue;
        }
        
        for(int c : alphabet) {
            State *to = state->to[c];
            
            if(to != NULL) {
                _inv[to->id][c].push_back(state->id);
            }
        }
    }
    
    for(int i = 1; i <= n; i++) {
        if(!states[i]->toTerminal || !states[i]->fromStart) {
            continue;
        }
        
        if(states[i]->isTerminal) {
            tmp1.insert(states[i]);
            _class[states[i]->id] = 0;
        } else {
            tmp2.insert(states[i]);
            _class[states[i]->id] = 1;
        }
    }
    
    Class *ff = new Class(tmp1);
    Class *ss = new Class(tmp2);
    
    if(tmp1.size() > 0) {
        p.push_back(ff);
    }
    
    if(tmp2.size() > 0) {
        p.push_back(ss);
    }
    
    for(int c : alphabet) {
        q.push(make_pair(ff, c));
        q.push(make_pair(ss, c));
    }
    
    tmp1.clear();
    tmp2.clear();
    
    while(!q.empty()) {
        pair<Class *, int> &cur = q.front();
        involved.clear();
        
        for(State * q : * (cur.first)) {
            for(int r : _inv[q->id][cur.second]) {
                int i = _class[r];
                involved[i].insert(states[r]);
            }
        }
        
        for(auto & pr : involved) {
            int i = pr.first;
            
            if(pr.second.size() < p[i]->size()) {
                int j = p.size();
                p.push_back(new Class());
                
                for(State * r : pr.second) {
                    p[i]->erase(r);
                    p[j]->insert(r);
                    _class[r->id] = j;
                }
                
                for(int c : alphabet) {
                    q.push(make_pair(p[j], c));
                    t++;
                }
            }
        }
        
        q.pop();
    }
    
    for(int i = 1; i <= n; i++) {
        if(!states[i]->toTerminal || !states[i]->fromStart) {
            _class[states[i]->id] = -1;
        }
    }
}



int main() {
    fscanf(fin, "%d %d %d", &n, &m, &k);
    states.resize(n + 1);
    
    for(int i = 1; i <= n; i++) {
        states[i] = new State();
        states[i]->id = i;
    }
    
    for(int i = 0, t; i < k; i++) {
        fscanf(fin, "%d", &t);
        states[t]->isTerminal = true;
    }
    
    g.resize(n + 5);
    _class.resize(n + 5);
    char c;
    
    for(int i = 0, a, b; i < m; i++) {
        fscanf(fin, "%d %d %c", &a, &b, &c);
        c -= 'a';
        alphabet.insert(c);
        states[a]->to[(int)c] = states[b];
        g[b].push_back(a);
    }
    
    _inv.resize(n + 5);
    
    for(size_t i = 0; i < _inv.size(); i++) {
        _inv[i].resize(26);
    }
    
    // INIT
    dfs1(states[1]);
    
    for(int i = 1; i <= n; i++) {
        if(states[i]->isTerminal) {
            dfs2(states[i]->id);
        }
    }
    
    for(int i = 1; i <= n; i++) {
        g[i].clear();
    }
    // /INIT

    findEqualientStates();
    int startClass = _class[1];
    
    if(startClass != -1) {
        for(int i = 1; i <= n; i++) {
            if(_class[states[i]->id] == startClass) {
                _class[states[i]->id] = 0;
            } else if(_class[states[i]->id] == 0) {
                _class[states[i]->id] = startClass;
            }
        }
    }
    
    int nn = p.size(), mm = 0, kk = 0;
    newStates.resize(nn);
    
    for(size_t i = 0; i < newStates.size(); i++) {
        newStates[i] = new State();
        newStates[i]->id = i;
    }
    
    for(int i = 1; i <= n; i++) {
        State *state = states[i];
        int from = _class[state->id];
        
        if(from == -1) {
            continue;
        }
        
        if(state->isTerminal && !newStates[from]->isTerminal) {
            kk++;
            newStates[from]->isTerminal = true;
        }
        
        for(int c : alphabet) {
            if(state->to[c] == NULL) {
                continue;
            }
            
            int to = _class[state->to[c]->id];
            
            if(to == -1) {
                continue;
            }
            
            if(newStates[from]->to[c] == NULL) {
                mm++;
                newStates[from]->to[c] = newStates[to];
            }
        }
    }
    
    fprintf(fout, "%d %d %d\n", nn, mm, kk);
    
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

