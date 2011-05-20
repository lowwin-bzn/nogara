#ifndef NOGARA_OGG_STREAM_HPP
#define NOGARA_OGG_STREAM_HPP

//////////////////////////////////////////////////
//! @file  nogara/sound/ogg_stream.hpp
//! @brief Oggファイルのストリーム再生
//////////////////////////////////////////////////
#include <vorbis/vorbisfile.h>
#include <nogara/sound/sound_resource.hpp>
#include <nogara/file_cover.hpp>
#include <nogara/sound/al_device_manager.hpp>
#include <nogara/sound/sound_buffer.hpp>

__NOGARA_BEGIN

//////////////////////////////////////////////////
//! @brief Oggファイルのストリーム再生を行うクラス
//////////////////////////////////////////////////
class ogg_stream : public sound_buffer_base{
    //! @brief バッファの上限
    static int    const MAX_READ_SIZE = 4096;
    //! @brief キューの上限
    static ALint  const MAX_QUEUE_SIZE = 32;

    //! @brief OggVorbis_Fileオブジェクトの終了時の綴じ方
    struct ovf_releaser{
        void operator()(OggVorbis_File* ovf){
            ov_clear(ovf);
            delete ovf;
        }
    };

    typedef smart_ptr::shared_ptr<OggVorbis_File> ogg_pointer;

public:
    //! @brief コンストラクタ
    ogg_stream():ovf(new OggVorbis_File(), ovf_releaser()), stream_end(false){}

    //! @biref 音楽の再生
    void play(ALuint source, float value = 1.0f, bool loop = false){
        volume(value); set_loop_flag(loop);
        alSourcef(source, AL_GAIN, volume());
        update(source);
        alSourcePlay(source);
    }

    //! @biref 音楽の停止
    virtual void stop(ALuint source){
        ov_pcm_seek(ovf.get(), 0);
        stream_end = false;
        alSourceStop(source);
        alSourcei(source, AL_BUFFER, AL_NONE);
    }

    //! @biref 音楽の一時停止切り替え
    virtual void toggle_pause(ALuint source) {
        if(is_pausing(source)){
            update(source);
        }else{
            alSourcePause(source);
        }

    }
    //! @biref 一時停止しているか
    virtual bool is_pausing(ALuint source) const{
        ALint state;
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        return state == AL_PAUSED;
    }

    //! @biref 停止しているか
    virtual bool is_stopped(ALuint source) const {
        ALint state;
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        return state == AL_STOPPED;
    }

    //! @brief ストリームの更新
    void update(ALuint source){
        ALuint buffer;
        ALint state;
        ALint n;
        alGetSourcei(source, AL_BUFFERS_QUEUED, &n);

        if(n >= MAX_QUEUE_SIZE && !is_stream_end()){
            alGetSourcei(source, AL_SOURCE_STATE, &state);
            if(state != AL_PLAYING){
                alSourcePlay(source);
            }

            alGetSourcei(source, AL_BUFFERS_PROCESSED, &n);
            if(n == 0){
                return;
            }
            alSourceUnqueueBuffers(source, 1, &buffer);
        }else{
            alGenBuffers(1, &buffer);
        }

        char data[MAX_READ_SIZE];
        int stream = 0;
        int count = 0;
        int require = MAX_READ_SIZE;
        while(count < MAX_READ_SIZE){
            int read_size = ov_read(ovf.get(), &data[count], require, 0, 2, 1, &stream);
            if(read_size <= 0){
                if(loopable()){
                    ov_pcm_seek(ovf.get(), loop_offset());
                }else{
                    stream_end = true;
                }
                return;
            }
            count += read_size;
            require = MAX_READ_SIZE - count;
        }

        alBufferData(buffer, al_format, data, count, chank.sample_rate);
        alSourceQueueBuffers(source, 1, &buffer);
    }

    //! @brief ストリーム再生するクラスか
    bool is_stream() const {return true;}
    //! @brief ストリーム再生が終了したか
    bool is_stream_end() const {return stream_end;}

    //! @brief PCMフォーマットの取得
    format_chank const& format() const {return chank;}

    using sound_buffer_base::loop_offset;
    //! @brief ループ先頭の設定
    void loop_offset(float value){sound_buffer_base::loop_offset(get_position(value));}


    //! @brief ファイルを割り当て、PCM情報を取得する
    static ogg_stream* load(char const* filename){
        file_ptr fp(make_file_ptr(filename, "rb"));
        if(!fp){
            return NULL;
        }
        
        std::auto_ptr<ogg_stream> ogg(new ogg_stream);

        if(ov_open(fp.get(), ogg->ovf.get(), NULL, 0)){
            return NULL;
        }
        fp.release();

        vorbis_info const* info = ov_info(ogg->ovf.get(), -1);
        if(!info){
            return NULL;
        }

        ogg->chank.id = format_chank::LINEAR_PCM_FORMAT;
        ogg->chank.channel = info->channels;
        ogg->chank.sample_rate = info->rate;
        ogg->chank.block_size = ogg->chank.channel * 2;
        ogg->chank.byte_per_sec = ogg->chank.sample_rate * ogg->chank.block_size;
        ogg->chank.bit_per_sample = 16;
        ogg->al_format = ogg->chank.channel == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
        return ogg.release();
    }

    //! @brief ファイルを割り当て、PCM情報を取得する
    static ogg_stream* load(std::string const& filename){
        return load(filename.c_str());
    }

private:
    //! @biref value秒移動したときの再生位置を返す
    uint32_t get_position(float value){
        return (value <= 0.0f) ? 0 : value * chank.byte_per_sec;
    }

private:
    ogg_pointer ovf;
    format_chank chank;
    int current_size;
    ALenum al_format;
    bool stream_end;
};

smart_ptr::shared_ptr<ogg_stream> load_ogg_stream(char const* filename){
    return smart_ptr::shared_ptr<ogg_stream>(ogg_stream::load(filename));
}

smart_ptr::shared_ptr<ogg_stream> load_ogg_stream(std::string const& filename){
    return smart_ptr::shared_ptr<ogg_stream>(ogg_stream::load(filename));
}


__NOGARA_END

#endif
