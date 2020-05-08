//
// Created by Dell on 05/05/2020.
//

#include "MusicManager.h"

// ---------- SongKey implementation ---------- //

MusicManager::SongKey::SongKey(int songID, int songNumberOfPlays):
                               songID(songID),songNumberOfPlays(songNumberOfPlays){}

int MusicManager::SongKey::getSongID() const {
    return songID;
}

int MusicManager::SongKey::getSongNumberOfPlays() const {
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
    maxSongID = 0;
    maxSongPlays = 0;
    currentMaxNotCheckedSong = 0;
    songs = AVLtree<SongKey,int>();
    songNodes = new AVLtree<SongKey,int>::AVLNode*[numberOfSongs];
    playsNodes = new List<int,PlaysData>::ListNode*[numberOfSongs];
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

AVLtree<MusicManager::SongKey,int> MusicManager::ArtistData::getSongs() const {
    return songs;
}

AVLtree<MusicManager::SongKey,int>::AVLNode** MusicManager::ArtistData::getSongNodes() const {
    return songNodes;
}

List<int,MusicManager::PlaysData>::ListNode** MusicManager::ArtistData::getPlaysNodes() const {
    return playsNodes;
}

int** MusicManager::ArtistData::getZeroPlays() const {
    return zeroPlays;
}

void MusicManager::ArtistData::setMaxSongID(int maxSongID) {
    this->maxSongID=maxSongID;
}

void MusicManager::ArtistData::setMaxSongPlays(int maxSongPlays) {
    this->maxSongPlays=maxSongPlays;
}

void MusicManager::ArtistData::setCurrentMaxNotCheckedSong(int maxNotChecked) {
    this->currentMaxNotCheckedSong=maxNotChecked;
}

// ---------- PlaysData implementation ---------- //

AVLtree<MusicManager::ArtistKey,AVLtree<MusicManager::ArtistKey,MusicManager::ArtistData>::AVLNode*> MusicManager::PlaysData::getArtistTree() const {
    return artistsTree;
}

// ---------- MusicManager implementation ---------- //

MusicManager::MusicManager() {
    artists = AVLtree<ArtistKey,ArtistData>();
    songPlays = List<int,PlaysData>();
}

void MusicManager::addArtist(int artistID, int numOfSongs) {
    MusicManager::ArtistData data = MusicManager::ArtistData(numOfSongs);
    MusicManager::ArtistKey key = MusicManager::ArtistKey(artistID);
    artists.insert(key,data);
}

void MusicManager::addToSongCount(int artistID, int songID) {
    MusicManager::ArtistKey artistKey = MusicManager::ArtistKey(artistID);
    AVLtree<ArtistKey,ArtistData>::AVLNode* artist = artists.find(artistKey);
    AVLtree<SongKey,int>::AVLNode* songNode = artist->getData().getSongNodes()[songID];
    if (songNode== nullptr){
        MusicManager::SongKey newSongKey = MusicManager::SongKey(songID,1);
        AVLtree<SongKey,int>::AVLNode* newNode = artist->getData().getSongs().insert(newSongKey,artistID);
        artist->getData().getSongNodes()[songID] = newNode;
        artist->getData().getZeroPlays()[artist->getData().getZeroPlays()[songID][0]][1] = artist->getData().getZeroPlays()[songID][1];
        artist->getData().getZeroPlays()[artist->getData().getZeroPlays()[songID][1]][0] = artist->getData().getZeroPlays()[songID][0];
        if (songPlays.getFirst()->getKey()!=1)
            songPlays.insertFirst(1,PlaysData());
        songPlays.getFirst()->getData().getArtistTree().insert(artistKey,artist);
        artist->getData().getPlaysNodes()[songID] = songPlays.getFirst();
        return;
    }
    int newNumberOfPlays = songNode->getKey().getSongNumberOfPlays()+1;
    MusicManager::SongKey oldSongKey = MusicManager::SongKey(songID,songNode->getKey().getSongNumberOfPlays());
    artist->getData().getSongs().erase(oldSongKey);
    MusicManager::SongKey newSongKey = MusicManager::SongKey(songID,newNumberOfPlays);
    artist->getData().getSongs().insert(newSongKey,artistID);

}