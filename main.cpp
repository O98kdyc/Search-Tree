#include <iostream>
#include "dySeaTab.h"
#include "BinSeaTre.h"
#include "AVL.h"
#include "users.h"
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <sys/time.h> //头文件
struct timeval startTime, endTime; //时间变量

using namespace std;

int main()
{
    double diff;


    SET<int,user> a[50000];
    ifstream fin("tree1.txt");
    if(!fin) {cout<<"cannot open"; return 1;}
    for(int i=0;i<50000;i++) fin>>a[i].key>>a[i].other;


    gettimeofday (&startTime, NULL);

    AvlTree<int,user> tree1;
    for(int i=0;i<50000;i++) tree1.insert(a[i]);

    gettimeofday(&endTime, NULL);
    diff = 1000000 * (endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
    cout<<"AVL"<<diff<<endl;

    gettimeofday (&startTime, NULL);

    BinarySearchTree<int,user> tree2;
    for(int i=0;i<50000;i++) tree2.insert(a[i]);

    gettimeofday(&endTime, NULL);
    diff = 1000000 * (endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
    cout<<"Binary"<<diff<<endl;

    int b[500],c[500];
    srand(time(NULL));
    for(int i=0;i<500;i++) b[i]=rand()%50000;
    for(int i=0;i<500;i++) c[i]=rand()%50000+50000;

    gettimeofday (&startTime, NULL);

    for(int j=0;j<100;j++)
    for(int i=0;i<500;i++) tree1.find(b[i]);

    gettimeofday(&endTime, NULL);
    diff = 10000 * (endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
    cout<<"AVLfind"<<diff<<endl;

    gettimeofday (&startTime, NULL);

    for(int j=0;j<100;j++)
    for(int i=0;i<500;i++) tree2.find(b[i]);

    gettimeofday(&endTime, NULL);
    diff = 10000 * (endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
    cout<<"Binaryfind"<<diff<<endl;

    gettimeofday (&startTime, NULL);

    for(int j=0;j<100;j++)
    for(int i=0;i<500;i++) tree1.find(c[i]);

    gettimeofday(&endTime, NULL);
    diff = 10000 * (endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
    cout<<"AVLnofind"<<diff<<endl;

    gettimeofday (&startTime, NULL);

    for(int j=0;j<100;j++)
    for(int i=0;i<500;i++) tree2.find(c[i]);

    gettimeofday(&endTime, NULL);
    diff = 10000 * (endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
    cout<<"Binarynofind"<<diff<<endl;

    gettimeofday (&startTime, NULL);

    for(int j=0;j<100;j++)
    for(int i=0;i<500;i++) tree1.remove(b[i]);

    gettimeofday(&endTime, NULL);
    diff = 10000 * (endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
    cout<<"AVLremove"<<diff<<endl;

    gettimeofday (&startTime, NULL);

    for(int j=0;j<100;j++)
    for(int i=0;i<500;i++) tree2.remove(b[i]);

    gettimeofday(&endTime, NULL);
    diff = 10000 * (endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
    cout<<"Binaryremove"<<diff<<endl;

    gettimeofday (&startTime, NULL);

    for(int j=0;j<100;j++)
    for(int i=0;i<500;i++) tree1.remove(c[i]);

    gettimeofday(&endTime, NULL);
    diff = 10000 * (endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
    cout<<"AVLnoremove"<<diff<<endl;

    gettimeofday (&startTime, NULL);

    for(int j=0;j<100;j++)
    for(int i=0;i<500;i++) tree2.remove(c[i]);

    gettimeofday(&endTime, NULL);
    diff = 10000 * (endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
    cout<<"Binarynoremove"<<diff<<endl;

    return 0;
}
