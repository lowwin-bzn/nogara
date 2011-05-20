#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

/////////////////////////////////////////
//! @file  nogara/sound/sound_manager.hpp
//! @brief 音楽データを管理するクラス
/////////////////////////////////////////

#include <map>
#include <vector>
#include <nogara/sound/sound_buffer.hpp>

__NOGARA_BEGIN

//! 音声データのグループを複数管理するクラス
class sound_manager{    
    static uint_t const DEFAULT_SE_COUNT = 64;
    typedef smart_ptr::shared_ptr<sound_buffer_base>       buffer_ptr;
    typedef smart_ptr::shared_ptr<sound_buffer_base const> const_buffer_ptr;
    typedef smart_ptr::shared_ptr<source_binder>           binder_ptr;
    typedef std::map<int, buffer_ptr>                      buffer_map;

public:
    //! @brief コンストラクタ
    sound_manager():max_se_count(DEFAULT_SE_COUNT),
                  se_sources(),
                  current_source(se_sources.begin()), initialize(false){}
    //! @brief デストラクタ
    ~sound_manager(){
        if(initialize){
            delete_se_sources();
        }
        if(alIsSource(bgm_source)){
            alDeleteSources(1, &bgm_source);
        }
    }
    //! @brief  BGMの追加
    void addBGM(int id, buffer_ptr buf){
        if(buf){bgms[id] = buf;}
    }
    //! @brief  SEの追加
    void addSE(int id, buffer_ptr buf){
        if(buf){ses[id] = buf;}
    }
    //! @brief  BGMの追加
    void addBGM(int id, sound_buffer_base* buf){
        if(buf){bgms[id] = buffer_ptr(buf);}
    }
    //! @brief  SEの追加
    void addSE(int id, sound_buffer_base* buf){
        if(buf){ses[id] = buffer_ptr(buf);}
    }

    //! @brief  idに対応するBGMの再生
    void playBGM(int id, float value = 1.0f, bool loop = false){
        stopBGM();
        alGenSources(1, &bgm_source);
        current_bgm.reset(new source_binder(bgm_source, *BGM(id)));
        current_bgm->play(value, loop);
    }

    //! @brief 現在再生中の曲の更新
    void updateBGM(){
        if(current_bgm){current_bgm->update();}
    }

    //! @brief 現在再生中の曲の停止
    void stopBGM(){
        if(current_bgm && alIsSource(bgm_source)){
            current_bgm->stop();
            current_bgm.reset();
            alDeleteSources(1, &bgm_source);
        }
    }

    //! @brief 現在曲を再生中か
    bool is_playing(){return static_cast<bool>(current_bgm);}

    void playSE(int id, float value = 1.0f){
        if(!initialize){
            initialize_se_sources();
        }
        source_binder(*current_source, *SE(id)).play(value);
        ++current_source;
        if(current_source == se_sources.end()){
            current_source = se_sources.begin();
        }
    }

    //! @brief SEのソースの最大数を設定
    void max_SE_count(int max){
        max_se_count = max;
        initialize = false;
    }
    //! @brief SEのソースの最大数
    int  max_SE_count() const {return max_se_count;}

    //! @brief  SEバッファの取得
    //! @return idに対応したSEバッファがあれば共有ポインタを、なければnullを返す
    const_buffer_ptr SE(int id)  const {
        buffer_map::const_iterator find = ses.find(id);
        return (find == ses.end()) ? const_buffer_ptr() : const_buffer_ptr(find->second);
    }
    //! @brief  SEバッファの取得
    //! @return idに対応したSEバッファがあれば共有ポインタを、なければnullを返す
    buffer_ptr SE(int id){
        buffer_map::iterator find = ses.find(id);
        return (find == ses.end()) ? buffer_ptr() : find->second;
    }

    //! @brief  BGMバッファの取得
    //! @return idに対応したBGMバッファがあれば共有ポインタを、なければnullを返す
    const_buffer_ptr BGM(int id) const {
        buffer_map::const_iterator find = bgms.find(id);
        return (find == bgms.end()) ? const_buffer_ptr() : const_buffer_ptr(find->second);
    }

    //! @brief  BGMバッファの取得
    //! @return idに対応したBGMバッファがあれば共有ポインタを、なければnullを返す
    buffer_ptr BGM(int id) {
        buffer_map::const_iterator find = bgms.find(id);
        return (find == bgms.end()) ? buffer_ptr() : find->second;
    }

private:
    //! @brief SEに使用している音源の解放
    void delete_se_sources(){
        alDeleteSources(se_sources.size(), &se_sources[0]);
    }
    
    //! @brief SEに使用する音源の取得
    void initialize_se_sources(){
        if(current_source != se_sources.end()){
            delete_se_sources();
        }
        se_sources.resize(max_SE_count());
        alGenSources(max_SE_count(), &se_sources[0]);
        current_source = se_sources.begin();
        initialize = true;
    }
private:
    buffer_map bgms;
    buffer_map ses;

    int max_se_count;
    std::vector<ALuint>           se_sources;
    std::vector<ALuint>::iterator current_source;
    ALuint     bgm_source;
    binder_ptr current_bgm;
    bool initialize;
};

__NOGARA_END

#endif
