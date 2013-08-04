#include "../../Futz.h"
#include "AxisAlignedBoundingBox.h"

AxisAlignedBoundingBox::AxisAlignedBoundingBox(){
    name = "AxisAlignedBoundingBox";
}

void AxisAlignedBoundingBox::Start(){
	Futz::Log("AxisAlignedBoundingBox Start");
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

void AxisAlignedBoundingBox::ReadModel(Model* m){
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

    
    SetLocalVerticesFromExtremes();
//    printf("Max: %f,%f\tMin: %f,%f\n",maxX, maxY, minX, minY);
}

void AxisAlignedBoundingBox::SetLocalVerticesFromExtremes(){

    float maxX = NULL;
    float minX = NULL;
    float maxY = NULL;
    float minY = NULL;
    float maxZ = NULL;
    float minZ = NULL;

    Matrix4 m = Matrix4();
    

    for(int i = 0; i < 6; i++){
        // Transformed vector
        Vector3 tv;
        tv.x = model->vertexArray[extremeIndices[i]];  
        tv.y = model->vertexArray[extremeIndices[i]+1];  
        tv.z = model->vertexArray[extremeIndices[i]+2];  

        m.SetIdentity();
        m.SetTranslation(tv.x, tv.y, tv.z);
        m = m * ((Node*)node)->transform.matrix;

        tv.x = m.values[12];
        tv.y = m.values[13];
        tv.z = m.values[14];


        if(maxX == NULL || maxX < tv.x){
            maxX = tv.x;
       // printf("Original x: %f, transformed: %f\n",model->vertexArray[extremeIndices[i]],tv.x);
        }
        if(minX == NULL || minX > tv.x){
            minX = tv.x;
        }

        if(maxY == NULL || maxY < tv.y){
            maxY = tv.y;
        }
        if(minY == NULL || minY > tv.y){
            minY = tv.y;
        }
        //printf("%d Original y: %f, transformed: %f\n",i, model->vertexArray[extremeIndices[i]+1],tv.y);

        if(maxZ == NULL || maxZ < tv.z){
            maxZ = tv.z;
        }
        if(minZ == NULL || minZ > tv.z){
            minZ = tv.z;
        }
    }

       // printf("======\n");
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

void AxisAlignedBoundingBox::Update(){
//    SetLocalVerticesFromExtremes();
    ReadModel(model);

}

void AxisAlignedBoundingBox::Draw(){

    Futz::Instance()->renderer->DrawLine(lv1, lv2);
    Futz::Instance()->renderer->DrawLine(lv2, lv3);
    Futz::Instance()->renderer->DrawLine(lv3, lv4);
    Futz::Instance()->renderer->DrawLine(lv4, lv1);

    Futz::Instance()->renderer->DrawLine(lv1, lv5);
    Futz::Instance()->renderer->DrawLine(lv2, lv6);
    Futz::Instance()->renderer->DrawLine(lv3, lv7);
    Futz::Instance()->renderer->DrawLine(lv4, lv8);

    Futz::Instance()->renderer->DrawLine(lv5, lv6);
    Futz::Instance()->renderer->DrawLine(lv6, lv7);
    Futz::Instance()->renderer->DrawLine(lv7, lv8);
    Futz::Instance()->renderer->DrawLine(lv8, lv5);


    /*
//    for(int i = 0; i < 6; i++){
    int i = 3;
    Vector3 blue;
    blue.x = 0;
    blue.y = 0;
    blue.z = 1;

    Vector3 v1;
    v1.x = model->vertexArray[extremeIndices[i]];
    v1.y = model->vertexArray[extremeIndices[i]+1];
    v1.z = model->vertexArray[extremeIndices[i]+2];

    Vector3 v2;

    Vector3 v3;
    v3.x = v1.x;
    v3.y = v1.y+0.2;
    v3.z = v1.z;

    Matrix4 m = Matrix4();
    m.SetIdentity();
    m.SetTranslation(v1.x, v1.y, v1.z);
    m = m * ((Node*)node)->transform.matrix;
    v2.x = m.values[12];
    v2.y = m.values[13];
    v2.z = m.values[14];

    Futz::Instance()->renderer->DrawLine(v1, v2, blue);
    blue.y = 1;
    Futz::Instance()->renderer->DrawLine(v1, v3, blue);
  //  }
    //printf("Extremes: %d,%d,%d,%d,%d,%d\n",extremeIndices[0],extremeIndices[1],extremeIndices[2],extremeIndices[3],extremeIndices[4],extremeIndices[5]);
    */
}
