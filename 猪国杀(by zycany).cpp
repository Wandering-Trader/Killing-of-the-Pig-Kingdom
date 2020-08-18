/*
P2482 猪国杀
基本思路:
模拟
字符串处理
为了节省时间,采用双向环形链表(手写) 
此代码由zycany共同完成 
*/
#include <bits/stdc++.h>
using namespace std;
#define N 15
#define M 2005
#define END 30 //链表尾部 
string str;
struct Player
{
	string cards;//卡牌 
	int ch;//对外身份(0未知1忠2反) 
	string id;//实际身份
	bool lfz;//是否是类反猪 
	int next;
	int pre;//前后的玩家 
	bool Ktimes;//在本轮中是否使用"杀" 
	bool alive;//是否还活着(1活0死) 
	int hp;//体力 
	bool Z;//是否有猪哥连弩 
	bool mp;//派别(主猪1反猪0) 
}p[N+END];
int n,m,fp;
void dead(int killer,int x) //死人处理 
{
	p[x].alive = false;//设为已死亡 
	p[p[x].pre].next = p[x].next;
	p[p[x].next].pre = p[x].pre;//死亡后更新双向环形链表 
	if(p[x].id == "FP")  
	{//如果是反猪死了,那么反猪数量减一,而且杀人者摸三张牌
		--fp;
		p[killer].cards+=str[0]+str[1]+str[2];
		str.erase(0,3);
	} 
	else if(killer==1) p[1].cards.clear();
	//如果忠猪死了而且是主猪杀的那么主猪的牌清空 
}
void drop(int killer,int x)//掉一点生命
{
	int pos; 
	--p[x].hp;//掉一点体力 
	if(!p[x].hp)//如果"死了" 
	{
		pos=p[x].cards.find('P');
		if(pos!=p[x].cards.npos)
		{
			p[x].cards.erase(pos,1);
			p[x].hp = 1;//如果有桃就复活
		}
		else
			dead(killer,x);
	}
} 
int J(int a,int b) //a向b发动无懈可击 
{
	int pos=p[a].cards.find('J');
	if(pos!=p[a].cards.npos) 
	{
		p[a].cards.erase(pos,1);
		return J(b,a);
	}
	else return b;
	//返回值是谁"赢了"
}
void NW(int j,char ch)
{
	/*
		南猪入侵或万箭齐发
		killer表示使用者,ch表示用什么牌可以抵消(杀或闪) 
	*/ 
	int pos;
	for(int k=p[j].next;k!=j;k=p[k].next)//遍历循环链表 
	{
		if(k==END) continue;
		if(J(k,j)==k) continue;//无懈可击 
		pos=p[k].cards.find(ch);
		if(pos!=p[k].cards.npos)
			p[k].cards.erase(pos,1); //如果可以抵消就跳过
		else
		{
			drop(j,k);
			if(k==1&&!p[j].ch)
				p[j].lfz=true;
			//如果打到主猪且没标明身份,设为类反猪 
		}
	}
} 
int find(int x)
{//寻找表敌意的对象 
	if(p[x].id == "FP")
		return 1;
	for(int i = p[x].next;i != x;i = p[i].next)
	{
		if(i == END) continue; 
		if(p[i].ch == 2)
			return i;
		else if(x == 1 && p[i].lfz)
			return i;
	} 
	return -1;
}
bool K(int x)
{//杀
	int goal = p[x].next;
	if(goal == END) goal = p[END].next;
	if(p[x].mp != p[goal].mp)//不在同一个派别就杀 
	{
		int pos = p[goal].cards.find('D');
		if(pos == p[goal].cards.npos)
			drop(x,goal);
		return true;
	}
	return false; 
} 
bool F(int x)
{//x发起决斗(0赢了2输了)
	int goal = find(x); 
	if(goal == -1)
		return false;//没有杀到人 
	if(J(goal,x)==goal) return false;
	//被无懈可击抵消了 
	if(x == 1 && p[goal].id == "ZP")
	{//如果主猪目标是忠猪那么忠猪直接掉1血 
		drop(x,goal);
		return true;
	}
	if(p[x].id == "FP") {p[x].ch = 1;p[x].lfz=false;}
	else {p[x].ch=2;p[x].lfz=false;}
	//跳忠or跳反,取消类反猪 
	int px = p[x].cards.find('K');
	int py = p[goal].cards.find('K');
	while(px != p[x].cards.npos && py != p[goal].cards.npos)
	{//只要都有杀就继续 
		p[x].cards.erase(px,1);
		p[goal].cards.erase(py,1);
		//互相扔杀 
	}
	if(py == p[goal].cards.npos)
		drop(x,goal);
	else drop(goal,x);
	return true; 
}
bool playgame()
{
	int temp,len,rnd = 0;
	while(p[1].alive && fp) 
	//只要主猪还活着而且存在反猪(游戏尚未结束)
	{
//		printf("Round %d:\n",++rnd);
//		if(rnd >= 5) return true;
		for(int i = p[END].next;i != END;i = p[i].next) 
		//摸牌+出牌 
		{
//			printf("Player %d:\n%d %d\n",i,p[i].pre,p[i].next);
			if(!p[i].alive) 
				continue; 
			//已死亡就跳过
			p[i].cards = p[i].cards+str.substr(0,2);
//			cout<<"Cards:"<<p[i].cards<<" "<<str.substr(0,2)<<endl;
			str.erase(0,2); 
			//摸牌 
//			cout << "Cards:" << p[i].cards << endl;
			len = p[i].cards.length();
			for(int j = 0;j < len;++ j)
			{
				if(p[i].cards[j] == 'P' && p[i].hp < 4)
				//桃 
					++p[i].hp,p[i].cards.erase(j,1),--j,--len; 
				else if(p[i].cards[j] == 'Z')
				//猪哥连弩 
				{
					p[i].Z = true;
					p[i].cards.erase(j,1);
					--j,--len; 
				}
				else if(p[i].cards[j] == 'K')//杀 
				{ 
					if(!p[i].Z && p[i].Ktimes)
						continue;
					//如果没有武器而且已经用过"杀"了就跳过 
					if(K(i))
					{
						p[i].cards.erase(j,1);
						--j,--len;
						//清除这张牌 
						p[i].Ktimes = true;
					}
					if(!p[1].alive)
						return false;
					if(!fp)
						return true;					
				}
				else if(p[i].cards[j] == 'N')//南猪入侵 
				{ 
					NW(i,'K') ;
					p[i].cards.erase(j,1);//清除这张卡 
					--j,--len;
					if(!p[1].alive)
						return false;
					if(!fp)
						return true;
				} 
				else if(p[i].cards[j] == 'W')
				{ 
					NW(i,'D');
					p[i].cards.erase(j,1);//清除这张卡 
					--j,--len;
					if(!p[1].alive)
						return false;
					if(!fp)
						return true;
				} 
				else if(p[i].cards[j] == 'F')//决斗
				{
					if(F(i)) 
						str.erase(j,1),--j,--len; 
					if(!p[1].alive)
						return false;
					if(!fp)
						return true;
				}
				else if(p[i].cards[j] == 'J')//无懈可击
				{
					continue;
				} 
			}
			p[i].Ktimes = false;
		}
	}
	if(p[1].alive) return true;
	return false; 			//结果 
}
int main()
{
	scanf("%d%d",&n,&m);
	char ch;
	for(int i = 1;i <= n;++ i)
		p[i].next = i+1,p[i].pre = i-1;
	for(int i = 1;i <= n;++ i){
		cin >> p[i].id;
		p[i].alive = 1;
		p[i].hp = 4; //初始化玩家信息 
		if(p[i].id == "FP") 
			++fp;
		else p[i].mp = 1;
		getchar();
		for(int j = 1;j <= 4;++ j)
		{
			ch = getchar();
			p[i].cards += ch;
			getchar();
		}
	}			//输入玩家手牌 
	p[1].ch = 1;
	p[1].pre = p[n].next = END; 
	p[END].pre = n,p[END].next = 1;
	for(int i = 1;i <= m;++ i)
	{
		getchar();
		ch = getchar();
		str = str+ch;
	}
	bool win = playgame(); // 玩游戏 
	printf("%s\n",win ? "MP" : "FP");
	for(int i = 1;i <= n;++ i)
	{
		if(!p[i].alive) {puts("DEAD");continue;}//死亡 
		int len = p[i].cards.length();
		for(int j = 0;j < len;++ j) 
			putchar(p[i].cards[j]),putchar(' ');
		putchar('\n');
	}
	return 0;
}
/*
样例: 
3 10
MP D D F F
ZP N N N D
FP J J J J
F F D D J J F F K D
*/

