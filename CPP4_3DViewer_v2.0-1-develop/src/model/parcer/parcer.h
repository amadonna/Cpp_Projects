#ifndef CPP4_3DVIEWER_V2_0_1_SRC_MODEL_PARCER_PARCER_H_
#define CPP4_3DVIEWER_V2_0_1_SRC_MODEL_PARCER_PARCER_H_

#include <fstream>
#include <sstream>
#include <string>

#include "../data/data_model.h"
namespace s21 {
class Read {
 public:
  virtual ~Read(){};
  virtual bool Search(std::string name_file, DataModel *data_model) = 0;
};

class ReadOne : public Read {
 public:
  bool Search(std::string name_file, DataModel *data_model) override;
  unsigned int getCountMemory(std::string &str);
};

class ReadTwo : public Read {
 public:
  bool Search(std::string name_file, DataModel *data_model) override;
  bool getDigit(std::string &str, DataModel *data_model);
  bool PushToFacets(std::string &str, unsigned int &first_element, int &step,
                    DataModel *data_model);
};

class Parser {
 public:
  Parser(Read *read) : read_(read){};
  ~Parser();
  void setStrategy(Read *read);
  bool ReadFile(std::string name_file, DataModel *data_model);

 private:
  Read *read_;
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODEL_PARCER_PARCER_H_
