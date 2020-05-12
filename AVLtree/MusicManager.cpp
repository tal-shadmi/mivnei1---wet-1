//
// Created by Dell on 05/05/2020.
//

#define INVALID_INDEX -1

#include "MusicManager.h"

// ---------- SongKey implementation ---------- //

MusicManager::SongKey::SongKey(int songID, int songNumberOfPlays): songID(songID),songNumberOfPlays(songNumberOfPlays){}

MusicManager::SongKey::SongKey(MusicManager::SongKey &songKey) {
    this->songID = songKey.getSongID();
    this->songNumberOfPlays = songKey.getSongNumberOfPlays();
}

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

MusicManager::ArtistKey::ArtistKey(MusicManager::ArtistKey &artistKey) {
    this->artistID = artistKey.getArtistID();
}

// ---------- ArtistData implementation ---------- //

MusicManager::ArtistData::ArtistData(int numberOfSongs){
    this->numberOfSongs = numberOfSongs;
    zeroPlaysSongCounter = numberOfSongs;
    maxSongID = 0;
    maxSongPlays = 0;
    currentMaxNotCheckedSong = 0;
    songs = new AVLtree<SongKey,int>();
    songNodes = new AVLtree<SongKey,int>::AVLNode*[numberOfSongs];
    playsNodes = new List<int,PlaysData>::ListNode*[numberOfSongs];
    zeroPlays = new int*[numberOfSongs+1];
    for (int i = 0; i < numberOfSongs+1; ++i) {
        if (i < numberOfSongs){
            songNodes[i]= nullptr;
            playsNodes[i]= nullptr;
        }
        zeroPlays[i] = new int[2];
        if (i==0) zeroPlays[i][0]= INVALID_INDEX;
        else zeroPlays[i][0]=i-1;
        if (i==numberOfSongs) zeroPlays[i][1]= INVALID_INDEX;
        else zeroPlays[i][1]=i+1;
    }
}

MusicManager::ArtistData::~ArtistData() {
    delete[] songNodes;
    delete[] playsNodes;
    for (int i = 0; i < numberOfSongs; ++i) {
        delete[] zeroPlays[i];
    }
    delete[] zeroPlays;
    delete songs;
}

AVLtree<MusicManager::SongKey,int>* MusicManager::ArtistData::getSongs() const {
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

int MusicManager::ArtistData::getZeroPlaysSongCounter() {
    return zeroPlaysSongCounter;
}

void MusicManager::ArtistData::setZeroPlaysSongCounter(int zeroPlaysSongs) {
    zeroPlaysSongCounter = zeroPlaysSongs;
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
    artistsTree = new AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>();
}

MusicManager::PlaysData::~PlaysData() {
    delete artistsTree;
}

AVLtree<MusicManager::ArtistKey,AVLtree<MusicManager::ArtistKey,MusicManager::ArtistData>::AVLNode*>* MusicManager::PlaysData::getArtistTree() const {
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
    AVLtree<MusicManager::ArtistKey,AVLtree<MusicManager::ArtistKey,MusicManager::ArtistData>::AVLNode*>::AVLNode* currentArtistNode = songPlays->getFirst()->getData().getMinID();
    int currentZeroPlaysSongID = currentArtistNode->getData()->getData().getZeroPlays()[0][1];
    int counter = 0;
    while (counter < numOfSongs){
        while (currentZeroPlaysSongID!=INVALID_INDEX){
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
    artists = new AVLtree<ArtistKey,ArtistData>();
    songPlays = new List<int,PlaysData>();
    songsCounter = 0;
}

MusicManager::~MusicManager() {
    delete artists;
    delete songPlays;
}

StatusType MusicManager::addArtist(int artistID, int numOfSongs) {
    AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AVLNode* artistSave = nullptr;
    MusicManager::ArtistKey *artistKey = new MusicManager::ArtistKey(artistID);
    MusicManager::ArtistData *artistData = new MusicManager::ArtistData(numOfSongs);
    AVLtree<ArtistKey,ArtistData>::AVLNode* artist;
    try {
        artist = artists->insert(*artistKey,*artistData);
    }
    catch (AVLtree<ArtistKey,ArtistData>::AlreadyExist_AVLtree &alreadyExistAvLtree){
        return FAILURE;
    }

    MusicManager::PlaysData *newPlaysData = new MusicManager::PlaysData();

    int *zeroPlaysNodeKey = new int(0);
    if (songPlays->getFirst()== nullptr || songPlays->getFirst()->getKey()!= 0){
        songPlays->insertFirst(*zeroPlaysNodeKey,*newPlaysData);
        artistSave = songPlays->getFirst()->getData().getArtistTree()->insert(*artistKey,artist);
        songPlays->getFirst()->getData().setMinID(artistSave);
    } else {
        artistSave = songPlays->getFirst()->getData().getArtistTree()->insert(*artistKey,artist);
        if (artistSave->getKey()>songPlays->getFirst()->getData().getMinID()->getKey())
            songPlays->getFirst()->getData().setMinID(artistSave);
    }

    for (int i = 0; i < numOfSongs; ++i) {
        artist->getData().getPlaysNodes()[i]=songPlays->getFirst();
    }

    songsCounter+=numOfSongs;

    //delete artistKey;
    //delete artistData;

    return SUCCESS;
}

StatusType MusicManager::removeArtist(int artistID){
    // get the key
    MusicManager::ArtistKey *artistKey = new MusicManager::ArtistKey(artistID);

    // get the artist node
    AVLtree<ArtistKey,ArtistData>::AVLNode* artist;
    try {
        artist = artists->find(*artistKey);
    }
    catch (AVLtree<ArtistKey,ArtistData>::NotFound_AVLtree &notFoundAvLtree){
        return FAILURE;
    }

    //get the artist's data
    MusicManager::ArtistData& data = artist->getData();

    AVLtree<SongKey,int>::AVLNode* currentSongNode = data.getSongNodes()[data.getMaxSongID()];

    if (currentSongNode == nullptr)
        songPlays->getFirst()->getData().getArtistTree()->erase(*artistKey);
    else {
        int currentNumberOfPlays = -1;
        while (currentSongNode->getPrevious() != nullptr){
            if (currentNumberOfPlays != data.getPlaysNodes()[currentSongNode->getKey().getSongID()]->getKey()){
                data.getPlaysNodes()[currentSongNode->getKey().getSongID()]->getData().getArtistTree()->erase(*artistKey);
                // remove the playsNode if his artist Tree is empty
                if (data.getPlaysNodes()[currentSongNode->getKey().getSongID()]->getData().getArtistTree()->getRoot() == nullptr){
                    songPlays->erase(data.getPlaysNodes()[currentSongNode->getKey().getSongID()]);
                }
                currentNumberOfPlays = data.getPlaysNodes()[currentSongNode->getKey().getSongID()]->getKey();
            }
            currentSongNode = currentSongNode->getPrevious();
        }
    }
    //remove the artist from the main artists tree
    songsCounter-=artist->getData().getNumberOfSongs();
    artists->erase(*artistKey);

    //delete artistKey;

    return SUCCESS;
}

StatusType MusicManager::addToSongCount(int artistID, int songID) {
    AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AVLNode* artistSave = nullptr;
    AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AVLNode* previousArtistSave = nullptr;
    List<int,PlaysData>::ListNode* playsSave= nullptr;
    MusicManager::SongKey *oldSongKey = nullptr;
    int newNumberOfPlays = 0;

    MusicManager::ArtistKey *artistKey = new MusicManager::ArtistKey(artistID);
    AVLtree<ArtistKey,ArtistData>::AVLNode* artist;
    try {
        artist = artists->find(*artistKey);
    }
    catch (AVLtree<ArtistKey,ArtistData>::NotFound_AVLtree &notFoundAvLtree){
        return FAILURE;
    }
    if (songID >= artist->getData().getNumberOfSongs())
        return INVALID_INPUT;

    AVLtree<SongKey,int>::AVLNode* songNode = artist->getData().getSongNodes()[songID];

    // in case this is the first play of this song
    if (songNode == nullptr){
        newNumberOfPlays = 1;
        // creating new song node and inserting it to the artist songs tree
        MusicManager::SongKey *newSongKey = new MusicManager::SongKey(songID,newNumberOfPlays);
        AVLtree<SongKey,int>::AVLNode* newNode = artist->getData().getSongs()->insert(*newSongKey,artistID);
        // updating the artist info arrays including the zeroPlays,songNodes
        artist->getData().getSongNodes()[songID] = newNode;
        artist->getData().getZeroPlays()[artist->getData().getZeroPlays()[songID+1][0]][1] = artist->getData().getZeroPlays()[songID+1][1];
        artist->getData().getZeroPlays()[artist->getData().getZeroPlays()[songID+1][1]][0] = artist->getData().getZeroPlays()[songID+1][0];
        if ( (songPlays->getFirst()->getKey()!=1 && songPlays->getFirst()->getNext()==nullptr ) ||
             (songPlays->getFirst()->getKey()!=1 && songPlays->getFirst()->getNext()->getKey()!=1) ){
            MusicManager::PlaysData *newPlaysData = new MusicManager::PlaysData();
            int *newPlaysNodeKey = new int(newNumberOfPlays);
            if (songPlays->getFirst()->getKey()==0){
                playsSave = songPlays->insertAfterNode(*newPlaysNodeKey,*newPlaysData,songPlays->getFirst());
            }
            else {
                playsSave = songPlays->insertFirst(*newPlaysNodeKey,*newPlaysData);
            }
            try {
                artistSave = playsSave->getData().getArtistTree()->insert(*artistKey,artist);
            }
            catch (AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AlreadyExist_AVLtree &alreadyExistAvLtree){}
        } else if (songPlays->getFirst()->getKey()==1){
            try {
                artistSave = songPlays->getFirst()->getData().getArtistTree()->insert(*artistKey,artist);
            }
            catch (AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AlreadyExist_AVLtree &alreadyExistAvLtree){}
        } else {
            try {
                artistSave = songPlays->getFirst()->getNext()->getData().getArtistTree()->insert(*artistKey,artist);
            }
            catch (AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AlreadyExist_AVLtree &alreadyExistAvLtree){}
        }
        artist->getData().setZeroPlaysSongCounter(artist->getData().getZeroPlaysSongCounter()-1);
        if (artist->getData().getZeroPlaysSongCounter()==0){
            songPlays->getFirst()->getData().getArtistTree()->erase(*artistKey);
        }
    }
    else {
        // in case the song has 1 play or more
        // creating a new songNode with updated plays and inserting it to the artist songsTree
        newNumberOfPlays = songNode->getKey().getSongNumberOfPlays()+1;
        oldSongKey = new MusicManager::SongKey(songID,songNode->getKey().getSongNumberOfPlays());
        MusicManager::SongKey *newSongKey = new MusicManager::SongKey(songID,newNumberOfPlays);
        artist->getData().getSongs()->erase(*oldSongKey);
        artist->getData().getSongs()->insert(*newSongKey,artistID);
        previousArtistSave = artist->getData().getPlaysNodes()[songID]->getData().getArtistTree()->find(*artistKey)->getPrevious();
        artist->getData().getPlaysNodes()[songID]->getData().getArtistTree()->erase(*artistKey);

        // updating the plays List in case the next node of the songPlays list is not the current+1
        if (artist->getData().getPlaysNodes()[songID]->getNext()->getKey()!=artist->getData().getPlaysNodes()[songID]->getKey()+1){
            MusicManager::PlaysData *newPlaysData = new MusicManager::PlaysData();
            int *newPlaysNodeKey = new int(artist->getData().getPlaysNodes()[songID]->getKey()+1);
            playsSave = songPlays->insertAfterNode(*newPlaysNodeKey,*newPlaysData,artist->getData().getPlaysNodes()[songID]);
            try {
                artistSave = artist->getData().getPlaysNodes()[songID]->getNext()->getData().getArtistTree()->insert(*artistKey,artist);
            }
            catch (AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AlreadyExist_AVLtree &alreadyExistAvLtree){}
            //artist->getData().getPlaysNodes()[songID]->getNext()->getData().setMinID(artistSave);
        }

        // updating the plays List in case the next node of the songPlays list is the current+1
        else {
            try {
                artistSave = artist->getData().getPlaysNodes()[songID]->getNext()->getData().getArtistTree()->insert(*artistKey,artist);
            }
            catch (AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AlreadyExist_AVLtree &alreadyExistAvLtree){}
            if (artistSave->getKey()>songPlays->getFirst()->getData().getMinID()->getKey())
                songPlays->getFirst()->getData().setMinID(artistSave);
        }

        // erasing the artist from the artist tree in the playNode if the artist has no more songs with the playNode number of plays
        if (artist->getData().getSongNodes()[songID]->getPrevious()->getKey().getSongNumberOfPlays() != artist->getData().getSongNodes()[songID]->getKey().getSongNumberOfPlays() &&
            artist->getData().getSongNodes()[songID]->getNext()->getKey().getSongNumberOfPlays() != artist->getData().getSongNodes()[songID]->getKey().getSongNumberOfPlays()){
            artist->getData().getPlaysNodes()[songID]->getData().getArtistTree()->erase(*artistKey);
        }

    }

    // erasing playNode if it is empty
    if (artist->getData().getPlaysNodes()[songID]->getData().getArtistTree()->getRoot()==nullptr){
        playsSave = artist->getData().getPlaysNodes()[songID]->getNext();
        songPlays->erase(artist->getData().getPlaysNodes()[songID]);
    } else if (previousArtistSave!= nullptr && previousArtistSave->getKey().getArtistID()>playsSave->getData().getMinID()->getKey().getArtistID()) {
        playsSave->getData().setMinID(artistSave);
    }

    artist->getData().getPlaysNodes()[songID] = playsSave;
    // updating the artist info about the max song he has
    if (newNumberOfPlays>artist->getData().getMaxSongPlays()||
        (newNumberOfPlays==artist->getData().getMaxSongPlays() && artist->getData().getMaxSongID()>songID)){
        artist->getData().setMaxSongPlays(newNumberOfPlays);
        artist->getData().setMaxSongID(songID);
        artist->getData().setCurrentMaxNotCheckedSong(songID);
    }

    // updating the new playNode of the song if he has a new max artist in his tree
    if (playsSave->getData().getMinID()== nullptr || artist->getKey().getArtistID()>playsSave->getData().getMinID()->getKey().getArtistID())
        playsSave->getData().setMinID(artistSave);

    delete oldSongKey;
    //delete newSongKey;
    //delete artistKey;

    return SUCCESS;
}

StatusType MusicManager::numberOfStreams(int artistID,int songID,int *streams){
    //get the key
    MusicManager::ArtistKey *artistKey = new MusicManager::ArtistKey(artistID);
    AVLtree<ArtistKey,ArtistData>::AVLNode* artist;
    try {
        //get the artist node
        artist = artists->find(*artistKey);
    }
    catch (AVLtree<ArtistKey,ArtistData>::NotFound_AVLtree &notFoundAvLtree){
        return FAILURE;
    }
    if (songID >= artist->getData().getNumberOfSongs())
        return INVALID_INPUT;
    //get the artist's data
    MusicManager::ArtistData& data = artist->getData();
    //get the array of the pointers to the plays list
    List<int,PlaysData>::ListNode** playsNodes = data.getPlaysNodes();
    //get plays number node
    List<int,PlaysData>::ListNode* plays_num_node = playsNodes[songID];
    //the key is the number of plays
    *streams = plays_num_node->getKey();
    return SUCCESS;
}

StatusType MusicManager::getRecommendedSongs(int numOfSongs, int *artists, int *songs) {
    List<int,PlaysData>::ListNode* currentPlaysNode = songPlays->getLast();
    if (numOfSongs<=songsCounter){
        if (currentPlaysNode->getKey()==0){
            rankZeroPlaysSongs(0,numOfSongs,artists,songs);
            return SUCCESS;
        }
    } else return FAILURE;
    AVLtree<MusicManager::ArtistKey,AVLtree<MusicManager::ArtistKey,MusicManager::ArtistData>::AVLNode*>::AVLNode* currentArtistNode = currentPlaysNode->getData().getMinID();
    AVLtree<SongKey,int>::AVLNode* currentSongNode = currentArtistNode->getData()->getData().getSongNodes()[currentArtistNode->getData()->getData().getCurrentMaxNotCheckedSong()];
    int counter = 0;
    if (numOfSongs<=songsCounter){
        while (counter<numOfSongs){
            if (currentSongNode->getKey().getSongNumberOfPlays()!=currentPlaysNode->getKey()){
                currentSongNode = currentArtistNode->getData()->getData().getSongNodes()[currentArtistNode->getData()->getData().getMaxSongID()];
            }
            while (counter<numOfSongs && currentSongNode!= nullptr && currentSongNode->getKey().getSongNumberOfPlays()==currentPlaysNode->getKey()){
                artists[counter] = currentArtistNode->getKey().getArtistID();
                songs[counter] = currentSongNode->getKey().getSongID();
                counter++;
                currentSongNode = currentSongNode->getPrevious();
            }
            if (counter==numOfSongs)
                return SUCCESS;
            if (currentSongNode== nullptr){
                currentArtistNode->getData()->getData().setCurrentMaxNotCheckedSong(currentArtistNode->getData()->getData().getMaxSongID());
            } else {
                currentArtistNode->getData()->getData().setCurrentMaxNotCheckedSong(currentSongNode->getKey().getSongID());
            }
            currentArtistNode = currentArtistNode->getPrevious();
            if (currentArtistNode== nullptr){
                currentPlaysNode = currentPlaysNode->getPrevious();
                if (currentPlaysNode->getKey()==0){
                    rankZeroPlaysSongs(counter,numOfSongs-counter,artists,songs);
                    return SUCCESS;
                }
                currentArtistNode = currentPlaysNode->getData().getMinID();
            }
            currentSongNode = currentArtistNode->getData()->getData().getSongNodes()[currentArtistNode->getData()->getData().getCurrentMaxNotCheckedSong()];
        }
    }
    else return FAILURE;
    return SUCCESS;
}