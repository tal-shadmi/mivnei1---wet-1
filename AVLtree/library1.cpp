//
// Created by Dell on 11/05/2020.
//

#include "library1.h"
#include "MusicManager.h"

void *Init(){
    MusicManager *DS = NULL;
    try {
        DS = new MusicManager();
    }
    catch (std::bad_alloc &badAlloc){
        return NULL;
    }
    return (void *)DS;
}

StatusType AddArtist(void *DS, int artistID, int numOfSongs){
    if (DS != NULL || numOfSongs<=0 || artistID<=0)
        return INVALID_INPUT;
    try {
        return ((MusicManager *)DS)->addArtist(artistID,numOfSongs);
    }
    catch (std::bad_alloc &badAlloc){
        return ALLOCATION_ERROR;
    }
}

StatusType RemoveArtist(void *DS, int artistID){
    if (DS != NULL || artistID <= 0)
        return INVALID_INPUT;
    try {
        return ((MusicManager *)DS)->removeArtist(artistID);
    }
    catch (std::bad_alloc &badAlloc) {
        return ALLOCATION_ERROR;
    }
}

StatusType AddToSongCount(void *DS, int artistID, int songID){
    if (DS != NULL || artistID <= 0)
        return INVALID_INPUT;
    try {
        return ((MusicManager *)DS)->addToSongCount(artistID,songID);
    }
    catch (std::bad_alloc &badAlloc){
        return ALLOCATION_ERROR;
    }
}

StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams){
    if (DS != NULL || songID < 0 || artistID <=0 || streams != NULL)
        return INVALID_INPUT;
    try {
        return ((MusicManager *)DS)->numberOfStreams(artistID,songID,streams);
    }
    catch (std::bad_alloc &badAlloc){
        return ALLOCATION_ERROR;
    }
}

StatusType GetRecommendedSongs(void *DS, int numOfSongs, int *artists, int *songs){
    if (DS != NULL || numOfSongs <= 0 || artists != NULL || artists != songs)
        return INVALID_INPUT;
    try {
        return ((MusicManager *)DS)->getRecommendedSongs(numOfSongs,artists,songs);
    }
    catch (std::bad_alloc &badAlloc){
        return ALLOCATION_ERROR;
    }
}

void Quit(void** DS){
    delete *((MusicManager **)DS);
    *DS = NULL;
}