#include "ModelValue.hpp"
//#include "Star"

ModelValue::ModelValue()
{

}
Matrix *ModelValue::getDRA_Decl_dR()
{
    return &dRA_Decl_dR;
}

std::vector<double> ModelValue::getCortesian_pos() const
{
    return cortesian_pos;
}

std::vector<double> ModelValue::getSpeed() const
{
    return speed;
}

void ModelValue::setRA(double newRA)
{
    RA = newRA;
}

void ModelValue::setDecl(double newDecl)
{
    Decl = newDecl;
}

void ModelValue::setDR_dB(const Matrix &newDR_dB)
{
    dR_dB = newDR_dB;
}

void ModelValue::VectorError(vector<vector<pair<double,double>>> &error){
//    error.clear();
//    error.resize(3);
//    error[0].resize(s2.getSpherical_history_obs().size());
//    error[1].resize(s38.getSpherical_history_obs().size());
//    error[3].resize(s55.getSpherical_history_obs().size());
//    for(int i=0;i<this->s2.getSpherical_history_obs().size();i++){
//        int step = round(s2.getSpherical_history_obs()[i].first*365);
//        error[0][i]={s2.getSpherical_history_obs()[i].second.first-s2.getSpherical_history_model()[step].first,
//                       s2.getSpherical_history_obs()[i].second.second-s2.getSpherical_history_model()[step].second};
//    }
//    for(int i=0;i<this->s38.getSpherical_history_obs().size();i++){
//        int step = round(s38.getSpherical_history_obs()[i].first*365);
//        error[1][i]={s38.getSpherical_history_obs()[i].second.first-s38.getSpherical_history_model()[step].first,
//                       s38.getSpherical_history_obs()[i].second.second-s38.getSpherical_history_model()[step].second};
//    }
//    for(int i=0;i<this->s55.getSpherical_history_obs().size();i++){
//        int step = round(s55.getSpherical_history_obs()[i].first*365);
//        error[2][i]={s55.getSpherical_history_obs()[i].second.first-s55.getSpherical_history_model()[step].first,
//                       s55.getSpherical_history_obs()[i].second.second-s55.getSpherical_history_model()[step].second};
//    }
}
