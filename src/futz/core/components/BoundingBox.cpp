#include "../../Futz.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox(){
    name = "BoundingBox";
    draw = true;
}

void BoundingBox::Start(){
	Futz::Log("BoundingBox Start");
    width = 3;

    // top right
    lv1.x = lv1.y = width;
    // bottom right
    lv2.x = width; lv2.y = -width;
    // top left
    lv3.x = -width; lv3.y = width;
    // bottom left
    lv4.x = lv4.y = -width;

    // top right
    lv5.x = lv5.y = width; lv5.z = width;
    // bottom right
    lv6.x = width; lv6.y = -width; lv6.z = width;
    // top left
    lv7.x = -width; lv7.y = width; lv7.z = width;
    // bottom left
    lv8.x = lv8.y = -width; lv8.z = width;
}

void BoundingBox::ReadModel(Model* m){
    model = m;
    float maxX = NULL;
    float minX = NULL;
    float maxY = NULL;
    float minY = NULL;
    float maxZ = NULL;
    float minZ = NULL;

    Matrix4 mat = Matrix4();
    Vector3 tv;
	for (int i = 0; i < m->triangles.size()*9; i+=3) {


        mat.SetIdentity();
        mat.SetTranslation(m->vertexArray[i], m->vertexArray[i+1], m->vertexArray[i+2]);
        mat = mat * ((Node*)node)->transform.matrix;


        tv.x = mat.values[12];
        tv.y = mat.values[13];
        tv.z = mat.values[14];

        tv.x = m->vertexArray[i];
        tv.y = m->vertexArray[i+1];
        tv.z = m->vertexArray[i+2];

        //printf("%d tv.y %f\n",i, tv.y);
        if(maxX == NULL || maxX < tv.x){
            maxX = tv.x;
            extremeIndices[0] = i;
        }

        if(minX == NULL || minX > tv.x){
            minX = tv.x;
            extremeIndices[1] = i;
        }

        if(maxY == NULL || maxY < tv.y){
            maxY = tv.y;
            extremeIndices[2] = i+1;
        }

        if(minY == NULL || minY > tv.y){
            minY = tv.y;
            extremeIndices[3] = i+1;
        }

        if(maxZ == NULL || maxZ < tv.z){
            maxZ = tv.z;
            extremeIndices[4] = i+2;
        }

        if(minZ == NULL || minZ > tv.z){
            minZ = tv.z;
            extremeIndices[5] = i+2;
        }

    }

    lv1.x = minX;
    lv1.y = maxY;
    lv1.z = maxZ;

    lv2.x = maxX;
    lv2.y = maxY;
    lv2.z = maxZ;

    lv3.x = maxX;
    lv3.y = minY;
    lv3.z = maxZ;

    lv4.x = minX;
    lv4.y = minY;
    lv4.z = maxZ;

    lv5.x = minX;
    lv5.y = maxY;
    lv5.z = minZ;

    lv6.x = maxX;
    lv6.y = maxY;
    lv6.z = minZ;

    lv7.x = maxX;
    lv7.y = minY;
    lv7.z = minZ;

    lv8.x = minX;
    lv8.y = minY;
    lv8.z = minZ;
    
}

void BoundingBox::Update(){
//    SetLocalVerticesFromExtremes();
//    ReadModel(model);

	
    v1 = lv1.Transform(((Node*)node)->transform.matrix);
    v2 = lv2.Transform(((Node*)node)->transform.matrix);
    v3 = lv3.Transform(((Node*)node)->transform.matrix);
    v4 = lv4.Transform(((Node*)node)->transform.matrix);
    v5 = lv5.Transform(((Node*)node)->transform.matrix);
    v6 = lv6.Transform(((Node*)node)->transform.matrix);
    v7 = lv7.Transform(((Node*)node)->transform.matrix);
    v8 = lv8.Transform(((Node*)node)->transform.matrix);
	

}

void BoundingBox::Draw(){
    if(draw){

        Futz::Instance()->renderer->DrawLine(v1, v2);
        Futz::Instance()->renderer->DrawLine(v2, v3);
        Futz::Instance()->renderer->DrawLine(v3, v4);
        Futz::Instance()->renderer->DrawLine(v4, v1);

        Futz::Instance()->renderer->DrawLine(v1, v5);
        Futz::Instance()->renderer->DrawLine(v2, v6);
        Futz::Instance()->renderer->DrawLine(v3, v7);
        Futz::Instance()->renderer->DrawLine(v4, v8);

        Futz::Instance()->renderer->DrawLine(v5, v6);
        Futz::Instance()->renderer->DrawLine(v6, v7);
        Futz::Instance()->renderer->DrawLine(v7, v8);
        Futz::Instance()->renderer->DrawLine(v8, v5);
    }

}
