#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
class FileReader
{
public:
  FileReader();
  ~FileReader();
  bool Open(std::string filePath, const bool& aBinary = false);
  bool Close();
  bool NextLine();
  bool Read(int& aInt);
  bool Read(float& aFloat);
  bool Read(double& aDouble);
  bool Read(std::string& aString);
  bool Read(void* aData, const int& aLength);
protected:
  FILE* myFile;
  bool myIsBinary;
  std::string myFilePath;
};

#endif // FILEREADER_H
