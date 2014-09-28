#include "FileReader.h"

FileReader::FileReader()
{
  myFile = NULL;
}


FileReader::~FileReader()
{
  myFile = NULL;
}


/**
* Open given file.
* @param filePath Path to the file to read.
* @param aBinary If the reader should read binary data or not, defaults to false.
* @return True on success else false.
*/
bool FileReader::Open(std::string filePath, const bool& aBinary)
{
  myIsBinary = aBinary;
  myFilePath = filePath;
  if (myFile != NULL) {
    if (!Close()) {
      return false;
    }
  }
  std::string flags = "r";
  if (myIsBinary) {
    flags += "b";
  }
  fopen_s(&myFile, filePath.c_str(), flags.c_str());
  if (myFile == NULL) {
    return false;
  }
  return true;
}


/**
* Close the reader.
* @return True on success else false.
*/
bool FileReader::Close()
{
  if (myFile == NULL) { // Already closed.
    return true;
  }
  if (fclose(myFile) != 0) {
    return false;
  }
  myFile = NULL;
  return true;
}

/**
* Move to next line
* @return True on success else false.
*/
bool FileReader::NextLine()
{
  unsigned char input;
  // NL 10 || 13.
  do {
    if (fread(&input, 1, 1, myFile) != 1) {
      return false;
    }
  } while (input != 13 && input != 10);
  return true;
}


/**
* Read int value from file.
* @param aInt Int to read the data to.
* @return True on success else false.
*/
bool FileReader::Read(int& aInt)
{
  std::string buffer = "";
  unsigned char input;
  for (;;) {
    if (fread(&input, 1, 1, myFile) != 1) {
      return false;
    }
    if (isdigit(input) || input == '-') {
      buffer += input;
    } else {
      aInt = atoi(buffer.c_str());
      return true;
    }
  }
}


/**
* Read float value from file.
* @param aFloat Float to read the data to.
* @return True on success else false.
*/
bool FileReader::Read(float& aFloat)
{
  std::string buffer = "";
  unsigned char input;
  for (;;){
    if (fread(&input, 1, 1, myFile) != 1) {
      return false;
    }
    if (isdigit(input) || input == '-' || input == '.') {
      buffer += input;
    } else {
      aFloat = static_cast<float>(atof(buffer.c_str()));
      return true;
    }
  }
}


/**
* Read double value from file.
* @param aDouble Double to read the data to.
* @return True on success else false.
*/
bool FileReader::Read(double& aDouble)
{
  return false;
}


/**
* Read string value from file.
* @param aString String to read the data to.
* @return True on success else false.
*/
bool FileReader::Read(std::string& aString)
{
  return false;
}

/**
* Read data from file.
* @param aData Date to read to.
* @param aLength Length to read.
* @return True on success else false.
*/
bool FileReader::Read(void* aData, const int& aLength)
{
  return false;
}
