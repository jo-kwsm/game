#include <bits/stdc++.h>
using namespace std;


class reversi {
private:
  int stage[8][8];
  char change[3]={' ','o','x'};
  int idy[8]={1,1,1,0,-1,-1,-1,0};
  int idx[8]={-1,0,1,1,1,0,-1,-1};
  int turn_player=1;
  int cantPlay=0;
  string name;
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
    cout << "put your name and enter:";
    cin >> name;
  }

  pair<int,int> count() {
    pair<int,int> res={0,0};
    for(int i=0;i<8;i++) {
      for(int j=0;j<8;j++) {
        if(stage[i][j]==1) {
          res.first++;
        }
        else if(stage[i][j]==2) {
          res.second++;
        }
      }
    }
    return res;
  }

  void display() {
    pair<int,int> cnt=count();
    cout << name << ":" << cnt.first << ", com:" << cnt.second << endl;
    cout << "  | a | b | c | d | e | f | g | h |" << endl;
    for(int i=0;i<8;i++) {
      cout << "--+---+---+---+---+---+---+---+---+" << endl;
      cout << i+1 << " | ";
      for(int j=0;j<8;j++) {
        cout << change[stage[i][j]] << " | ";
      }
      cout << endl;
    }
    cout << "--+---+---+---+---+---+---+---+---+" << endl;
  }

  bool check() {
    for(int i=0;i<8;i++) {
      for(int j=0;j<8;j++) {
        if(stage[i][j]==0) return true;
      }
    }
    return false;
  }

  void search(int v) {
    candidate.clear();
    for(int i=0;i<8;i++) {
      for(int j=0;j<8;j++) {
        if(stage[i][j]) {
          continue;
        }
        if(process(i,j,v,0)) {
          candidate.push_back({i,j});
        }
      }
    }
  }

  bool process(int y, int x, int v, int reverse=1) {
    bool res=false;
    for(int i=0;i<8;i++) {
      int ny=y+idy[i];
      int nx=x+idx[i];
      if(ny>=8&&nx>=8&&nx<0&&ny<0) {
        continue;
      }
      if(stage[ny][nx]==v) {
        continue;
      }
      int f=0;
      while(ny<8&&nx<8&&nx>=0&&ny>=0&&stage[ny][nx]!=0) {
        if(stage[ny][nx]==v) {
          f=1;
          break;
        }
        ny+=idy[i];
        nx+=idx[i];
      }
      if(f) {
        while(ny!=y||nx!=x) {
          if(reverse) {
            stage[ny][nx]=v;
          }
          ny-=idy[i];
          nx-=idx[i];
        }
        if(reverse) {
          stage[ny][nx]=v;
        }
        res=true;
      }
    }
    return res;
  }

  bool com() {
    search(2);
    if(candidate.size()==0) {
      cout << "com can't play" << endl;
      cantPlay=1;
      return false;
    }
    int idx=rand()%candidate.size();
    int y=candidate[idx].first;
    int x=candidate[idx].second;
    process(y,x,2,1);
    return true;
  }

  pair<int,int> input() {
    cout << name << "'s turn:";
    while(1) {
      string hand;
      cin >> hand;
      if(hand=="win") {
        return {-1,0};
      }
      if(hand=="lose") {
        return {0,-1};
      }
      if(hand.size()!=2) {
        cout << "you should put two characters:";
        continue;
      }
      if(hand[0]>hand[1]) {
        int tmp=hand[0];
        hand[0]=hand[1];
        hand[1]=tmp;
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

  bool turn() {
    display();
    if(turn_player==1) {
      search(1);
      int f=0;
      if(candidate.size()) {
        pair<int,int> hand;
        while(1) {
          hand=input();
          if(hand.first==-1||hand.second==-1) {
            break;
          }
          for(int i=0;i<candidate.size();i++) {
            if(hand==candidate[i]) {
              f=1;
            } 
          }
          if(f) {
            break;
          }
        }
        if(f) {
          (hand.first,hand.second,1);
          cantPlay=0;
        }
        else {
          int v=1;
          if(hand.second==-1) v=2;
          for(int i=0;i<8;i++) {
            for(int j=0;j<8;j++) {
              stage[i][j]=v;
            }
          }
        }
      }
      else {
        cout << "you can't play" << endl;
        wait();
        if(cantPlay) {
          return false;
        }
        cantPlay=1;
      }
    }
    else {
      cout << "com turn" << endl;
      wait();
      if(com()) {
        cantPlay=0;
      }
      else {
        if(cantPlay) {
          return false;
        }
        else {
          cantPlay=1;
        }
      }
    }
    turn_player=3-turn_player;
    return true;
  }

  void endhing() {
    pair<int,int> cnt=count();
    if(cnt.first>cnt.second) {
      cout << name << " win" << endl;
    }
    else if(cnt.first<cnt.second) {
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
      if(!turn()) {
        break;
      }
    }
    display();
    endhing();
  }
};

int main() {
  reversi game;
  game.play();
  cout << "end" << endl;
}