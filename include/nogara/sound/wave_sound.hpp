#ifndef NOGARA_WAVE_SOUND_HPP
#define NOGARA_WAVE_SOUND_HPP

///////////////////////////////////////
//! @file  nogara/sound/wave_sound.hpp
//! @brief Wave音源を取り扱うクラス
///////////////////////////////////////

#include <nogara/sound/sound_resource.hpp>
#include <string>

__NOGARA_BEGIN

#define CHAR_TO_INT32(a, b, c, d) ((d << 24) | (c << 16) | (b << 8) | a)

//! @brief waveフォーマット
class wave_format{
public:
    //! @brief waveのロード
    static bool load(char const* filename, format_chank& chank, std::vector<char>& data){
        std::FILE* fp = std::fopen(filename, "rb");
        if(fp == NULL){
            return false;
        }

        uint32_t const riff = read_to_int<uint32_t>(fp);
        if(riff != CHAR_TO_INT32('R', 'I', 'F', 'F')){
            return fail_close(fp);
        }
        uint32_t const file_size = read_to_int<uint32_t>(fp); int x = file_size; x = 0;
        uint32_t const wave = read_to_int<uint32_t>(fp);
        if(wave != CHAR_TO_INT32('W', 'A', 'V', 'E')){
            return fail_close(fp);
        }
        
        char buffer[0xFFFF];
        while(!std::feof(fp)){
            uint32_t const chank_type = read_to_int<uint32_t>(fp);
            uint32_t const chank_size = read_to_int<uint32_t>(fp);
 
             switch(chank_type){
                case CHAR_TO_INT32('f', 'm', 't', ' '):{
                    fread(&chank, sizeof(chank), 1, fp);
                    if(chank_size > sizeof(chank)){
                        fread(buffer, 1, chank_size - sizeof(chank), fp);
                    }
                } break;
                case CHAR_TO_INT32('d', 'a', 't', 'a'):{
                    data.reserve(chank_size);
                    uint32_t count = 0;
                    while(count < chank_size){
                        uint32_t read_count = fread(buffer, 1, sizeof(buffer), fp);
                        data.insert(data.end(), buffer, buffer + read_count);
                        count += read_count;
                    }
                } break;
                default:{
                    uint32_t count = 0;
                    uint32_t const read_bytes = (sizeof(buffer) < chank_size) ? sizeof(buffer) : chank_size;
                    while(count < chank_size){
                        count += fread(buffer, 1, read_bytes, fp);
                    }
                } break;
             }
        }
        std::fclose(fp);
        return true;
    }

    //
    template<class T>
    static typename boost::enable_if_c<(sizeof(T) == 1), bool>::type
    load_from_data(std::vector<T> const& from_data, format_chank& chank, std::vector<char>& data){
        typedef std::vector<T> vector;
        typedef typename vector::const_iterator const_iterator;
        const_iterator it = from_data.begin();
        uint32_t const riff = read_to_int<uint32_t>(it);
        if(riff != CHAR_TO_INT32('R', 'I', 'F', 'F')){
            return false;
        }
        read_to_int<uint32_t>(it);
        uint32_t const wave = read_to_int<uint32_t>(it);
        if(wave != CHAR_TO_INT32('W', 'A', 'V', 'E')){
            return false;
        }
        
        char buffer[0xFFFF];
        const_iterator end = from_data.end();
        while(it != end){
            uint32_t const chank_type = read_to_int<uint32_t>(it);
            uint32_t const chank_size = read_to_int<uint32_t>(it);
 
             switch(chank_type){
                case CHAR_TO_INT32('f', 'm', 't', ' '):{
                    chank.id             = read_to_int<uint16_t>(it);
                    chank.channel        = read_to_int<uint16_t>(it);
                    chank.sample_rate    = read_to_int<uint32_t>(it);
                    chank.byte_per_sec   = read_to_int<uint32_t>(it);
                    chank.block_size     = read_to_int<uint16_t>(it);
                    chank.bit_per_sample = read_to_int<uint16_t>(it);
                    if(chank_size > sizeof(chank)){
                        std::copy(it, it + (chank_size - sizeof(chank)), buffer);
                    }
                } break;
                case CHAR_TO_INT32('d', 'a', 't', 'a'):{
                    data.reserve(chank_size);
                    uint32_t count = 0;
                    while(count < chank_size){
                        std::copy(it, it + sizeof(buffer), buffer);
                        data.insert(data.end(), buffer, buffer + sizeof(buffer));
                        count += sizeof(buffer);
                    }
                } break;
                default:{
                    uint32_t count = 0;
                    uint32_t const read_bytes = (sizeof(buffer) < chank_size) ? sizeof(buffer) : chank_size;
                    while(count < chank_size){
                        std::copy(it, it + read_bytes, buffer);
                        count += read_bytes;
                    }
                } break;
             }
        }
        return true;
    }


private:
    //! @brief ポインタからIntへの変換
    template<class Int>
    static Int to_int(void* data){
        return *static_cast<Int*>(data);
    }

    //! @brief ファイルからIntサイズ分のデータを読み取る
    template<class Int>
    static Int read_to_int(std::FILE* fp){
        char data[sizeof(Int)];
        fread(data, sizeof(Int), 1, fp);
        return to_int<Int>(data);
    }

    template<class Int, class Iter>
    static Int read_to_int(Iter it){
        char data[sizeof(Int)];
        std::copy(it, it + 4, data);
        return to_int<Int>(data);
    }


    static bool fail_close(std::FILE* fp){
        std::fclose(fp);
        return false;
    }
};

#undef CHAR_TO_INT32

typedef sound_resource<wave_format> wave_resource;

//! @brief waveフォーマットのファイルをロードする
inline wave_resource* load_wave_resource(char const* filename){
    wave_resource* resource = new wave_resource;
    if(!resource->load(filename)){
        delete resource;
        return NULL;
    }
    return resource;
}

//! @brief waveフォーマットのファイルをロードする
inline wave_resource* load_wave_resource(std::string const& filename){
    return load_wave_resource(filename.c_str());
}

__NOGARA_END

#endif
