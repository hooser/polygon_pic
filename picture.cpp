  
/*1552492 ������ */
#include <glut.h>
#include<math.h>
#include<iostream>
#define WINDOW_HEIGHT 1000
#define PI 3.1415926
using namespace std;

//ɨ�����㷨��
/*
ET
ymax���ߵ��϶˵��y����ֵ
x���ߵ��¶˵��x����
dmax���ߵ�б�ʵĵ���

AET��
ymax�������ߵ����yֵ
x����ǰɨ������ߵĽ����x����
dmax���ߵ�б�ʵĵ���
*/

typedef struct Edge
{ 
   int ymax;          
   float deltax;         
   float x;      
   struct Edge *next;
}Edge,*ptrtoEdge;

typedef struct edge      //��������м�¼�ı�
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
	 int ylow;            //�߶��¶˵��yֵ
	 Edge *next;          //ָ��ָ��Edge�ڵ�
 }EThead;

 typedef struct temppoint
 {
	 double x;
	 double y;
 }temppoint,*ptrtotemppoint;
 double alpha;
 int k;                 //�������
 POINT *p;
 bool select=false;
 EThead head[50];       //�������Ϊ50
 int headlen;
 edge *pe;             //�ߣ�������ƽ�бߣ�
 int pelen;            //�ߣ�������ƽ�бߣ�����Ŀ
 ptrtoEdge AEL;        //ael��ͷ

/*POINT changetonew(double x,double y,double alpha) //����׼����ת��Ϊ��б����
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
temppoint changetonew(double x,double y,double alpha) //����׼����ת��Ϊ��б����
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
/*POINT changetoori(double x,double y,double alpha) //����б����ת��Ϊ��׼����
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

temppoint changetoori(double x,double y,double alpha) //����б����ת��Ϊ��׼����
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
//���ܣ��ж�AEL��ͷ�Ƿ�Ϊ��
//���أ��� false�� �ǿ� true

//void createET(EThead head[],POINT *new_p,int k);   
void createET(EThead head[],temppoint *new_p,int k);    
//���ܣ�����ET�ṹ��
//������head, new_p������������ϵ�µ����꣬k�������Ŀ
//���أ�head����ṹ��

void print();
//���ܣ����Ӱ��

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
	if(select==true)              //������k����
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
				if(new_p[i].y!=new_p[i-1].y)      //����ƽ�бߣ�����pe����
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
				if(new_p[i].y!=new_p[0].y)      //����ƽ�бߣ�����pe����
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
void myMouse(int button, int state,int x,int y)  //�����Ʋ��֣�ͨ���������¼��
{
  static int number=0;
  
	if(state==GLUT_DOWN)
  {
	  if(button==GLUT_LEFT_BUTTON)
	  {
		  p[number].x=x;
	      p[number].y=480-y;
		                     //��׼����ϵ������

		  glBegin(GL_POINTS);
	      glVertex2i(x,480-y);
          glEnd();          //������ʾ��board��

		  glFlush();
		 // POINT b;
		  temppoint b;
		  b=changetonew(p[number].x,p[number].y,alpha);
		  cout<<"ԭʼ����Ϊ��"<<p[number].x<<" "<<p[number].y<<endl;
		  cout<<"ת��������Ϊ��"<<b.x<<"  "<<b.y<<endl;
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
    cout<<"���������"<<endl;
	cin>>k;
	pe=new edge[k+1];
	pelen=0;
	headlen=0;
	AEL=new Edge;
	AEL->next=NULL;
	AEL->x=-1<<30;
	cout<<"������Ӱ�߽Ƕ�"<<endl;
	cin>>alpha;
	alpha=alpha*PI/180.0;
	p=(POINT*)malloc(k*sizeof(POINT));
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("����ͼ��Ӱ��������");
	glutMouseFunc(myMouse);
    glutDisplayFunc(myDisplay);
	myInit();
    glutMainLoop();
    return 0;
}

//void createET(EThead head[],POINT *new_p,int k)
void createET(EThead head[],temppoint *new_p,int k)
{
	//���¶˵�yֵ˳���ظ�����
	int pecount=0;        //��¼����pe����Ԫ�صĸ���
	int flag[50];         //��¼ֵ�Ƿ񱻷��ʹ�
	for(int i=0;i<50;i++)
	{
		flag[i]=0;
	}
	int mini=0;
	int min=10000;
	while(pecount<pelen) //������ĿС�ڼ�¼����
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
		for(int i=0;i<pelen;i++)   //���������ҵ���ylow��ͬ�Ľڵ�Ҳ��Ϊ����״̬
		{
			if(flag[i]==0 && pe[i].lowy==min)
			{
				pecount++;
				flag[i]=1;
			}
		}
		min=10000;
	} //while(pecount<pelen)
	//����ET�ṹ��
	for(int i=0;i<headlen;i++)
	{
		for(int j=0;j<pelen;j++)           
		{
			if(head[i].ylow==pe[j].lowy)        //��pe[j]�Ĳ����ڵ���뵽head[i]��
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
	//��head��ҽڵ㰴��xֵ˳������
	for(int i=0;i<headlen;i++)
	{
		if(head[i].next->next!=NULL)
		//��ֻ��һ���ڵ�
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
	//ptrtoEdge tail=AEL;        //tailָ��AELβ�ڵ�
	int smx=head[0].ylow;      //smx����Ϊͼ����͵�yֵ
	int db=0;
	//cout<<"smx="<<smx<<endl;
	int count=0;               //����head[]��¼�����Ϊheadlen
	while(isnull()==true || count<headlen)
	{

		if(smx==head[count].ylow) 

		//ɨ�����뵱ǰ�߶��¶˵�yֵ��ȣ���head����������AEL
		//�����˳��Ϊx˳������
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
		
		//��ymax<=smx�Ľڵ�ɾ��
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
		if(isnull()==false)   //Ϊ��
		{
			break;
		}

		//����ת����ͶӰ
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
		//���½ڵ��smx
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