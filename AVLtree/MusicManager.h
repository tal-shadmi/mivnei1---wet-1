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
    class ArtistReducedData;
    class PlaysData;

    class SongKey{
        int songID;
        int songNumberOfPlays;

        public:

        SongKey()= delete;
        SongKey(int songID,int songNumberOfPlays);
        ~SongKey()= default;
        int getSongID();
        int getSongNumberOfPlays();
        friend bool operator<(SongKey &songKey1,SongKey &songKey2){
            if (songKey1.songNumberOfPlays<songKey2.songNumberOfPlays) return true;
            if (songKey1.songNumberOfPlays>songKey2.songNumberOfPlays) return false;
            else return songKey1.songID>songKey2.songID;
        };
    };

    class ArtistKey{
        int artistID;

        public:

        ArtistKey()= delete;
        explicit ArtistKey(int artistID);
        ~ArtistKey()= default;
        int getArtistID();
        friend bool operator<(ArtistKey &artistKey1,ArtistKey &artistKey2){
            return artistKey1.artistID<artistKey2.artistID;
        };
    };

    class PlaysData{
        AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*> artistsTree;
        PlaysData* next;
        PlaysData* previous;

    public:

        PlaysData()= delete;
        PlaysData(AVLtree<ArtistKey,ArtistReducedData> artistTree,PlaysData* next,
                  PlaysData* previous);
        ~PlaysData()= default;
    };

    class ArtistData{
        int numberOfSongs;
        AVLtree<SongKey,int> songs;
        AVLtree<SongKey,int>::AVLNode** songNodes;
        PlaysData** playsNodes;
        int** zeroPlays;

    public:

        ArtistData()= delete;
        explicit ArtistData(int numberOfSongs);
        ~ArtistData();
    };

    /*
    class ArtistReducedData{
         AVLtree<ArtistKey,ArtistData>::AVLNode* artistNode;
    public:

        ArtistReducedData()= delete;
        explicit ArtistReducedData(AVLtree<ArtistKey,ArtistData>::AVLNode* artistNode);
        ~ArtistReducedData()= default;
        const AVLtree<ArtistKey,ArtistData>::AVLNode& getArtistNode();
    };
    */

    // ---------- Properties ---------- //

    AVLtree<ArtistKey,ArtistData> artists;
    List<int,PlaysData> songPlays;

    // ---------- Functions ---------- //

    MusicManager();
    ~MusicManager();
    void addArtist(int artistID,int numOfSongs);
    void removeArtist(int artistID);
    void addToSongCount(int artistID,int songID);
    int numberOfStreams(int artistID,int songID);
    void getRecommendedSongs(int numOfSongs,int *artists,int *songs);

};

#endif //AVLTREE_MUSICMANAGER_H
