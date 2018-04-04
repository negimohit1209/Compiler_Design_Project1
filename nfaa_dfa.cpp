#include<iostream>
#include<stdio.h>
#include<list>
#include<queue>
#include<vector>
#include<tuple>
#include<string>
#include<stdlib.h>
#include<algorithm>
using namespace std;

class nfa_dfa{
	int states;
	list<tuple<int , char> > *adj;
	list<int> *epsilon ;

	public:
		nfa_dfa(int states){
			this->states = states;
			adj = new list< tuple<int , char>>[states];
			epsilon = new list<int>[states];
		}
    void transitions(int i , int f, char ch)
    {
        adj[i].push_back(make_tuple(f,ch));
    }

    void print()
    {
        cout<<"The Transitions\n";
        int i;
        for(i=0;i<states;i++)
        {
            list<tuple<int,char>>::iterator it;
            for(it = adj[i].begin() ; it!=adj[i].end() ;++it)
                cout<<i<<" "<<get<1>(*it)<<" "<<get<0>(*it)<<"\n";
            cout<<endl;
        }
    }

    void epsilonClosure()
    {
        cout<<"---------------------------------------------------------------------------------------------------------";
        cout<<"\n\n\n\nEpsilon Closure for all the states:\n\n";
        for(int i=0;i<states;i++)
        {
            bool *visited = new bool[states];
            for(int i1 = 0; i1 < states ; i1++)
                visited[i1] = false;

            queue <int> q;
            visited[i] = true;
            q.push(i);

            while(!q.empty())
            {
                int first = q.front();
                q.pop();
                list<tuple<int,char>>::iterator it;
                for(it = adj[first].begin() ; it!=adj[first].end() ;++it)
                {
                    if(get<1>(*it) == 'e' && visited[get<0>(*it)] != true)
                    {
                        q.push(get<0>(*it));
                        visited[get<0>(*it)] = true;
                    }

                }

            }
            for(int j =0; j<states ;j++)
            {
                if(visited[j] == true)
                    epsilon[i].push_back(j);
            }
        }
    }

    void printepsilon()
    {
        int i;
        for(i=0;i<states;i++)
        {
            list<int>::iterator it;
            cout<<i<<"----";
            for(it = epsilon[i].begin() ; it!=epsilon[i].end() ;++it)
                cout<<*it<<" ";
            cout<<"\n";
        }
        cout<<"--------------------------------------------------------------------------------------------------------";

    }

    string arraytostring(list<int> &arr, int size_of_array) {
        string returnstring = "";
        list<int>::iterator it;
        for(it = arr.begin() ; it!=arr.end() ;++it)
            returnstring += to_string(*it);
        return returnstring;
    }


    void toDFA(int start)
    {
        cout<<"\nThe DFA for the above epsilon NFA\n";
        vector<string>vect;
        vector<bool> mybool(states);
        queue<string> que;
        list<int> closure;
        string str , stra , strb;
        int flag =0;
        str = arraytostring(epsilon[0] , epsilon[0].size());
        que.push(str);
        while(!que.empty())
        {
            string temp;
            temp = que.front();
            vector<int> aa;
            vector<int> bb;
            que.pop();

            for(int it = 0 ; it < temp.size() ; ++it)
            {

                int temp1 = temp[it] -48;
                list<tuple<int,char>>::iterator i;
                for(i= adj[temp1].begin() ; i!=adj[temp1].end() ;++i)
                {
                    if(get<1>(*i) == 'a')
                        aa.push_back(get<0>(*i));
                    if(get<1>(*i) == 'b')
                        bb.push_back(get<0>(*i));
                }
            }
            sort(aa.begin() , aa.end());

            sort(bb.begin() , bb.end());
            mybool.clear();
            for(int i =0 ; i<states ; i++ )
                mybool[i] = false;
            for(int it = 0 ; it<aa.size() ; ++it)
            {
                list<int>::iterator i;
                int no = aa[it];
                for(i = epsilon[no].begin() ; i!=epsilon[no].end() ;++i)
                    if(mybool[*i] == false)
                        mybool[*i] = true;
            }
            closure.clear();
            for(int i=0;i<states ;i++)
            {
                if(mybool[i] == true)
                    closure.push_back(i);
            }
            stra = arraytostring(closure , closure.size());
            vector<string>::iterator it;
            flag = 0;
            for(int it = 0; it < vect.size() ; ++it)
            {
                if(stra.compare(vect[it]) == 0)
                    {flag = 1;
                     break;
                    }
            }
            if(flag == 0)
            {
                que.push(stra);
                vect.push_back(stra);
            }
            flag =0;

            cout<<endl<<temp<<"---a--->"<<stra;



            for(int i =0 ; i<states ; i++ )
                mybool[i] = false;
            for(int it = 0 ; it<bb.size() ; ++it)
            {
                list<int>::iterator i;
                int no = aa[it];
                for(i = epsilon[no].begin() ; i!=epsilon[no].end() ;++i)
                    if(mybool[*i] == false)
                        mybool[*i] = true;
            }
            closure.clear();
            for(int i=0;i<states ;i++)
            {
                if(mybool[i] == true)
                    closure.push_back(i);
            }
            strb = arraytostring(closure , closure.size());

            for(int it = 0; it < vect.size() ; ++it)
            {
                if(strb.compare(vect[it]) == 0)
                    {flag = 1;
                        break;
                    }
            }
            if(flag == 0)
            {
                que.push(strb);
                vect.push_back(strb);
            }
            flag =0;

            cout<<endl<<temp<<"---b--->"<<strb;
            aa.clear();
            bb.clear();





        }

    }
};

int main()
{
    nfa_dfa ND(9);
    ND.transitions(0,1,'e');
    ND.transitions(0,7,'e');
    ND.transitions(1,2,'e');
    ND.transitions(1,4,'e');
    ND.transitions(2,3,'a');
    ND.transitions(3,6,'e');
    ND.transitions(4,5,'b');
    ND.transitions(5,6,'e');
    ND.transitions(6,7,'e');
    ND.transitions(6,1,'e');
    ND.transitions(7,8,'a');
    ND.print();
    ND.epsilonClosure();
    ND.printepsilon();
    ND.toDFA(0);

    return 0;
}
