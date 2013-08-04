#ifndef BOX_H_

/*
 * 0 1
 * 2 3
 *
 * 4 5
 * 6 7
 *
 * */
class Box {
    public:
    float corners[24];
    
    bool PointIsInside(Vector3 v1){
        bool x = false;
        bool y = false;
        bool z = false;

        bool greaterThanAll = true;
        bool lessThanAll = true;

        for(int i = 0; i < 24; i+=3){
            if(v1.x <= corners[i]){
                greaterThanAll = false;
            }
            if(v1.x >= corners[i]){
                lessThanAll = false;
            }
            if(!greaterThanAll && !lessThanAll){
                x = true;
            }
        }

        greaterThanAll = true;
        lessThanAll = true;
        for(int i = 0; i < 24; i+=3){
            if(v1.y <= corners[i+1]){
                greaterThanAll = false;
            }
            if(v1.y >= corners[i+1]){
                lessThanAll = false;
            }
            if(!greaterThanAll && !lessThanAll){
                y = true;
            }
        }

        greaterThanAll = true;
        lessThanAll = true;
        for(int i = 0; i < 24; i+=3){
            if(v1.z <= corners[i+2]){
                greaterThanAll = false;
            }
            if(v1.z >= corners[i+2]){
                lessThanAll = false;
            }
            if(!greaterThanAll && !lessThanAll){
                z = true;
            }
        }

        return x && y && z;
    }

    Vector3 GetVector3(int index){
        Vector3 v1;
        v1.x = corners[index * 3];
        v1.y = corners[index * 3 + 1];
        v1.z = corners[index * 3 + 2];
        return v1;
    }

    void Transform(Matrix4 m){
        for(int i = 0; i < 8; i++){
            Vector3 tv = GetVector3(i).Transform(m);
            corners[i * 3] = tv.x;
            corners[i * 3+1] = tv.y;
            corners[i * 3+2] = tv.z;
        }

    }

    void Set(Vector3 v){
        corners[0] = -v.x/2; 
        corners[1] = v.y/2; 
        corners[2] = v.z/2; 

        corners[3] = v.x/2; 
        corners[4] = v.y/2; 
        corners[5] = v.z/2; 

        corners[6] = -v.x/2; 
        corners[7] = -v.y/2; 
        corners[8] = v.z/2; 

        corners[9] = v.x/2; 
        corners[10] = -v.y/2; 
        corners[11] = v.z/2; 

        corners[12] = -v.x/2; 
        corners[13] = v.y/2; 
        corners[14] = -v.z/2; 

        corners[15] = v.x/2; 
        corners[16] = v.y/2; 
        corners[17] = -v.z/2; 

        corners[18] = -v.x/2; 
        corners[19] = -v.y/2; 
        corners[20] = -v.z/2; 

        corners[21] = v.x/2; 
        corners[22] = -v.y/2; 
        corners[23] = -v.z/2; 
    }

};

#endif
