#ifndef NOGARA_AL_DEVICE_MANAGER_HPP
#define NOGARA_AL_DEVICE_MANAGER_HPP

/////////////////////////////////////////////////////////
//! @file  nogara/sound/al_device_manager.hpp
//! @brief OpenALのデバイスデータの初期化、解放を担当する
/////////////////////////////////////////////////////////

#include <OpenAL/alc.h>
#include <nogara/nogara_define.hpp>

__NOGARA_BEGIN

///////////////////////////////////////////////////////////
//! @brief OpenALのデバイスデータの初期化、解放を担当する
//!        al_device_manager::instance()を呼び出し時点から
//!        destroy関数呼出までの間、デバイス管理をする
///////////////////////////////////////////////////////////
class al_device_manager{
public:
    static void open(){
        instance();
    }
    
    static al_device_manager& instance(){
        static al_device_manager inst;
        return inst;
    }

    void destroy(){
        alcMakeContextCurrent(NULL);
        alcDestroyContext(main_context);
        alcCloseDevice(device);
    }

    ALCdevice* get_device(){
        return device;
    }

private:
    al_device_manager(){
        device = alcOpenDevice(NULL);
        main_context = alcCreateContext(device, NULL);
        alcMakeContextCurrent(main_context);
    }

    ~al_device_manager(){destroy();}

    al_device_manager(al_device_manager const&);
    al_device_manager& operator=(al_device_manager const&);

private:
    ALCdevice*  device;
    ALCcontext* main_context;
};

__NOGARA_END

#endif
