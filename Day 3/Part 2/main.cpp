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
    std::vector<int> gears = {};
    int temp;
    for (int i = 0; i < list.size(); i++) {
        for (int o = 0; o < list[i].length(); o++) {
            // if symbol
            if (!in(list[i][o],nums) and list[i][o]!='.') {
                gears = {};
                // check for part numbers
                if (i > 0) {
                    // top
                    if (in(list[i-1][o],nums)) {
                        temp = o;
                        part = "";
                        while (in(list[i-1][temp],nums)) {
                            part = list[i-1][temp] + part;
                            temp--;
                        }
                        temp = o+1;
                        while (in(list[i-1][temp],nums)) {
                            part += list[i-1][temp];
                            temp++;
                        }
                        gears.push_back(std::stoi(part));
                    } else {
                        // top left
                        if (o > 0 && in(list[i-1][o-1],nums)) {
                            temp = o-1;
                            part = "";
                            while (in(list[i-1][temp],nums)) {
                                part = list[i-1][temp] + part;
                                temp--;
                            }
                            gears.push_back(std::stoi(part));
                        } 
                        // top right
                        if (o < list[i].length()-1 && in(list[i-1][o+1],nums)) {
                                temp = o+1;
                                part = "";
                                while (in(list[i-1][temp],nums)) {
                                    part += list[i-1][temp];
                                    temp++;
                                }
                                gears.push_back(std::stoi(part));
                        }
                    }
                    
                } 
                    
                    
                if (i < list.size()-1) {
                    if (in(list[i+1][o],nums)) {
                        temp = o;
                        part = "";
                        while (in(list[i+1][temp],nums)) {
                            part = list[i+1][temp] + part;
                            temp--;
                        }
                        temp = o+1;
                        while (in(list[i+1][temp],nums)) {
                            part += list[i+1][temp];
                            temp++;
                        }
                        gears.push_back(std::stoi(part));
                    } else {
                        if (o > 0 && in(list[i+1][o-1],nums)) {
                            temp = o-1;
                            part = "";
                            while (in(list[i+1][temp],nums)) {
                                part = list[i+1][temp] + part;
                                temp--;
                            }
                            gears.push_back(std::stoi(part));
                        } if (o < list[i].length()-1 && in(list[i+1][o+1],nums)) {
                            temp = o+1;
                            part = "";
                            while (in(list[i+1][temp],nums)) {
                                part += list[i+1][temp];
                                temp++;
                            }
                            gears.push_back(std::stoi(part));
                        }
                    }
                
                } 
                
                // left
                if (o > 0) {
                    if (in(list[i][o-1],nums)) {
                        part = "";
                        temp = o-1;
                        while (in(list[i][temp],nums)) {
                            part = list[i][temp] + part;
                            temp--;
                        }
                        gears.push_back(std::stoi(part));
                    }
                    }
                // right
                if (o < list[i].length()-1) {
                    if (in(list[i][o+1],nums)) {
                        temp = o+1;
                        part = "";
                        while (in(list[i][temp],nums)) {
                            part += list[i][temp];
                            temp++;
                        }
                        gears.push_back(std::stoi(part));
                    }
                    // lower diagonal
                }

                if (list[i][o] == '*' && gears.size() == 2) {
                    sum += gears[0]*gears[1];
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