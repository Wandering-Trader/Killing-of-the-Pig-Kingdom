/*
'P': 1; ��Ѫ��
'K': 2; ����ɱ
'D': 3; ������
'F': 4; ���������˺�����
'N': 5; ��������1ɱ����1Ѫ��������
'W': 6; ��������1������1Ѫ����뷢
'J': 7; ��֪����ɶ��и�ɻ�
'Z': 8; ���������������
*/
//��� P2482 ���ɱ
//������ģ�⣡����
#include <bits/stdc++.h>
struct player{
    int kind;//�������
    char card[10050]={0};int end=4;//��
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
bool wxkj(int a,int b,int went)//��и�ɻ�
{
    int piga,pigb;
    piga=a;
    pigb=went?b:a;
    for(;true;)
    {
        if(went==1)
        {
            if(zps[b]==pig[piga].kind || (zps[b]==1 && pig[piga].kind==1) )//�ж�
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
    for(int pigb=pig[piga].next;pigb!=piga;pigb=pig[pigb].next)//����һ��һֱִ��
    {
        if(!wxkj(piga,pigb,1))//��и�ɻ�����Ч
        {
            bool find=false;
            for(int i=0;i<pig[pigb].end;i++)//��ɱ
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
                if(pigb==1&&zps[piga]==-1)//���������
                {
                    //�����
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
    for(int pigb=pig[piga].next;pigb!=piga;pigb=pig[pigb].next)//����һ��һֱִ��
    {
        if(!wxkj(piga,pigb,1))//��и�ɻ�����Ч
        {
            bool find=false;
            for(int i=0;i<pig[pigb].end;i++)//��ɱ
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
                if(pigb==1&&zps[piga]==-1)//���������
                {
                    //�����
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
void deadkill(int piga,int pigb)//����
{
    if(wxkj(piga,pigb,1))return;//��и�ɻ��ɵ�
    if(pig[piga].id==1&&pig[pigb].id==2)//������
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
    //������ɱ
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
            if(pig[i].card[j]==0)//��������
            {
                
            }
            if(pig[i].card[j]==1)//��
            {
                if(pig[i].hp<4){
                    pig[i].hp++;
                    pig[i].card[j]=0;
                }
                else{
                    continur;
                }
            }
            if(pig[i].card[j]==2)//ɱ
            {
                if(usek==false||pig[i].zgln==true)
                {
                    //�������ң���������
                    if(pig[i].kind==2&&zps[pig[i].next]!=3)//���¼�
                    {
                        continue;
                    }
                    if(pig[i].kind==3&&zps[pig[i].next]!=2&&zps[pig[i].next]!=1)
                }
            }
            if(pig[i].card[j]==4)//����
            { 
            }
            if(pig[i].card[j]==5)//��������
            {
                pig[i].card[j]=0;
                nzrq(i);
            }
            if(pig[i].card[j]==6)//����뷢
            {
                pig[i].card[j]=0;
                wjqf(i);
            }
            if(pig[i].card[j]==8)//�������
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
