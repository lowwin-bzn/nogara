#ifndef MODEL_CONTAINAER_HPP
#define MODEL_CONTAINAER_HPP

/////////////////////////////////////////////
//! @file  nogara/model/model_manager.hpp
//! @brief モデル、バッファの管理
/////////////////////////////////////////////

#include <map>
#include <nogara/model/model.hpp>
#include <nogara/typedef.hpp>
#include <boost/optional.hpp>

__NOGARA_BEGIN

/////////////////////////////////////////////
//! @brief モデル、バッファの管理を行うクラス
/////////////////////////////////////////////
class model_manager{
    typedef std::map<uint_t, nogara::mesh_buffer> buffer_map;
public:
    //! @brief バッファを登録する
    void set_buffer(uint_t id, nogara::mesh_buffer const& buffer){
        map.insert(std::make_pair(id, buffer));
    }

    ///////////////////////////////////////////////////////////
    //! @brief 登録したバッファを取得する
    //! @return  登録したバッファを、存在しなければnone_tを返す
    ///////////////////////////////////////////////////////////
    boost::optional<nogara::mesh_buffer> get_buffer(uint_t id){
        buffer_map::iterator it = map.find(id);
        if(it == map.end()){
            return boost::none;
        }
        return it->second;
    }

    //! @brief  登録したバッファからモデルを生成し返す
    //! @return 生成されたモデルの共有ポインタを、存在しなければ空ポインタを返す
    nogara::model::shared_ptr generate_model(uint_t id){
        if(boost::optional<nogara::mesh_buffer> buffer = get_buffer(id)){
            return nogara::make_model(nogara::make_mesh(*buffer));
        }
        return nogara::model::shared_ptr();
    }
private:
    buffer_map map;
};

__NOGARA_END

#endif
