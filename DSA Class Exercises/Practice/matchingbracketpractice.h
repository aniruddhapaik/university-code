#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

class MatchingBracket {
public:
  static MatchingBracket& get();
  const void setString(std::string*);
  void match();

private:
  MatchingBracket();
  MatchingBracket(const MatchingBracket&) = delete;
  MatchingBracket& operator=(const MatchingBracket&) = delete;
  const void balanced() const;
  const void imBalanced(char&) const;

private:
  std::string* str;
  std::unordered_map<char,char> map;
  std::stack<char> stck;
  static MatchingBracket minstance;
};

