#include "parcer.h"

namespace s21 {

bool ReadOne::Search(std::string file_name, DataModel *data_model) {
  bool res = true;
  std::ifstream fp(file_name);
  if (fp.is_open()) {
    std::string str = "";
    while (std::getline(fp, str)) {
      if (str[0] == 'v' && str[1] == ' ') {
        data_model->count_vertex += 3;
      }
      if (str[0] == 'f' && str[1] == ' ') {
        data_model->count_edges++;
        data_model->count_facets += getCountMemory(str);
      }
    }
    fp.close();
  } else {
    res = false;
  }
  if ((!data_model->count_vertex) || (!data_model->count_edges)) {
    res = false;
  }
  return res;
};

unsigned int ReadOne::getCountMemory(std::string &str) {
  unsigned int res = 0;
  for (size_t i = 0; i <= str.size(); ++i) {
    if (str[i] >= '0' && str[i] <= '9') {
      if ((str[i - 1] == ' ') || ((str[i - 1] == '-') && (str[i - 2] == ' '))) {
        res++;
      }
    }
  }
  return res;
}

bool ReadTwo::Search(std::string file_name, DataModel *data_model) {
  bool res = true;
  std::ifstream fp(file_name);
  std::string str = "";
  while (std::getline(fp, str)) {
    if (((str[0] == 'v') || (str[0] == 'f')) && (str[1] == ' ')) {
      res = getDigit(str, data_model);
    }
    if (res == false) {
      return res;
    }
  }
  fp.close();
  if ((data_model->facets.empty()) || (data_model->vertexes.empty())) {
    res = false;
  }

  return res;
}

bool ReadTwo::getDigit(std::string &str, DataModel *data_model) {
  bool res = true;
  std::stringstream ss(str);
  std::string buffer;
  if (str[0] == 'v') {
    int count = 0;
    while ((std::getline(ss, buffer, ' ')) && (count < 3)) {
      if ((isdigit(buffer[0]) || (isdigit(buffer[1])))) {
        data_model->vertexes.push_back(stof(buffer));
        count++;
      }
    }
  }
  if (str[0] == 'f') {
    int step = 0;
    unsigned int first_element = 0;
    while ((std::getline(ss, buffer, ' ')) && (res)) {
      if ((isdigit(buffer[0]) || (isdigit(buffer[1])))) {
        res = PushToFacets(buffer, first_element, step, data_model);
      }
      if (res == false) {
        return res;
      }
    }

    if (step && res) {
      data_model->facets.push_back(first_element - 1);
    }
  }
  return res;
}

bool ReadTwo::PushToFacets(std::string &str, unsigned int &first_element,
                           int &step, DataModel *data_model) {
  bool res = true;
  double x = 0;
  if (!str.empty()) {
    x = stof(str);
    if (x < 0) {
      return false;
    }
    if (step == 0) {
      step = 1;
      first_element = x;
      data_model->facets.push_back(first_element - 1);
    } else {
      data_model->facets.push_back(x - 1);
      data_model->facets.push_back(x - 1);
    }
  }
  return res;
}

Parser::~Parser() { delete read_; }

void Parser::setStrategy(Read *read) {
  if (read_ != nullptr) {
    delete read_;
  }
  read_ = read;
}

bool Parser::ReadFile(std::string name_file, DataModel *data_model) {
  bool flag = read_->Search(name_file, data_model);
  return flag;
}
}  // namespace s21
