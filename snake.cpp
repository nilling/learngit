//
//
//
//	GAME  贪吃蛇
//	AUTHOR  nil
//	DATE  2018/8/8
//
//







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
#include <deque>

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
		deque <int> direction;			//保存每次前进方向
		int mod;						//游戏模式，普通为0，冒险为1
		int score;						//游戏分数
		int grade;						//游戏等级
		int autoSpeed;					//游戏自动更新速度
		char map[N][N];					//地图
		int opposite_direction[5]={0,80,72,77,75};						//保存个方向的方向ASC码
		int speed[9] = {0,800,600,500,420,250,100,40,5};				//保存各个等级速度值
	public:
	Map():head({N/2,N/2}),tail({N/2,N/2-2}),mod(0),score(0),grade(1),autoSpeed(speed[grade]){}
	void Hello();
	void Print_Hello(int);
	void Start_Game();
	void Initialize_Map();
	int Update_Map();
	void Show_Map();
	void Rand_Food();
	void Reset();
		
};

void Map::Hello()
{
	while(true)
	{
		system("cls");
		Print_Hello(mod);     
		
		if (_getch()!=13)      			//判断是否为回车键，判断选择的模式
		{
			switch(_getch()){				//判断上下移动
				case 80 : mod=1;break;
				case 72 : mod=0;break;
				
			}
			continue;
		}
		
		if (mod==0)
		{
			do{
				system("cls");
				cout << "\n\n\n\n\t\t\t 请输入游戏级别（1-8）：";
				cin >> grade;
			}while(grade>8||grade<1);
			autoSpeed = speed[grade];       //更新游戏级别速度
			break;
		}
		else break;
	}
	Start_Game();
}

void Map::Print_Hello(int mod)
{
	srand((unsigned)time(NULL));
	cout<<"\n\n\n\t\t\t\t 贪吃蛇 \n\n\n\n";
	cout<< "\t\t\t  请选择你的模式：";
	cout << "\n\n\t\t\t     普通模式";
	if(mod==0) cout << "  *";
	cout << "\n\n\t\t\t     冒险模式";
	if (mod==1) cout << "  *";
	cout << "\n\n\n\n\n\n\n\n  版本V1.0      \t\t\t\t作者：nil"; 
}

void Map::Start_Game()
{
	char choose;
	Initialize_Map();  //初始化地图
	Rand_Food();
	do{								//进行游戏
		Show_Map();
	}while(Update_Map());
	cout << "\t\t Game Over!  你还继续吗？（Y或其它建）:";
	cin >> choose;
	if(choose=='y'||choose=='Y')  //重新开始
	{
		Reset();
		Hello();
	}
}

void Map::Initialize_Map()   
{
	for (int i = 0;i < N;i++)                       //打印边界
		{
			map[0][i] = map[N-1][i] = '*';
			map[i][0] = map[i][N-1] = '*';
		}
	for (int i = 1;i < N-1;i++)                    //打印中间的空白
		for (int j =1;j <N-1;j++ )
			map[i][j]=' ';
		
	map[N/2][N/2] = '@';
	map[N/2][N/2-1] = map[N/2][N/2-2] = '.';
	direction.push_front(Right);                  //蛇尾需要两个向右才能到达蛇头，所以需要push两次
	direction.push_front(Right);
	
	
}

void Map::Show_Map()       	//打印
{
	
	system("cls");
	for (int i = 0; i<N;i++)
	{
		cout<<"\t";
		for (int j=0;j<N;j++)
			cout << map[i][j]<<' ';
		if(i == N/4)
			cout << "\t Score: " << score;
		if(i == N / 4 + 4)
			cout << "\t grade: " << grade;
		if(i == N / 4 + 8)
			cout << "按空格键暂停/继续";
		cout << endl;
	}
}

int Map::Update_Map()
{
	
	int tmp_direction,tmp_others,sign=0;
	double start_time = (double)clock() / CLOCKS_PER_SEC;         		//记录开始时间
	
	do{
		if(_kbhit()){                									//判断是否有键盘输入但不读入
			tmp_others = _getch();
			if(tmp_others == 32)                                        //判断是否为空格
				while(_getch() != 32);
			else if (tmp_others == 224)                       			 //上下左右ASC码有两位。第一位都是224
			{
				tmp_direction = _getch();
				if(opposite_direction[direction.front()] == tmp_direction)                     //判断是否为反方向，反方向无效
					continue;
				switch (tmp_direction){
					case 72: direction.push_front(Up); sign=1; break;
					case 80: direction.push_front(Down); sign=1; break;
					case 75: direction.push_front(Left); sign=1; break;
					case 77: direction.push_front(Right); sign=1; break;
				}
				if (sign )break;
			}
			
		}
		if ((double)clock() / CLOCKS_PER_SEC - start_time > autoSpeed / 1000.0)                    //超过自动更新时间则自动更新蛇的位置
		{
			direction.push_front(direction.front());
			break;
		}
	}while(true);
	
	map[head.x][head.y] = '.';
	switch (direction.front()){
		case Up: head.x -= 1; break;
		case Down: head.x += 1; break;
		case Left: head.y -=1; break;
		case Right: head.y +=1; break;
	}
	
	
	if (head.x == food.x && head.y == food.y){  							//如果吃到食物
		map[head.x][head.y] = '@';
		score += 10;
		if(mod == 1){
			if(score / 60 >= grade)											//每吃6个食物加一个等级，最高为5级
			{
				if(grade < 5){
					grade++;
					autoSpeed = speed[grade];								//更新蛇的速度
				}
			}
		}
		Rand_Food();														//产生新的食物
	}
	else if (map[head.x][head.y]!=' '&&!(head.x == tail.x && head.y == tail.y))     //判断蛇头不再空白区域并且不再蛇尾的位置，因为蛇尾已经前进了
		return 0;
		
	else {																	//没吃到食物
		map[tail.x][tail.y] = ' ';
		map[head.x][head.y] = '@';
		switch(direction.back()){						//更新蛇尾坐标
			case Up: tail.x -= 1; break;
			case Down: tail.x +=1; break;
			case Left: tail.y -= 1; break;
			case Right: tail.y +=1; break;
		}
		direction.pop_back();                      //弹出最后一个蛇尾坐标
	}
	return 1;
}

void Map::Rand_Food()
{
	do{
		food.x = rand() % (N-2) + 1;
		food.y = rand() % (N-2) + 1;
	}while(map[food.x][food.y]!=' ');
	
	map[food.x][food.y] = '#';
}

void Map::Reset()        //重置游戏
{
	Initialize_Map();
	head = {N / 2,N / 2};
	tail = {N / 2,N / 2 - 2};
	mod = 0;
	score = 0;
	grade = 1;
	autoSpeed = 800;
	direction.clear();
} 

int main()
{
	HANDLE hdle = GetStdHandle(STD_OUTPUT_HANDLE);			//隐藏光标的方法
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hdle,&CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(hdle,&CursorInfo);
	
	Map m;
	m.Hello();
	
	return 0;
}








