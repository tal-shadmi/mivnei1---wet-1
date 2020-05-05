//
// Created by Dell on 03/05/2020.
//

#ifndef AVLTREE_MUSICMANAGER_H
#define AVLTREE_MUSICMANAGER_H

#include "AVLtree.h"

typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;

class MusicManager{

    class SongKey{
        int songID;
        int songNumberOfPlays;

        public:

        SongKey()= delete;
        SongKey(int songID,int songNumberOfPlays);
        ~SongKey()= default;
        int getSongID();
        int getSongNumberOfPlays();
    };

    class ArtistKey{
        int artistID;

        public:

        ArtistKey()= delete;
        ArtistKey(int artistID);
        ~ArtistKey()= default;
        int getArtistID();
    };

    class ArtistReducedData{
        // AVLNode* artistNode; // this is problematic at the moment because we
                                // don't have access to create AVLNode pointers
        public:

        ArtistReducedData()= delete;
        // ArtistReducedData(AVLNode* artistNode);
        ~ArtistReducedData()= default;
        // AVLNode* getArtistNode();
    };

    class AVLReducedArtistsTree : public AVLtree<ArtistKey,ArtistReducedData>{

        public:

        explicit AVLReducedArtistsTree()= default;
        explicit AVLReducedArtistsTree(AVLNode* root);
        ~AVLReducedArtistsTree() override = default;
    };

    class PlaysNode{
        int numberOfPlays;
        AVLReducedArtistsTree artistsTree;
        PlaysNode* next;
        PlaysNode* previous;

        public:

        PlaysNode()= delete;
        PlaysNode(int numberOfPlays,AVLReducedArtistsTree artistTree,PlaysNode* next,
                  PlaysNode* previous);
        ~PlaysNode()= default;
    };

    class ArtistData{
        // AVLNode* songNode; // this is problematic at the moment because we
                              // don't have access to create AVLNode pointers
        PlaysNode* playsNode;
        int* zeroPlays;

        public:

        ArtistData()= delete;
        ArtistData(PlaysNode* playsNode, int numberOfSongs); // we will need to use "new"
                                                             // in the size of numberOfSongs
        ~ArtistData(); // we need to write this function ourselves and delete the array
    };

    class AVLArtistsTree : public AVLtree<ArtistKey,ArtistData>{

        public:

        explicit AVLArtistsTree()= default;
        explicit AVLArtistsTree(AVLNode* root);
        ~AVLArtistsTree() override = default;
    };

    class AVLSongsTree : public AVLtree<SongKey,int>{

        public:

        explicit AVLSongsTree()= default;
        explicit AVLSongsTree(AVLNode* root);
        ~AVLSongsTree() override = default;
    };

};

#endif //AVLTREE_MUSICMANAGER_H
