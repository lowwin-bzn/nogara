#ifndef NOGARA_SOUND_RESOURCE_HPP
#define NOGARA_SOUND_RESOURCE_HPP

///////////////////////////////////////////
//! @file  nogara/sound/sound_resource.hpp
//! @brief OpenALのバッファ管理オブジェクト
///////////////////////////////////////////
#include <cstdio>
#include <vector>
#include <nogara/nogara_define.hpp>
#include <nogara/typedef.hpp>
#include <boost/utility/enable_if.hpp>

__NOGARA_BEGIN

//! @brief PCMフォーマット
struct format_chank{
    static uint_t const LINEAR_PCM_FORMAT = 1;
    uint16_t id;
    uint16_t channel;
    uint32_t sample_rate;
    uint32_t byte_per_sec;
    uint16_t block_size;
    uint16_t bit_per_sample;
};

//! @brief ファイルからRCMフォーマット、データを読み取る
template<class Format>
class sound_resource{
public:
    //! @brief 音声データのロード
    bool load(char const* filename){
        return Format::load(filename, chank, data);
    }

    //! @brief 音声データのロード
    bool load(std::string const& filename){
        return load(filename.c_str());
    }

    template<class T>
    typename boost::enable_if_c<(sizeof(T) == 1), bool>::type
    load_from_data(std::vector<T> const& from_data){
        return Format::load_from_data(from_data, chank, data);
    }

    //! @brief 音声ファイルのチャンネル数
    uint32_t channel()      const {return chank.channel;}
    //! @brief サンプリングレート
    uint32_t sample_rate()  const {return chank.sample_rate;}
    //! @brief 秒間のデータ速度
    uint32_t byte_per_sec() const {return chank.byte_per_sec;}
    //! @brief ブロックサイズ
    uint32_t block_size()   const {return chank.block_size;}
    //! @brief サンプルあたりのビット数
    uint32_t bits()         const {return chank.bit_per_sample;}
    //! @brief データのサイズ
    uint32_t data_size()    const {return data.size();}

    //! @brief データの先頭
    char const* data_front() const {return &data.front();}

private:
    format_chank      chank;
    std::vector<char> data;
};

__NOGARA_END

#endif
