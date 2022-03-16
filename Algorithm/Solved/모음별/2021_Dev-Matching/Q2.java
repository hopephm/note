// MoveLine 수정하자
// >> dX,dY 정의 후 특정 조건 만나면 d증가 시켜서 방향전환하게...

class Solution {
    private int[][] board;
    
    private final int UP = 1;
    private final int RIGHT = 2;
    private final int DOWN = 3;
    private final int LEFT = 4;
    
    private void setDefault(int rows, int columns){
        board = new int[rows][columns];
        
        int count = 1;
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                board[i][j] = count++;
            }
        }
    }
    
    private void printBoard(){
        for(int i = 0; i < board.length; i++){
            for(int j = 0; j < board[i].length; j++)
                System.out.print(board[i][j]+"\t");
            System.out.println();
        }
    }
    
    private void moveLine(int from, int to, int line, int dir){
        if(dir == UP){
            for(int i = to; i < from; i++)
                board[i][line] = board[i+1][line];
        }else if(dir == DOWN){
            for(int i = to; i > from; i--)
                board[i][line] = board[i-1][line];
        }else if(dir == LEFT){
            for(int i = to; i < from; i++)
                board[line][i] = board[line][i+1];            
        }else if(dir == RIGHT){
            for(int i = to; i > from; i--)
                board[line][i] = board[line][i-1];
        }
    }
    
    private void rotateBoard(int[] queries){
        int minY = queries[0]-1;
        int minX = queries[1]-1;
        int maxY = queries[2]-1;
        int maxX = queries[3]-1;
        
        int minValue = board[minY][minX];
        
        moveLine(maxY, minY, minX, UP);
        moveLine(maxX, minX, maxY, LEFT);
        moveLine(minY, maxY, maxX, DOWN);
        moveLine(minX, maxX, minY, RIGHT);
        
        board[minY][minX+1] = minValue;
    }
    
    private int getMinValue(int[] queries){
        int minY = queries[0]-1;
        int minX = queries[1]-1;
        int maxY = queries[2]-1;
        int maxX = queries[3]-1;
        
        int minValue = board[minY][minX];
        for(int i = minY; i <= maxY; i++){
            for(int j = minX; j <= maxX; j++){
                if(i != minY && i != maxY && j != minX && j != maxX) continue;
                if(board[i][j] < minValue) minValue = board[i][j];
            }
        }
        
        return minValue;
    }
    
    public int[] solution(int rows, int columns, int[][] queries) {
        int[] answer = new int[queries.length];
        
        setDefault(rows, columns);
        
        for(int i = 0; i < queries.length; i++){
            rotateBoard(queries[i]);
            answer[i] = getMinValue(queries[i]);
        }
        
        return answer;
    }
}