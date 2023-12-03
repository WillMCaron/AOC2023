#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> load (std::string filename) {
    std::vector<std::string> output = {};
    std::fstream file(filename+".txt");
    std::string line;
    if (file.is_open()) {
        while (getline(file,line)) {
            //process
            output.push_back(line);
            
        }
    }
    return output;
}

bool in(char a, std::vector<char> b) {
    for (int j = 0; j < b.size(); j++) {
        if (a == b[j]) {
            return true;
        }
    }
    return false;
}

int process (std::vector<std::string> list) {
    int sum = 0;
    std::vector<char> nums = {'0','1','2','3','4','5','6','7','8','9'};
    std::string part = "";
    for (int i = 0; i < list.size(); i++) {
        for (int o = 0; o < list[i].length(); o++) {
            part = "";
            // if part number
            if (in(list[i][o],nums)) {
                // guaranteed at start
                // get the part number (and length)
                while (in(list[i][o],nums)) {
                    part+=list[i][o];
                    o++;
                }
                // check for symbols (o-length of parts)
                // left + diagonals
                if (o-part.length() > 0) {
                    // left
                    if (!in(list[i][o-part.length()-1],nums) && list[i][o-part.length()-1] != '.') {
                        sum += std::stoi(part);
                        continue;
                    }
                    // upper diagonal
                    if (i > 0 && !in(list[i-1][o-part.length()-1],nums) && list[i-1][o-part.length()-1] != '.') {
                        sum+= std::stoi(part);
                        continue;
                    }
                    // lower diagonal
                    if (i < list.size()-1 && !in(list[i+1][o-part.length()-1],nums) && list[i+1][o-part.length()-1] != '.') {
                        sum+= std::stoi(part);
                        continue;
                    }
                    
                }
                // right + diagonals
                if (o < list[i].length()-1) {
                    // lright
                    if (!in(list[i][o],nums) && list[i][o] != '.') {
                        sum += std::stoi(part);
                        continue;
                    }
                    // upper diagonal
                    if (i > 0 && !in(list[i-1][o],nums) && list[i-1][o] != '.') {
                        sum+= std::stoi(part);
                        continue;
                    }
                    // lower diagonal
                     if (i < list.size()-1 && !in(list[i+1][o],nums) && list[i+1][o] != '.') {
                        sum+= std::stoi(part);
                        continue;
                    }
                }
                // top
                if (i > 0) {
                    for (int j = 1; j <= part.length(); j++) {
                        if (list[i-1][o-j] != '.' && !in(list[i-1][o-j],nums)) {
                            sum+= std::stoi(part);
                            continue;
                        }
                    }
                }
                // bottom
                if (i < list[i].length()-1) {
                    for (int j = 1; j <= part.length(); j++) {
                        if (list[i+1][o-j] != '.' && !in(list[i+1][o-j],nums)) {
                            sum+= std::stoi(part);
                            continue;
                        }
                    }
                }
            }
        }
    }
    return sum;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> inputs = load("input");
    std::cout << process(inputs);


}