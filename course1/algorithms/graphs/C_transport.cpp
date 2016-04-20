#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
 
using namespace std;
 
FILE *fin = fopen("transport.in", "r");
FILE *fout = fopen("transport.out", "w");

int n;
vector<int> xc, yc;

double cost(int v1, int v2){
    return sqrt(pow((xc[v2]-xc[v1]),2)+pow((yc[v2]-yc[v1]),2));
}

int main(int argc, char **argv) {
    fscanf(fin, "%d", &n);
    vector<double> roads;
    xc.push_back(0);
    yc.push_back(0);
    for(int i = 1, x; i <= n; i++) {
        fscanf(fin, "%d", &x);
        xc.push_back(x);
    }
    
    for(int i = 0, y; i < n; i++) {
        fscanf(fin, "%d", &y);
        yc.push_back(y);
    }

    double r, a;
    fscanf(fin, "%lf %lf", &r, &a);
    double answer = (n == 1) ? 0 : a * n;
    double answer2 = 0;
    if(n == 1){
		fprintf(fout, "%.10f\n", answer);
        fclose(fin);
        fclose(fout);
        return 0;
    }
    
    

    vector<bool> used(n + 1);
    vector<double> min_e(n + 1, (double) INT_MAX);
    vector<int> sel_e(n + 1, -1);
    
    min_e[1] = 0;
    
    for(int i = 1; i <= n; ++i) {
        int v = -1;
        
        for(int j = 1; j <= n; ++j) {
            if(!used[j] && (v == -1 || min_e[j] < min_e[v])) {
                v = j;
            }
        }
        
        used[v] = true;
        
        if(sel_e[v] != -1) {
			double d = r * cost(v, sel_e[v]);
			answer2 += d;
			roads.push_back(d);
        }
        
        for(int to = 1; to <= n; ++to){
            if(cost(v, to) < min_e[to]) {
                min_e[to] = cost(v, to);
                sel_e[to] = v;
            }
		}
    }

    sort(roads.begin(), roads.end());

    for(unsigned i = 0; i < roads.size() - 1; i++){
        if(roads[i] < a){
            answer = answer - a + roads[i];
		} else {
            break;
		}
	}

	fprintf(fout, "%.10f\n", min(answer, answer2));
    fclose(fin);
    fclose(fout);
    return 0;
}
