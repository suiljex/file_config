#include "file_config.hpp"

namespace slx
{
  Config::Config()
  {

  }

  Config::~Config()
  {

  }

  std::string Config::GetParameterValue(
      const std::string & i_section
      , const std::string & i_parameter)
  {
    if (parameters.count(i_section) == 0
        || parameters[i_section].count(i_parameter) == 0)
    {
      return std::string();
    }

    return parameters[i_section][i_parameter];
  }

  int Config::SetParameterValue(
      const std::string & i_section
      , const std::string & i_parameter
      , const std::string & i_value)
  {
    parameters[i_section][i_parameter] = i_value;
    return 0;
  }

  int Config::DelParameter(
      const std::string & i_section
      , const std::string & i_parameter)
  {
    if (parameters.count(i_section) == 0
        || parameters[i_section].count(i_parameter) == 0)
    {
      return 1;
    }

    parameters[i_section].erase(i_parameter);
    return 0;
  }

  int Config::DelSection(const std::string & i_section)
  {
    if (parameters.count(i_section) == 0)
    {
      return 1;
    }

    parameters.erase(i_section);
    return 0;
  }

  std::vector<std::string> Config::GetSectionsKeys()
  {
    std::vector<std::string> ret_vec;
    for (auto it = parameters.begin(); it != parameters.end(); ++it)
    {
      ret_vec.push_back(it->first);
    }
    return ret_vec;
  }

  std::vector<std::string> Config::GetSectionParametersKeys(const std::string & i_section)
  {
    std::vector<std::string> ret_vec;
    if (parameters.count(i_section) == 0)
    {
      return ret_vec;
    }

    for (auto it = parameters[i_section].begin(); it != parameters[i_section].end(); ++it)
    {
      ret_vec.push_back(it->first);
    }
    return ret_vec;
  }

  int Config::Load(std::istream & i_fin) //TODO Исправить парсинг
  {
    static const std::regex comment_regex{R"x(\s*[;#].*)x"};
    static const std::regex section_regex{R"x(\s*\[([^\]]+)\]\s*[;#]?.*)x"};
    static const std::regex value_regex{R"x(\s*(\S[^ \t=]*)\s*=\s*((\s?\S+)+?)\s*[;#]?.*)x"};
    std::string current_section;
    std::smatch pieces;
    for (std::string line; std::getline(i_fin, line);)
    {
      if (line.empty() || std::regex_match(line, pieces, comment_regex))
      {
        // skip comment lines and blank lines
      }
      else if (std::regex_match(line, pieces, section_regex))
      {
        if (pieces.size() == 2)
        { // exactly one match
          current_section = pieces[1].str();
        }
      }
      else if (std::regex_match(line, pieces, value_regex))
      {
        if (pieces.size() == 4)
        { // exactly enough matches
          parameters[current_section][pieces[1].str()] = pieces[2].str();
        }
      }
    }

    return 0;
  }

  int Config::FileLoad(const std::string & i_file)
  {
    std::ifstream fin(i_file);
    if (fin.is_open())
    {
      return Load(fin);
    }
    return 1;
  }

  int Config::Save(std::ostream & i_fout)
  {
    for (auto its = parameters.begin(); its != parameters.end(); ++its)
    {
      i_fout << "[" << its->first << "]" << std::endl;
      for(auto itp = its->second.begin(); itp != its->second.end(); ++itp)
      {
        i_fout << itp->first << " = " << itp->second << std::endl;
      }
    }

    return 0;
  }

  int Config::FileSave(const std::string & i_file)
  {
    std::ofstream fout(i_file);
    if (fout.is_open())
    {
      return Save(fout);
    }
    return 1;
  }

}
