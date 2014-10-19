#ifndef LISTEXCEPTION_H
#define LISTEXCEPTION_H
 
class ListException {
 public:
 	ListException(std::string &reason){ _reason = reason;}
 	std::string getReason(){ return _reason;}
 	
 private:
  std::string _reason;
};
 
#endif

