#include <iostream>
struct Pos
{
        int X;
        int Y;
};
struct Elem
{
        Pos seat;
        int direct;
        int ord;
};
typedef Elem ElemType ;
class Stack
{
private:
    ElemType*Base,*Top;
        int Size;
        int INIT_SIZE;
public:
        Stack()
        {
                 INIT_SIZE = 3;
                 Base = new ElemType[INIT_SIZE];
                 Top = Base;
                 Size = INIT_SIZE;
        }
        bool Push(ElemType date)
        {
                if(Top-Base>=Size)
                {
                        ElemType *Temp = new ElemType[Size + INIT_SIZE];
                        memcpy(Temp,Base,Size * sizeof(ElemType));
                        delete []Base;
                        Base = Temp;
                        Top = Base + Size;
                        Size += INIT_SIZE;
                }
                *Top++ = date;
                return true;
        }
        bool Pop(ElemType &date)
        {
                if(Base == Top) return false;
                date = *--Top;
                return  true;
        }
        bool StackEmp() //ջ�շ���true
        {
                return Base==Top?true:false;
        }
};

#define H 7 //��
#define L 7 //��
class Meth
{
private:
        int Map[H][L]; //1��ͨ�� 0����ͨ�� 3�Ѿ��߹� //������100
        Stack stack;
public:
        Meth()
        {
                 
        }
        // ���к���֮�����Ϊ
        void setMap(const int *p,int  hang,int lie)
        {
                size_t size =  hang * lie;
                //���Ƶ�ͼ
                memcpy(Map,p,sizeof(int)*size);
        }
        //���յ�
        void find(Pos start,Pos End)
        {
                
                Elem ed;
                ed.seat = start;
                ed.ord = 1;
                ed.direct = 1;
                Pos cur = start;//��ǰλ��
                do
                {
                        //��ǰλ�ÿ�ͨ��
                        if(Pass(cur))
                        {
                                if(cur.X == End.X && cur.Y == End.Y) return ;
                                ed.seat = cur;
                                ed.direct=1;
                                ed.ord++;
                                stack.Push(ed);
                                cur = Next(cur,1);
                        }
                        else{
                                if(!stack.StackEmp()) stack.Pop(ed);
                                while(ed.direct==4 && !stack.StackEmp()) stack.Pop(ed);
                                if(ed.direct<4)
                                {
                                        ed.direct++;
                                        stack.Push(ed);
                                        cur = Next(ed.seat,ed.direct);
                                }

                                //��ǰλ�ò���ͨ�� ���������߲���¼
                        }
                } while (!stack.StackEmp());
        }
        bool Pass(Pos pos)
        {
                 
                 
                int k = Map[pos.X][pos.Y];
                if(k==1){
                        Map[pos.X][pos.Y] = 3;//����߹�
                        return true;
                }
                 Map[pos.X][pos.Y] = 3;//����߹�
                  return false;
        }
        Pos Next(Pos pos,int re)
        {
                switch (re)
                {
                case 1:  //��
                        pos.Y++;
                        return pos;
                        break;
                case 2: //��
                        pos.X++;
                        return pos;
                        break;
                case 3: //��
                        pos.Y--;
                        return pos;
                        break;
                case 4://��
                        pos.X--;
                        return pos;
                        break;
                
                }

        }

        //��ӡ��·��
        void foot()
        {
                while(!stack.StackEmp())
                {
                        Elem kl;
                        stack.Pop(kl);
                        std::cout<<kl.seat.X<<","<<kl.seat.Y<<std::endl;
                }
        }
        //��ӡ��ͼ
        void printMap()
        {
                for (int i = 0; i < H; i++)
                {
                        for (int k = 0; k < L; k++)
                        {
                                std::cout<<Map[i][k]<<" ";
                        }
                        std::cout<<std::endl;
                }
        }
};

int main(void)
{
        Stack A;
        Meth meth;


        //��ͼ
        int Map[8][7] = {1,0,1,0,0,1,1,
                                                        1,1,0,0,0,0,1,
                                                        0,1,1,1,0,0,0,
                                                        1,1,0,1,1,1,0,
                                                        1,1,0,0,1,1,1,
                                                        0,1,0,1,0,1,0,
                                                        0,1,0,1,1,1,1,
                                                        };
        
        std::cout<<"�Թ���ͼΪ:"<<std::endl;
        meth.setMap((const int*)Map,H,L);
        meth.printMap();
        Pos start,End;
        start.X = 0;
        start.Y = 0;

        //�յ�λ��
        End.X = 4;
        End.Y = 6;
        std::cout<<"·��(�յ㵽���)"<<std::endl;
        meth.find(start,End);
        meth.foot();

        return 0;
}