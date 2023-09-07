#ifndef _COSINESIMILARITY_H_
#define _COSINESIMILARITY_H_
#include"Document.h"
using namespace std;
class CosineSimilarity{
    private:
        vector<double> v;
        vector<vector<double>> v2;
    public:
        double Cosine_S(Document d1,Document d2){
            map<string,double>::const_iterator iter;
            double dot=0;
            double denom_a=0;
            double denom_b=0;
            for(iter=d1.begin();iter!=d1.end();iter++){
                dot+=d1.GetOcc(iter)*d2.GetOcc(iter);
                denom_a+=d1.GetOcc(iter)*d1.GetOcc(iter);
                denom_b+=d2.GetOcc(iter)*d2.GetOcc(iter);
            }
            if(denom_a*denom_b==0){return 0;}
            return dot/(sqrt(denom_a)*sqrt(denom_b));
        }
        
};
#endif
