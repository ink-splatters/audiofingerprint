#include "Processor.h"

#include "gnsdk.hpp"

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
      ("settings", po::value<std::string>(&settings)->required(), "Settings file name")
      ("input", po::value<std::string>(&input)->required(), "Fingerprint File")
      ("output", po::value<std::string>(&output)->required(), "Output JSON file name")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);

    if (vm.count("help") || argc == 1)
    {
      std::cout << desc << std::endl;
      return 0;
    }

    po::notify(vm);

    AudioFingerprint::Processor processor (settings);
    
    processor.process(input, output);      
  }
  catch (gracenote::GnError& e)
  {
    std::cout << "ERROR: " << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
    return 1;
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown exception!" << std::endl;   
    return 1;
  }
  

  return 0;
}