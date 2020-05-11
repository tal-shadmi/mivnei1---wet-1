//
// Created by Dell on 05/05/2020.
//

#include "MusicManager.h"

// ---------- SongKey implementation ---------- //

MusicManager::SongKey::SongKey(int songID, int songNumberOfPlays):
                               songID(songID),songNumberOfPlays(songNumberOfPlays){}

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
        if (i==0) zeroPlays[i][0]= (int)NULL;
        else zeroPlays[i][0]=i-1;
        if (i==numberOfSongs-1) zeroPlays[i][0]= (int)NULL;
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
        while (currentZeroPlaysSongID!=(int)NULL){
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
    MusicManager::ArtistData *data = new MusicManager::ArtistData(numOfSongs);
    MusicManager::ArtistKey *key = new MusicManager::ArtistKey(artistID);
    AVLtree<ArtistKey,ArtistData>::AVLNode* artist = artists->insert(*key,*data);

    artistSave = songPlays->getFirst()->getData().getArtistTree()->insert(*artistKey,artist);

    if (songPlays->getFirst()->getKey()!=0){
        songPlays->insertFirst(0,PlaysData());
        songPlays->getFirst()->getData().setMinID(artistSave);
    }
    else if (artistSave->getKey()>songPlays->getFirst()->getData().getMinID()->getKey())
        songPlays->getFirst()->getData().setMinID(artistSave);

    for (int i = 0; i < numOfSongs; ++i) {
        artist->getData().getPlaysNodes()[i]=songPlays->getFirst();
    }

    songsCounter+=numOfSongs;

    delete artistKey;
    delete data;
    delete key;

    return SUCCESS;
}

StatusType MusicManager::removeArtist(int artistID){
    // get the key
    MusicManager::ArtistKey *artistKey = new MusicManager::ArtistKey(artistID);
    // get the artist node
    AVLtree<ArtistKey,ArtistData>::AVLNode* artist = artists->find(*artistKey);
    //get the artist's data
    MusicManager::ArtistData& data = artist->getData();

    //------------------------- tal edit - begin -----------------------------//

    AVLtree<SongKey,int>::AVLNode* currentSongNode = data.getSongNodes()[data.getMaxSongID()];
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
    //remove the artist from the main artists tree
    artists->erase(*artistKey);

    delete artistKey;

    //------------------------- tal edit - end -------------------------------//

    //get the array of the pointers to the plays list
    List<int,PlaysData>::ListNode** playsNodes = data.getPlaysNodes();
    int songs_num = data.getNumberOfSongs();
    for(int i=0;i<songs_num;i++){
        List<int,PlaysData>::ListNode* current = playsNodes[i];
        AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*> tree = *(current->getData().getArtistTree());
        try {
            //remove the artist from the current plays tree
            tree.erase(*artistKey);
        }
        //handle the exception so we continue run
        catch (NotFound& e){
        }
    }
    //remove the artist from the main artists tree
    artists->erase(*artistKey);

    delete artistKey;

    return SUCCESS;
}

int MusicManager::numberOfStreams(int artistID,int songID){
    //get the key
    MusicManager::ArtistKey *artistKey = new MusicManager::ArtistKey(artistID);
    //get the artist node
    AVLtree<ArtistKey,ArtistData>::AVLNode* artist = artists->find(*artistKey);
    //get the artist's data
    MusicManager::ArtistData& data = artist->getData();
    //get the array of the pointers to the plays list
    List<int,PlaysData>::ListNode** playsNodes = data.getPlaysNodes();
    //get plays number node
    List<int,PlaysData>::ListNode* plays_num_node = playsNodes[songID];
    //the key is the number of plays
    return plays_num_node->getKey();
}

StatusType MusicManager::addToSongCount(int artistID, int songID) {
    AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AVLNode* artistSave = nullptr;
    List<int,PlaysData>::ListNode* playsSave= nullptr;
    int newNumberOfPlays;

    MusicManager::ArtistKey *artistKey = new MusicManager::ArtistKey(artistID);
    AVLtree<ArtistKey,ArtistData>::AVLNode* artist = artists->find(*artistKey);
    AVLtree<SongKey,int>::AVLNode* songNode = artist->getData().getSongNodes()[songID];

    // in case the song has 1 play or more
    // creating a new songNode with updated plays and inserting it to the artist songsTree
    newNumberOfPlays = songNode->getKey().getSongNumberOfPlays()+1;
    MusicManager::SongKey *oldSongKey = new MusicManager::SongKey(songID,songNode->getKey().getSongNumberOfPlays());
    artist->getData().getSongs()->erase(*oldSongKey);
    MusicManager::SongKey *newSongKey = new MusicManager::SongKey(songID,newNumberOfPlays);
    artist->getData().getSongs()->insert(*newSongKey,artistID);
    artist->getData().getPlaysNodes()[songID]->getData().getArtistTree()->erase(*artistKey);

    // in case this is the first play of this song
    if (newNumberOfPlays == 1){
        // creating new song node and inserting it to the artist songs tree
        AVLtree<SongKey,int>::AVLNode* newNode = artist->getData().getSongs()->insert(*newSongKey,artistID);
        // updating the artist info arrays including the zeroPlays,songNodes
        artist->getData().getSongNodes()[songID] = newNode;
        artist->getData().getZeroPlays()[artist->getData().getZeroPlays()[songID+1][0]][1] = artist->getData().getZeroPlays()[songID+1][1];
        artist->getData().getZeroPlays()[artist->getData().getZeroPlays()[songID+1][1]][0] = artist->getData().getZeroPlays()[songID+1][0];
    }

    // updating the plays List in case the next node of the songPlays list is not the current+1
    if (artist->getData().getPlaysNodes()[songID]->getNext()->getKey()!=artist->getData().getPlaysNodes()[songID]->getKey()+1){
        playsSave = songPlays->insertAfterNode(artist->getData().getPlaysNodes()[songID]->getKey()+1,PlaysData(),artist->getData().getPlaysNodes()[songID]);
        artistSave = artist->getData().getPlaysNodes()[songID]->getNext()->getData().getArtistTree()->insert(*artistKey,artist);
        artist->getData().getPlaysNodes()[songID]->getNext()->getData().setMinID(artistSave);
    }
    // updating the plays List in case the next node of the songPlays list is the current+1
    else {
        artistSave = artist->getData().getPlaysNodes()[songID]->getNext()->getData().getArtistTree()->insert(*artistKey,artist);
        if (artistSave->getKey()>songPlays->getFirst()->getData().getMinID()->getKey())
            songPlays->getFirst()->getData().setMinID(artistSave);
    }

    // erasing the artist from the artist tree in the playNode if the artist has no more songs with the playNode number of plays
    if (artist->getData().getSongNodes()[songID]->getPrevious()->getKey().getSongNumberOfPlays() != artist->getData().getSongNodes()[songID]->getKey().getSongNumberOfPlays() &&
        artist->getData().getSongNodes()[songID]->getNext()->getKey().getSongNumberOfPlays() != artist->getData().getSongNodes()[songID]->getKey().getSongNumberOfPlays()){
        artist->getData().getPlaysNodes()[songID]->getData().getArtistTree()->erase(*artistKey);
    }

    // erasing playNode if it is empty
    if (artist->getData().getPlaysNodes()[songID]->getData().getArtistTree()->getRoot()==nullptr){
        playsSave = artist->getData().getPlaysNodes()[songID]->getNext();
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

    delete oldSongKey;
    delete newSongKey;
    delete artistKey;

    return SUCCESS;
}

StatusType MusicManager::getRecommendedSongs(int numOfSongs, int *artists, int *songs) {
    List<int,PlaysData>::ListNode* currentPlaysNode = songPlays->getLast();
    if (currentPlaysNode->getKey()==0 && numOfSongs<=songsCounter){
        rankZeroPlaysSongs(0,numOfSongs,artists,songs);
        return SUCCESS;
    }
    AVLtree<MusicManager::ArtistKey,AVLtree<MusicManager::ArtistKey,MusicManager::ArtistData>::AVLNode*>::AVLNode* currentArtistNode = currentPlaysNode->getData().getMinID();
    AVLtree<SongKey,int>::AVLNode* currentSongNode = currentArtistNode->getData()->getData().getSongNodes()[currentArtistNode->getData()->getData().getCurrentMaxNotCheckedSong()];
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
                    return SUCCESS;
                }
                currentArtistNode = currentPlaysNode->getData().getMinID();
            }
            currentSongNode = currentArtistNode->getData()->getData().getSongNodes()[currentArtistNode->getData()->getData().getCurrentMaxNotCheckedSong()];
        }
    }
    return SUCCESS;
}