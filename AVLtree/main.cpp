#include <iostream>
#include "AVLtree.h"
#include "MusicManager.h"

#define num_of_recommended_songs 4
int main() {
    int *artist = new int[num_of_recommended_songs];
    int *songs = new int[num_of_recommended_songs];
    int stream=999;
    MusicManager *manager = new MusicManager();
    cout << "test 1: " << manager->addArtist(115,5)<< endl;
    cout << "test 2: " << manager->addArtist(10,2)<< endl;
    cout << "test 3: " << manager->addArtist(123,3) << endl;
    cout << "test 4: " << manager->addArtist(456,3) << endl;
    cout << "test 5: " << manager->addArtist(457,3) << endl;
    cout << "test 6: " << manager->addArtist(120,4) << endl;
    cout << "test 7: " << manager->removeArtist(115) << endl;
    cout << "test 8: " << manager->removeArtist(456) << endl;
    cout << "test 9: " << manager->addArtist(10,2)<< endl; //already exists
    cout << "test 10: " << manager->addToSongCount(123,2)<< endl;
    cout << "test 11: " << manager->numberOfStreams(123,2,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 12: "<< manager->numberOfStreams(123,1,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 13: " << manager->addToSongCount(123,1)<< endl;
    cout << "test 14: " << manager->numberOfStreams(123,1,&stream)<< endl;
    cout << "stream: " << stream << endl;
   /* cout << "test 15: " << manager->getRecommendedSongs(num_of_recommended_songs,artist,songs)<< endl;
    for(int i=0;i<num_of_recommended_songs;i++){
        cout << i << ". artist: " << artist[i] << ", ";
        cout << "song: " << songs[i] << endl;
    }
   */ cout << "test 16: " << manager->addToSongCount(123,2)<< endl;
    cout << "test 17: " << manager->numberOfStreams(123,2,&stream)<< endl;
    cout << "stream: " << stream << endl;
   /* cout << "test 16: " << manager->addToSongCount(123,2)<< endl;
    cout << "test 17: " << manager->numberOfStreams(123,2,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 18: " << manager->addToSongCount(456,1) << endl;
    cout << "test 19: " << manager->numberOfStreams(10,1,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 20: " << manager->addToSongCount(10,1)<< endl;
    cout << "test 21: " << manager->addToSongCount(115,3)<< endl;
    manager->addToSongCount(10,1);
     manager->addToSongCount(10,1);
     manager->addToSongCount(123,2);
     manager->addToSongCount(123,1);
   */  return 0;
}


    /* SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
            */
