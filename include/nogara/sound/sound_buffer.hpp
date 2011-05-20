#ifndef NOGARA_SOUND_BUFFER_HPP
#define NOGARA_SOUND_BUFFER_HPP

///////////////////////////////////////////
//! @file  nogara/sound/sound_buffer.hpp
//! @brief OpenALのバッファ管理オブジェクト
///////////////////////////////////////////

#include <utility>
#include <OpenAL/al.h>
#include <nogara/nogara_define.hpp>
#include <nogara/typedef.hpp>
#include <nogara/smart_ptr.hpp>

__NOGARA_BEGIN

class sound_buffer_base{
public:
    sound_buffer_base():vol(1.0), loop_offset_(0){alGenBuffers(1, &buf);}
    virtual ~sound_buffer_base(){alDeleteBuffers(1, &buf);}

    //! @biref 音楽の再生
    virtual void play(ALuint source, float value = 1.0f, bool loop = false) = 0;
    //! @biref 音楽の停止
    virtual void stop(ALuint source) = 0;
    //! @biref 音楽の一時停止切り替え
    virtual void toggle_pause(ALuint source) = 0;
    //! @biref 一時停止しているか
    virtual bool is_pausing(ALuint source) const = 0;
    //! @biref 停止しているか
    virtual bool is_stopped(ALuint source) const = 0;
    //! @brief ストリーム再生時などに使用する
    virtual void update(ALuint /*source*/){}
    //! @brief ストリーム再生型か否か
    virtual bool is_stream() const {return false;}
    //! @brief ストリーム再生が終了したか否か
    virtual bool is_stream_end() const {return false;}
    //! @brief OpenALのバッファID
    ALuint buffer() const {return buf;}
    //! @brief 音量調整
    void   volume(float v)   {vol = v;}
    //! @brief 音量の取得
    float  volume()    const {return vol;}
    //! @brief ループするか否か
    ALboolean loopable() const {return loop;}
    //! @brief ループフラグを立てる
    void  set_loop_flag(bool b){loop = b ? AL_TRUE : AL_FALSE;}
    //! @biref ループの先頭位置の設定
    void loop_offset(uint32_t value){loop_offset_ = value;}
    //! @biref ループの先頭位置
    uint32_t loop_offset() const {return loop_offset_;}
protected:
    ALuint    buf;
    float     vol;
    uint32_t  loop_offset_;
    ALboolean loop;
};

template<class Resource>
class sound_buffer : public sound_buffer_base{
    typedef typename smart_ptr::shared_ptr<Resource> resource_ptr;
public:
    explicit sound_buffer(resource_ptr r):
        sound_buffer_base(), resource(r),
        buffer_pos(0, r ? r->data_size() : 0),
        binding(false){}
    explicit sound_buffer(Resource* r):
        sound_buffer_base(), resource(r),
        buffer_pos(0, (r != NULL) ? r->data_size() : 0),
        binding(false){}

    sound_buffer(resource_ptr r, float head, float tail):
        sound_buffer_base(), resource(r), binding(false)
    {
        buffer_range(head, tail);
    }

    //! @biref 音楽の再生
    void play(ALuint source, float value = 1.0f, bool loop = false){
        if(!binding){
            bind();
        }
        volume(value); set_loop_flag(loop);
        alSourcei(source, AL_BUFFER,  buffer());
        alSourcei(source, AL_LOOPING, loopable());
        alSourcef(source, AL_GAIN, volume());
        alSourcePlay(source);
    }

    //! @biref 音楽の停止
    void stop(ALuint source){
        alSourceStop(source);
    }

    //! @biref 一時停止切り替え
    void toggle_pause(ALuint source){
        if(is_pausing(source)){
            alSourcePlay(source);
        }else{
            alSourcePause(source);
        }
    }

    //! @biref 一時停止中か
    bool is_pausing(ALuint source) const{
        ALint state;
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        return state == AL_PAUSED;
    }

    //! @biref 停止中か
    bool is_stopped(ALuint source) const{
        ALint state;
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        return state == AL_STOPPED;
    }

    //! @biref データバッファの先頭位置の設定
    void buffer_head(float value){
        buffer_pos.first = get_position(value);
    }
    //! @biref データバッファの先頭位置
    uint32_t buffer_head() const {return buffer_pos.first;}

    //! @biref データバッファの末尾位置の設定
    void buffer_tail(float value){
        buffer_pos.second = get_position(value);
    }
    //! @biref データバッファの末尾位置
    uint32_t buffer_tail() const {return buffer_pos.second;}

    //! @biref データバッファの範囲設定
    void buffer_range(float head, float tail){
        buffer_head(head); buffer_tail(tail);
    }

private:
    //! @biref value秒移動したときの再生位置を返す
    uint32_t get_position(float value){
        if(value <= 0.0f){
            return 0;
        }

        uint32_t result = value * resource->byte_per_sec();
        return (result > resource->data_size()) ? resource->data_size() : result;
    }
    //! @biref OpenALのフォーマットを返す
    ALenum get_al_format(uint32_t channel, uint32_t bits){
        ALenum const format[2][2] = {
            {AL_FORMAT_MONO8,   AL_FORMAT_MONO16},
            {AL_FORMAT_STEREO8, AL_FORMAT_STEREO16},
        };
        return format[channel == 1 ? 0 : 1][bits == 8 ? 0 : 1];
    }

    //! @brief バッファの割り当て
    void bind(){
        alBufferData(buffer(), get_al_format(resource->channel(), resource->bits()),
                     resource->data_front() + buffer_head(), buffer_tail(), resource->sample_rate());
        binding = true;
    }

private:
    resource_ptr                  resource;
    std::pair<uint32_t, uint32_t> buffer_pos;
    bool binding;
};


//! @brief バッファに音源情報を割り当てる
struct source_binder{
    source_binder(ALuint s, sound_buffer_base& b):source(s), buffer(b){}
    //! @brief 音楽の再生
    void play(float volume = 1.0f, bool loop = false){
        buffer.play(source, volume, loop);
    }

    //! @brief 音楽の停止
    void stop(){
        buffer.stop(source);
    }

    //! @brief 一時停止切り替え
    void toggle_pause(){
        buffer.toggle_pause(source);
    }

    //! @brief 一時停止中か
    bool is_pausing() const {
        return buffer.is_pausing(source);
    }

    //! @brief 停止中か
    bool is_stopped() const {
        return buffer.is_stopped(source);
    }

    //! @brief サウンドの更新
    void update(){
        buffer.update(source);
    }
    
    ALuint source;
    sound_buffer_base& buffer;
};

__NOGARA_END

#endif
