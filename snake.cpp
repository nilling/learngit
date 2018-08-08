/*


	GAME  贪吃蛇
	AUTHOR  nil
	DATE  2018/8/8



*/






#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <queue>
#include <stack>
#include <math.h>
#include <map>
#include <algorithm>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define N 30                 //地图边长
#define Up 1				//ASC码 72
#define Down 2				//ASC码 80
#define Left 3				//ASC码 75
#define Right 4				//ASC码 77

using namespace std;

class Map
{
	private :
		class snake{               //蛇坐标类
			public :
			int x;
			int y;
			
		};
		class Food{               //食物坐标类
			public:
				int x;
				int y;
			
		};
		Food food;				//食物
		snake head ,tail;		//蛇头 蛇尾
};

int main()
{
	
	
	return 0;
}








