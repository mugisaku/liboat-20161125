#ifndef MG_PATTERN_DISPLAY_HPP_INCLUDED
#define MG_PATTERN_DISPLAY_HPP_INCLUDED


#include"oat.hpp"




struct PatternTable;


class
PatternDisplay: public oat::Widget
{
  const PatternTable*  bottom;
        PatternTable&     top;

  oat::Point  cursor;

  void  render_table(const PatternTable&  tbl);

public:
  PatternDisplay(PatternTable&  top_, const PatternTable*  bottom_=nullptr);

  void  process_mouse(const oat::Mouse&  mouse) override;

  void  render() override;

};





#endif




