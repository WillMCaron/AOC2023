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

std::vector<std::string> split(std::vector<std::string> arg, std::string item) {
    int idx_start = 0;
    int idx_end = 0;
    std::vector<std::string> output = {};
    for (int i = 0; i < item.length(); i++) {
        if (item[i] == arg[0][0] or item[i] == arg[1][0]) {
            idx_end = i;
            output.push_back(item.substr(idx_start, idx_end-idx_start));
            idx_start = i+2;
        }
    }
    output.push_back(item.substr(idx_start, item.length()-idx_start));
    return output;
}

bool in(std::string a, int idx, std::vector<std::string> b) {
    for (int j = 0; j < b.size(); j++) {
        if (a.length()-idx >= b[j].length()) {
            if (a.substr(idx,b[j].length()) == b[j]) {
                return true;
            }
        }
    }
    return false;
}

int process (std::vector<std::string> list) {
    int sum = 0;
    std::string item = "";
    // rgb
    std::vector<int> colors = {0,0,0};

    // remove game number, irrelavant
    for (int p = 0; p < list.size(); p++) {
        colors = {0,0,0};
        for (int u = 0; u < list[p].size(); u++) {
            if (list[p][u] == ':') {
                item = list[p].substr(u+2,list[p].length()-u-2);
                break;
            }
        }
        //std::cout << item << "\n";
        //item = list[p].substr(8,list[p].length()-8);
        std::vector<std::string> temp = split({";",","},item);
        for (int i = 0; i < temp.size(); i++) {
            if (in(temp[i],temp[i].length()-3,{"red"})) {
                if (colors[0]<std::stoi(temp[i].substr(0,temp[i].length()-4))) {
                    colors[0] = std::stoi(temp[i].substr(0,temp[i].length()-4));
                }
            } else if (in(temp[i],temp[i].length()-4,{"blue"})) {
                if (colors[2]<std::stoi(temp[i].substr(0,temp[i].length()-5))) {
                    colors[2] = std::stoi(temp[i].substr(0,temp[i].length()-5));
                }

            } else if (in(temp[i],temp[i].length()-5,{"green"})) {
                if (colors[1]<std::stoi(temp[i].substr(0,temp[i].length()-6))) {
                    colors[1] = std::stoi(temp[i].substr(0,temp[i].length()-6));
                }
            }
        }
        //std::cout << colors[0] << " " << colors[1] << " " << colors[2] << "\n";
        if (colors[0] <= 12 && colors[1] <=13 && colors[2] <= 14) {
            sum +=p+1;
            std::cout << colors[0] << " " << colors[1] << " " << colors[2] << " | " << p+1 << "\n";
        }
    }
    // separate instances per game
    return sum;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> inputs = load("input");
    std::cout << process(inputs);


}