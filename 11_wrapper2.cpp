#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <regex>

class FileWriteUtil {
public:
	void write(std::string& fileName, std::string& data){
		//执行写入
		std::ofstream osm(fileName, std::ios::out);
		if(!osm){
			throw "Write file fail..";
		}
        
        osm << data;

		osm.flush();
		osm.close();
	}
};

class FileWriteWrapper {
public:
    virtual void write(std::string& fileName, std::string& data) = 0;
};

//加密
class FileEncryWrapper {
public:
    FileEncryWrapper(FileWriteUtil* fileUtil){
        this->_fileUtil = fileUtil;
    }
    void write(std::string& fileName, std::string& data){
        //加密
        std::cout << _fileUtil << "执行加密" << std::endl;
        reverse(data.begin(), data.end());
    }
    FileWriteUtil* getFileWriteUtil() const{
        return _fileUtil;
    }
private:
    FileWriteUtil* _fileUtil;
};


//压缩
class FileCompressWrapper : public FileWriteWrapper {
public:
    //先加密-后压缩
    FileCompressWrapper(FileEncryWrapper* encryWrapper) {
        this->_encryWrapper = encryWrapper;
    }
    void write(std::string& fileName, std::string& data) {
        this->_encryWrapper->write(fileName, data);
        std::cout << "执行压缩"  << std::endl;
        data = std::regex_replace(data, std::regex("\\s+"), "");
        this->_encryWrapper->getFileWriteUtil()->write(fileName, data);
     }

private:
    FileEncryWrapper* _encryWrapper;
};

int main(){

	std::cout << "wrapper2"  << std::endl;

    std::string fileName = "hello.abc";
    std::string data = "  \n\n  line 1\nline2\nthis is wrapper pattern demo.   \n      ";
    
	FileWriteUtil fileUtil;
	fileUtil.write(fileName, data);
	
    FileEncryWrapper* encryWrapper = new FileEncryWrapper(&fileUtil);
    FileCompressWrapper* compressWrapper = new FileCompressWrapper(encryWrapper);    
    compressWrapper->write(fileName, data);

    delete encryWrapper;
    delete compressWrapper;    

	return EXIT_SUCCESS;
}
