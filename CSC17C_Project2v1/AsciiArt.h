// AsciiArt.h
#ifndef ASCIIART_H
#define ASCIIART_H

#include <iostream>
#include <map>
#include <string>

class AsciiArt {
public:
    void INTRO() const {
        printAsciiMap({
            {1, " WW     WWW     WW   AAA     RRRR    !!" },
            {2, "  WW   WW WW   WW   AA AA    R  RR   !!" },
            {3, "   WW WW   WW WW   AA A AA   RRRR    !!" },
            {4, "    WWW     WWW   AA     AA  R  RR     " },
            {5, "     W       W   AA       AA R   RR  !!" }
        });
    }

    void WIN() const {
        printAsciiMap({
            {1, " WW     WWW     WW IIIII NN    N" },
            {2, "  WW   WW WW   WW    I   N NN  N" },
            {3, "   WW WW   WW WW     I   N  N  N" },
            {4, "    WWW     WWW      I   N   NNN" },
            {5, "     W       W     IIIII N     N" }
        });
    }

    void LOSS() const {
        printAsciiMap({
            {1, " L     OOOO  SSSS  SSSS " },
            {2, " L     O  O  S     S    " },
            {3, " L     O  O  SSSS  SSSS " },
            {4, " L     O  O     S     S " },
            {5, " LLLL  OOOO  SSSS  SSSS " }
        });
    }
    void TWO() const {
        printAsciiMap({
            {1, "     2222"},
            {2, "        2"},
            {3, "x x  2222"},
            {4, " x   2   "},
            {5, "x x  2222"}            
        });
    }
    
    void THREE() const {
        printAsciiMap({
            {1, "     3333"},
            {2, "        3"},
            {3, "x x  3333"},
            {4, " x      3"},
            {5, "x x  3333"}            
        });
    }
    
    void FOUR() const {
        printAsciiMap({
            {1, "     4  4"},
            {2, "     4  4"},
            {3, "x x  4444"},
            {4, " x      4"},
            {5, "x x     4"}            
        });
    }

    void FIVE() const {
        printAsciiMap({
            {1, "     5555"},
            {2, "     5   "},
            {3, "x x  5555"},
            {4, " x      5"},
            {5, "x x  5555"}            
        });
    }
    
    void SIX() const {
        printAsciiMap({
            {1, "     6   "},
            {2, "     6   "},
            {3, "x x  6666"},
            {4, " x   6  6"},
            {5, "x x  6666"}            
        });
    }
        
    void SEVEN() const {
        printAsciiMap({
            {1, "     7777"},
            {2, "        7"},
            {3, "x x     7"},
            {4, " x      7"},
            {5, "x x     7"}            
        });
    }    
    
    void EXIT() const {
        printAsciiMap({
            {1, "EEEE  X   X  IIIII  TTTTT"},
            {2, "E      X X     I      T  "},
            {3, "EEE     X      I      T  "},
            {4, "E      X X     I      T  "},
            {5, "EEEE  X   X  IIIII    T  "}            
        });
    }
    
    void STAT() const {
        printAsciiMap({
            {1, "SSSSS  TTTTT      A      TTTTT  SSSSS"},
            {2, "S        T       A A       T    S    "},
            {3, "SSSSS    T      AAAAA      T    SSSSS"},
            {4, "    S    T     A     A     T        S"},
            {5, "SSSSS    T    A       A    T    SSSSS"}            
        });
    }
    
private:
    void printAsciiMap(const std::map<int, std::string>& asciiMap) const {
        for (auto it = asciiMap.cbegin(); it != asciiMap.cend(); ++it) {
            std::cout << it->second << std::endl;
        }
        std::cout << std::endl;
    }
};

#endif // ASCIIART_H