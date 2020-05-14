//
// Created by Dell on 03/05/2020.
//

#ifndef AVLTREE_MUSICMANAGER_H
#define AVLTREE_MUSICMANAGER_H

#include "AVLtree.h"
#include "List.h"
#include "new"
#include "library1.h"

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
        SongKey(SongKey &songKey) = default;
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
            if (songKey1.songNumberOfPlays!=songKey2.songNumberOfPlays)
                return false;
            else return songKey1.songID==songKey2.songID;
        };
    };

    class ArtistKey{
        int artistID;

    public:

        ArtistKey()= delete;
        ArtistKey(ArtistKey &artistKey)= default;
        explicit ArtistKey(int artistID);
        ~ArtistKey()= default;
        int getArtistID() const;
        friend bool operator>(const ArtistKey &artistKey1, const ArtistKey &artistKey2){
            return artistKey1.artistID<artistKey2.artistID;
        };
        friend bool operator<(const ArtistKey &artistKey1, const ArtistKey &artistKey2){
            return artistKey1.artistID>artistKey2.artistID;
        };
        friend bool operator==(ArtistKey &artistKey1, ArtistKey &artistKey2){
            return artistKey1.artistID==artistKey2.artistID;
        };
    };

    class PlaysData{
        AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>* artistsTree;
        AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AVLNode* minID;

    public:

        PlaysData();
        PlaysData(PlaysData &playsData);
        ~PlaysData();
        AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>* &getArtistTree();
        void setMinID(AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AVLNode* minID);
        AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AVLNode* &getMinID ();
    };

    class ArtistData{
        int numberOfSongs;
        int zeroPlaysSongCounter;
        AVLtree<SongKey,int>* songs;
        AVLtree<SongKey,int>::AVLNode** songNodes;
        List<int,PlaysData>::ListNode** playsNodes;
        int** zeroPlays;
        int maxSongID;
        int maxSongPlays;
        int currentMaxNotCheckedSong;

    public:

        ArtistData()= delete;
        ArtistData(ArtistData &artistData);
        explicit ArtistData(int numberOfSongs);
        ~ArtistData();
        AVLtree<SongKey,int>* &getSongs();
        AVLtree<SongKey,int>::AVLNode** &getSongNodes();
        List<int,PlaysData>::ListNode** &getPlaysNodes();
        int getNumberOfSongs();
        void setZeroPlaysSongCounter(int zeroPlaysSongs);
        int getZeroPlaysSongCounter();
        int** &getZeroPlays();
        int getMaxSongID();
        int getMaxSongPlays() const;
        int getCurrentMaxNotCheckedSong();
        void setMaxSongID(int maxSongID);
        void setMaxSongPlays(int maxSongPlays);
        void setCurrentMaxNotCheckedSong(int maxNotChecked);
    };

    // ---------- Properties ---------- //

    AVLtree<ArtistKey,ArtistData>* artists;
    List<int,PlaysData>* songPlays;
    int songsCounter;

    // ---------- private functions ---------- //

    void rankZeroPlaysSongs(int currentPlace,int numOfSongs,int *artists,int *songs);

    // ---------- public functions ---------- //

public:

    MusicManager();
    ~MusicManager();
    StatusType addArtist(int artistID,int numOfSongs);
    StatusType removeArtist(int artistID);
    StatusType addToSongCount(int artistID,int songID);
    StatusType numberOfStreams(int artistID,int songID,int *streams);
    StatusType getRecommendedSongs(int numOfSongs,int *artists,int *songs);

};

#endif //AVLTREE_MUSICMANAGER_H