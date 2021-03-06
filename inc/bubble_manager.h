/**
 * @class BubbleManager
 *
 * BubbleManager manges the bubbles, in the sense that it controls what operations are 
 * performed on the bubbles after they are constructed by the BubbleBuilder.
 *
 * @author Cole Lyman
 *
 * @date 2017/7/14
 *
 */

#ifndef BUBBLE_MANAGER
#define BUBBLE_MANAGER

#include <fstream>
#include <map>
#include <utility>

#include "bubble.h"
#include "color_manager.h"

using std::ofstream;
using std::endl;
using std::map;
using std::pair;

class BubbleManager {

    public:
        BubbleManager() { }

        BubbleManager(ofstream* bubbleFile, ofstream* matrixFile);

        /// Write the various paths of the bubble to a file in FASTA format
        void writeBubble(Bubble bubble);

        /// Count the number of shared kmers in the bubble and add it to the matrix
        void countSharedKmers(Bubble bubble, unsigned int kmerLen);

        /// Averages the sharedKmerMatrix so that the values are normalized
        /// @return the sharedKmerMatrix normalized
        map<int, map<int, float> > averageSharedKmerMatrix();

        /// Writes the sharedKmerMatrix distance matrix to the specified file in the
        /// lower triangular matrix format with the number of colors printed on the first line
        void writeSharedKmerMatrix(map<int, map<int, float> > matrix, ColorManager& colorManager);

    private:
        /// The pointer to the file handle in which the bubbles will be written to
        ofstream* bubbleFile;


        /// The point to the file handle in which the matrix will be written to
        ofstream* matrixFile;

        /** 
         * The matrix showing the similarity between colors based on shared kmers.
         * The key is a pair of ints that represent the color's ID, and the value is
         * also a pair, but of unsigned int's representing the number of shared kmers
         * between the two colors, and the number of bubbles the colors are found in.
         *
         * The number of bubbles that the colors are found in are kept so that the 
         * average number of shared kmers can more accurately be calculated.
         */
        map<pair<int, int>, pair<unsigned int, unsigned int> > sharedKmerMatrix;

        /// The number of bubbles that have been processed
        unsigned int n;

};

#endif // BUBBLE_MANAGER
