//
// Created by Dell on 11/05/2020.
//

#include "library1.h"
#include "MusicManager.h"

void *Init(){
    MusicManager *DS = new MusicManager();
    return (void *)DS;
}

StatusType AddArtist(void *DS, int artistID, int numOfSongs){
    return ((MusicManager *)DS)->addArtist(artistID,numOfSongs);
}

StatusType RemoveArtist(void *DS, int artistID){

}

StatusType AddToSongCount(void *DS, int artistID, int songID){

}

StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams){

}

StatusType GetRecommendedSongs(void *DS, int numOfSongs, int *artists, int *songs){

}

void Quit(void** DS){

}