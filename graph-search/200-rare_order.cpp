#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Letter{
    int position;
    char c;
};

bool compareLetters(Letter l1, Letter l2) { 
    return (l1.position < l2.position); 
}

void getOrder(vector<string> names, int longest){
    int length = 26;
    Letter letters[length];
    
    for (int i = 0; i < length; i++){
        char c = 'A' + i;
        letters[i] = Letter{0, c};
    }

    string s;
    char c;
    int order = 1;

    for (int i = 0; i < longest; i++){
        for (int j = 0; j < names.size(); j++){
            s = names.at(j);

            if (i < s.length()){
                c = s[i];
                int index = c - 'A';

                if (letters[index].position == 0){
                    letters[index].position = order;
                    order += 1;
                }
            }
        }
    }

    sort(letters, letters + length, compareLetters);

    for (int i = 0; i < length; i++){
        Letter l = letters[i];

        if (l.position != 0){
            cout << l.c;
        }
    }
    cout << endl;
}

int main(){
    vector<string> names;

    int longest = 0;
    string s;
    while(1){
        cin >> s;

        if (s.compare("#") == 0){
            break;
        }

        if (s.length() > longest){
            longest = s.length();
        }

        names.push_back(s);
    }

    getOrder(names, longest);

    return 0;
}