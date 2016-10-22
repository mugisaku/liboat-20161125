#ifndef PWG_MONITOR_HPP_INCLUDED
#define PWG_MONITOR_HPP_INCLUDED


#include"pwg/pwg_device.hpp"
#include"oat.hpp"




namespace pwg{




class
Monitor: public oat::Widget
{
  std::vector<sample_t>  wave;

public:
  Monitor();

  void  push(sample_t  v);

  void  clear();

  void  render() override;

};


}


#endif




