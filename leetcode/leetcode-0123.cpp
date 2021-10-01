class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int N = prices.size();
        vector<int> max_before = vector<int>(N);
        vector<int> max_after = vector<int>(N);
        
        max_before[0] = 0;
        int min_price = prices[0];
        
        for (int i = 1; i < N; i++) {
            min_price = min(min_price, prices[i]);
            max_before[i] = max(max_before[i-1], prices[i] - min_price);
        }
                
        max_after[N-1] = 0;
        int max_price = prices[N-1];
        
        for (int i = N-2; i >= 0; i--) {
            max_price = max(max_price, prices[i]);
            max_after[i] = max(max_after[i+1], max_price - prices[i]);
        }
        
        int max_profit = 0;
        for (int i = 0; i < N; i++)
            max_profit = max(max_profit, max_before[i] + max_after[i]);
                
        return max_profit;
    }
};
