#include <bits/stdc++.h>

using namespace std;

template <typename T>
 
 class Graph{
    unordered_map<T,list<pair<T,int>>> l;
    public:
    void addEdge(T x, T y,int wt=0, bool bidir=true){
        l[x].push_back({y,wt});
        if(bidir){
            l[y].push_back({x,wt});
        }
    }
    
    //code to print a graph
    void printGraph(){
        for(auto p : l){
            T city = p.first;
            list<pair<T,int>> nbrs=p.second;
            cout<<"City : "<<city<<endl;
            for(auto nbr : nbrs){
                T dest = nbr.first;
                int distance=nbr.second;
                cout<<"Destination city is "<<dest<<" at distance "<<distance<<endl;
            }
            cout<<endl;
        }
        
    }
    
    //code for single source shortest path
    void shortestPath(T src){
        unordered_map<T,int> dist;
        for(auto p : l){
            T city=p.first;
            dist[city]=INT_MAX;
        }
        queue<T> q;
        q.push(src);
        dist[src]=0;
        while(!q.empty()){
            T city=q.front();
            q.pop();
            for(auto p : l[city]){
                T nbr=p.first;
                int distance=p.second;
                if(dist[nbr]==INT_MAX){
                    dist[nbr]=dist[city]+distance;
                    q.push(nbr);
                }
            }
        }
        for(auto p : dist){
            cout<<"City : "<<p.first<<" at a distance : "<<p.second<<endl;
        }
        
        cout<<endl;
        
    }
    
    //utility function for counting connected components in undirected graph
    void dfs(T src,unordered_map<T,bool> &visited){
        visited[src]=true;
        for(auto nbrs : l[src]){
            T nbr=nbrs.first;
            if(!visited[nbr]){
                dfs(nbr,visited);
            }
        }
    }
    
    //function to count connected components
    void countConnectedComponents(){
        unordered_map<T,bool> visited;
        for(auto p : l){
            visited[p.first]=false;
        }
        
        int count=0;
        for(auto p : l){
            T node=p.first;
            if(!visited[node]){
                count++;
                dfs(node,visited);
            }
        }
        
        cout<<"Number of connected components = "<<count<<endl;
        cout<<endl;
    }
    
    
    //utility function to check if a graph has a cycle
    bool dfs2(T node, T parent,unordered_map<T,bool> &visited){
        visited[node]=true;
        for(auto p : l[node]){
            T nbr = p.first;
            if(!visited[nbr]){
                 if(dfs2(nbr,node,visited)){
                     return true;
                 }
            }
            else{
                if(nbr!=parent){
                    return true;
                }
            }
        }
        return false;
    }
    
    
    //function to check if a graph has a cycle or not
    void hasCycle(){
        unordered_map<T,bool> visited;
        for(auto p : l){
            visited[p.first]=false;
        }
        
        for(auto p : l){
            T node=p.first;
            if(!visited[node]){
                
                bool cycle=dfs2(node,node,visited);
                if(cycle){
                    cout<<"There is a cycle"<<endl;
                    return;
                }
            }
        }
        
        cout<<"No cycle present"<<endl;
    }
    
    //utility function for bipartite graph check
    bool bip_dfs(T src,T parent, int color, unordered_map<T,int> &visited){
        visited[src]=color;
        for(auto nbrs : l[src]){
            T nbr= nbrs.first;
            if(visited[nbr]==0){
                if(!bip_dfs(nbr,src,3-color,visited)){
                    return false;
                }
            }
            else if(nbr!=parent){
                if(visited[nbr]==color){
                    return false;
                }
            }
        }
        return true;
    }
    
    
    //Check if a graph is bipartite
    void checkBipartite(){
        unordered_map<T,int> visited;
        for(auto p : l){
            visited[p.first]=0;
        }
        
        //state 0 - not visited
        //state 1 - visited and coloured 1
        //state 2 - visited and coloured 2
        for(auto p : l){
            if(!visited[p.first]){
                bool isBipartite=bip_dfs(p.first,p.first,1,visited);
                if(isBipartite){
                    cout<<"The graph is bipartite"<<endl;
                    return;
                }
            }
        }
        cout<<"The graph is not bipartite"<<endl;
        
        
    }
    
    //utility function for shortest cycle
    void bfs(T src,int &ans){
        queue<T> q;
        unordered_map<T,int> visited;
        for(auto p : l){
            visited[p.first]=INT_MAX;
        }
        visited[src]=0;
        q.push(src);
        while(!q.empty()){
            T node = q.front();
            q.pop();
            for(auto nbrs : l[node]){
                T nbr=nbrs.first;
                if(visited[nbr]==INT_MAX){
                   visited[nbr]=visited[node]+1;
                   q.push(nbr);
                }
                else{
                    if(visited[nbr]>=visited[node]){
                        ans=min(ans,visited[nbr]+visited[node]+1);
                    }
                }
            }
        }
        
    }
    
    //main function for shortest cycle
    void findShortestCycle(){
        int ans=INT_MAX;
        for(auto p : l){
            bfs(p.first,ans);
        }
        
        if(ans==INT_MAX){
            cout<<"NO cycle"<<endl;
        }
        else{
            cout<<"Shortest cycle is "<<ans<<endl;
        }
    }
     
 };

int main()
{
   Graph<string> g;
   g.addEdge("Delhi","Kolkata",250);
   g.addEdge("Kolkata","Prague",2000);
   g.addEdge("Prague","Delhi",1750);
   g.addEdge("Kolkata","Berlin",3000);
   g.addEdge("Berlin","LA",1500,false);
   g.addEdge("Delhi","Mumbai",1000);
   g.addEdge("Mumbai","Prague",800,false);
   g.addEdge("Mumbai","Berlin",1200,false);
   g.printGraph();
   
   Graph<string> p;
   p.addEdge("Delhi","Kolkata",250);
   p.addEdge("Kolkata","Prague",2000);
   p.addEdge("Prague","Delhi",1750);
   p.addEdge("Kolkata","Berlin",3000);
   p.addEdge("Berlin","LA",1500);
   p.addEdge("Delhi","Mumbai",1000);
   p.addEdge("Mumbai","Prague",800);
   p.addEdge("Mumbai","Berlin",1200);
   p.shortestPath("Kolkata");
   
   Graph<char> a;
   a.addEdge('A','B');
   a.addEdge('B','C');
   a.addEdge('C','A');
   a.countConnectedComponents();
   a.hasCycle();
   a.checkBipartite();
   
   
   Graph<int> b;
   b.addEdge(1,2);
   b.addEdge(2,3);
   b.addEdge(3,4);
   b.addEdge(4,5);
   b.addEdge(5,6);
   b.addEdge(6,1);
   b.addEdge(3,7);
   b.addEdge(7,5);
   b.addEdge(1,8);
   b.addEdge(8,2);
   b.findShortestCycle();
   
   return 0;
}
