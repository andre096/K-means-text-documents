#ifndef _CLUSTER_H_
#define _CLUSTER_H_
#include"DocumentCollection.h"
#include"CosineSimilarity.h"
using namespace std;
class Clustering{
    private:
        vector<double> cluster;
        DocumentCollection doc;
        vector<int> vecOfCluster;
        vector<double> vecOfDistance;
        vector<double> vecOfBaryCenter;
        void InitializeCenter(const int k, DocumentCollection doc_){
            if(k>doc_.GetSize()/2){
                cerr<<"There are fewer document"<<endl;
                exit(0);
            }
            for(int z=0;z<k;z++){
                int center = rand()%doc_.GetSize()+1;
                cluster.push_back(center);
                cout<<" Center: "<<center+1<<endl;
            }
        }
        inline const int GetCenter(const int i){return cluster[i];}
        int FindCenter(const int i){
            for(int j=0;j<cluster.size();j++){
                if(GetCenter(j)+1==i) 
                    return GetCenter(j)+1;
            }
        }
        int CenterPosition(const int i){
            for(int j=0;j<cluster.size();j++)
                if(GetCenter(j)+1==i)
                    return j;
        }
        void FirstIter(DocumentCollection doc_){
            CosineSimilarity cs;
            double max;
            int index;
            for(int z=0;z<doc_.GetSize();z++){
                max=0;
                cout<<"File:"<<endl;
                for(int i=0;i<cluster.size();i++){
                        cout<<"File:"<<z+1<<" "<<"Cluster:"<<GetCenter(i)+1<<endl;                    
                        cout<<"Cosine Similarity:"<<endl;
                        cout<<cs.Cosine_S((doc_.GetDocument(z)),doc_.GetDocument(GetCenter(i)))<<endl;
                        if(max==0){            
                            max=cs.Cosine_S((doc_.GetDocument(z)),doc_.GetDocument(GetCenter(i)));
                            index=GetCenter(i)+1;
                        }
                        else
                            if(cs.Cosine_S((doc_.GetDocument(z)),doc_.GetDocument(GetCenter(i)))>max){
                                max=cs.Cosine_S((doc_.GetDocument(z)),doc_.GetDocument(GetCenter(i)));
                                index=GetCenter(i)+1;
                            }
                }
                vecOfDistance.push_back(max);
                vecOfCluster.push_back(index);
            }
            for(int i=0;i<vecOfCluster.size();i++) cout<<i+1<<"->"<<vecOfCluster[i]<<"->"<<vecOfDistance[i]<<endl;
        }
        void CalculateBarycenter(){
            double sum;
            int n;
            double barycenter;
            for(int i=0;i<cluster.size();i++){
                sum=0;
                n=0;
                for(int j=0;j<vecOfCluster.size();j++){
                    if(vecOfCluster[j]==GetCenter(i)+1 && vecOfDistance[j]!=1){
                        sum+=vecOfDistance[j];
                        n++;
                    }
                }
                for(int z=0;z<vecOfDistance.size();z++){
                    if(z+1==GetCenter(i)+1)
                        vecOfDistance[z]=sum/n;
                }
                barycenter=sum/n;
                cout<<"Barycenter cluster "<<GetCenter(i)+1<<"->"<<barycenter<<endl;
                vecOfBaryCenter.push_back(barycenter);
            }
        }
         int ReassignFile(DocumentCollection doc_){
            CosineSimilarity cs;
            double min_dist;
            int index;
            int file;
            int center;
            int flag=0;
            vector<int> vecNewCluster;
                for(int i=0;i<vecOfDistance.size();i++){
                    min_dist=-1.0;
                      for(int j=0;j<cluster.size();j++){
                        if(FindCenter(i+1)!=i+1){
                           if(min_dist==-1.0){
                                 min_dist=abs(vecOfDistance[i]-vecOfBaryCenter[j]); file=i+1; center=GetCenter(j)+1;
                                  }
                                  else
                                     if(abs(vecOfDistance[i]-vecOfBaryCenter[j])<min_dist){
                                           min_dist=abs(vecOfDistance[i]-vecOfBaryCenter[j]); file=i+1; center=GetCenter(j)+1;
                                     }
                            }
                            else {file=i+1; center=FindCenter(i+1); min_dist=vecOfBaryCenter[CenterPosition(FindCenter(i+1))]; break;}
                        }
                          cout<<file<<"->"<<center<<"->"<<min_dist<<endl;
                          vecNewCluster.push_back(center);
                  }
                  for(int i=0;i<vecOfCluster.size();i++){
                    if(vecOfCluster[i]==vecNewCluster[i]){
                        flag++;
                        }
                    else {vecOfCluster[i]=vecNewCluster[i]; cout<<"File "<<i+1<<" changed to cluster "<<vecOfCluster[i]<<endl;}
                    }
                   vecNewCluster.clear();
                   vecOfBaryCenter.clear();
                   return flag;
         }
    public:
        Clustering(const DocumentCollection doc_){doc=doc_;}
        void run(){
            int i=0; 
            doc.SetIDF(); 
            InitializeCenter(2,doc); 
            FirstIter(doc);
            while(i!=doc.GetSize()){
                CalculateBarycenter();
                i=ReassignFile(doc);
            }
        }
};
#endif
