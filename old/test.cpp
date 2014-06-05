#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>

using namespace std;

string encode(string s)
{
  for(int i = 0; i < s.size(); i++)
    if(s[i] == ' ')
      s[i] == '_';
  return s;
}
string decode(string s)
{
  for(int i = 0; i < s.size(); i++)
    if(s[i] == '_')
      s[i] == ' ';
  return s;
}

int version;
map<string, string> dict;
void load()
{
  ifstream fin("version.txt");
  string s;
  fin >> s;
  version = atoi(s.c_str());
  fin.close();
  ifstream fin2((s + ".txt").c_str());
  string word, def;
  while(fin2 >> word >> def)
    dict[encode(word)] = encode(def);
  fin2.close();
}
void save()
{
  ofstream fout("version.txt");
  fout << version;
  fout.close();
  for(map<string, string>::iterator it = dict.begin(); it != dict.end(); it++)
    cout << encode(it->first) << ' ' << encode(dict[it->second]) << endl;
}

int main()
{
  while(1)
  {
    cout << "press i to insert, l to lookup, d to delete, q to quit\n";
    string c, s, t;
    getline(cin, c);
    switch(c[0])
    {
      case 'i':
        getline(cin, s);
        getline(cin, t);
        dict[s] = t;
        cout << "inserted\n";
      break;
      case 'l':
        getline(cin, s);
        if(dict.find(s) != dict.end())
          cout << dict[s] << endl;
        else
          cout << "not found\n";
      break;
      case 'd':
        getline(cin, s);
        if(dict.find(s) != dict.end())
        {
          dict.erase(s);
          cout << "deleted\n";
        }
        else
          cout << "not found\n";
      break;
      case 'q':
        version++; // new version
        save();
        cout << "saved to version" << version << endl;
      return 0;
      break;
    }
  }
  return 0;
}
