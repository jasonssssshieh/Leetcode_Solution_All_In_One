题目链接：https://leetcode.com/problems/robot-room-cleaner/description/
扫地机器人问题。当时准备Google面试的时候的高频题，不过已经被ban了，比较大家都知道怎么做了。很经典的一道模拟DFS的题。
题目大意是给了一个机器人和4个API接口：左转90度，右转90度，以及clean当前位置，和 move函数。这个move函数是比较烦人的，
因为如果能够移动，会返回true并且走到了你的当前方向的下一个。不能移动就返回false。
初始状态机器人是朝向正北方向的。
interface Robot {
  // returns true if next cell is open and robot moves into the cell.
  // returns false if next cell is obstacle and robot stays on the current cell.
  boolean move();

  // Robot will stay on the same cell after calling turnLeft/turnRight.
  // Each turn will be 90 degrees.
  void turnLeft();
  void turnRight();

  // Clean the current cell.
  void clean();
}
由于我们没办法知道整个room有多大，而且你移动之后的位置也没办法确定，很有可能重复，或者 没有清理完整个room。因此，这里我们就需要模拟DFS的过程：
对于初始位置，我们记为[0,0]，同时用一个hash map记录我们走过的position，这样我们就不会走重复的路。
同时对于每一个position，我们都去走四个方向，前后左右，每走完一次，我们都将方向恢复到走这一步之前的方向，这样就保证了无重复无遗漏的走完整个room。

代码如下：

class Solution {
public:
    int i = 0;//初始位置
    int j = 0;//初始位置
    unordered_map<int, unordered_set<int>> position;//已经走过的位置，hash map来储存，方法查找。
    vector<vector<int>> dir = {{-1, 0}, {0, -1}, {1,0}, {0,1}};//前后左右四个方向，这里方向的坐标一定要和robot移动的方向一致。不能随意设置
    int d = 0;//方向的index，每次我们都走4个方向。
    void cleanRoom(Robot& robot) {
        if(position.count(i) && position[i].count(j)) return;//如果当前位置已经访问过，那么就不再访问
        position[i].insert(j);//加入当前位置作为已经访问过的位置
        robot.clean();//清扫房间
        int count = 4;//我们要走四个方向，计数
        while(count){
            if(robot.move()){//如果是能够移动的 那么我们就进入dfs过程
                i += dir[d][0];//更新当前位置坐标
                j += dir[d][1];
                cleanRoom(robot);//进入dfs
                robot.turnRight();
                robot.turnRight();
                //上面两步是调头180度，因为我们要走回到原来的位置
                robot.move();
                //往回走一步，这样就恢复到初始位置，但此时方向还没有恢复，因此我们还需要恢复方向
                robot.turnRight();
                robot.turnRight();
                //恢复方向
                i -= dir[d][0];//恢复坐标
                j -= dir[d][1];
            }
            robot.turnLeft();//下一个应该访问的方向
            d = (d+1)%4;//下一个方向的坐标
            count--;
        }
        return;
    }
};
