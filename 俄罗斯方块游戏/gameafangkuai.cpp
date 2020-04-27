#include<iostream>
#include<string>
#include<stdio.h>
#include<Windows.h>
#include<graphics.h>
#include<time.h>
#include<conio.h>//kbhit();头文件
#define COUNT  5 
#define WIDTH  5
#define HEIGHT 5
#define PEX    20
#define START_X 130
#define START_Y 30

#define UP  72
#define RIGHT 77
#define LEFT  75
#define SPACE 32
#define DOWN   80
int speed=500;
#define minX 30
#define  minY 30
//按键
typedef enum{
	BLOCK_UP,
	BLOCK_RIGHT,
	BLOCK_DOWN,	
	BLOCK_LEFT
}block_dir_t;
//方向
typedef enum{
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT
}move_dir_t;
int score=0;//分数变量
int rank=0;//等级变量
int NextIndex=-1;//下一个方块的种类
int BlockIndex=-1;
//设置颜色
int color[COUNT]={
	GREEN,CYAN,BLUE,RED,MAGENTA
};
int visit[30][15];//访问数组
int markColor[30][15];//表示对应位置的颜色
//设置方块的形态
int block[COUNT*4][HEIGHT][WIDTH]={
	// | 形方块
	{ 
	0,0,0,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,0,0,0 },

	{ 
	0,0,0,0,0,
	0,0,0,0,0,
	0,1,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	{ 
	0,0,0,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,0,0,0 },

	{ 
	0,0,0,0,0,
	0,0,0,0,0,
	0,1,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	// L 形方块
	{ 
	0,0,0,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,1,0,
	0,0,0,0,0 },

	{ 
	0,0,0,0,0,
	0,0,0,0,0,
	0,1,1,1,0,
	0,1,0,0,0,
	0,0,0,0,0 },

	{ 
	0,0,0,0,0,
	0,1,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,0,0,0 },

	{ 
	0,0,0,0,0,
	0,0,0,1,0,
	0,1,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	// 田 形方块
	{ 
	0,0,0,0,0,
	0,1,1,0,0,
	0,1,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	{ 
	0,0,0,0,0,
	0,1,1,0,0,
	0,1,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	{ 
	0,0,0,0,0,
	0,1,1,0,0,
	0,1,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	{ 
	0,0,0,0,0,
	0,1,1,0,0,
	0,1,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	// T 形方块
	{ 
	0,0,0,0,0,
	0,1,1,1,0,
	0,0,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	{ 
	0,0,0,0,0,
	0,0,0,1,0,
	0,0,1,1,0,
	0,0,0,1,0,
	0,0,0,0,0 },

	{ 
	0,0,0,0,0,
	0,0,1,0,0,
	0,1,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	{ 
	0,0,0,0,0,
	0,1,0,0,0,
	0,1,1,0,0,
	0,1,0,0,0,
	0,0,0,0,0 },

	// Z 形方块
	{ 
	0,0,0,0,0,
	0,1,1,0,0,
	0,0,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	{ 
	0,0,0,0,0,
	0,0,1,0,0,
	0,1,1,0,0,
	0,1,0,0,0,
	0,0,0,0,0 },

	{ 
	0,0,0,0,0,
	0,1,1,0,0,
	0,0,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	{ 
	0,0,0,0,0,
	0,0,1,0,0,
	0,1,1,0,0,
	0,1,0,0,0,
	0,0,0,0,0 },

};//
//欢迎界面
void welcome(void){
//初始画布
	initgraph(550,660);
	//设置窗口标题
	HWND window=GetHWnd();//获取窗口
	SetWindowText(window,_T("俄罗斯方块 刘先生开发"));//设置窗口标题
	//设置文本样式
	//setfont(40,0,_T("宋体"));
	settextstyle(40,0,_T("宋体"));
	setcolor(YELLOW);
	outtextxy(205,200,_T("俄罗斯方块"));//设置文字窗口大小
	settextstyle(22,0,_T("隶书"));
	setcolor(RED);
	outtextxy(175,300,_T("编程 刘先生开发！"));//设置文字窗口大小
	Sleep(2000);//2秒=2000毫秒

}
//初始化游戏场景
void initGameScene(){
	char str[16];
	char sstr[16];
	cleardevice();//清除屏幕
	//设置游戏实线方框
	setcolor(YELLOW);
	rectangle(27,27,336,635);
	rectangle(29,29,334,633);
	rectangle(370,50,515,195);
	//设置文本位置样式及颜色
	setfont(24,0,_T("楷体"));
	setcolor(LIGHTGRAY);
	outtextxy(405,215,_T("下一个"));
	setcolor(RED);
	outtextxy(405,280,_T("分数"));//分数文本位置
	sprintf(str,"%d",score);
	outtextxy(415,310,str);
	outtextxy(405,375,_T("等级"));
	sprintf(sstr,"%d",rank);
	outtextxy(425,405,sstr);
	//设置操作说明文本
	setcolor(LIGHTBLUE);
	outtextxy(390,475,_T("操作说明："));
	outtextxy(390,500,_T("↑：旋转"));
	outtextxy(390,525,_T("↓：加速"));
	outtextxy(390,550,_T("←：向左"));
	outtextxy(390,575,_T("→：向右"));
	outtextxy(390,600,_T("空格：暂停"));
}
//方块的清除
void clearBlock(){
	setcolor(BLACK);
	setfont(23,0,"楷体");
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
	        int x=391+j*PEX;
			int y=71+i*PEX;
			outtextxy(x,y,"■");
		
		}
	
	}

}
//*************************//
//清除指定方向的方块
//参数x:表示左上角的x的坐标
//参数y:表示左上角游戏区域的坐标，也表示到顶部的距离
void clearBlock(int x,int y,block_dir_t dir){
    setcolor(BLACK);
	int id=BlockIndex*4+dir;
	y+=START_Y;
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(block[id][i][j]==1){
			//擦除第i行j列
				outtextxy(x+20*j,y+i*20,"■");
			
			}
		
		
		}
	
	}
}

//绘制下降方块
void drawBlock(int x,int y,int blockIndex,block_dir_t dir){
setcolor(color[blockIndex]);
	setfont(23,0,"楷体");
	int id=blockIndex*4+dir;
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
	        if(block[id][i][j]==1){
			outtextxy(x+PEX*j,y+PEX*i,"■");
			}
		}
	
	}	

}
//在右上角绘制下一个方块
void drawBlock(int x,int y){
	setcolor(color[NextIndex]);
	setfont(23,0,"楷体");
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
	        if(block[NextIndex*4][i][j]==1){
			outtextxy(x+PEX*j,y+PEX*i,"■");
			}
		}
	
	}	
}


void nextblock(){
clearBlock();//清除右上角区域

//随机选择一个方块
srand(time(NULL));//使用时间函数的返回值作为随机种子
NextIndex=rand()%COUNT;
//画随机方块
drawBlock(391,71);
}
//指定方向位置运动返回1，否则返回0
int moveable(int x,int y,move_dir_t moveDir,block_dir_t blockDir){
	
	//计算当前方块的左上角游戏区位置
	int x1=(y-minY)/PEX;
	int y1=(x-minX)/PEX;
	int id=BlockIndex*4+blockDir;
	int ret=1;
	if(moveDir==MOVE_DOWN){
		for(int i=0;i<5;i++){
			for(int j=0;j<5;j++){
				if(block[id][i][j]==1&&(x1+i+1>=30||visit[x1+i+1][y1+j]==1)){
					ret=0;

				}
			
			
			}
		
		}
	
	}else if(moveDir==MOVE_LEFT){
	for(int i=0;i<5;i++){
			for(int j=0;j<5;j++){
				if(block[id][i][j]==1&&(y1+j==0||visit[x1+i][y1+j-1]==1)){
					ret=0;

				}
			
			
			}
		
		}

	}else if(moveDir==MOVE_RIGHT){
	for(int i=0;i<5;i++){
			for(int j=0;j<5;j++){
				if(block[id][i][j]==1&&(y1+j+1>=15||visit[x1+i][y1+j+1]==1)){
					ret=0;

				}
			
			
			}
		
		}
	
	}



	return ret;

}
//检测游戏是否结束
void failCheck(){
	if(!moveable(START_X,START_Y,MOVE_DOWN,BLOCK_UP)){
	  
		setcolor(WHITE);
		settextstyle(45,0,_T("隶体"));
		outtextxy(75,300,"游戏结束！");
		Sleep(1000);
		system("pause");
		closegraph();//关闭画布
		exit(0);//程序结束按钮
	
	}

}
void wait(int interval){
	int count=interval/10;
	for(int i=0;i<count;i++){
	Sleep(10);
	if(kbhit()){
	return;
	
	}
	}
}
//判断当前方块是否可以转到指定方向
int rotatable(int x,int y,block_dir_t dir){
	int id=BlockIndex*4+dir;
	int xIndex=(y-minY)/20;
	int yIndex=(x-minX)/20;
	if(!moveable(x,y,MOVE_DOWN,dir)){
	return 0;
	}
	
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(block[id][i][j]==1&&(yIndex+j<0||yIndex+j>=15||visit[xIndex+i][yIndex+j]==1)){
			 return 0;
			}
		
		}
	}
	return 1;

}
void mark(int x,int y,int blockIndex,block_dir_t dir){
	int id=blockIndex*4+dir;
	int x1=(y-minY)/20;
	int y1=(x-minX)/20;
	for(int i=0;i<5;i++){
	for(int j=0;j<5;j++)
		if(block[id][i][j]==1){
		visit[x1+i][y1+j]=1;
		markColor[x1+i][y1+j]=color[blockIndex];
		
		}
	}
	


}
//使方块开始降落
void move(){
	int x=START_X;
	int y=START_Y;
	int k=0;
	block_dir_t blockDir=BLOCK_UP;
	int curSpeed=speed;
	//检测游戏是否结束
	failCheck();
	//持续降落
	while(1){
		if(kbhit()){
		int key=getch();
		if(key==SPACE) {
		//Sleep(100000);
			getch();//暂停
		}
		
		
		}
	//清除当前方块
	
	clearBlock(x,k,blockDir);
	if(kbhit()){
		int key=getch();
		if(key==UP) {
	            block_dir_t nextDir=(block_dir_t)((blockDir+1)%4);
				if(rotatable(x,y+k,nextDir)){
				blockDir=nextDir;
				}
		}else if(key==DOWN){
		curSpeed=50;
		
		}else if(key==LEFT){
			if(moveable(x,y+k+20,MOVE_LEFT,blockDir)){
			x-=PEX;
			}
		
		}else if(key==RIGHT){
		if(moveable(x,y+k+20,MOVE_RIGHT,blockDir)){
		x+=PEX;
		}
		}
		}
	//绘制当前方块
    k+=PEX;
	drawBlock(x,y+k,BlockIndex,blockDir);
	wait(curSpeed);
	//Sleep(curSpeed);
	//方块的固定处理
	
	if(!moveable(x,y+k,MOVE_DOWN,blockDir)){
	 mark(x,y+k,BlockIndex,blockDir);
	 break;
	
	}

	}	
}
//绘制方块下落
void newblock(){
	//确定使用方块的种类
	BlockIndex=NextIndex;
	//绘制顶部下降的方块
	drawBlock(START_X,START_Y);
	Sleep(300);
	//右上角绘制下一个方块
	nextblock();
	//方块降落
	move();

}
//消除x行，并下移一格
void down(int x){
	for(int i=x;i>=0;i--){
		for(int j=0;j<15;j++){
			if(visit[i-1][j]){
			visit[i][j]=1;
			markColor[i][j]=markColor[i-1][j];
			setcolor(markColor[i][j]);
			outtextxy(PEX*j+minX,PEX*i+minY,"■");
			}else {
			visit[i][j]=0;
			setcolor(BLACK);
			outtextxy(PEX*j+minX,PEX*i+minY,"■");
			
			}
		
		}
	}
	 //清除顶上那一行
	setcolor(BLACK);
	for(int j=0;j<15;j++){
		visit[0][j]=0;
		outtextxy(PEX*j+minX,minY,"■");
	
	}
}
//设置分数的变化
void addScore(int lines){
	char str[10];
	setcolor(RED);
	score+=lines;
	sprintf(str,"%d",score);
	outtextxy(415,310,str);


}
void updateGrade(){
	//50分一级
	rank=score/50;
	char str[16];
	setcolor(RED);
	sprintf(str,"%d",rank);
	outtextxy(425,405,str);
	//更新速度
	speed=500-rank*100;
	if(speed<=100){
	speed=100;
	}
	 
}
void check(){
	int j,i;
	int line=0;
	for( i=29;i>=0;i--){
		//检查第i行有没有满
		for( j=0;j<15&&visit[i][j];j++);
		if(j>=15){
		//消除i行,并下降一行
			down(i);
			i++;
			line+=10;
		}	
	}
	//更新分数
	addScore(line);
	//更新等级，更新速度
	updateGrade();
}
int main(){
welcome();
initGameScene();
//产生新方块
nextblock();
Sleep(500);
//初始化访问数组
memset(visit,0,sizeof(visit));
while(1){
	newblock();
	//消除满行，并更新分数和速度
	check();
}
system("pause");
closegraph();//关闭画布

}