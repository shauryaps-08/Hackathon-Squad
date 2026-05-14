#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <chrono>
#include <ctime>

using namespace std;


int N, M;
vector<long long> skills;
unordered_map<int, unordered_set<int>> conflicts;
unordered_set<int> selected;
vector<int> conflict_count;
long long total_score;


void local_search() {
    bool improved = true;

    while (improved) {
        improved = false;

        vector<int> current_team;
        for (int u : selected) {
            current_team.push_back(u);
        }

   
        for (int i = 0; i < current_team.size(); i++) {
            int u = current_team[i];

            if (selected.count(u) == 0) continue;

            selected.erase(u);
            total_score -= skills[u];
            for (int nb : conflicts[u]) {
                conflict_count[nb]--;
            }

            long long gained = 0;
            vector<int> added;

            for (int nb : conflicts[u]) {
                if (conflict_count[nb] == 0) {

                    selected.insert(nb);
                    total_score += skills[nb];
                    gained += skills[nb];
                    added.push_back(nb);

                    for (int nb2 : conflicts[nb]) {
                        conflict_count[nb2]++;
                    }
                }
            }

   
            if (gained > skills[u]) {
                
                improved = true;
            } else {
           

            
                for (int j = 0; j < added.size(); j++) {
                    int nb = added[j];
                    selected.erase(nb);
                    total_score -= skills[nb];
                    for (int nb2 : conflicts[nb]) {
                        conflict_count[nb2]--;
                    }
                }

                selected.insert(u);
                total_score += skills[u];
                for (int nb : conflicts[u]) {
                    conflict_count[nb]++;
                }
            }
        }
    }
}


void shake(int remove_count) {

    vector<int> sel_vec;
    for (int u : selected) {
        sel_vec.push_back(u);
    }

    if (remove_count > sel_vec.size()) {
        remove_count = sel_vec.size();
    }


    for (int i = 0; i < remove_count; i++) {
        int idx = rand() % sel_vec.size();
        int u = sel_vec[idx];

       
        sel_vec[idx] = sel_vec[sel_vec.size() - 1];
        sel_vec.pop_back();

   
        selected.erase(u);
        total_score -= skills[u];
        for (int nb : conflicts[u]) {
            conflict_count[nb]--;
        }
    }
}


void greedy(vector<pair<long long, int>> order) {
    
    selected.clear();
    for (int i = 0; i <= N; i++) {
        conflict_count[i] = 0;
    }
    total_score = 0;

    for (int i = 0; i < order.size(); i++) {
        int coder = order[i].second;

        if (conflict_count[coder] == 0) {
           
            selected.insert(coder);
            total_score += skills[coder];

       
            for (int nb : conflicts[coder]) {
                conflict_count[nb]++;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

   
    skills.resize(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> skills[i];
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        conflicts[u].insert(v);
        conflicts[v].insert(u);
    }


    conflict_count.resize(N + 1, 0);


    vector<pair<long long, int>> order;
    for (int i = 1; i <= N; i++) {
        order.push_back(make_pair(skills[i], i));
    }
    sort(order.begin(), order.end());
    reverse(order.begin(), order.end());

  
    srand(time(0));


    greedy(order);
    local_search();

    long long best_score = total_score;
    unordered_set<int> best_selected = selected;

   
    auto start_time = chrono::steady_clock::now();
    int no_improve_streak = 0;

    while (true) {
        
        auto now = chrono::steady_clock::now();
        double elapsed = chrono::duration<double>(now - start_time).count();
        if (elapsed > 290.0) break; 

        if (no_improve_streak > 30) {
       
            for (int i = order.size() - 1; i > 0; i--) {
                int j = rand() % (i + 1);
                pair<long long, int> temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
    
            stable_sort(order.begin(), order.end());
            reverse(order.begin(), order.end());

            greedy(order);
            no_improve_streak = 0;
        } else {
         
            int remove_count = 3 + no_improve_streak / 5;
            shake(remove_count);
        }

       
        local_search();

      
        if (total_score > best_score) {
            best_score = total_score;
            best_selected = selected;
            no_improve_streak = 0;
        } else {
            no_improve_streak++;
        }
    }


    cout << best_score << "\n";

    vector<int> result;
    for (int u : best_selected) {
        result.push_back(u);
    }
    sort(result.begin(), result.end());

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << "\n";

    return 0;
}