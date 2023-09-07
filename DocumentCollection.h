#ifndef _DOCUMENTCOLLECTION_H_
#define _DOCUMENTCOLLECTION_H_
#include<vector>
#include"Document.h"
#include<math.h>
class DocumentCollection{
    private:
        map<string,double>n_occ;
        map<string,double> n_tf;
        vector<Document> document;
        public:
        void ReadIDF(){
                map<string,double>::const_iterator iter;
                bool flag;
                int numDoc=0;
                for(int i=0;i<document.size();i++){
                    flag=false;
                    Document d1 = document[i];
                        for(iter=d1.begin();iter!=d1.end();iter++){
                             for(int j=i;j<document.size();j++){
                                Document d2 = document[j];
                                        if(d2.Search(d1.GetWords(iter))==true && flag==false){
                                            numDoc++;
                                            n_occ[d1.GetWords(iter)]+=numDoc;
                                            flag=true;
                                        }
                            }
                        numDoc=0;
                        flag=false;
                        }
                 }
        }
    void SetIDF(){
        ReadIDF();
        map<string,double>::const_iterator iter;
        map<string,double>::const_iterator iter2;
        cout<<"TF-IDF"<<endl;
        for(int i=0;i<document.size();i++){
            Document d1 = document[i];
            for(iter=n_occ.begin();iter!=n_occ.end();iter++){
                for(iter2=d1.begin();iter2!=d1.end();iter2++){
                    if(d1.GetWords(iter)==iter2->first){
                        d1.SetOcc(iter2,(1.0+log(document.size()/n_occ[iter->first]))*d1.GetOcc(iter2));
                        cout<<d1.GetWords(iter2)<<"=="<<iter->first<<d1.GetOcc(iter2)<<endl;
                    }
                }
             }
         }
    }
    public:
        void Add(Document d){
            document.push_back(d);
        }
        inline const int GetSize(){
            return document.size();                       
        }
        inline Document GetDocument(int i){
            return document[i];
        }
};
#endif
