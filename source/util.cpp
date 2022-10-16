//******************************************************************************
/*! @file       util.cpp
    @brief      Source definition for utilities
*/
//******************************************************************************
#include "util.hpp"
#if defined(WORK_AROUND_STRDUP)
#include <string.h>
#include <stdlib.h>
#endif // WORK_AROUND_STRDUP

//******************************************************************************
//               Private macros
//******************************************************************************

/* size of direction to string objects list */
#define DIRECTION_COVERTER_SIZE ((sizeof(s_directionConverter))/\
                                    (sizeof(s_directionConverter[0])))

//******************************************************************************
//               Private type definition
//******************************************************************************

/*
* @brief direction to string converter object
*/
typedef struct {
    CDirection directionVal;
    std::string directionName;
}stDirectionConverter;

/*
* @brief direction to string objects list
*/
static stDirectionConverter s_directionConverter[] = {
    { CDirection::NORTH, "NORTH" },
    { CDirection::EAST, "EAST" },
    { CDirection::SOUTH, "SOUTH" },
    { CDirection::WEST, "WEST" },
};

//******************************************************************************
//               public function definition
//******************************************************************************

void SplitString(std::string str, char delimiter, std::vector<std::string>& dest)
{
    size_t pos = 0;
    std::string token;
    while (std::string::npos != (pos = str.find(delimiter))) {
        token = str.substr(0, pos);
        dest.push_back(token);
        str.erase(0, pos + 1);
    }
    if (0 < str.length())
    {
        dest.push_back(str);
    }
}

bool StringToDirection(std::string directionName, CDirection* direction) {
    bool valid = false;
    unsigned int i = 0U;
    stDirectionConverter curr;
    while (DIRECTION_COVERTER_SIZE > i) {
        curr = s_directionConverter[i];
        if (curr.directionName == directionName) {
            (*direction) = curr.directionVal;
            valid = true;
            break;
        }
        i++;
    }
    return valid;
}

std::string DirectionToString(CDirection directionVal) {
    std::string directionName = "";
    unsigned int i = 0U;
    stDirectionConverter curr;
    while (DIRECTION_COVERTER_SIZE > i ) {
        curr = s_directionConverter[i];
        if (curr.directionVal == directionVal) {
            directionName = curr.directionName;
            break;
        }
        i++;
    }
    return directionName;
}

#if defined(WORK_AROUND_STRDUP)
char* wa_strdup(const char* s)
{
    size_t slen = strlen(s);
    char* result = (char*)malloc(slen + 1);
    if (result == NULL)
    {
        return NULL;
    }

    memcpy(result, s, slen + 1);
    return result;
}
#endif // WORK_AROUND_STRDUP
