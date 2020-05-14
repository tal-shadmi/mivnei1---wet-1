#include <iostream>
#include "AVLtree.h"
#include "MusicManager.h"

#define num_of_recommended_songs 7
int main() {
    int *artist = new int[num_of_recommended_songs];
    int *songs = new int[num_of_recommended_songs];
    int stream=999;
    MusicManager *manager = new MusicManager();
    cout << "test 1: " << manager->addArtist(115,3)<< endl;
    cout << "test 2: " << manager->addToSongCount(115,1)<< endl;
    cout << "test 3: " << manager->addToSongCount(115,0)<< endl;
    cout << "test 4: " << manager->addToSongCount(115,1)<< endl;
    cout << "test 5: " << manager->addToSongCount(115,2)<< endl;
    cout << "test 6: " << manager->getRecommendedSongs(num_of_recommended_songs,artist,songs)<< endl;
    for(int i=0;i<num_of_recommended_songs;i++){
        cout << i << ". artist: " << artist[i] << ", ";
        cout << "song: " << songs[i] << endl;
    }
    cout << "test 7: " << manager->addArtist(10,2)<< endl;
    cout << "test 8: " << manager->addToSongCount(10,1)<< endl;
    cout << "test 9: " << manager->addToSongCount(10,2)<< endl; //failure
    cout << "test 10: " << manager->addArtist(123,3) << endl;
    cout << "test 11: " << manager->removeArtist(115) << endl;
    cout << "test 12: " << manager->addArtist(150,1) << endl;
    cout << "test 13: " << manager->addToSongCount(123,1)<< endl;
    cout << "test 14: " << manager->numberOfStreams(115,2,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 15: " << manager->addArtist(115,2)<< endl;
    cout << "test 16: " << manager->addToSongCount(115,0)<< endl;
    cout << "test 17: " << manager->numberOfStreams(115,0,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 18: " << manager->removeArtist(150) << endl;
    cout << "test 19: " << manager->addToSongCount(10,1)<< endl;
    cout << "test 20: " << manager->numberOfStreams(10,1,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 21: " << manager->getRecommendedSongs(num_of_recommended_songs,artist,songs)<< endl;
    for(int i=0;i<num_of_recommended_songs;i++){
        cout << i << ". artist: " << artist[i] << ", ";
        cout << "song: " << songs[i] << endl;
    }
    /*
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
    cout << "test 11: " << manager->addToSongCount(123,2)<< endl;
    cout << "test 12: " << manager->addToSongCount(120,1)<< endl;
    cout << "test 13: " << manager->addToSongCount(123,2)<< endl;
    cout << "test 14: " << manager->numberOfStreams(123,2,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 15: " << manager->getRecommendedSongs(num_of_recommended_songs,artist,songs)<< endl;
    for(int i=0;i<num_of_recommended_songs;i++){
        cout << i << ". artist: " << artist[i] << ", ";
        cout << "song: " << songs[i] << endl;
    }
    cout << "test 16: "<< manager->numberOfStreams(123,1,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 17: " << manager->addToSongCount(123,1)<< endl;
    cout << "test 18: " << manager->numberOfStreams(123,1,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 19: " << manager->addToSongCount(120,1)<< endl;
    cout << "test 20: " << manager->numberOfStreams(120,1,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 21: " << manager->addToSongCount(457,1)<< endl;
    cout << "test 22: " << manager->addToSongCount(457,1)<< endl;
    cout << "test 23: " << manager->addToSongCount(123,1)<< endl;
    cout << "test 24: " << manager->getRecommendedSongs(num_of_recommended_songs,artist,songs)<< endl;
    for(int i=0;i<num_of_recommended_songs;i++){
        cout << i << ". artist: " << artist[i] << ", ";
        cout << "song: " << songs[i] << endl;
    }
    cout << "test 25: " << manager->addToSongCount(123,2)<< endl;
    cout << "test 26: " << manager->numberOfStreams(123,2,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 27: " << manager->addToSongCount(123,2)<< endl;
    cout << "test 28: " << manager->numberOfStreams(123,2,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 29: " << manager->addToSongCount(456,1) << endl;
    cout << "test 30: " << manager->numberOfStreams(10,1,&stream)<< endl;
    cout << "stream: " << stream << endl;
    cout << "test 31: " << manager->addToSongCount(10,1)<< endl;
    cout << "test 32: " << manager->addToSongCount(115,3)<< endl;
   */ delete [] artist;
    delete [] songs;
    delete manager;
     return 0;
}


    /* SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
            */
