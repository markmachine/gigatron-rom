#ifndef LOADER_H
#define LOADER_H


#include <vector>

#include "timing.h"


#define PAYLOAD_SIZE              60
#define SEGMENT_SIZE              255
#define SEGMENT_HEADER_SIZE       3
#define GT1FILE_TRAILER_SIZE      3
#define DEFAULT_START_ADDRESS_HI  0x02
#define DEFAULT_START_ADDRESS_LO  0x00

#define HIGH_SCORES_INI  "high_scores.ini"


namespace Loader
{
    struct Gt1Segment
    {
        bool _isRomAddress = false;
        uint8_t _hiAddress;
        uint8_t _loAddress;
        uint8_t _segmentSize;
        std::vector<uint8_t> _dataBytes;
    }; 

    struct Gt1File
    {
        std::vector<Gt1Segment> _segments;
        uint8_t _terminator=0;
        uint8_t _hiStart=DEFAULT_START_ADDRESS_HI;
        uint8_t _loStart=DEFAULT_START_ADDRESS_LO;
    };


    bool loadGt1File(const std::string& filename, Gt1File& gt1File);
    bool saveGt1File(const std::string& filepath, Gt1File& gt1File, std::string& filename);
    uint16_t printGt1Stats(const std::string& filename, const Gt1File& gt1File);


#ifndef STAND_ALONE
    enum Endianness {Little, Big};

    struct SaveData
    {
        bool _initialised = false;
        int _updaterate = VSYNC_RATE;
        std::string _filename;

        std::vector<uint16_t> _counts;
        std::vector<uint16_t> _addresses;
        std::vector<Endianness> _endianness;
        std::vector<std::vector<uint8_t>> _data;
    };


    void initialise(void);

    bool getStartUploading(void);
    void setStartUploading(bool start);
    void disableUploads(bool disable);

    bool loadDataFile(SaveData& saveData);
    bool saveDataFile(const SaveData& saveData);
    void loadHighScore(void);
    void saveHighScore(void);
    void updateHighScore(void);

    void upload(int vgaY);
#endif
}

#endif
