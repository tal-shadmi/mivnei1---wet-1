//
// Created by Dell on 03/05/2020.
//

#ifndef AVLTREE_MUSICMANAGER_H
#define AVLTREE_MUSICMANAGER_H

#include "AVLtree.h"
#include "List.h"

typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;

class MusicManager{

    // ---------- Subclasses ---------- //

    class SongKey;
    class ArtistKey;
    class ArtistData;
    class PlaysData;

    class SongKey{
        int songID;
        int songNumberOfPlays;

        public:

        SongKey()= delete;
        SongKey(int songID,int songNumberOfPlays);
        ~SongKey()= default;
        int getSongID() const;
        int getSongNumberOfPlays() const;
        friend bool operator>(const SongKey &songKey1, const SongKey &songKey2){
            if (songKey1.songNumberOfPlays>songKey2.songNumberOfPlays) return true;
            if (songKey1.songNumberOfPlays<songKey2.songNumberOfPlays) return false;
            else return songKey1.songID<songKey2.songID;
        };
        friend bool operator<(const SongKey &songKey1, const SongKey &songKey2){
            if (songKey1.songNumberOfPlays<songKey2.songNumberOfPlays) return true;
            if (songKey1.songNumberOfPlays>songKey2.songNumberOfPlays) return false;
            else return songKey1.songID>songKey2.songID;
        };
        friend bool operator==(SongKey &songKey1,SongKey &songKey2){
            return songKey1.songNumberOfPlays==songKey2.songNumberOfPlays;
        };
    };

    class ArtistKey{
        int artistID;

        public:

        ArtistKey()= delete;
        explicit ArtistKey(int artistID);
        ~ArtistKey()= default;
        int getArtistID() const;
        friend bool operator>(const ArtistKey &artistKey1, const ArtistKey &artistKey2){
            return artistKey1.artistID<artistKey2.artistID;
        };
        friend bool operator<(const ArtistKey &artistKey1, const ArtistKey &artistKey2){
            return artistKey1.artistID>artistKey2.artistID;
        };
        friend bool operator==(ArtistKey &artistKey1,ArtistKey &artistKey2){
            return artistKey1.artistID==artistKey2.artistID;
        };
    };

    class PlaysData{
        AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*> artistsTree;
        AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AVLNode* minID;

    public:

        PlaysData();
        ~PlaysData()= default;
        AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*> getArtistTree() const;
        void setMinID(AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AVLNode* minID);
        AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AVLNode* getMinID ();
    };

    class ArtistData{
        int numberOfSongs;
        AVLtree<SongKey,int> songs;
        AVLtree<SongKey,int>::AVLNode** songNodes;
        List<int,PlaysData>::ListNode** playsNodes;
        int** zeroPlays;
        int maxSongID;
        int maxSongPlays;
        int currentMaxNotCheckedSong;

    public:

        ArtistData()= delete;
        explicit ArtistData(int numberOfSongs);
        ~ArtistData();
        AVLtree<SongKey,int> getSongs() const ;
        AVLtree<SongKey,int>::AVLNode** getSongNodes() const ;
        List<int,PlaysData>::ListNode** getPlaysNodes() const ;
        int** getZeroPlays() const ;
        int getMaxSongID();
        int getMaxSongPlays() const;
        int getCurrentMaxNotCheckedSong();
        void setMaxSongID(int maxSongID);
        void setMaxSongPlays(int maxSongPlays);
        void setCurrentMaxNotCheckedSong(int maxNotChecked);
    };

    // ---------- Properties ---------- //

    AVLtree<ArtistKey,ArtistData> artists;
    List<int,PlaysData> songPlays;
    int songsCounter;

    // ---------- private functions ---------- //



    // ---------- public functions ---------- //

    public:

    MusicManager();
    ~MusicManager();
    void addArtist(int artistID,int numOfSongs);
    void removeArtist(int artistID);
    void addToSongCount(int artistID,int songID);
    int numberOfStreams(int artistID,int songID);
    void getRecommendedSongs(int numOfSongs,int *artists,int *songs);

};

#endif //AVLTREE_MUSICMANAGER_H
