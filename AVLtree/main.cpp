#include <iostream>
#include "AVLtree.h"
#include "MusicManager.h"

int main() {
    //AVLtree<int, int> tree;
    //int a=1,b=2,c=3,d=4,e=5,f=6,g=7,h=8,i=9,j=10,k=11,l=12,m=13,n=14,o=15,p=16,
    //        q=17,r=18,s=19,t=20,u=21,v=22,w=23,x=24,y=25,z=26;
    int *artist = new int[3];
    int *songs = new int[3];
    int stream=999;
    MusicManager *manager = new MusicManager();
    cout << "test 1: " << manager->addArtist(115,5)<< endl;
    cout << "test 2: " << manager->addArtist(10,2)<< endl;
    cout << "test 3: " << manager->numberOfStreams(10,1,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 4: " << manager->addArtist(123,3) << endl;
    cout << "test 5: " << manager->addArtist(456,3) << endl;
    cout << "test 6: " << manager->addArtist(456,3) << endl;
    cout << "test 7: " << manager->addArtist(123,4) << endl;
    cout << "test 8: " << manager->removeArtist(456) << endl;
    cout << "test 9: " << manager->removeArtist(456) << endl;
    cout << "test 10: " << manager->addArtist(10,2)<< endl;
    cout << "test 11: " << manager->addToSongCount(123,3)<< endl;
    cout << "test 12: " << manager->numberOfStreams(123,3,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 13: "<< manager->numberOfStreams(123,2,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 14: " << manager->addToSongCount(123,1)<< endl;
    cout << "test 15: " << manager->addToSongCount(123,2)<< endl;
    cout << "test 16: " << manager->numberOfStreams(123,2,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 17: " << manager->addToSongCount(456,1) << endl;
    cout << "test 18: " << manager->addToSongCount(10,1)<< endl;
    cout << "test 19: " << manager->addToSongCount(115,3)<< endl;
    /*  manager->addToSongCount(10,1);
     manager->addToSongCount(10,1);
     manager->addToSongCount(123,2);
     manager->addToSongCount(123,1);
     manager->getRecommendedSongs(3,artist,songs);
   */  return 0;



    /* SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
            */
    return 0;
}