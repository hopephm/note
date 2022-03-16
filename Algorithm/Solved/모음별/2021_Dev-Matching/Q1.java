class Solution {
    private int maxRank;
    private int minRank;
    
    private final int numbers = 6;
    
    private void setDefault(){
        maxRank = -1;
        minRank = -1;
    }
    
    private int getZeroCount(int[] lottos){
        int count = 0;
        for(int i = 0; i < numbers; i++)
            if(lottos[i] == 0)
                count ++;
        return count;
    }
    
    private int checkNumbers(int[] lottos, int[] win_nums){
        int matched = 0;
        for(int i = 0; i < numbers; i++){
            if(lottos[i] == 0) continue;
            for(int j = 0; j < numbers; j++){
                if(lottos[i] == win_nums[j]){
                    matched++; 
                    break;
                }
            }
        }
        
        return matched;
    }
    
    private void getMinMaxRank(int[] lottos, int[] win_nums){
        int zeroCount = getZeroCount(lottos);
        int minMatched = checkNumbers(lottos, win_nums);
        int maxMatched = minMatched+zeroCount;
        
        this.minRank = 6-maxMatched+1;
        this.maxRank = 6-minMatched+1;
        
        if(this.minRank > 6) this.minRank = 6;
        if(this.maxRank > 6) this.maxRank = 6;
    }
    
    public int[] solution(int[] lottos, int[] win_nums) {
        int[] answer = {-1, -1};
        
        setDefault();
        getMinMaxRank(lottos, win_nums);    
        
        answer[0] = minRank;
        answer[1] = maxRank;
        
        
        return answer;
    }
}