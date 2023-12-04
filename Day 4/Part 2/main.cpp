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

std::vector<std::string> split(std::string arg, std::string item) {
    int idx_start = 0;
    int idx_end = 0;
    std::vector<std::string> output = {};
    for (int i = 0; i < item.length(); i++) {
        if (item[i] == arg[0]) {
            idx_end = i;
            output.push_back(item.substr(idx_start, idx_end-idx_start));
            idx_start = i+2;
        }
    }
    output.push_back(item.substr(idx_start, item.length()-idx_start));
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
    std::vector<std::string> win_nums = {};
    std::vector<std::string> user_nums = {};
    std::vector<int> copies = {};
    for (int h = 0; h < list.size(); h++) {
        copies.push_back(0);
    }
    std::string game;
    std::string temp;
    std::string temp2;
    int score;
    for (int i = 0; i < list.size(); i++) {
        score = 0;
        game = "";
        win_nums = {};
        user_nums = {};
        // remove game header
        game = split(":",list[i])[1];
        // split off into winning and user numbers
        
        // win nums first
        temp = split("|",game)[0];
        for (int o = 0; o < temp.length(); o++) {
            temp2 = "";
            while (in(temp[o],nums)) {
                temp2 += temp[o];
                o++;
            }
            if (temp2 != "") {
                win_nums.push_back(temp2);
            }
        }

        // user nums
        temp = split("|",game)[1];
        for (int o = 0; o < temp.length(); o++) {
            temp2 = "";
            while (in(temp[o],nums)) {
                temp2 += temp[o];
                o++;
            }
            user_nums.push_back(temp2);
        }

        // compare
        // copies
        int ct;
        for (int f = 0; f < copies[i]+1; f++) {
            ct = 0;
            // actual check of nums
            for (int k = 0; k < win_nums.size(); k++) {
                for (int j = 0; j < user_nums.size(); j++) {
                    if (win_nums[k] == user_nums[j]) {
                        ct++;
                        if (ct < list.size()-1) {
                            copies[i+ct]++;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < copies.size(); i++) {
        //std::cout << copies[i] << "\n";
        sum+=copies[i];
    }
    return sum+copies.size();
}

int main(int argc, char *argv[]) {
    std::vector<std::string> inputs = load("input");
    std::cout << process(inputs);


}