#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> load (std::string filename) {
    // {x, y, d} where d is > (1), < (2), ^ (3), v (4)
    std::vector<std::string> output = {};
    std::fstream file(filename+".txt");
    std::string line;
    int count = 1;
    if (file.is_open()) {
        while (getline(file,line)) {
            //process
            output.push_back(line);
            
        }
    }
    return output;
}

bool in (char a, std::vector<char> b) {
    for (int j = 0; j < b.size(); j++) {
        if (a == b[j]) {
            return true;
        }
    }
    return false;
}

int in_text (std::string a, int idx, std::vector<std::string> b) {
    for (int j = 0; j < b.size(); j++) {
        if (a.length()-idx >= b[j].length()) {
            if (a.substr(idx,b[j].length()) == b[j]) {
                return j;
            }
        }
    }
    return -1;
}

int process (std::vector<std::string> list) {
    int sum = 0;
    std::vector<char> nums = {'1','2','3','4','5','6','7','8','9'};
    std::vector<std::string> text_nums = {"one","two","three","four","five","six","seven","eight","nine"};
    for (int i = 0; i < list.size(); i++) {
        // first digit
        for (int o = 0; o < list[i].length(); o++) {
            if (in(list[i][o],nums)) {
                sum+= 10 * ((int)list[i][o]-48);
                break;
            } else if (in_text(list[i], o,text_nums) >= 0) {
                sum += 10*(in_text(list[i], o,text_nums)+1);
                break;
            }
        }
        // second digit
        for (int o = list[i].length()-1; o >= 0; o--) {
            if (in(list[i][o],nums)) {
                sum+= ((int)list[i][o]-48);
                break;
            } else if (in_text(list[i], o,text_nums) >= 0) {
                sum += (in_text(list[i], o,text_nums)+1);
                break;
            }
        } 
    }
    return sum;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> inputs = load("input");
    std::cout << process(inputs);


}