#include <bits/stdc++.h>
using namespace std;



class reversi {
private:
  int stage[8][8];
  char change[3]={' ','o','x'};
  int turn_player=1;
  vector<pair<int,int>> candidate;
public:
  void init() {
    for(int i=0;i<8;i++) {
      for(int j=0;j<8;j++) {
        int v=0;
        if(i==j&&(i==3||i==4)) {
          v=1;
        }
        if(i*j==12&&(i==3||i==4)) {
          v=2;
        }
        stage[i][j]=v;
      }
    }
  }

  void wait() {
    cout << "push any buttn and enter:";
    string s;
    cin >> s;
  }

  void opening() {
    cout << "---------------" << endl;
    cout << "----reversi----" << endl;
    cout << "---------------" << endl;
    wait();
  }

  void display() {
    cout << " a|b|c|d|e|f|g|h" << endl;
    for(int i=0;i<8;i++) {
      cout << i;
      for(int j=0;j<8;j++) {
        if(j) cout << "|";
        cout << change[stage[i][j]];
      }
      cout << endl;
    }
  }

  bool check() {
    for(int i=0;i<8;i++) {
      for(int j=0;j<8;j++) {
        if(stage[i][j]==0) return true;
      }
    }
    return false;
  }

  void search() {
    candidate.clear();
    for(int i=0;i<8;i++) {
      for(int j=0;j<8;j++) {

      }
    }
  }

  void process(int y, int x) {

  }

  void com() {
    search();
    if(candidate.size()==0) {
      cout << "com can't play" << endl;
      return;
    }
    int idx=rand()%candidate.size();
    int y=candidate[idx].first;
    int x=candidate[idx].second;
    process(y,x);
  }

  pair<int,int> input() {
    cout << "your turn:";
    while(1) {
      string hand;
      cin >> hand;
      if(hand.size()!=2) {
        cout << "you should put two characters:";
        continue;
      }
      int y=hand[0]-'1';
      int x=hand[1]-'a';
      if(x<0||x>7||y<0||y>7) {
        cout << "you should put one number and one alphabet:";
        continue;
      }
      return {y,x};
    }
  }

  void turn() {
    display();
    if(turn_player==1) {
      search();
      pair<int,int> hand=input();

    }
    else {
      cout << "com turn" << endl;
      wait();
      com();
    }
    turn_player=3-turn_player;
  }

  int count() {
    int res=0;
    for(int i=0;i<8;i++) {
      for(int j=0;j<8;j++) {
        if(stage[i][j]==1) {
          res++;
        }
        else if(stage[i][j]==2) {
          res--;
        }
      }
    }
    return res;
  }

  void endhing() {
    int cnt=count();
    if(cnt>0) {
      cout << "player win" << endl;
    }
    else if(cnt<0) {
      cout << "com win" << endl;
    }
    else {
      cout << "draw" << endl;
    }
  }

  void play() {
    init();
    opening();
    while(check()) {
      turn();
    }
    endhing();
  }
};

int main() {
  reversi game;
  game.play();
  cout << "end" << endl;
}