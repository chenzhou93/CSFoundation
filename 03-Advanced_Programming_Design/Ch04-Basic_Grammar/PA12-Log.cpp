#include <iostream>
#include <string>
using namespace std;

class Log{//设置Log类
    private:
    int currentLevel;//存储log的错误比较结果
    public:
    static string errorLevel;//设置错误级别，静态变量
    void set_level(string error);//设置错误级别
    Log& operator<< (int levelNum);//重载<<，根据比较结果决定是否输出
    ostream& operator<<(string s){//支持字符串输入
        if(currentLevel){
            cout << s;
        }
        return cout;
    }
};

string Log::errorLevel = "";

void Log::set_level(string error){
    errorLevel = error;
}

int level(string error){
    if(error == "fatal"){
        return 1;
    }else if(error == "error"){
        if(Log::errorLevel == "warning"){
            return 1;
        }else{
            return 0;
        }
    }
    return 0;
}

Log& Log::operator<< (int levelNum){
    this->currentLevel = levelNum;
	return *this;
}

int main(){
    Log obj;
    obj << "debug message" << endl;
    obj.set_level("error");
    
    obj << level("warning") << "WARNING MESSAGE" << endl;
    obj << level("fatal") << "BROKEN" << endl;

    return 0;
}