//
// Created by Dell on 05/05/2020.
//

#define INVALID_INDEX -1

#include "MusicManager.h"

// ---------- SongKey implementation ---------- //

MusicManager::SongKey::SongKey(int songID, int songNumberOfPlays): songID(songID),songNumberOfPlays(songNumberOfPlays){}

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
    for (int i = 0; i < numberOfSongs+1; ++i) {
        delete[] zeroPlays[i];
    }
    delete[] zeroPlays;
    delete songs;
}

MusicManager::ArtistData::ArtistData(MusicManager::ArtistData &artistData) {
    numberOfSongs = artistData.numberOfSongs;
    zeroPlaysSongCounter = artistData.zeroPlaysSongCounter;
    maxSongID = artistData.maxSongID;
    maxSongPlays = artistData.maxSongPlays;
    currentMaxNotCheckedSong = artistData.currentMaxNotCheckedSong;
    songs = new AVLtree<SongKey,int>(); // this is because we will always copy an ArtistData object with an empty tree
    songNodes = new AVLtree<SongKey,int>::AVLNode*[artistData.numberOfSongs];
    playsNodes = new List<int,PlaysData>::ListNode*[artistData.numberOfSongs];
    zeroPlays = new int*[artistData.numberOfSongs+1];
    for (int i = 0; i < artistData.numberOfSongs+1; ++i) {
        if (i < numberOfSongs){
            songNodes[i]= artistData.songNodes[i];
            playsNodes[i]= artistData.playsNodes[i];
        }
        zeroPlays[i] = new int[2];
        zeroPlays[i][0] = artistData.zeroPlays[i][0];
        zeroPlays[i][1] = artistData.zeroPlays[i][1];
    }
}

AVLtree<MusicManager::SongKey,int>* &MusicManager::ArtistData::getSongs() {
    return songs;
}

AVLtree<MusicManager::SongKey,int>::AVLNode** &MusicManager::ArtistData::getSongNodes() {
    return songNodes;
}

List<int,MusicManager::PlaysData>::ListNode** &MusicManager::ArtistData::getPlaysNodes(){
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

int** &MusicManager::ArtistData::getZeroPlays(){
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

MusicManager::PlaysData::PlaysData(MusicManager::PlaysData &playsData) {
    minID = playsData.minID;
    artistsTree = new AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>();
}

AVLtree<MusicManager::ArtistKey,AVLtree<MusicManager::ArtistKey,MusicManager::ArtistData>::AVLNode*>* &MusicManager::PlaysData::getArtistTree() {
    return artistsTree;
}

void MusicManager::PlaysData::setMinID(AVLtree<MusicManager::ArtistKey, AVLtree<MusicManager::ArtistKey, MusicManager::ArtistData>::AVLNode *>::AVLNode *minID) {
    this->minID = minID;
}

AVLtree<MusicManager::ArtistKey,AVLtree<MusicManager::ArtistKey,MusicManager::ArtistData>::AVLNode*>::AVLNode* &MusicManager::PlaysData::getMinID() {
    return minID;
}

// ---------- MusicManager implementation - private ---------- //

void MusicManager::rankZeroPlaysSongs(int currentPlace , int numOfSongs, int *artists, int *songs) {
    AVLtree<MusicManager::ArtistKey,AVLtree<MusicManager::ArtistKey,MusicManager::ArtistData>::AVLNode*>::AVLNode* currentArtistNode = songPlays->getFirst()->getData().getMinID();
    int currentZeroPlaysSongID = currentArtistNode->getData()->getData().getZeroPlays()[0][1];
    int counter = 0;
    while (counter < numOfSongs){
        while (currentZeroPlaysSongID!=INVALID_INDEX && counter < numOfSongs){
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
    MusicManager::ArtistKey artistKey(artistID);
    MusicManager::ArtistData artistData(numOfSongs);
    AVLtree<ArtistKey,ArtistData>::AVLNode* artist = nullptr;
    try {
        artist = artists->insert(artistKey,artistData);
    }
    catch (AVLtree<ArtistKey,ArtistData>::AlreadyExist_AVLtree &alreadyExistAvLtree){
        return FAILURE;
    }

     MusicManager::PlaysData newPlaysData;
    int zeroPlayNodeKey=0;
    if (songPlays->getFirst()== nullptr || songPlays->getFirst()->getKey()!= 0){
        songPlays->insertFirst(zeroPlayNodeKey,newPlaysData);
        artistSave = songPlays->getFirst()->getData().getArtistTree()->insert(artistKey,artist);
        songPlays->getFirst()->getData().setMinID(artistSave);
    } else {
        artistSave = songPlays->getFirst()->getData().getArtistTree()->insert(artistKey,artist);
        if (artistSave->getKey()>songPlays->getFirst()->getData().getMinID()->getKey())
            songPlays->getFirst()->getData().setMinID(artistSave);
    }

    for (int i = 0; i < numOfSongs; ++i) {
        artist->getData().getPlaysNodes()[i]=songPlays->getFirst();
    }

    songsCounter+=numOfSongs;

    return SUCCESS;
}

StatusType MusicManager::removeArtist(int artistID){
    // get the key
    MusicManager::ArtistKey artistKey(artistID);

    // get the artist node
    AVLtree<ArtistKey,ArtistData>::AVLNode* artist;
    try {
        artist = artists->find(artistKey);
    }
    catch (AVLtree<ArtistKey,ArtistData>::NotFound_AVLtree &notFoundAvLtree){
        return FAILURE;
    }

    //get the artist's data
    MusicManager::ArtistData& data = artist->getData();

    AVLtree<SongKey,int>::AVLNode* currentSongNode = data.getSongNodes()[data.getMaxSongID()];

    if (currentSongNode == nullptr)
        songPlays->getFirst()->getData().getArtistTree()->erase(artistKey);
    else {
        int currentNumberOfPlays = -1;
        while (currentSongNode->getPrevious() != nullptr){
            if (currentNumberOfPlays != data.getPlaysNodes()[currentSongNode->getKey().getSongID()]->getKey()){
                data.getPlaysNodes()[currentSongNode->getKey().getSongID()]->getData().getArtistTree()->erase(artistKey);
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
    artists->erase(artistKey);

    return SUCCESS;
}

StatusType MusicManager::addToSongCount(int artistID, int songID) {
    AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AVLNode* artistSave = nullptr;
    AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AVLNode* previousArtistSave = nullptr;
    List<int,PlaysData>::ListNode* playsSave = nullptr;
    AVLtree<SongKey,int>::AVLNode* newSongNode = nullptr;
    int newNumberOfPlays = 0;

    MusicManager::ArtistKey artistKey(artistID);
    AVLtree<ArtistKey,ArtistData>::AVLNode* artist;
    try {
        artist = artists->find(artistKey);
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
        // updating the artist info arrays including the zeroPlays,songNodes
        MusicManager::SongKey newSongKey(songID,newNumberOfPlays);
        artist->getData().getSongNodes()[songID] = artist->getData().getSongs()->insert(newSongKey,artistID);
        newSongNode = artist->getData().getSongNodes()[songID];
        if (artist->getData().getZeroPlays()[songID+1][0]!=INVALID_INDEX)
            artist->getData().getZeroPlays()[artist->getData().getZeroPlays()[songID+1][0]][1] = artist->getData().getZeroPlays()[songID+1][1];
        if (artist->getData().getZeroPlays()[songID+1][1]!=INVALID_INDEX)
            artist->getData().getZeroPlays()[artist->getData().getZeroPlays()[songID+1][1]][0] = artist->getData().getZeroPlays()[songID+1][0];

        // checking if the first node in the songPlays list is not 1 and there are no more
        // or the first node in the songPlays list is not 1 and the second one is not 1
        if ( (songPlays->getFirst()->getKey()!=1 && songPlays->getFirst()->getNext()==nullptr ) ||
             (songPlays->getFirst()->getKey()!=1 && songPlays->getFirst()->getNext()->getKey()!=1) ){
             MusicManager::PlaysData newPlaysData;

             // inserting a new node for 1 plays and saving it (the first node is 0)
            if (songPlays->getFirst()->getKey()==0){
                playsSave = songPlays->insertAfterNode(newNumberOfPlays,newPlaysData,songPlays->getFirst());
            }

            // inserting a new node for 1 plays and saving it (the first node is 1)
            else {
                playsSave = songPlays->insertFirst(newNumberOfPlays,newPlaysData);
            }

            // inserting the artist to the artist tree of the playsNode if it is not already in there
            if ((newSongNode->getNext() == nullptr || newSongNode->getNext()->getKey().getSongNumberOfPlays()!=newSongNode->getKey().getSongNumberOfPlays() ) &&
                ( newSongNode->getPrevious() == nullptr || newSongNode->getPrevious()->getKey().getSongNumberOfPlays()!=newSongNode->getKey().getSongNumberOfPlays()))
                artistSave = playsSave->getData().getArtistTree()->insert(artistKey,artist);
        }

        // if the songPlays node for 1 plays does already exist and it is the first one on the list
        else if (songPlays->getFirst()->getKey()==1){
            if ((newSongNode->getNext() == nullptr || newSongNode->getNext()->getKey().getSongNumberOfPlays()!=newSongNode->getKey().getSongNumberOfPlays() ) &&
                ( newSongNode->getPrevious() == nullptr || newSongNode->getPrevious()->getKey().getSongNumberOfPlays()!=newSongNode->getKey().getSongNumberOfPlays())){
                artistSave = songPlays->getFirst()->getData().getArtistTree()->insert(artistKey,artist);
            }
            playsSave = songPlays->getFirst();
        }

        // if the songPlays node for 1 plays does already exist and it is the second one on the list
        else {
            if ((newSongNode->getNext() == nullptr || newSongNode->getNext()->getKey().getSongNumberOfPlays()!=newSongNode->getKey().getSongNumberOfPlays() ) &&
                ( newSongNode->getPrevious() == nullptr || newSongNode->getPrevious()->getKey().getSongNumberOfPlays()!=newSongNode->getKey().getSongNumberOfPlays())){
                artistSave = songPlays->getFirst()->getNext()->getData().getArtistTree()->insert(artistKey,artist);
            }
            playsSave = songPlays->getFirst()->getNext();
        }

        // updating the new playNode of the song if he has a new max artist in his tree
        if (playsSave!= nullptr && (playsSave->getData().getMinID()== nullptr || artist->getKey().getArtistID()>playsSave->getData().getMinID()->getKey().getArtistID()))
            playsSave->getData().setMinID(artistSave);

        // update the artist counter for songs with zero plays, if the artist has no more songs with 0 plays
        // erase the artist from the 0 plays playNode and set a new max artist for this playNode
        artist->getData().setZeroPlaysSongCounter(artist->getData().getZeroPlaysSongCounter()-1);
        if (artist->getData().getZeroPlaysSongCounter()==0){
            previousArtistSave = artist->getData().getPlaysNodes()[songID]->getData().getArtistTree()->find(artistKey)->getPrevious();
            songPlays->getFirst()->getData().getArtistTree()->erase(artistKey);
            songPlays->getFirst()->getData().setMinID(previousArtistSave);
        }
    }

    // in case the song has 1 play or more
    else {

        // erasing the artist from the artist tree in his current playNode if the artist has no more songs with the playNode number of plays
        // also updating the max artist in the current playNode
        if ((artist->getData().getSongNodes()[songID]->getPrevious()== nullptr || artist->getData().getSongNodes()[songID]->getPrevious()->getKey().getSongNumberOfPlays() != artist->getData().getSongNodes()[songID]->getKey().getSongNumberOfPlays() )&&
            (artist->getData().getSongNodes()[songID]->getNext()== nullptr || artist->getData().getSongNodes()[songID]->getNext()->getKey().getSongNumberOfPlays() != artist->getData().getSongNodes()[songID]->getKey().getSongNumberOfPlays() ) ){
            previousArtistSave = artist->getData().getPlaysNodes()[songID]->getData().getArtistTree()->find(artistKey)->getPrevious();
            artist->getData().getPlaysNodes()[songID]->getData().getArtistTree()->erase(artistKey);
            artist->getData().getPlaysNodes()[songID]->getData().setMinID(previousArtistSave);
        }

        // creating a new songNode with updated plays and inserting it to the artist songsTree
        // also updating the songNodes array
        newNumberOfPlays = songNode->getKey().getSongNumberOfPlays()+1;
        MusicManager::SongKey oldSongKey(songID,songNode->getKey().getSongNumberOfPlays());
        MusicManager::SongKey newSongKey(songID,newNumberOfPlays);
        artist->getData().getSongs()->erase(oldSongKey);
        artist->getData().getSongNodes()[songID] = artist->getData().getSongs()->insert(newSongKey,artistID);

        // updating the plays List in case the next node of the songPlays list is not the current+1
        if (artist->getData().getPlaysNodes()[songID]->getNext()== nullptr || artist->getData().getPlaysNodes()[songID]->getNext()->getKey()!=artist->getData().getPlaysNodes()[songID]->getKey()+1){
            MusicManager::PlaysData newPlaysData;
            int newPlaysNodeKey = artist->getData().getPlaysNodes()[songID]->getKey()+1;
            playsSave = songPlays->insertAfterNode(newPlaysNodeKey,newPlaysData,artist->getData().getPlaysNodes()[songID]);
            artistSave = artist->getData().getPlaysNodes()[songID]->getNext()->getData().getArtistTree()->insert(artistKey,artist);
            artist->getData().getPlaysNodes()[songID]->getNext()->getData().setMinID(artistSave);
        }

        // updating the plays List in case the next node of the songPlays list is the current+1
        else {
            playsSave = artist->getData().getPlaysNodes()[songID]->getNext();
            if ((artist->getData().getSongNodes()[songID]->getNext() == nullptr || artist->getData().getSongNodes()[songID]->getNext()->getKey().getSongNumberOfPlays()!=artist->getData().getSongNodes()[songID]->getKey().getSongNumberOfPlays() ) &&
                ( artist->getData().getSongNodes()[songID]->getPrevious() == nullptr || artist->getData().getSongNodes()[songID]->getPrevious()->getKey().getSongNumberOfPlays()!=artist->getData().getSongNodes()[songID]->getKey().getSongNumberOfPlays())){
                artistSave = artist->getData().getPlaysNodes()[songID]->getNext()->getData().getArtistTree()->insert(artistKey,artist);
                if (artistSave!= nullptr && artistSave->getKey()>artist->getData().getPlaysNodes()[songID]->getNext()->getData().getMinID()->getKey())
                    artist->getData().getPlaysNodes()[songID]->getNext()->getData().setMinID(artistSave);
            }
        }
    }

    // erasing current playNode if it is empty, if not finding a new max artist for the the current playNode
    if (artist->getData().getPlaysNodes()[songID]->getData().getArtistTree()->getRoot()==nullptr){
        //playsSave = artist->getData().getPlaysNodes()[songID]->getNext();
        songPlays->erase(artist->getData().getPlaysNodes()[songID]);
    }

    artist->getData().getPlaysNodes()[songID] = playsSave;

    // updating the artist info about the max song he has
    if (newNumberOfPlays>artist->getData().getMaxSongPlays()||
        (newNumberOfPlays==artist->getData().getMaxSongPlays() && artist->getData().getMaxSongID()>songID)){
        artist->getData().setMaxSongPlays(newNumberOfPlays);
        artist->getData().setMaxSongID(songID);
        artist->getData().setCurrentMaxNotCheckedSong(songID);
    }

    return SUCCESS;
}

StatusType MusicManager::numberOfStreams(int artistID,int songID,int *streams){
    //get the key
    MusicManager::ArtistKey artistKey(artistID);
    AVLtree<ArtistKey,ArtistData>::AVLNode* artist;
    try {
        //get the artist node
        artist = artists->find(artistKey);
    }
    catch (AVLtree<ArtistKey,ArtistData>::NotFound_AVLtree &notFoundAvLtree){
        return FAILURE;
    }
    if (songID >= artist->getData().getNumberOfSongs())
        return INVALID_INPUT;
    *streams = artist->getData().getPlaysNodes()[songID]->getKey();
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