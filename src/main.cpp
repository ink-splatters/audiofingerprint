#include "Processor.h"

#include <iostream>
#include <boost/program_options.hpp>

int main (int argc, char* argv[])
{
  namespace po = boost::program_options;

  po::options_description desc("General options");
  
  try
  {
    std::string settings, input, output;

    desc.add_options()
      ("help,h", "Show help")
      ("settings,s", po::value<std::string>(&settings), "Settings file name")
      ("input,i", po::value<std::string>(&input), "Fingerprint File")
      ("output,o", po::value<std::string>(&output), "Output JSON file name")
    ;

    // AudioFingerprint::Processor processor (settings);
    
    // processor.process(input, output);  

    po::variables_map vm;
    const auto & parsed = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
    po::store(parsed, vm) ;
    po::notify(vm);
    std::cout << "test" << std::endl;
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "Unknown exception!" << std::endl;   
  }
  

  return 0;
}