#include"DocumentCollection.h"
#include"Cluster.h"
int main(){
    DocumentCollection doc;
    doc.Add(Document("./files/file.txt"));
    doc.Add(Document("./files/file2.txt"));
    doc.Add(Document("./files/file3.txt"));
    doc.Add(Document("./files/file4.txt"));
    doc.Add(Document("./files/file5.txt"));
    doc.Add(Document("./files/file6.txt"));
    doc.Add(Document("./files/file7.txt"));
    doc.Add(Document("./files/file8.txt"));
    doc.Add(Document("./files/file9.txt"));
    doc.Add(Document("./files/file10.txt"));

    Clustering c(doc);
    c.run();
}
