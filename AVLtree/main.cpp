#include <iostream>
#include "AVLtree.h"
#include "MusicManager.h"

int main() {
    int *artists = new int[4];
    int *songs = new int[4];
    int stream=999;
    MusicManager *manager = new MusicManager();
    /*
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
    */
    /*
    cout << "test 1: " << manager->addArtist(115,5)<< endl;
    cout << "test 3: " << manager->addToSongCount(115,0)<< endl;
    cout << "test 3: " << manager->addToSongCount(115,1)<< endl;
    cout << "test 2: " << manager->addToSongCount(115,2)<< endl;
    cout << "test 3: " << manager->addToSongCount(115,3)<< endl;
    cout << "test 3: " << manager->addToSongCount(115,4)<< endl;
    cout << "test 3: " << manager->addToSongCount(115,0)<< endl;
    cout << "test 3: " << manager->addToSongCount(115,1)<< endl;
    */
    /*
    cout << "test 1: " << manager->addArtist(115,5)<< endl;
    cout << "test 2: " << manager->addArtist(10,2)<< endl;
    cout << "test 3: " << manager->addArtist(123,3)<< endl;
    cout << "test 4: " << manager->addArtist(456,3)<< endl;
    cout << "test 5: " << manager->addArtist(457,3)<< endl;
    cout << "test 6: " << manager->addArtist(120,4)<< endl;
    cout << "test 6: " << manager->removeArtist(115)<< endl;
    cout << "test 6: " << manager->removeArtist(456)<< endl;
    cout << "test 6: " << manager->addArtist(10,2)<< endl;
    cout << "test 7: " << manager->addToSongCount(123,2)<< endl;
    cout << "test 7: " << manager->numberOfStreams(123,2,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 7: " << manager->numberOfStreams(123,1,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 7: " << manager->addToSongCount(123,1)<< endl;
    cout << "test 7: " << manager->numberOfStreams(123,1,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 7: " << manager->addToSongCount(120,1)<< endl;
    cout << "test 7: " << manager->numberOfStreams(120,1,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 7: " << manager->addToSongCount(457,1)<< endl;
    cout << "test 7: " << manager->addToSongCount(457,1)<< endl;
    cout << "test 8: " << manager->getRecommendedSongs(5,artists,songs)<< endl;
    for (int i = 0; i < 5; ++i) {
        printf("artist number %d : %d, song number %d : %d \n",i+1,artists[i],i+1,songs[i]);
    }
    */
    /*
    cout << "test 1: " << manager->addArtist(115,2)<< endl;
    cout << "test 2: " << manager->addArtist(10,2)<< endl;
    cout << "test 2: " << manager->addArtist(15,2)<< endl;
    cout << "test 3: " << manager->addToSongCount(115,1)<< endl;
    cout << "test 4: " << manager->addToSongCount(115,0)<< endl;
    cout << "test 5: " << manager->addToSongCount(10,0)<< endl;
    cout << "test 6: " << manager->addToSongCount(10,1)<< endl;
    cout << "test 7: " << manager->addToSongCount(115,0)<< endl;
    cout << "test 8: " << manager->addToSongCount(115,1)<< endl;
    cout << "test 9: " << manager->removeArtist(10)<< endl;
    cout << "test 7: " << manager->addToSongCount(115,0)<< endl;
    cout << "test 8: " << manager->addToSongCount(115,1)<< endl;
    cout << "test 7: " << manager->addToSongCount(15,0)<< endl;
    cout << "test 8: " << manager->addToSongCount(15,1)<< endl;
    cout << "test 7: " << manager->addToSongCount(15,0)<< endl;
    cout << "test 8: " << manager->addToSongCount(15,1)<< endl;
    cout << "test 7: " << manager->addToSongCount(15,0)<< endl;
    cout << "test 8: " << manager->addToSongCount(15,1)<< endl;
    cout << "test 7: " << manager->addToSongCount(15,0)<< endl;
    cout << "test 8: " << manager->addToSongCount(15,1)<< endl;
    cout << "test 7: " << manager->addToSongCount(15,0)<< endl;
    cout << "test 8: " << manager->addToSongCount(15,1)<< endl;
    cout << "test 8: " << manager->getRecommendedSongs(4,artists,songs)<< endl;
    for (int i = 0; i < 4; ++i) {
        printf("artist number %d : %d, song number %d : %d \n",i+1,artists[i],i+1,songs[i]);
    }
    */
    cout << "test 1: " << manager->addArtist(115,3)<< endl;
    cout << "test 2: " << manager->addToSongCount(115,1)<< endl;
    cout << "test 3: " << manager->addToSongCount(115,0)<< endl;
    cout << "test 4: " << manager->addToSongCount(115,1)<< endl;
    cout << "test 5: " << manager->addToSongCount(115,2)<< endl;
    cout << "test 6: " << manager->removeArtist(115)<< endl;
    delete [] artists;
    delete [] songs;
    delete manager;
    return 0;



    /*
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
    */
}