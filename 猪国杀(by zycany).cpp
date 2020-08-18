/*
P2482 ���ɱ
����˼·:
ģ��
�ַ�������
Ϊ�˽�ʡʱ��,����˫��������(��д) 
�˴�����zycany��ͬ��� 
*/
#include <bits/stdc++.h>
using namespace std;
#define N 15
#define M 2005
#define END 30 //����β�� 
string str;
struct Player
{
	string cards;//���� 
	int ch;//�������(0δ֪1��2��) 
	string id;//ʵ�����
	bool lfz;//�Ƿ����෴�� 
	int next;
	int pre;//ǰ������ 
	bool Ktimes;//�ڱ������Ƿ�ʹ��"ɱ" 
	bool alive;//�Ƿ񻹻���(1��0��) 
	int hp;//���� 
	bool Z;//�Ƿ���������� 
	bool mp;//�ɱ�(����1����0) 
}p[N+END];
int n,m,fp;
void dead(int killer,int x) //���˴��� 
{
	p[x].alive = false;//��Ϊ������ 
	p[p[x].pre].next = p[x].next;
	p[p[x].next].pre = p[x].pre;//���������˫�������� 
	if(p[x].id == "FP")  
	{//����Ƿ�������,��ô����������һ,����ɱ������������
		--fp;
		p[killer].cards+=str[0]+str[1]+str[2];
		str.erase(0,3);
	} 
	else if(killer==1) p[1].cards.clear();
	//����������˶���������ɱ����ô���������� 
}
void drop(int killer,int x)//��һ������
{
	int pos; 
	--p[x].hp;//��һ������ 
	if(!p[x].hp)//���"����" 
	{
		pos=p[x].cards.find('P');
		if(pos!=p[x].cards.npos)
		{
			p[x].cards.erase(pos,1);
			p[x].hp = 1;//������Ҿ͸���
		}
		else
			dead(killer,x);
	}
} 
int J(int a,int b) //a��b������и�ɻ� 
{
	int pos=p[a].cards.find('J');
	if(pos!=p[a].cards.npos) 
	{
		p[a].cards.erase(pos,1);
		return J(b,a);
	}
	else return b;
	//����ֵ��˭"Ӯ��"
}
void NW(int j,char ch)
{
	/*
		�������ֻ�����뷢
		killer��ʾʹ����,ch��ʾ��ʲô�ƿ��Ե���(ɱ����) 
	*/ 
	int pos;
	for(int k=p[j].next;k!=j;k=p[k].next)//����ѭ������ 
	{
		if(k==END) continue;
		if(J(k,j)==k) continue;//��и�ɻ� 
		pos=p[k].cards.find(ch);
		if(pos!=p[k].cards.npos)
			p[k].cards.erase(pos,1); //������Ե���������
		else
		{
			drop(j,k);
			if(k==1&&!p[j].ch)
				p[j].lfz=true;
			//�����������û�������,��Ϊ�෴�� 
		}
	}
} 
int find(int x)
{//Ѱ�ұ����Ķ��� 
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
{//ɱ
	int goal = p[x].next;
	if(goal == END) goal = p[END].next;
	if(p[x].mp != p[goal].mp)//����ͬһ���ɱ��ɱ 
	{
		int pos = p[goal].cards.find('D');
		if(pos == p[goal].cards.npos)
			drop(x,goal);
		return true;
	}
	return false; 
} 
bool F(int x)
{//x�������(0Ӯ��2����)
	int goal = find(x); 
	if(goal == -1)
		return false;//û��ɱ���� 
	if(J(goal,x)==goal) return false;
	//����и�ɻ������� 
	if(x == 1 && p[goal].id == "ZP")
	{//�������Ŀ����������ô����ֱ�ӵ�1Ѫ 
		drop(x,goal);
		return true;
	}
	if(p[x].id == "FP") {p[x].ch = 1;p[x].lfz=false;}
	else {p[x].ch=2;p[x].lfz=false;}
	//����or����,ȡ���෴�� 
	int px = p[x].cards.find('K');
	int py = p[goal].cards.find('K');
	while(px != p[x].cards.npos && py != p[goal].cards.npos)
	{//ֻҪ����ɱ�ͼ��� 
		p[x].cards.erase(px,1);
		p[goal].cards.erase(py,1);
		//������ɱ 
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
	//ֻҪ�������Ŷ��Ҵ��ڷ���(��Ϸ��δ����)
	{
//		printf("Round %d:\n",++rnd);
//		if(rnd >= 5) return true;
		for(int i = p[END].next;i != END;i = p[i].next) 
		//����+���� 
		{
//			printf("Player %d:\n%d %d\n",i,p[i].pre,p[i].next);
			if(!p[i].alive) 
				continue; 
			//������������
			p[i].cards = p[i].cards+str.substr(0,2);
//			cout<<"Cards:"<<p[i].cards<<" "<<str.substr(0,2)<<endl;
			str.erase(0,2); 
			//���� 
//			cout << "Cards:" << p[i].cards << endl;
			len = p[i].cards.length();
			for(int j = 0;j < len;++ j)
			{
				if(p[i].cards[j] == 'P' && p[i].hp < 4)
				//�� 
					++p[i].hp,p[i].cards.erase(j,1),--j,--len; 
				else if(p[i].cards[j] == 'Z')
				//������� 
				{
					p[i].Z = true;
					p[i].cards.erase(j,1);
					--j,--len; 
				}
				else if(p[i].cards[j] == 'K')//ɱ 
				{ 
					if(!p[i].Z && p[i].Ktimes)
						continue;
					//���û�����������Ѿ��ù�"ɱ"�˾����� 
					if(K(i))
					{
						p[i].cards.erase(j,1);
						--j,--len;
						//��������� 
						p[i].Ktimes = true;
					}
					if(!p[1].alive)
						return false;
					if(!fp)
						return true;					
				}
				else if(p[i].cards[j] == 'N')//�������� 
				{ 
					NW(i,'K') ;
					p[i].cards.erase(j,1);//������ſ� 
					--j,--len;
					if(!p[1].alive)
						return false;
					if(!fp)
						return true;
				} 
				else if(p[i].cards[j] == 'W')
				{ 
					NW(i,'D');
					p[i].cards.erase(j,1);//������ſ� 
					--j,--len;
					if(!p[1].alive)
						return false;
					if(!fp)
						return true;
				} 
				else if(p[i].cards[j] == 'F')//����
				{
					if(F(i)) 
						str.erase(j,1),--j,--len; 
					if(!p[1].alive)
						return false;
					if(!fp)
						return true;
				}
				else if(p[i].cards[j] == 'J')//��и�ɻ�
				{
					continue;
				} 
			}
			p[i].Ktimes = false;
		}
	}
	if(p[1].alive) return true;
	return false; 			//��� 
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
		p[i].hp = 4; //��ʼ�������Ϣ 
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
	}			//����������� 
	p[1].ch = 1;
	p[1].pre = p[n].next = END; 
	p[END].pre = n,p[END].next = 1;
	for(int i = 1;i <= m;++ i)
	{
		getchar();
		ch = getchar();
		str = str+ch;
	}
	bool win = playgame(); // ����Ϸ 
	printf("%s\n",win ? "MP" : "FP");
	for(int i = 1;i <= n;++ i)
	{
		if(!p[i].alive) {puts("DEAD");continue;}//���� 
		int len = p[i].cards.length();
		for(int j = 0;j < len;++ j) 
			putchar(p[i].cards[j]),putchar(' ');
		putchar('\n');
	}
	return 0;
}
/*
����: 
3 10
MP D D F F
ZP N N N D
FP J J J J
F F D D J J F F K D
*/

