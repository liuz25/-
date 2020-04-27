#include<iostream>
#include<string>
#include<stdio.h>
#include<Windows.h>
#include<graphics.h>
#include<time.h>
#include<conio.h>//kbhit();ͷ�ļ�
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
//����
typedef enum{
	BLOCK_UP,
	BLOCK_RIGHT,
	BLOCK_DOWN,	
	BLOCK_LEFT
}block_dir_t;
//����
typedef enum{
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT
}move_dir_t;
int score=0;//��������
int rank=0;//�ȼ�����
int NextIndex=-1;//��һ�����������
int BlockIndex=-1;
//������ɫ
int color[COUNT]={
	GREEN,CYAN,BLUE,RED,MAGENTA
};
int visit[30][15];//��������
int markColor[30][15];//��ʾ��Ӧλ�õ���ɫ
//���÷������̬
int block[COUNT*4][HEIGHT][WIDTH]={
	// | �η���
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

	// L �η���
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

	// �� �η���
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

	// T �η���
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

	// Z �η���
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
//��ӭ����
void welcome(void){
//��ʼ����
	initgraph(550,660);
	//���ô��ڱ���
	HWND window=GetHWnd();//��ȡ����
	SetWindowText(window,_T("����˹���� ����������"));//���ô��ڱ���
	//�����ı���ʽ
	//setfont(40,0,_T("����"));
	settextstyle(40,0,_T("����"));
	setcolor(YELLOW);
	outtextxy(205,200,_T("����˹����"));//�������ִ��ڴ�С
	settextstyle(22,0,_T("����"));
	setcolor(RED);
	outtextxy(175,300,_T("��� ������������"));//�������ִ��ڴ�С
	Sleep(2000);//2��=2000����

}
//��ʼ����Ϸ����
void initGameScene(){
	char str[16];
	char sstr[16];
	cleardevice();//�����Ļ
	//������Ϸʵ�߷���
	setcolor(YELLOW);
	rectangle(27,27,336,635);
	rectangle(29,29,334,633);
	rectangle(370,50,515,195);
	//�����ı�λ����ʽ����ɫ
	setfont(24,0,_T("����"));
	setcolor(LIGHTGRAY);
	outtextxy(405,215,_T("��һ��"));
	setcolor(RED);
	outtextxy(405,280,_T("����"));//�����ı�λ��
	sprintf(str,"%d",score);
	outtextxy(415,310,str);
	outtextxy(405,375,_T("�ȼ�"));
	sprintf(sstr,"%d",rank);
	outtextxy(425,405,sstr);
	//���ò���˵���ı�
	setcolor(LIGHTBLUE);
	outtextxy(390,475,_T("����˵����"));
	outtextxy(390,500,_T("������ת"));
	outtextxy(390,525,_T("��������"));
	outtextxy(390,550,_T("��������"));
	outtextxy(390,575,_T("��������"));
	outtextxy(390,600,_T("�ո���ͣ"));
}
//��������
void clearBlock(){
	setcolor(BLACK);
	setfont(23,0,"����");
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
	        int x=391+j*PEX;
			int y=71+i*PEX;
			outtextxy(x,y,"��");
		
		}
	
	}

}
//*************************//
//���ָ������ķ���
//����x:��ʾ���Ͻǵ�x������
//����y:��ʾ���Ͻ���Ϸ��������꣬Ҳ��ʾ�������ľ���
void clearBlock(int x,int y,block_dir_t dir){
    setcolor(BLACK);
	int id=BlockIndex*4+dir;
	y+=START_Y;
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(block[id][i][j]==1){
			//������i��j��
				outtextxy(x+20*j,y+i*20,"��");
			
			}
		
		
		}
	
	}
}

//�����½�����
void drawBlock(int x,int y,int blockIndex,block_dir_t dir){
setcolor(color[blockIndex]);
	setfont(23,0,"����");
	int id=blockIndex*4+dir;
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
	        if(block[id][i][j]==1){
			outtextxy(x+PEX*j,y+PEX*i,"��");
			}
		}
	
	}	

}
//�����Ͻǻ�����һ������
void drawBlock(int x,int y){
	setcolor(color[NextIndex]);
	setfont(23,0,"����");
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
	        if(block[NextIndex*4][i][j]==1){
			outtextxy(x+PEX*j,y+PEX*i,"��");
			}
		}
	
	}	
}


void nextblock(){
clearBlock();//������Ͻ�����

//���ѡ��һ������
srand(time(NULL));//ʹ��ʱ�亯���ķ���ֵ��Ϊ�������
NextIndex=rand()%COUNT;
//���������
drawBlock(391,71);
}
//ָ������λ���˶�����1�����򷵻�0
int moveable(int x,int y,move_dir_t moveDir,block_dir_t blockDir){
	
	//���㵱ǰ��������Ͻ���Ϸ��λ��
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
//�����Ϸ�Ƿ����
void failCheck(){
	if(!moveable(START_X,START_Y,MOVE_DOWN,BLOCK_UP)){
	  
		setcolor(WHITE);
		settextstyle(45,0,_T("����"));
		outtextxy(75,300,"��Ϸ������");
		Sleep(1000);
		system("pause");
		closegraph();//�رջ���
		exit(0);//���������ť
	
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
//�жϵ�ǰ�����Ƿ����ת��ָ������
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
//ʹ���鿪ʼ����
void move(){
	int x=START_X;
	int y=START_Y;
	int k=0;
	block_dir_t blockDir=BLOCK_UP;
	int curSpeed=speed;
	//�����Ϸ�Ƿ����
	failCheck();
	//��������
	while(1){
		if(kbhit()){
		int key=getch();
		if(key==SPACE) {
		//Sleep(100000);
			getch();//��ͣ
		}
		
		
		}
	//�����ǰ����
	
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
	//���Ƶ�ǰ����
    k+=PEX;
	drawBlock(x,y+k,BlockIndex,blockDir);
	wait(curSpeed);
	//Sleep(curSpeed);
	//����Ĺ̶�����
	
	if(!moveable(x,y+k,MOVE_DOWN,blockDir)){
	 mark(x,y+k,BlockIndex,blockDir);
	 break;
	
	}

	}	
}
//���Ʒ�������
void newblock(){
	//ȷ��ʹ�÷��������
	BlockIndex=NextIndex;
	//���ƶ����½��ķ���
	drawBlock(START_X,START_Y);
	Sleep(300);
	//���Ͻǻ�����һ������
	nextblock();
	//���齵��
	move();

}
//����x�У�������һ��
void down(int x){
	for(int i=x;i>=0;i--){
		for(int j=0;j<15;j++){
			if(visit[i-1][j]){
			visit[i][j]=1;
			markColor[i][j]=markColor[i-1][j];
			setcolor(markColor[i][j]);
			outtextxy(PEX*j+minX,PEX*i+minY,"��");
			}else {
			visit[i][j]=0;
			setcolor(BLACK);
			outtextxy(PEX*j+minX,PEX*i+minY,"��");
			
			}
		
		}
	}
	 //���������һ��
	setcolor(BLACK);
	for(int j=0;j<15;j++){
		visit[0][j]=0;
		outtextxy(PEX*j+minX,minY,"��");
	
	}
}
//���÷����ı仯
void addScore(int lines){
	char str[10];
	setcolor(RED);
	score+=lines;
	sprintf(str,"%d",score);
	outtextxy(415,310,str);


}
void updateGrade(){
	//50��һ��
	rank=score/50;
	char str[16];
	setcolor(RED);
	sprintf(str,"%d",rank);
	outtextxy(425,405,str);
	//�����ٶ�
	speed=500-rank*100;
	if(speed<=100){
	speed=100;
	}
	 
}
void check(){
	int j,i;
	int line=0;
	for( i=29;i>=0;i--){
		//����i����û����
		for( j=0;j<15&&visit[i][j];j++);
		if(j>=15){
		//����i��,���½�һ��
			down(i);
			i++;
			line+=10;
		}	
	}
	//���·���
	addScore(line);
	//���µȼ��������ٶ�
	updateGrade();
}
int main(){
welcome();
initGameScene();
//�����·���
nextblock();
Sleep(500);
//��ʼ����������
memset(visit,0,sizeof(visit));
while(1){
	newblock();
	//�������У������·������ٶ�
	check();
}
system("pause");
closegraph();//�رջ���

}