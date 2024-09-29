#include "matchingbracketpractice.h"

MatchingBracket::MatchingBracket() : str(nullptr) {}

MatchingBracket& MatchingBracket::get() { return minstance; }

const void MatchingBracket::setString(std::string* strbrackets) {
  this->str = strbrackets;
  this->map = {{')','('},{']','['},{'}','{'}};
}

void MatchingBracket::match() {
  for(char& c: *(this->str)) {
    std::cout << c << ' ';
    if (c == '[' or c == '{' or c == '(') { this->stck.push(c); }
    else if (this->stck.size() > 0) {
      if (c == ')' or c == ']' or c == '}') {
        if (this->stck.top() == this->map[c]) {
          this->stck.pop(); continue;
        } else {
          this->imBalanced(c); return;
        }
      }
    } else { this->imBalanced(c); return; }
  }

  if (this->stck.size() == 0) { this->balanced(); } 
  else { this->imBalanced(this->stck.top()); }
}

const void MatchingBracket::balanced() const {
  std::cout << "\nString of brackets is balanced." << std::endl;
}

const void MatchingBracket::imBalanced(char& c) const {
  std::cout << "\nString of brackets is imbalanced at : " << c << std::endl;
}

MatchingBracket MatchingBracket::minstance;

// Alternate solution for line 18 to 22
    //  if (c == ']') {
    //    if (this->stck.top() == '[') {
    //      this->stck.pop(); continue;
    //    } else {
    //      this->imBalanced( c ); return;
    //    }
    //  } else if (c == '}') {
    //    if (this->stck.top() == '{') {
    //      this->stck.pop(); continue;
    //    } else {
    //      this->imBalanced( c ); return;
    //    }
    //  } else if (c == ')') {
    //    if (this->stck.top() == '(') {
    //      this->stck.pop(); continue;
    //    } else {
    //      this->imBalanced( c ); return;
    //    }
    //  }