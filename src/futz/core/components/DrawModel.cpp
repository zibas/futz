#include "../../Futz.h"
#include "DrawModel.h"

DrawModel::DrawModel(){
    name = "DrawModel";
    transparent = false;
    model = NULL;
}

void DrawModel::Start(){
	//Futz::Log("DrawModel Start");

    if(model != NULL){
        map<string,Material>::iterator pair;
        for ( pair=model->materials.begin() ; pair != model->materials.end(); pair++ ){
            if((*pair).second.rgba[3] < 1){
                transparent = true;
                ((Node*)node)->transparent = true;
               // Futz::Log("DrawModel: transparent");
            }
        }
    } else {
        Futz::Log("DrawModel: missing model");
    }

}


void DrawModel::DrawLocal(){
	Futz::Instance()->renderer->DrawModel(model);
}
