//
//
//
//	GAME  ̰����
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

#define N 30                 //��ͼ�߳�
#define Up 1				//ASC�� 72
#define Down 2				//ASC�� 80
#define Left 3				//ASC�� 75
#define Right 4				//ASC�� 77

using namespace std;

class Map
{
	private :
		class snake{               //��������
			public :
			int x;
			int y;
			
		};
		class Food{               //ʳ��������
			public:
				int x;
				int y;
			
		};
		Food food;				//ʳ��
		snake head ,tail;		//��ͷ ��β
		deque <int> direction;			//����ÿ��ǰ������
		int mod;						//��Ϸģʽ����ͨΪ0��ð��Ϊ1
		int score;						//��Ϸ����
		int grade;						//��Ϸ�ȼ�
		int autoSpeed;					//��Ϸ�Զ������ٶ�
		char map[N][N];					//��ͼ
		int opposite_direction[5]={0,80,72,77,75};						//���������ķ���ASC��
		int speed[9] = {0,800,600,500,420,250,100,40,5};				//��������ȼ��ٶ�ֵ
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
		
		if (_getch()!=13)      			//�ж��Ƿ�Ϊ�س������ж�ѡ���ģʽ
		{
			switch(_getch()){				//�ж������ƶ�
				case 80 : mod=1;break;
				case 72 : mod=0;break;
				
			}
			continue;
		}
		
		if (mod==0)
		{
			do{
				system("cls");
				cout << "\n\n\n\n\t\t\t ��������Ϸ����1-8����";
				cin >> grade;
			}while(grade>8||grade<1);
			autoSpeed = speed[grade];       //������Ϸ�����ٶ�
			break;
		}
		else break;
	}
	Start_Game();
}

void Map::Print_Hello(int mod)
{
	srand((unsigned)time(NULL));
	cout<<"\n\n\n\t\t\t\t ̰���� \n\n\n\n";
	cout<< "\t\t\t  ��ѡ�����ģʽ��";
	cout << "\n\n\t\t\t     ��ͨģʽ";
	if(mod==0) cout << "  *";
	cout << "\n\n\t\t\t     ð��ģʽ";
	if (mod==1) cout << "  *";
	cout << "\n\n\n\n\n\n\n\n  �汾V1.0      \t\t\t\t���ߣ�nil"; 
}

void Map::Start_Game()
{
	char choose;
	Initialize_Map();  //��ʼ����ͼ
	Rand_Food();
	do{								//������Ϸ
		Show_Map();
	}while(Update_Map());
	cout << "\t\t Game Over!  �㻹�����𣿣�Y����������:";
	cin >> choose;
	if(choose=='y'||choose=='Y')  //���¿�ʼ
	{
		Reset();
		Hello();
	}
}

void Map::Initialize_Map()   
{
	for (int i = 0;i < N;i++)                       //��ӡ�߽�
		{
			map[0][i] = map[N-1][i] = '*';
			map[i][0] = map[i][N-1] = '*';
		}
	for (int i = 1;i < N-1;i++)                    //��ӡ�м�Ŀհ�
		for (int j =1;j <N-1;j++ )
			map[i][j]=' ';
		
	map[N/2][N/2] = '@';
	map[N/2][N/2-1] = map[N/2][N/2-2] = '.';
	direction.push_front(Right);                  //��β��Ҫ�������Ҳ��ܵ�����ͷ��������Ҫpush����
	direction.push_front(Right);
	
	
}

void Map::Show_Map()       	//��ӡ
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
			cout << "���ո����ͣ/����";
		cout << endl;
	}
}

int Map::Update_Map()
{
	
	int tmp_direction,tmp_others,sign=0;
	double start_time = (double)clock() / CLOCKS_PER_SEC;         		//��¼��ʼʱ��
	
	do{
		if(_kbhit()){                									//�ж��Ƿ��м������뵫������
			tmp_others = _getch();
			if(tmp_others == 32)                                        //�ж��Ƿ�Ϊ�ո�
				while(_getch() != 32);
			else if (tmp_others == 224)                       			 //��������ASC������λ����һλ����224
			{
				tmp_direction = _getch();
				if(opposite_direction[direction.front()] == tmp_direction)                     //�ж��Ƿ�Ϊ�����򣬷�������Ч
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
		if ((double)clock() / CLOCKS_PER_SEC - start_time > autoSpeed / 1000.0)                    //�����Զ�����ʱ�����Զ������ߵ�λ��
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
	
	
	if (head.x == food.x && head.y == food.y){  							//����Ե�ʳ��
		map[head.x][head.y] = '@';
		score += 10;
		if(mod == 1){
			if(score / 60 >= grade)											//ÿ��6��ʳ���һ���ȼ������Ϊ5��
			{
				if(grade < 5){
					grade++;
					autoSpeed = speed[grade];								//�����ߵ��ٶ�
				}
			}
		}
		Rand_Food();														//�����µ�ʳ��
	}
	else if (map[head.x][head.y]!=' '&&!(head.x == tail.x && head.y == tail.y))     //�ж���ͷ���ٿհ������Ҳ�����β��λ�ã���Ϊ��β�Ѿ�ǰ����
		return 0;
		
	else {																	//û�Ե�ʳ��
		map[tail.x][tail.y] = ' ';
		map[head.x][head.y] = '@';
		switch(direction.back()){						//������β����
			case Up: tail.x -= 1; break;
			case Down: tail.x +=1; break;
			case Left: tail.y -= 1; break;
			case Right: tail.y +=1; break;
		}
		direction.pop_back();                      //�������һ����β����
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

void Map::Reset()        //������Ϸ
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
	HANDLE hdle = GetStdHandle(STD_OUTPUT_HANDLE);			//���ع��ķ���
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hdle,&CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(hdle,&CursorInfo);
	
	Map m;
	m.Hello();
	
	return 0;
}








