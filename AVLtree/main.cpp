#include <iostream>
#include "AVLtree.h"
#include "MusicManager.h"

int main() {
    //AVLtree<int, int> tree;
    //int a=1,b=2,c=3,d=4,e=5,f=6,g=7,h=8,i=9,j=10,k=11,l=12,m=13,n=14,o=15,p=16,
    //        q=17,r=18,s=19,t=20,u=21,v=22,w=23,x=24,y=25,z=26;
    int *artist = new int[3];
    int *songs = new int[3];
    MusicManager *manager = new MusicManager();
    manager->addArtist(123,5);
    manager->addArtist(456,3);
    manager->addArtist(123,3);
    manager->removeArtist(456);
    manager->removeArtist(789);
    manager->addToSongCount(123,3);
    manager->addToSongCount(123,2);
    manager->addToSongCount(123,2);
    //manager->getRecommendedSongs(3,artist,songs);
    return 0;
}