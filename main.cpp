#include "dgnlibp.h"
#include "stdio.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <filesystem>
#include <sys/types.h>
#include <dirent.h>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <sstream>
#include <string>


static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
}

static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

typedef std::vector<std::string> stringvec;

bool isdgn(std::string str) {
    if (str.length() < 4) return false;
    return str.substr(str.length() - 4) == ".dgn";
}

void read_directory(const std::string &name, stringvec &v) {
    DIR *dirp = opendir(name.c_str());
    struct dirent *dp;
    while ((dp = readdir(dirp)) != nullptr) {
        std::string test = (std::string(dp->d_name));
        trim(test);
        if (!test.empty() && test.length() > 3 && isdgn(test)) {
            v.push_back(test);
        }
    }
    closedir(dirp);
}


int main(int argc, char **argv) {


    stringvec v;
    std::string dir = "/home/anton/ClionProjects/dgscrawler/resource/dgn";
    read_directory(dir, v);

    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << "Öffne Datei: [" << *it << "]" << '\n';
        const char *filename = (*it).c_str();

        std::stringstream ss;
        ss << dir << "/" << filename;
        std::string fullpath_pp = ss.str();

        std::string dateiname = std::string(filename);


        DGNHandle hDGN;
        DGNElemCore *psElement;
        char achRaw[128];
        double dfSFXMin = 0.0, dfSFXMax = 0.0, dfSFYMin = 0.0, dfSFYMax = 0.0;
        memset(achRaw, 0, 128);

        hDGN = DGNOpen(fullpath_pp.c_str(), FALSE);
        if (hDGN == nullptr) {
            std::cout << "Fehler bei " << fullpath_pp;
            continue;
        } else {


            DGNSetSpatialFilter(hDGN, dfSFXMin, dfSFYMin, dfSFXMax, dfSFYMax);
            while ((psElement = DGNReadElement(hDGN)) != nullptr) {
                if (17 == psElement->type) {
                    DGNElemText *psText = (DGNElemText *) psElement;
                    std::string textinhalt = std::string(psText->string);
                    trim(textinhalt);
                    if (textinhalt.length() > 2)
                        std::cout << "Datei: " << dateiname << " Textinhalt: " << textinhalt << '\n';
                    //DGNDumpElement(hDGN, psElement, stdout);
                }
                DGNFreeElement(hDGN, psElement);
            }

            DGNClose(hDGN);
        }
    }

    return 0;
}

