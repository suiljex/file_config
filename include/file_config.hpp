#ifndef FILE_CONFIG
#define FILE_CONFIG

#include <map>
#include <vector>
#include <fstream>
#include <istream>
#include <ostream>
#include <string>
#include <regex>

namespace slx
{
  class Config
  {
  public:
    Config();

    ~Config();

    std::string GetParameterValue
    (
        const std::string & i_section
      , const std::string & i_parameter
    );

    int SetParameterValue
    (
        const std::string & i_section
      , const std::string & i_parameter
      , const std::string & i_value
    );

    int DelParameter
    (
        const std::string & i_section
      , const std::string & i_parameter
    );

    int DelSection
    (
        const std::string & i_section
    );

    std::vector<std::string> GetSectionsKeys();

    std::vector<std::string> GetSectionParametersKeys
    (
        const std::string & i_section
    );

    int Load
    (
        std::istream & i_fin
    );

    int FileLoad
    (
        const std::string & i_file
    );

    int Save
    (
        std::ostream & i_fout
    );

    int FileSave
    (
        const std::string & i_file
    );

  private:
    std::map<std::string, std::map<std::string, std::string>> parameters;
  };
}

#endif //FILE_CONFIG
