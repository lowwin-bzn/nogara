#ifndef NOGARA_FILE_COVER_HPP
#define NOGARA_FILE_COVER_HPP

/////////////////////////////////////////////////////////////
//! @file nogara/file_cover.hpp
//! @brief ファイルから読み取られたデータのバッファクラスなど
/////////////////////////////////////////////////////////////

#include <cstdio>
#include <fstream>
#include <vector>
#include <string>
#include <nogara/nogara_define.hpp>
#include <nogara/smart_ptr.hpp>

__NOGARA_BEGIN

//! @brief smart_ptrに指定するファイル開放関数オブジェクト
struct file_releaser{
    void operator ()(std::FILE* fp){fclose(fp);}
};

//! @brief 例外安全性を高めたファイルポインタ
typedef smart_ptr::unique_ptr<std::FILE, file_releaser> file_ptr;

//////////////////////////////////////////////////////////////////////
//! @brief Visual Studio2005以降のfopen_sとfopenを一元化するための関数
//////////////////////////////////////////////////////////////////////
inline std::FILE* fopen(char const* filename, char const* flag){
#if defined(NG_MSC) && NG_MSC_VER >= 1400
    std::FILE *fp = NULL;
    if(::fopen_s(&fp, filename, flag) != 0){
        return NULL;
    }
    return fp;
#else
    return std::fopen(filename, flag);
#endif
}

//! @brief ファイルポインタを生成する
inline file_ptr make_file_ptr(char const* filename, char const* flag){
    return file_ptr(nogara::fopen(filename, flag));
}

/////////////////////////////////////////////////////////
//! @brief ファイルのデータを全て読み取り、保持するクラス
/////////////////////////////////////////////////////////
class file_data{
    typedef void (file_data::*bool_type)() const;
    void bool_checker() const {}
public:
    typedef std::vector<char> data_type;

    //! @brief コンストラクタ
    //! @param filename ファイル名
	file_data(char const* filename):success(false){load_data(filename);}
    //! @brief コンストラクタ
    //! @param filename ファイル名
    file_data(std::string const& filename):success(false){load_data(filename.c_str());}
    //! @brief データ参照
    data_type&       data()       {return data_;}
    //! @brief データ参照
    data_type const& data() const {return data_;}
    //! @brief データの先頭ポインタ
	char*         pointer()       {return &data_[0];}
    //! @brief データの先頭ポインタ
	char const*   pointer() const {return &data_[0];}
    //! @brief データのサイズ
    std::size_t      size() const {return data_.size();}

    //! @brief 成功か否かを通知する
    operator bool_type() const {return success ? &file_data::bool_checker : 0;}
    //! @brief 読み取り失敗を通知する
    bool fail() const {return !success;}
    //! @brief 読み取り失敗を通知する
    bool operator !()    const {return fail();}
    //! @brief データのイテレータ先頭
    data_type::iterator       begin()       {return data_.begin();}
    //! @brief データのイテレータ先頭
    data_type::const_iterator begin() const {return data_.begin();}
    //! @brief データのイテレータ末尾
    data_type::iterator       end()         {return data_.end();}
    //! @brief データのイテレータ末尾
    data_type::const_iterator end()   const {return data_.end();}

private:
    //! @brief データ読み込み機構
	void load_data(const char *filename){
        std::ifstream ifs(filename, std::ios::binary);
        if(!ifs){
            return;
        }

        ifs.seekg(0, std::ifstream::end);
        data_.resize(ifs.tellg());
        ifs.seekg(0, std::ifstream::beg);
        ifs.read(&data_[0], data_.size());
        success = true;
    }

private:
    data_type data_;
    bool success;
};

__NOGARA_END

#endif
