/*
'P': 1; 加血桃
'K': 2; 攻击杀
'D': 3; 防御闪
'F': 4; 单个猪互相伤害决斗
'N': 5; 除非弃置1杀否则1血南猪入侵
'W': 6; 除非弃置1闪否则1血万箭齐发
'J': 7; 不知道干啥无懈可击
'Z': 8; 连续攻击猪哥连弩
*/
//洛谷 P2482 猪国杀
//毒瘤大模拟！！！
#include <bits/stdc++.h>
struct player{
    int kind;//猪的类型
    char card[10050]={0};int end=4;//牌
    int hp=4;
    bool zgln=false;
    int next,last;
}pig[100];
int zps[100],card[10000],qwq[100];
int pignum,cardnum,fzcnt;
bool ended=false;
void getcard(int pigc)
{
    cardnum--;
    pig[pigc].end++;
    pig[pigc].card[pig[pigc].end]=card[cardnum];
    return;
}
void clear(int pigc)
{
    memset(pig[pigc].card,0,sizeof(pig[pigc].card));
    pig[pigc].zgln=false;
}
void kill(int piga,int pigb)
{
    bool deaded=true;
    for(int i=0;i<pig[pigb].end;i++)
    {
        if(pig[pigb].card[i]==1)
        {
            deaded=false;
            pig[pigb].hp++;
            pig[pigb].card[i]=0;
            return;
        }
    }
    if(deaded)
    {
        pig[pigb].hp=-1;
        clear(pigb);
        pig[pig[pigb].next].last=pig[pigb].last;
        pig[pig[pigb].last].next=pig[pigb].next;
        if(pig[pigb].kind==1)
        {
            ended=true;
            return;
        }
        if(pig[pigb].kind==3)
        {
            fzcnt--;
            getcard(piga);
            getcard(piga);
            getcard(piga);
            if(fzcnt<=0)
            {
                ended=true;
                return;
            }
            
        }
        if(pig[piga].kind==1&&pig[pigb].kind==2)
        {
            //mp kill zp
            clear(piga);
        }
    }
    return;
}
void hurt(int piga,int pigb)
{
    for(int i=0;i<pig[pigb].end;i++)
    {
        if(pig[pigb].card[i]==3)
        {
            pig[pigb].card[i]=0;
            return;
        }
        if(pig[pigb].card[i]==1&&pig[pigb].hp!=4)
        {
            pig[pigb].card[i]=0;
            pig[pigb].hp++;
        }
    }
    pig[pigb].hp--;
    if(pig[pigb].hp<=0)
    {
        kill(piga,pigb);
    }
    return;
}
bool wxkj(int a,int b,int went)//无懈可击
{
    int piga,pigb;
    piga=a;
    pigb=went?b:a;
    for(;true;)
    {
        if(went==1)
        {
            if(zps[b]==pig[piga].kind || (zps[b]==1 && pig[piga].kind==1) )//敌对
            {
                for(int i=0;i<pig[piga].end;i++)
                {
                    if(pig[piga].card[i]==7)
                    {
                        pig[piga].card[i]=0;
                        zps[piga]=pig[piga].kind;
                    }
                }
            }
        }
        else
        {
            if(zps[b]==pig[piga].kind && zps[b]!=pig[pigb].kind )
            {
                return true;
            }
        }
    }
    return false;
}
void nzrq(int piga)
{
    for(int pigb=pig[piga].next;pigb!=piga;pigb=pig[pigb].next)//从下一家一直执行
    {
        if(!wxkj(piga,pigb,1))//无懈可击不生效
        {
            bool find=false;
            for(int i=0;i<pig[pigb].end;i++)//搜杀
            {
                if(pig[pigb].card[i]==2)
                {
                    find=true;
                    pig[pigb].card[i]=0;
                    break;
                }
            }
            if(!find)
            {
                pig[pigb].hp--;
                if(pigb==1&&zps[piga]==-1)//如果是主猪
                {
                    //表敌意
                    zps[pigb]=1;
                }
                if(pig[pigb].hp<=0)
                {
                    kill(piga,pigb);
                }
                if(ended)return;
            }
        }
    }
    return;
}

xiaozeng 22:24:31

void wjqf(int piga)
{
    for(int pigb=pig[piga].next;pigb!=piga;pigb=pig[pigb].next)//从下一家一直执行
    {
        if(!wxkj(piga,pigb,1))//无懈可击不生效
        {
            bool find=false;
            for(int i=0;i<pig[pigb].end;i++)//搜杀
            {
                if(pig[pigb].card[i]==3)
                {
                    find=true;
                    pig[pigb].card[i]=0;
                    break;
                }
            }
            if(!find)
            {
                pig[pigb].hp--;
                if(pigb==1&&zps[piga]==-1)//如果是主猪
                {
                    //表敌意
                    zps[pigb]=1;
                }
                if(pig[pigb].hp<=0)
                {
                    kill(piga,pigb);
                }
                if(ended)return;
            }
        }
    }
    return;
}
void deadkill(int piga,int pigb)//决斗
{
    if(wxkj(piga,pigb,1))return;//无懈可击干掉
    if(pig[piga].id==1&&pig[pigb].id==2)//主打忠
    {
        pig[pigb].hp--;
        if(pig[pigb].hp<=0)kill(piga,pigb);
        return;
    }
    int a,b;
    for(int i=0;i<pig[piga].end;i++)
    {
        if(pig[piga].card[i]==2)a++;
    }
    for(int i=0;i<pig[pigb].end;i++)
    {
        if(pig[pigb].card[i]==2)b++;
    }
    //搜两边杀
    if(a>b)
    {
        pig[pigb].hp--;
        int num=b;
        for(int i=0;num+1>=0;i++)
        {
            if(pig[piga].card[i]==2)
            {
                num--;
                pig[piga].card[i]=0;
            }
        }
        for(int i=0;num>=0;i++)
        {
            if(pig[pigb].card[i]==2)
            {
                num--;
                pig[pigb].card[i]=0;
            }
        }
        if(pig[pigb].hp<=0)kill(piga,pigb);
    }
    else
    {
        pig[piga].hp--;
        for(int i=0;num>=0;i++)
        {
            if(pig[piga].card[i]==2)
            {
                num--;
                pig[piga].card[i]=0;
            }
        }
        for(int i=0;num+1>=0;i++)
        {
            if(pig[pigb].card[i]==2)
            {
                num--;
                pig[pigb].card[i]=0;
            }
        }
        if(pig[piga].hp<=0)kill(pigb,piga);
    }
    if(fzcnt<=0)
    {
        ended=true;
        return;
    }
    return;
}
void roundn()
{
    char ch;
    if(fzcnt<=0)
    {
        ended=true;
        return;
    }
    for(int i=1;i!=0;i=a[i].next){
        getcard(i);getcard(i);
        bool usek=false;
        for(int j=0;j<pig[i].end;j++)
        {
            if(pig[i].card[j]==0)//卡牌弃置
            {
                
            }
            if(pig[i].card[j]==1)//桃
            {
                if(pig[i].hp<4){
                    pig[i].hp++;
                    pig[i].card[j]=0;
                }
                else{
                    continur;
                }
            }
            if(pig[i].card[j]==2)//杀
            {
                if(usek==false||pig[i].zgln==true)
                {
                    //反找跳忠，忠找跳反
                    if(pig[i].kind==2&&zps[pig[i].next]!=3)//找下家
                    {
                        continue;
                    }
                    if(pig[i].kind==3&&zps[pig[i].next]!=2&&zps[pig[i].next]!=1)
                }
            }
            if(pig[i].card[j]==4)//决斗
            { 
            }
            if(pig[i].card[j]==5)//南猪入侵
            {
                pig[i].card[j]=0;
                nzrq(i);
            }
            if(pig[i].card[j]==6)//万箭齐发
            {
                pig[i].card[j]=0;
                wjqf(i);
            }
            if(pig[i].card[j]==8)//诸葛连弩
            {
                pig[i].card[j]=0;
                pig[i].zgln=true;
            }
        }
    }
}
int main()
{
    return 0;
}
