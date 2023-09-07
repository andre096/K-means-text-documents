#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_
#include<map>
#include<fstream>
#include<stdlib.h>
#include<iostream>
using namespace std;
class Document{
    private:
        map<string,double> words;
        void Read(const string& file){
            ifstream is;
            is.open(file.c_str());
            if(!is.good()){
                cerr<<"Error opening file.\n";
            }
            string str;
            while(is>>str){
                words[str]++;
            }
            map<string,double>::const_iterator iter;
            cout<<"File:"<<endl;
	        for(iter=words.begin();iter!=words.end();++iter){
                words[iter->first]=words[iter->first]/10;
			    cout<<iter->first<<"->"<<iter->second<<endl;
			}
           
        }
        void SetOcc(map<string,double>::const_iterator iter,double n){
            words[iter->first]=n;
            cout<<words[iter->first];
        }
    public:

        Document(const string& str){Read(str);}
        void setOcc(string str,double n){
            map<string,double>::const_iterator iter;
            words[str]=n;
        }
        inline const string GetWords(map<string,double>::const_iterator iter){
            return iter->first;
        }
        inline const double GetOcc(map<string,double>::const_iterator iter){
            return words[iter->first];
        }
        inline const int GetSize(){
            return words.size();
        }

        bool Search(const string& word){
            map<string,double>::const_iterator iter;
            iter=words.find(word);
            if(iter!=words.end()){
                return true;
            }
            return false;
        }
        const map<string,double>::const_iterator begin(){return words.begin();}
        const map<string,double>::const_iterator end(){return words.end();}
        friend class DocumentCollection;
};
#endif
