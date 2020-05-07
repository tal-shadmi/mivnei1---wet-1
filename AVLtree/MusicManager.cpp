//
// Created by Dell on 05/05/2020.
//

#include "MusicManager.h"
#include "AVLtree.h"

// ---------- SongKey implementation ---------- //

MusicManager::SongKey::SongKey(int songID, int songNumberOfPlays):
                               songID(songID),songNumberOfPlays(songNumberOfPlays){}

int MusicManager::SongKey::getSongID() {
    return songID;
}

int MusicManager::SongKey::getSongNumberOfPlays() {
    return songNumberOfPlays;
}

// ---------- ArtistKey implementation ---------- //

MusicManager::ArtistKey::ArtistKey(int artistID): artistID(artistID) {}

int MusicManager::ArtistKey::getArtistID() {
    return artistID;
}

// ---------- ArtistData implementation ---------- //

MusicManager::ArtistData::ArtistData(int numberOfSongs){
    this->numberOfSongs = numberOfSongs;
    songs = AVLtree<SongKey,int>();
    songNodes = new AVLtree<SongKey,int>::AVLNode*[numberOfSongs];
    playsNodes = new PlaysData*[numberOfSongs];
    zeroPlays = new int*[numberOfSongs];
    for (int i = 0; i < numberOfSongs; ++i) {
        songNodes[i]= nullptr;
        playsNodes[i]= nullptr;
        zeroPlays[i] = new int[2];
        if (i==0) zeroPlays[i][0]= NULL;
        else zeroPlays[i][0]=i-1;
        if (i==numberOfSongs-1) zeroPlays[i][0]=NULL;
        zeroPlays[i][0]=i+1;
    }
}

MusicManager::ArtistData::~ArtistData() {
    delete[] songNodes;
    delete[] playsNodes;
    for (int i = 0; i < numberOfSongs; ++i) {
        delete[] zeroPlays[i];
    }
    delete[] zeroPlays;
}

// ---------- PlaysNode implementation ---------- //

MusicManager::PlaysData::PlaysData(AVLtree<MusicManager::ArtistKey, MusicManager::ArtistReducedData> artistTree,
                                   MusicManager::PlaysData *next,
                                   MusicManager::PlaysData *previous) {
    artistsTree = AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>();
    next = nullptr;
    previous = nullptr;
}

// ---------- MusicManager implementation ---------- //

