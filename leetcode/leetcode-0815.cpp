struct route {
    unordered_set<int> neighbours;
    bool is_start;
    bool is_end;
    int path;
    bool visited;
} rts[500];

int route_idx = 0;

class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) return 0;
        
        unordered_map<int, vector<int>> stop_to_routes;
        for (int i = 0; i < routes.size(); i++) {
            rts[i].neighbours = {};
            rts[i].is_start = false;
            rts[i].is_end = false;
            rts[i].visited = false;
            for (auto stop : routes[i]) {
                if (stop == source) rts[i].is_start = true;
                if (stop == target) rts[i].is_end = true;
                stop_to_routes[stop].push_back(i);
            }
            if (rts[i].is_start) rts[i].path = 0;
            else rts[i].path = 1000;

            if (rts[i].is_start && rts[i].is_end) {
                return 1;
            }
        } // sum(routes[i].length) <= 10^5 !
        
        for (int i = 0; i < routes.size(); i++) {
            for (auto stop : routes[i]) {
                copy(
                    stop_to_routes[stop].begin(),
                    stop_to_routes[stop].end(),
                    inserter(rts[i].neighbours, rts[i].neighbours.end())
                );
            }
        }
                        
        while (true) {
            int min_val = 1000;
            int min_idx = -1;
            for (int i = 0; i < routes.size(); i++) {
                if (!rts[i].visited && rts[i].path < min_val) {
                    min_val = rts[i].path;
                    min_idx = i;
                }
            }
            
            if (min_idx < 0) return -1;
            rts[min_idx].visited = true;
            
            for (auto neigh : rts[min_idx].neighbours) {
                rts[neigh].path = min(rts[neigh].path, rts[min_idx].path + 1);
                if (rts[neigh].is_end) return rts[neigh].path + 1;
            }
        }
        
    }
};
