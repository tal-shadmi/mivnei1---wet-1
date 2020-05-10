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

int MusicManager::ArtistKey::getArtistID() const {
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
    zeroPlays = new int*[numberOfSongs+1];
    for (int i = 0; i < numberOfSongs+1; ++i) {
        if (i < numberOfSongs){
            songNodes[i]= nullptr;
            playsNodes[i]= nullptr;
        }
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

int MusicManager::ArtistData::getNumberOfSongs() {
    return numberOfSongs;
}

int** MusicManager::ArtistData::getZeroPlays() const {
    return zeroPlays;
}

int MusicManager::ArtistData::getMaxSongID() {
    return maxSongID;
}

int MusicManager::ArtistData::getMaxSongPlays() const {
    return maxSongPlays;
}

int MusicManager::ArtistData::getCurrentMaxNotCheckedSong(){
    return currentMaxNotCheckedSong;
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

MusicManager::PlaysData::PlaysData() {
    minID = nullptr;
    artistsTree = AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>();
}

AVLtree<MusicManager::ArtistKey,AVLtree<MusicManager::ArtistKey,MusicManager::ArtistData>::AVLNode*> MusicManager::PlaysData::getArtistTree() const {
    return artistsTree;
}

void MusicManager::PlaysData::setMinID(AVLtree<MusicManager::ArtistKey, AVLtree<MusicManager::ArtistKey, MusicManager::ArtistData>::AVLNode *>::AVLNode *minID) {
    this->minID = minID;
}

AVLtree<MusicManager::ArtistKey,AVLtree<MusicManager::ArtistKey,MusicManager::ArtistData>::AVLNode*>::AVLNode* MusicManager::PlaysData::getMinID() {
    return minID;
}

// ---------- MusicManager implementation - private ---------- //

void MusicManager::rankZeroPlaysSongs(int currentPlace , int numOfSongs, int *artists, int *songs) {
    AVLtree<MusicManager::ArtistKey,AVLtree<MusicManager::ArtistKey,MusicManager::ArtistData>::AVLNode*>::AVLNode* currentArtistNode = songPlays.getFirst()->getData().getMinID();
    int currentZeroPlaysSongID = currentArtistNode->getData()->getData().getZeroPlays()[0][1];
    int counter = 0;
    while (counter < numOfSongs){
        while (currentZeroPlaysSongID!=NULL){
            artists[currentPlace+counter] = currentArtistNode->getKey().getArtistID();
            songs[currentPlace+counter] = currentZeroPlaysSongID;
            counter++;
            currentZeroPlaysSongID = currentArtistNode->getData()->getData().getZeroPlays()[currentZeroPlaysSongID][1];
        }
        currentArtistNode = currentArtistNode->getPrevious();
    }
}

// ---------- MusicManager implementation - public ---------- //

MusicManager::MusicManager() {
    artists = AVLtree<ArtistKey,ArtistData>();
    songPlays = List<int,PlaysData>();
    songsCounter = 0;
}

void MusicManager::addArtist(int artistID, int numOfSongs) {
    AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AVLNode* artistSave = nullptr;
    MusicManager::ArtistKey *artistKey = new MusicManager::ArtistKey(artistID);
    MusicManager::ArtistData *data = new MusicManager::ArtistData(numOfSongs);
    MusicManager::ArtistKey *key = new MusicManager::ArtistKey(artistID);
    AVLtree<ArtistKey,ArtistData>::AVLNode* artist = artists.insert(*key,*data);

    artistSave = songPlays.getFirst()->getData().getArtistTree().insert(*artistKey,artist);

    if (songPlays.getFirst()->getKey()!=0){
        songPlays.insertFirst(0,PlaysData());
        songPlays.getFirst()->getData().setMinID(artistSave);
    }
    else if (artistSave->getKey()>songPlays.getFirst()->getData().getMinID()->getKey())
        songPlays.getFirst()->getData().setMinID(artistSave);

    for (int i = 0; i < numOfSongs; ++i) {
        artist->getData().getPlaysNodes()[i]=songPlays.getFirst();
    }

    songsCounter+=numOfSongs;

    delete artistKey;
    delete data;
    delete key;
}

void MusicManager::addToSongCount(int artistID, int songID) {
    AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AVLNode* artistSave = nullptr;
    List<int,PlaysData>::ListNode* playsSave= nullptr;
    int newNumberOfPlays;

    MusicManager::ArtistKey *artistKey = new MusicManager::ArtistKey(artistID);
    AVLtree<ArtistKey,ArtistData>::AVLNode* artist = artists.find(*artistKey);
    AVLtree<SongKey,int>::AVLNode* songNode = artist->getData().getSongNodes()[songID];

    /*

    // in case the song has 0 plays
    if (songNode== nullptr){
        // creating new song node and inserting it to the artist songs tree
        newNumberOfPlays = 1;
        MusicManager::SongKey newSongKey = MusicManager::SongKey(songID,newNumberOfPlays);
        AVLtree<SongKey,int>::AVLNode* newNode = artist->getData().getSongs().insert(newSongKey,artistID);
        // updating the artist info arrays including the zeroPlays,songNodes
        artist->getData().getSongNodes()[songID] = newNode;
        artist->getData().getZeroPlays()[artist->getData().getZeroPlays()[songID][0]][1] = artist->getData().getZeroPlays()[songID][1];
        artist->getData().getZeroPlays()[artist->getData().getZeroPlays()[songID][1]][0] = artist->getData().getZeroPlays()[songID][0];
        // in case the first node of the songPlays list is not 1
        if (songPlays.getFirst()->getKey()!=1){
            // updating the artist info array PlaysNodes and the List songPlays and the minID property
            songPlays.insertFirst(1,PlaysData());
            artistSave = songPlays.getFirst()->getData().getArtistTree().insert(artistKey,artist);
            songPlays.getFirst()->getData().setMinID(artistSave);
            artist->getData().getPlaysNodes()[songID] = songPlays.getFirst();
            return;
        }
        // in case the first node of the songPlays list is 1
        // updating the artist info array PlaysNodes and the List songPlays and the minID property
        artistSave = songPlays.getFirst()->getData().getArtistTree().insert(artistKey,artist);
        if (artistSave->getKey()>songPlays.getFirst()->getData().getMinID()->getKey())
            songPlays.getFirst()->getData().setMinID(artistSave);
        artist->getData().getPlaysNodes()[songID] = songPlays.getFirst();
        return;
    }

    */

    // in case the song has 1 play or more
    // creating a new songNode with updated plays and inserting it to the artist songsTree
    newNumberOfPlays = songNode->getKey().getSongNumberOfPlays()+1;
    MusicManager::SongKey oldSongKey = MusicManager::SongKey(songID,songNode->getKey().getSongNumberOfPlays());
    artist->getData().getSongs().erase(oldSongKey);
    MusicManager::SongKey newSongKey = MusicManager::SongKey(songID,newNumberOfPlays);
    artist->getData().getSongs().insert(newSongKey,artistID);
    artist->getData().getPlaysNodes()[songID]->getData().getArtistTree().erase(*artistKey);

    // in case this is the first play of this song
    if (newNumberOfPlays == 1){
        // creating new song node and inserting it to the artist songs tree
        AVLtree<SongKey,int>::AVLNode* newNode = artist->getData().getSongs().insert(newSongKey,artistID);
        // updating the artist info arrays including the zeroPlays,songNodes
        artist->getData().getSongNodes()[songID] = newNode;
        artist->getData().getZeroPlays()[artist->getData().getZeroPlays()[songID+1][0]][1] = artist->getData().getZeroPlays()[songID+1][1];
        artist->getData().getZeroPlays()[artist->getData().getZeroPlays()[songID+1][1]][0] = artist->getData().getZeroPlays()[songID+1][0];
    }

    // updating the plays List in case the next node of the songPlays list is not the current+1
    if (artist->getData().getPlaysNodes()[songID]->getNext()->getKey()!=artist->getData().getPlaysNodes()[songID]->getKey()+1){
        playsSave = songPlays.insertAfterNode(artist->getData().getPlaysNodes()[songID]->getKey()+1,PlaysData(),artist->getData().getPlaysNodes()[songID]);
        artistSave = artist->getData().getPlaysNodes()[songID]->getNext()->getData().getArtistTree().insert(*artistKey,artist);
        artist->getData().getPlaysNodes()[songID]->getNext()->getData().setMinID(artistSave);
    }
    // updating the plays List in case the next node of the songPlays list is the current+1
    else {
        artistSave = artist->getData().getPlaysNodes()[songID]->getNext()->getData().getArtistTree().insert(*artistKey,artist);
        if (artistSave->getKey()>songPlays.getFirst()->getData().getMinID()->getKey())
            songPlays.getFirst()->getData().setMinID(artistSave);
    }
    // erasing playNode if it is empty
    if (artist->getData().getPlaysNodes()[songID]->getData().getArtistTree().getRoot()==nullptr){
        playsSave = artist->getData().getPlaysNodes()[songID]->getNext();
        songPlays.erase(artist->getData().getPlaysNodes()[songID]);
    }
    artist->getData().getPlaysNodes()[songID] = playsSave;
    // updating the artist info about the max song he has
    if (newNumberOfPlays>artist->getData().getMaxSongPlays()||
        (newNumberOfPlays==artist->getData().getMaxSongPlays() && artist->getData().getMaxSongID()>songID)){
        artist->getData().setMaxSongPlays(newNumberOfPlays);
        artist->getData().setMaxSongID(songID);
        artist->getData().setCurrentMaxNotCheckedSong(songID);
    }

    delete artistKey;
}

void MusicManager::getRecommendedSongs(int numOfSongs, int *artists, int *songs) {
    List<int,PlaysData>::ListNode* currentPlaysNode = songPlays.getLast();
    if (currentPlaysNode->getKey()==0 && numOfSongs<=songsCounter){
        rankZeroPlaysSongs(0,numOfSongs,artists,songs);
        return;
    }
    AVLtree<MusicManager::ArtistKey,AVLtree<MusicManager::ArtistKey,MusicManager::ArtistData>::AVLNode*>::AVLNode* currentArtistNode = currentPlaysNode->getData().getMinID();
    const AVLtree<SongKey,int>::AVLNode* currentSongNode = currentArtistNode->getData()->getData().getSongNodes()[currentArtistNode->getData()->getData().getCurrentMaxNotCheckedSong()];
    int counter = 0;
    if (numOfSongs<=songsCounter){
        while (counter<numOfSongs){
            if (currentSongNode->getKey().getSongNumberOfPlays()!=currentPlaysNode->getKey()){
                currentSongNode = currentArtistNode->getData()->getData().getSongNodes()[currentArtistNode->getData()->getData().getMaxSongID()];
            }
            while (counter<numOfSongs && currentSongNode->getKey().getSongNumberOfPlays()==currentPlaysNode->getKey()){
                artists[counter] = currentArtistNode->getKey().getArtistID();
                songs[counter] = currentSongNode->getKey().getSongID();
                counter++;
                currentSongNode = currentSongNode->getPrevious();
            }
            currentArtistNode->getData()->getData().setCurrentMaxNotCheckedSong(currentSongNode->getKey().getSongID());
            currentArtistNode = currentArtistNode->getPrevious();
            if (currentArtistNode== nullptr){
                currentPlaysNode = currentPlaysNode->getPrevious();
                if (currentPlaysNode->getKey()==0){
                    rankZeroPlaysSongs(counter,numOfSongs-counter,artists,songs);
                    return;
                }
                currentArtistNode = currentPlaysNode->getData().getMinID();
            }
            currentSongNode = currentArtistNode->getData()->getData().getSongNodes()[currentArtistNode->getData()->getData().getCurrentMaxNotCheckedSong()];
        }
    }
}