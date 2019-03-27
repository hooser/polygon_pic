# polygon_pic
在程序的画板上将你点击形成的点连接成多边形，并且按照你所给的角度，给多边形填充投影线
运行此程序之前需要正确的安装配置open_gl. 
程序设计参考了扫描线算法，并对该算法进行了改进，程序运行结果较为理想，部分思路展示如下：

1、坐标转换：
为了能够使用任意角度的影线填充，所以要有坐标转换。定义标准坐标系为，以界面左下角为原点，
正右方向为x正方向；正上方向为y正方向。转移坐标系为，以界面左下角为原点，影线向右方向为x正
方向，垂直影线向上方向为y正方向。

2、扫描线算法：
   经过上述变换就得到了图形在以影线方向为x轴的坐标系的坐标，接
下来选择平行投影线的线为扫描线与图形相交。并且将两端的交点转换
   至标准坐标系，从而得到一条投影线。这里需要使用两个数据结构来
协助完成。ET结构体和AEL结构体，其中ET结构体与书上介绍的略有
不同。书上是以最低点y值为数组序号，但是本程序中，坐标变换后的
y值往往可能是负值，所以这里的ET结构体数组部分定义如下：
typedef struct EThead
 {
	 int ylow;            //线段下端点的y值
	 Edge *next;          //指针指向Edge节点
 }EThead;

在本程序中，ET数组是一个“紧致”的数组结构，即：从EThead[0]到
最后一个元素中间没有为空的情况。ET后的节点是相同最低点的一系列
边的参数。这些节点在插入后会对其进行排序，按照x值从小到大排列，
在将节点插入AEL中时就可以保证AEL的顺序排列。
定义smx变量，初值为最小y值。然后以下循环至ET和AEL都空
One：如果smx==ET表头的值则将该表头后的链表插入到AEL。插入的过
程为：两个指针f、r，保持f在r前一位。

If(f不为空 && f->data > ET第一个节点data) 
f=f->next;

  只需要将r指向ET链表，ET链表末端指向f即可完成插入操作。将smx
与图形的交点坐标经过坐标转换后的点坐标送到打印函数打印出该条扫
描线。
Two：如果smx>该边较高端点的y值，则在AEL中将该节点删除
Three：将AEL中每个节点的x值加上deltax，smx++

3、总体思路：

  a、鼠标在界面上点击k个点，mymouse函数记录点在标准坐标系的坐标
值。New_P数组记录相应点在转换坐标系上的坐标值。

b、edge结构体数组pe记录转换后的k个边（与投影线方向平行的边不
记录）的情况

typedef struct edge      
{
	int highy;
	int lowy;
	int lowx;
	float deltax;
}edge；
包括：边较高的端点的y值；较低端点的x、y值；斜率的倒数。
记录方式为：定义一个count，初值为0。每进一个点，count++，若count==2，
则将pe[i]、pe[i+1]生成一条边。最后将pe[k-1]、pe[0]生成一条边。

c、建立ET结构体：
 将pe数组中的lowy按照从小到大不重复排列，并且插入到ET的数组部分（EThead）,设为EThead[0~n]。


d、扫描线算法填充图形
先将原图形打印。再按照2中的扫描线算法，结合ET结构体和AEL链表进行扫描。只要ET和AEL不为空就持续进行。

展示如下：

case1(三十边形)：

![ooops!!!](https://github.com/hooser/polygon_pic/blob/master/images/case1.png)

![ooops!!!](https://github.com/hooser/polygon_pic/blob/master/images/example1.png)

case2(二十边形)：

![ooops!!!](https://github.com/hooser/polygon_pic/blob/master/images/case2.png)

![ooops!!!](https://github.com/hooser/polygon_pic/blob/master/images/example2.png)

case3(五边形)：

![ooops!!!](https://github.com/hooser/polygon_pic/blob/master/images/case3.png)

![ooops!!!](https://github.com/hooser/polygon_pic/blob/master/images/example3.png)




