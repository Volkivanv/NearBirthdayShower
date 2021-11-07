#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>

struct friendBirthday{
    std::string name;
    std::time_t bd;
};

void inputFriend(friendBirthday& fb, std::string friendName){
    //std::cout<<"Input name of friend: ";
    fb.name = friendName;
    fb.bd = std::time(nullptr);
    std::tm local = *std::localtime(&fb.bd);
    std::cout<<"Input his/her birthday in fmt Y/m/d"<<std::endl;
    std::cin >> std::get_time(&local, "%Y/%m/%d");
    fb.bd = mktime(&local);
}

void outputFriend(friendBirthday& fb){
    std::tm local = *std::localtime(&fb.bd);
    std::cout << fb.name<<"  "<< std::put_time(&local,"%Y/%m/%d")<<std::endl;
}

int main() {
    std::vector<friendBirthday> friendBirthdays;
    std::string request;
    std::cout<<"Input name of your friend"<<std::endl;
    std::cin >> request;
    while(request!="end"){
        friendBirthday fb;
        inputFriend(fb,request);
        friendBirthdays.push_back(fb);
        std::cout<<"Input name of your friend"<<std::endl;
        std::cin >> request;
    }
    std::time_t tNow = std::time(nullptr);
    std::tm local = *std::localtime(&tNow);
    int  nearest = 366;
    for(int i = 0; i < friendBirthdays.size();i++){
        std::tm localBD = *std::localtime(&friendBirthdays[i].bd);
        if(local.tm_yday<=localBD.tm_yday){
          //  outputFriend(friendBirthdays[i]);
            nearest = (localBD.tm_yday - local.tm_yday < nearest? localBD.tm_yday - local.tm_yday : nearest );
          //  std::cout<<nearest;
        }

    }

    for(int i = 0; i < friendBirthdays.size();i++){
        std::tm localBD = *std::localtime(&friendBirthdays[i].bd);
        if(abs(localBD.tm_yday - local.tm_yday) == nearest){
            outputFriend(friendBirthdays[i]);
        }

    }

    return 0;
}
