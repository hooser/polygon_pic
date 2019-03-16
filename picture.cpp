  
/*1552492 胡世杰 */
#include <glut.h>
#include<math.h>
#include<iostream>
#define WINDOW_HEIGHT 1000
#define PI 3.1415926
using namespace std;

//扫描线算法：
/*
ET
ymax：边的上端点的y坐标值
x：边的下端点的x坐标
dmax：边的斜率的倒数

AET：
ymax：所交边的最大y值
x：当前扫描线与边的交点的x坐标
dmax：边的斜率的倒数
*/

typedef struct Edge
{ 
   int ymax;          
   float deltax;         
   float x;      
   struct Edge *next;
}Edge,*ptrtoEdge;

typedef struct edge      //输入过程中记录的边
{
	int highy;
	int lowy;
	int lowx;
	float deltax;
}edge,*ptrtoedge;

 typedef struct POINT
{
  int x;
  int y; 
} POINT,*ptrtoPOINT;

 typedef struct EThead
 {
	 int ylow;            //线段下端点的y值
	 Edge *next;          //指针指向Edge节点
 }EThead;

 typedef struct temppoint
 {
	 double x;
	 double y;
 }temppoint,*ptrtotemppoint;
 double alpha;
 int k;                 //输入点数
 POINT *p;
 bool select=false;
 EThead head[50];       //点数最大为50
 int headlen;
 edge *pe;             //边（不包括平行边）
 int pelen;            //边（不包括平行边）的数目
 ptrtoEdge AEL;        //ael表头

/*POINT changetonew(double x,double y,double alpha) //将标准坐标转换为倾斜坐标
{
	POINT node;
	if(alpha==0)
	{
		node.x=x;
		node.y=y;
	}

	else 
	{
		double r=sqrt(x*x+y*y);
		double cita=acos(x/r);
		node.x=r*cos(alpha+cita);
		node.y=r*sin(alpha+cita);
	}
	return node;
}   */
temppoint changetonew(double x,double y,double alpha) //将标准坐标转换为倾斜坐标
{
	temppoint node;
	if(alpha==0)
	{
		node.x=x;
		node.y=y;
	}

	else 
	{
		double r=sqrt(x*x+y*y);
		double cita=acos(x/r);
		node.x=r*cos(alpha+cita);
		node.y=r*sin(alpha+cita);
	}
	return node;
}    
/*POINT changetoori(double x,double y,double alpha) //将倾斜坐标转换为标准坐标
{
	POINT node;
	if(alpha==0)
	{
		node.x=x;
		node.y=y;
	}
	else
	{
		double r=sqrt(x*x+y*y);
		double belta=acos(x/r);
		if(y<0)
			belta=-fabs(belta);
		node.x=r*cos(belta-alpha);
		node.y=r*sin(belta-alpha);
	}
	return node;
} */

temppoint changetoori(double x,double y,double alpha) //将倾斜坐标转换为标准坐标
{
	temppoint node;
	if(alpha==0)
	{
		node.x=x;
		node.y=y;
	}
	else
	{
		double r=sqrt(x*x+y*y);
		double belta=acos(x/r);
		if(y<0)
			belta=-fabs(belta);
		node.x=r*cos(belta-alpha);
		node.y=r*sin(belta-alpha);
	}
	return node;
}

bool isnull();    
//功能：判断AEL表头是否为空
//返回：空 false、 非空 true

//void createET(EThead head[],POINT *new_p,int k);   
void createET(EThead head[],temppoint *new_p,int k);    
//功能：创建ET结构体
//参数：head, new_p：点在新坐标系下的坐标，k：点的数目
//返回：head数组结构体

void print();
//功能：填充影线

void myInit(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0f,0.0f,0.0f);
	glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,640.0,0.0,480.0);
}

void myDisplay()
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	//POINT *new_p=new POINT[k+1];
	temppoint *new_p=new temppoint[k+1];
	temppoint *ori_p=new temppoint[k+1];
	int isedge=0;
	if(select==true)              //输入了k个点
	{
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<k;i++)
	{
		
		new_p[i]=changetonew(p[i].x,p[i].y,alpha);
		isedge++;
		if(isedge==2)
		{
			
			//else
			//{
				if(new_p[i].y!=new_p[i-1].y)      //不是平行边，加入pe数组
				{
					isedge--;
					if(new_p[i].y>new_p[i-1].y)
					{
						pe[pelen].highy=new_p[i].y;
						pe[pelen].lowy=new_p[i-1].y;
						pe[pelen].lowx=new_p[i-1].x;
						pe[pelen].deltax=(new_p[i-1].x-new_p[i].x)/(new_p[i-1].y-new_p[i].y);
						pelen++;
					}
					else
					{
						pe[pelen].highy=new_p[i-1].y;
						pe[pelen].lowy=new_p[i].y;
						pe[pelen].lowx=new_p[i].x;
						pe[pelen].deltax=(new_p[i-1].x-new_p[i].x)/(new_p[i-1].y-new_p[i].y);
						pelen++;
					}
				} //if(new_p[i].y!=new_p[0].y)
			//}
					if(i==k-1)      //k-1&0
			   {
				if(new_p[i].y!=new_p[0].y)      //不是平行边，加入pe数组
				{
					if(new_p[i].y>new_p[0].y)
					{
						pe[pelen].highy=new_p[i].y;
						pe[pelen].lowy=new_p[0].y;
						pe[pelen].lowx=new_p[0].x;
						pe[pelen].deltax=(new_p[0].x-new_p[i].x)/(new_p[0].y-new_p[i].y);
						pelen++;
					}
					else
					{
						pe[pelen].highy=new_p[0].y;
						pe[pelen].lowy=new_p[i].y;
						pe[pelen].lowx=new_p[i].x;
						pe[pelen].deltax=(new_p[0].x-new_p[i].x)/(new_p[0].y-new_p[i].y);
						pelen++;
					}
				} //if(new_p[i].y!=new_p[0].y)
			   }
		} //if(isedge==2)
		ori_p[i]=changetoori(new_p[i].x,new_p[i].y,alpha);
        glVertex2i(ori_p[i].x,ori_p[i].y);
	}
     glEnd();
	 createET(head,new_p,k);
	 print();
	}//if(select==true)  
	glutSwapBuffers();
    glFlush();
	 
}
void myMouse(int button, int state,int x,int y)  //鼠标控制部分，通过点击来记录点
{
  static int number=0;
  
	if(state==GLUT_DOWN)
  {
	  if(button==GLUT_LEFT_BUTTON)
	  {
		  p[number].x=x;
	      p[number].y=480-y;
		                     //标准坐标系的坐标

		  glBegin(GL_POINTS);
	      glVertex2i(x,480-y);
          glEnd();          //鼠标点显示在board上

		  glFlush();
		 // POINT b;
		  temppoint b;
		  b=changetonew(p[number].x,p[number].y,alpha);
		  cout<<"原始坐标为："<<p[number].x<<" "<<p[number].y<<endl;
		  cout<<"转换后坐标为："<<b.x<<"  "<<b.y<<endl;
		  number++;
		  
	  if(number==k)
	  { number=0;
	    select=true;
		glutPostRedisplay();
	  }
	  }
	  else if(button==GLUT_RIGHT_BUTTON)
	  {
		 glClear(GL_COLOR_BUFFER_BIT);
		 glFlush();
	  }
	}
}
int main(int argc, char *argv[])
{
	for(int i=0;i<50;i++)
		head[i].next=NULL;
    cout<<"请输入点数"<<endl;
	cin>>k;
	pe=new edge[k+1];
	pelen=0;
	headlen=0;
	AEL=new Edge;
	AEL->next=NULL;
	AEL->x=-1<<30;
	cout<<"请输入影线角度"<<endl;
	cin>>alpha;
	alpha=alpha*PI/180.0;
	p=(POINT*)malloc(k*sizeof(POINT));
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("任意图形影线填充程序");
	glutMouseFunc(myMouse);
    glutDisplayFunc(myDisplay);
	myInit();
    glutMainLoop();
    return 0;
}

//void createET(EThead head[],POINT *new_p,int k)
void createET(EThead head[],temppoint *new_p,int k)
{
	//将下端点y值顺序不重复排列
	int pecount=0;        //记录访问pe数组元素的个数
	int flag[50];         //记录值是否被访问过
	for(int i=0;i<50;i++)
	{
		flag[i]=0;
	}
	int mini=0;
	int min=10000;
	while(pecount<pelen) //访问数目小于记录边数
	{
		for(int i=0;i<pelen;i++)
		{
			if(flag[i]==0) 
			{
				if(min>pe[i].lowy)
				{
			    	min=pe[i].lowy;
			    	mini=i;
					//cout<<"i="<<i<<endl;
					//cout<<"min="<<min<<endl;
					//cout<<"mini="<<mini<<endl;
				}
			}
		}
		pecount++;
		head[headlen].ylow=min;
		headlen++;
		flag[mini]=1;
		for(int i=0;i<pelen;i++)   //把与上面找到的ylow相同的节点也置为访问状态
		{
			if(flag[i]==0 && pe[i].lowy==min)
			{
				pecount++;
				flag[i]=1;
			}
		}
		min=10000;
	} //while(pecount<pelen)
	//建立ET结构体
	for(int i=0;i<headlen;i++)
	{
		for(int j=0;j<pelen;j++)           
		{
			if(head[i].ylow==pe[j].lowy)        //将pe[j]的参数节点插入到head[i]后
			{
				ptrtoEdge info=new Edge;
				info->ymax=pe[j].highy;
				info->x=pe[j].lowx;
				info->deltax=pe[j].deltax;
				info->next=NULL;
				if(head[i].next==NULL)
				{
					head[i].next=info;
				}
				else
				{
					ptrtoEdge find=head[i].next;
					while(find->next!=NULL)
					{
						find=find->next;
					}//while(find->next!=NULL)
					find->next=info;
				}
			} //if(head[i].ylow==pe[j].lowy)
		}
	}
	//将head后挂节点按照x值顺序排列
	for(int i=0;i<headlen;i++)
	{
		if(head[i].next->next!=NULL)
		//不只挂一个节点
		{
			ptrtoEdge r=head[i].next;
			//ptrtoEdge f=head[i].next->next;
			while(r!=NULL)
			{
				ptrtoEdge f=head[i].next->next;
				while(f!=NULL)
				{
			    	if(r->x>f->x)
			    	{
						int tempymax;
						int tempx;
						double tempdeltax;
						tempymax=f->ymax;
						tempx=f->x;
						tempdeltax=f->deltax;
						f->ymax=r->ymax;
						f->x=r->x;
						f->deltax=r->deltax;
						r->ymax=tempymax;
						r->x=tempx;
						r->deltax=tempdeltax;
		    		}
					f=f->next;
				} //while(f!=NULL)
				r=r->next;
			}
		} //if(head[i].next!=NULL)
	}
}
bool isnull()
{
	if(AEL->next==NULL)
	{
		return false;
	}
	else
		return true;
}
void print()
{
	//ptrtoEdge tail=AEL;        //tail指向AEL尾节点
	int smx=head[0].ylow;      //smx定义为图形最低点y值
	int db=0;
	//cout<<"smx="<<smx<<endl;
	int count=0;               //遍历head[]记录，最大为headlen
	while(isnull()==true || count<headlen)
	{

		if(smx==head[count].ylow) 

		//扫描线与当前线段下端点y值相等，将head后的链表加入AEL
		//插入的顺序为x顺序排列
		{
			if(AEL->next==NULL)
				AEL->next=head[count].next;
			else
			{
				ptrtoEdge f=AEL->next;
				ptrtoEdge r=AEL;
				while(f!=NULL && f->x<head[count].next->x)
				{
					r=f;
					f=f->next;
				}//while(f->next!=NULL && f->x<head[count].next->x)
				if(f==NULL)
					r->next=head[count].next;
				else
				{
					r->next=head[count].next;
					while(r->next!=NULL)
						r=r->next;
					r->next=f;
				}
			} 
			count++;
		}//if(smx==head[count].ylow) 
		
		//将ymax<=smx的节点删除
		ptrtoEdge f=AEL->next;
		ptrtoEdge r=AEL;
		while(f!=NULL)
		{
			while(f!=NULL && f->ymax<=smx)
			{
				r->next=f->next;
			    f=f->next;
			}
			r=f;
			if(f!=NULL)
				f=f->next;
		}
		if(isnull()==false)   //为空
		{
			break;
		}

		//坐标转换后投影
		temppoint new_p1,new_p2,ori_p1,ori_p2;
		r =AEL->next;
		f=r->next;
		new_p1.x=r->x;
		new_p1.y=smx;
		new_p2.x=f->x;
		new_p2.y=smx;
		ori_p1=changetoori(new_p1.x,new_p1.y,alpha);
		ori_p2=changetoori(new_p2.x,new_p2.y,alpha);
		while(1)
		{
			if((db+1)%5==0)
			{
    		    glBegin(GL_LINES);
                glVertex2i(int(ori_p1.x),int(ori_p1.y));
	    	    glVertex2i(int(ori_p2.x),int(ori_p2.y));
                glEnd();
			}
			    r=f->next;
			    if(r==NULL)
				    break;
			    f=r->next;
			    if(f==NULL)
				    break;
			    new_p1.x=r->x;
	    	    new_p1.y=smx;
    		    new_p2.x=f->x;
	    	    new_p2.y=smx;
    		    ori_p1=changetoori(new_p1.x,new_p1.y,alpha);
    		    ori_p2=changetoori(new_p2.x,new_p2.y,alpha);
			
		}
		//更新节点和smx
		smx++;
		db++;
		r=AEL->next;
		while(r!=NULL)
		{
			r->x=r->x+r->deltax;
			r=r->next;
		}
	}//while(isnull()==true || count<headlen)
}