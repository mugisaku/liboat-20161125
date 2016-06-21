#ifndef OAT_TEXT_HPP
#define OAT_TEXT_HPP


#include"oat_widget.hpp"
#include<string>


namespace oat{


class
Text: public Widget
{
public:
  using Callback = void  (*)(Text&  txt);

protected:
  std::string        string;
  std::u16string  u16string;

  Callback  callback;

public:
  Text(const std::string&     s);
  Text(const std::u16string&  s);


  void  change_string(const std::string&     s);
  void  change_string(const std::u16string&  s);

  const std::string&     get_string() const;
  const std::u16string&  get_u16string() const;

  void  render() override;
  
};


}




#endif




